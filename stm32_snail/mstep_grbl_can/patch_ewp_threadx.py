#!/usr/bin/env python3
"""Generate mstep_grbl_can_threadx.ewp — ThreadX only, no FreeRTOS kernel."""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
EWP = ROOT / "mstep_grbl_can.ewp"
EWT = ROOT / "mstep_grbl_can.ewt"
OUT_EWP = ROOT / "mstep_grbl_can_threadx.ewp"
OUT_EWT = ROOT / "mstep_grbl_can_threadx.ewt"
AZRTOS = ROOT.parent / "common" / "azure_rtos"

THREADX_PORT = AZRTOS / "threadx" / "ports" / "cortex_m3" / "iar"
THREADX_COMMON = AZRTOS / "threadx" / "common" / "src"

INCLUDE_PATHS = [
    "$PROJ_DIR$\\.",
    "$PROJ_DIR$\\src\\board",
    "$PROJ_DIR$\\src\\inc",
    "$PROJ_DIR$\\azure_port",
    "$PROJ_DIR$\\..\\common\\dbg",
    "$PROJ_DIR$\\..\\common\\can",
    "$PROJ_DIR$\\..\\common_stm32\\libraries\\STM32F2xx_StdPeriph_Driver\\inc",
    "$PROJ_DIR$\\..\\common_stm32\\libraries\\STM32F2xx_StdPeriph_Driver",
    "$PROJ_DIR$\\..\\common_stm32\\usb\\cdc_vcp",
    "$PROJ_DIR$\\..\\common_stm32\\usb\\drv\\inc",
    "$PROJ_DIR$\\..\\common_stm32\\usb\\core\\inc",
    "$PROJ_DIR$\\..\\common_stm32\\usb\\inc",
    "$PROJ_DIR$\\..\\common_stm32\\grbl",
    "$PROJ_DIR$\\..\\common_stm32\\i2c",
    "$PROJ_DIR$\\..\\common\\azure_rtos\\threadx\\common\\inc",
    "$PROJ_DIR$\\..\\common\\azure_rtos\\threadx\\ports\\cortex_m3\\iar\\inc",
]

DEFINES_ADD = ["USE_THREADX", "TX_INCLUDE_USER_DEFINE_FILE", "USE_USB_OTG_FS", "USB_GRBL_CAN"]

MAIN_EXCLUDED = """        <file>
            <name>$PROJ_DIR$\\src\\main.c</name>
            <excluded>
                <configuration>Debug</configuration>
                <configuration>mstep_gbrl_can_dbg</configuration>
            </excluded>
        </file>"""


def collect_threadx_sources():
    files = [
        ROOT / "azure_port" / "tx_initialize_low_level.s",
        ROOT / "azure_port" / "rtos_compat.c",
        ROOT / "azure_port" / "tx_application.c",
        THREADX_PORT / "src" / "tx_iar.c",
    ]
    files.extend(sorted(THREADX_COMMON.glob("*.c")))
    for p in sorted(THREADX_PORT.glob("src/*.s")):
        if p.name != "tx_misra.s":
            files.append(p)
    return files


def strip_freertos(text: str) -> str:
    text = re.sub(r"    <group>\s*<name>FreeRTOS</name>.*?</group>\s*", "", text, flags=re.DOTALL)
    lines = []
    for line in text.splitlines(keepends=True):
        low = line.lower()
        if "<state>" in line and "freertos" in low:
            continue
        lines.append(line)
    return "".join(lines)


def normalize_include_paths(text: str) -> str:
    def replacer(_match):
        block = "                <option>\n                    <name>CCIncludePath2</name>\n"
        for p in INCLUDE_PATHS:
            block += f"                    <state>{p}</state>\n"
        block += "                </option>"
        return block

    return re.sub(
        r"                <option>\s*<name>CCIncludePath2</name>.*?</option>",
        replacer,
        text,
        flags=re.DOTALL,
    )


def normalize_defines(text: str) -> str:
    def replacer(match):
        block = match.group(0)
        for d in DEFINES_ADD:
            if f"<state>{d}</state>" not in block:
                block = block.replace(
                    "<state>USEUSB</state>",
                    f"<state>USEUSB</state>\n                    <state>{d}</state>",
                    1,
                )
        return block

    return re.sub(
        r"                <option>\s*<name>CCDefines</name>.*?</option>",
        replacer,
        text,
        flags=re.DOTALL,
    )


def normalize_assembler_defines(text: str) -> str:
    asm_defines = "USE_THREADX"

    def replacer(match):
        block = match.group(0)
        if f"<state>{asm_defines}</state>" in block:
            return block
        if "<state></state>" in block:
            return block.replace("<state></state>", f"<state>{asm_defines}</state>", 1)
        return block + f"                    <state>{asm_defines}</state>\n"

    return re.sub(
        r"                <option>\s*<name>ADefines</name>.*?</option>",
        replacer,
        text,
        flags=re.DOTALL,
    )


def strip_i2c_debug_exclusion(text: str) -> str:
    return re.sub(
        r"(<name>\$PROJ_DIR\$\\\.\\.\\common_stm32\\i2c\\i2c\.(?:c|h)</name>\s*)"
        r"<excluded>\s*<configuration>Debug</configuration>\s*</excluded>\s*",
        r"\1",
        text,
        flags=re.DOTALL,
    )


def normalize_linker_config(text: str) -> str:
    return text.replace(
        "$PROJ_DIR$\\mstep_rtos.icf",
        "$PROJ_DIR$\\mstep_threadx.icf",
    )


def patch_ewp(text: str) -> str:
    text = text.replace("$PROJ_DIR$\\..\\..\\common\\", "$PROJ_DIR$\\..\\common\\")
    text = strip_freertos(text)
    text = strip_i2c_debug_exclusion(text)
    text = normalize_include_paths(text)
    text = normalize_defines(text)
    text = normalize_assembler_defines(text)
    text = normalize_linker_config(text)

    for remove in ["USE_USBX", "USE_HAL_DRIVER", "UX_INCLUDE_USER_DEFINE_FILE", "STM32F205xx"]:
        text = text.replace(f"                    <state>{remove}</state>\n", "")

    text = re.sub(r"    <group>\s*<name>ThreadX</name>.*?</group>\s*", "", text, flags=re.DOTALL)

    if "            <name>$PROJ_DIR$\\src\\main.c</name>\n        </file>" in text:
        text = text.replace(
            "        <file>\n            <name>$PROJ_DIR$\\src\\main.c</name>\n        </file>",
            MAIN_EXCLUDED,
            1,
        )

    group = build_threadx_group(collect_threadx_sources())
    text = text.replace("</project>", group + "</project>")
    return text


def build_threadx_group(files):
    lines = ["    <group>\n", "        <name>ThreadX</name>\n"]
    for f in files:
        rel = f.relative_to(ROOT.parent)
        lines.append("        <file>\n")
        lines.append(f"            <name>$PROJ_DIR$\\..\\{rel.as_posix().replace('/', chr(92))}</name>\n")
        lines.append("        </file>\n")
    lines.append("    </group>\n")
    return "".join(lines)


def main():
    if not EWP.exists():
        print(f"Missing {EWP}")
        return 1

    out = patch_ewp(EWP.read_text(encoding="utf-8"))
    OUT_EWP.write_text(out, encoding="utf-8")
    print(f"Wrote {OUT_EWP}")

    if EWT.exists():
        ewt = strip_freertos(EWT.read_text(encoding="utf-8"))
        ewt = re.sub(r"freertos_compat\.c", "rtos_compat.c", ewt)
        OUT_EWT.write_text(ewt, encoding="utf-8")
        print(f"Wrote {OUT_EWT}")

    print("ThreadX only: no FreeRTOS kernel sources. azure_port/FreeRTOS.h is a legacy shim.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
