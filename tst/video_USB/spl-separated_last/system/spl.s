;// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
;///////////////////////////////////////////////////////////////////////////////
            AREA    SPLFILE, CODE, READONLY

            ALIGN   4
            IF      :DEF:PCB_TINY200V2
            INCBIN  ..\..\output\f1c100s-spl_uart1.bin
            ELSE
            INCBIN  ..\..\output\f1c100s-spl_uart0.bin
            ENDIF

;///////////////////////////////////////////////////////////////////////////////
            END

