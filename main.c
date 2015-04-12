#include "lpc43xx_gpio.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_libcfg_default.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_timer.h"

#define LED1_BIT            11 //LEDUSB
#define LED1_PORT           1
#define LED2_BIT            12 //LEDUSB
#define LED2_PORT           1

TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;

void delay(uint32_t delay_ms)
{
    TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
    TIM_ConfigStruct.PrescaleValue  = 1000;

    // use channel 0, MR0
    TIM_MatchConfigStruct.MatchChannel = 0;
    // Disable interrupt when MR0 matches the value in TC register
    TIM_MatchConfigStruct.IntOnMatch   = TRUE;
    //Enable reset on MR0: TIMER will reset if MR0 matches it
    TIM_MatchConfigStruct.ResetOnMatch = TRUE;
    //Stop on MR0 if MR0 matches it
    TIM_MatchConfigStruct.StopOnMatch  = FALSE;
    //Toggle MR0.0 pin if MR0 matches it
    TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
    TIM_MatchConfigStruct.MatchValue   = delay_ms;

    // Set configuration for Tim_config and Tim_MatchConfig
    TIM_Init(LPC_TIMER0, TIM_TIMER_MODE,&TIM_ConfigStruct);
    TIM_ConfigMatch(LPC_TIMER0,&TIM_MatchConfigStruct);
    TIM_Cmd(LPC_TIMER0,ENABLE);

    while ( !(TIM_GetIntStatus(LPC_TIMER0,TIM_MR0_INT)));
    TIM_ClearIntPending(LPC_TIMER0,(TIM_INT_TYPE)0);

    TIM_Cmd(LPC_TIMER0,DISABLE);
}

int main(void)
{
    CGU_Init();

    scu_pinmux(0x2 ,11 , MD_PUP, FUNC0);    // P2.11 : GPIO1_11: Xplorer BOARD (LED D2)
    GPIO_SetDir(LED1_PORT,(1<<LED1_BIT), 1);
    GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));
    scu_pinmux(0x2 ,12 , MD_PUP, FUNC0);    // P2.12 : GPIO1_12: Xplorer BOARD (LED D3)
    GPIO_SetDir(LED2_PORT,(1<<LED2_BIT), 1);
    GPIO_ClearValue(LED2_PORT,(1<<LED2_BIT));

    while (1)
    {
        delay(500);
        GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));
        delay(500);
        GPIO_ClearValue(LED2_PORT,(1<<LED2_BIT));
        GPIO_SetValue(LED1_PORT,(1<<LED1_BIT));
        delay(500);
        GPIO_SetValue(LED2_PORT,(1<<LED2_BIT));
    }

}
