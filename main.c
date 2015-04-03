#include "lpc43xx_gpio.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_libcfg_default.h"
#include "lpc43xx_cgu.h"
#include "lpc43xx_utils.h"

#define LED1_BIT			11 //LEDUSB
#define LED1_PORT			1
#define LED2_BIT			12 //LEDUSB
#define LED2_PORT			1

void delay(void)
{
    int i;
    for (i = 0; i < 2000000; i++)   /* Wait a bit. */
        __asm__("nop");
}

int main(void)
{

    CGU_Init();
    scu_pinmux(0x2 ,11 , MD_PUP, FUNC0); 	// P2.11 : GPIO1_11: Xplorer BOARD (LED D2)
    GPIO_SetDir(LED1_PORT,(1<<LED1_BIT), 1);
    GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));
    scu_pinmux(0x2 ,12 , MD_PUP, FUNC0); 	// P2.12 : GPIO1_12: Xplorer BOARD (LED D3)
    GPIO_SetDir(LED2_PORT,(1<<LED2_BIT), 1);
    GPIO_ClearValue(LED2_PORT,(1<<LED2_BIT));

    while (1)
    {
//        timer_delay_ms(50);
        delay();
        GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));
//        timer_delay_ms(50);
        delay();
        GPIO_ClearValue(LED2_PORT,(1<<LED2_BIT));
        GPIO_SetValue(LED1_PORT,(1<<LED1_BIT));
//        timer_delay_ms(50);
        delay();
        GPIO_SetValue(LED2_PORT,(1<<LED2_BIT));
    }

}

