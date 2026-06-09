import re
from pathlib import Path

ewp = Path(__file__).resolve().parents[1] / "app_step_axis_dima.ewp"
mstep = Path(__file__).resolve().parents[1].parent / "mstep_grbl_can" / "mstep_grbl_can_threadx.ewp"

content = ewp.read_text(encoding="utf-8", errors="replace")
mstep_text = mstep.read_text(encoding="utf-8", errors="replace")

m = re.search(r"(<group>\s*<name>ThreadX</name>.*?</group>)", mstep_text, re.S)
if not m:
    raise SystemExit("ThreadX group not found")
threadx = m.group(1).replace(
    r"$PROJ_DIR$\..\mstep_grbl_can\azure_port", r"$PROJ_DIR$\azure_port"
)

content, n = re.subn(
    r"<group>\s*<name>FreeRTOS</name>.*?</group>",
    lambda _m: threadx,
    content,
    count=1,
    flags=re.S,
)
if n != 1:
    raise SystemExit(f"FreeRTOS group replace count={n}")

inc_block = (
    "                    <state>$PROJ_DIR$\\src\\inc</state>\r\n"
    "                    <state>$PROJ_DIR$\\azure_port</state>\r\n"
    "                    <state>$PROJ_DIR$\\..\\common\\azure_rtos\\threadx\\common\\inc</state>\r\n"
    "                    <state>$PROJ_DIR$\\..\\common\\azure_rtos\\threadx\\ports\\cortex_m3\\iar\\inc</state>\r\n"
)
content = content.replace(
    "                    <state>$PROJ_DIR$\\src\\inc</state>\r\n",
    inc_block,
)
content = re.sub(
    r"\s*<state>\$PROJ_DIR\$\\\.\\.\\\.\\.\\common\\freertos\\source\\inc</state>\r\n",
    "",
    content,
)
content = re.sub(
    r"\s*<state>\$PROJ_DIR\$\\\.\\.\\\.\\.\\common\\freertos\\source\\port\\ARM_CM3</state>\r\n",
    "",
    content,
)

if "USE_THREADX" not in content:
    content = content.replace(
        "<state>STM32F205xx</state>",
        "<state>STM32F205xx</state>\r\n"
        "                    <state>USE_THREADX</state>\r\n"
        "                    <state>TX_INCLUDE_USER_DEFINE_FILE</state>",
    )

content = content.replace("app_step_rtos.icf", "app_step_threadx.icf")
ewp.write_text(content, encoding="utf-8")
print("OK:", ewp)
