;// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
;///////////////////////////////////////////////////////////////////////////////
            AREA    UHEAD, DATA, READONLY

            IMPORT  ||Load$$EXE_CODE$$Length||
            IMPORT  ||Image$$EXE_CODE$$Base||
            IMPORT  Reset_Handler

            ;// ����DCD�����32λ������Ҫ�����ư�mksunxi������Ϊ����ֽ���

            DCD     0x27051956                      ;// ih_magic
            DCD     0                               ;// ih_hcrc
            DCD     0                               ;// ih_time
            DCD     ||Load$$EXE_CODE$$Length||      ;// ih_size
            DCD     ||Image$$EXE_CODE$$Base||       ;// ih_load
            DCD     Reset_Handler                   ;// ih_ep
            DCD     0                               ;// ih_dcrc
            DCD     0x11020500                      ;// ih_os etc.
            DCB     "DESIGNER: Xuyao Hong, QQ26750452"

;///////////////////////////////////////////////////////////////////////////////
            END

