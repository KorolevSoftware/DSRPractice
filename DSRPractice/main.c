#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h> 
#include <stm32f4xx_rcc.h> 
#include <stm32f4xx_tim.h> 

TIM_OCInitTypeDef oc_init; 
void initLeds(void)
{
    TIM_OCStructInit(&oc_init);
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;  
    oc_init.TIM_OutputState = TIM_OutputState_Enable;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High; 

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;



    // Add led to timer out
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
}

void initTimer()
{
    //      TIMER
    TIM_TimeBaseInitTypeDef base_timer; 
    TIM_TimeBaseStructInit(&base_timer); 
    base_timer.TIM_Prescaler = 0;
    base_timer.TIM_Period = 1000; 
    base_timer.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &base_timer);
    TIM_ARRPreloadConfig(TIM4,ENABLE); 
    TIM_Cmd(TIM4,ENABLE);
}

void setRed(int red)
{
    oc_init.TIM_Pulse = red; 
    TIM_OC3Init(TIM4,&oc_init); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
}

void setGreen(int green)
{
    oc_init.TIM_Pulse = green;
    TIM_OC1Init(TIM4, &oc_init);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
}

void setOrange(int orange)
{
    oc_init.TIM_Pulse = orange; 
    TIM_OC2Init(TIM4,&oc_init); 
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
}

void setBlue(int blue)
{
     oc_init.TIM_Pulse = blue; 
    TIM_OC4Init(TIM4,&oc_init);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 

}


void delay(uint32_t milliseconds) {
  uint32_t start = 0;
 for(int i =0; i < milliseconds; i++){};
}
int main(void){
    initLeds(); 
    initTimer();
 
    while (1)
    {
        int i;
        for( i = 0; i<1000; i++)
        {
                setRed(i);
                setBlue(i);
                setGreen(1000 - i);
                setOrange(1000 - i);
                delay(10000);
        }

        for(; i>0; i--)
        {
                setRed(i);
                setBlue(i);
                setGreen(1000 - i);
                setOrange(1000 - i);
                delay(10000);
        }
    } 
    return 0; 
}