#include "main.h"

void init_leds(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            
}

int main(void)
{
    init_leds();

    const uint16_t arr_of_leds[4] = { GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15 };
    uint8_t current_led = 0;

    while (1)
    {   
        GPIO_ResetBits(GPIOD, arr_of_leds[current_led]);
        current_led = (current_led + 1 + 2) % 4;
        GPIO_SetBits(GPIOD, arr_of_leds[current_led]);
        for(int i = 0; i < 10000000; i++);
    }
}