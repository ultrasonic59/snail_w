
#include "cam_can_brd.h"

void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = TST1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TST1_GPIO, &GPIO_InitStructure);
}
///=============== led =======================================
void set_led(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(LED_GPIO,LED_PIN,Bit_SET);
 else
     GPIO_WriteBit(LED_GPIO,LED_PIN, Bit_RESET);
}
///=============== tst1 =======================================
void set_tst1(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(TST1_GPIO,TST1_PIN,Bit_SET);
 else
     GPIO_WriteBit(TST1_GPIO,TST1_PIN, Bit_RESET);
}


#if 0
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u8 i = 0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    printf("GPIO Toggle TEST\r\n");
    GPIO_Toggle_INIT();

    while(1)
    {
        Delay_Ms(250);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }
}
#endif
