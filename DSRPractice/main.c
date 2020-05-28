#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h> 
#include <stm32f4xx_rcc.h> 
#include <stm32f4xx_tim.h> 


void initLeds(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;


    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);


}

void initTimer()
{
        //                 TIMER
    TIM_TimeBaseInitTypeDef base_timer; 
    TIM_TimeBaseStructInit(&base_timer); 

    base_timer.TIM_Prescaler = 8400 - 1;   // делитель частоты 
    base_timer.TIM_Period = 10000;  // период
    base_timer.TIM_CounterMode = TIM_CounterMode_Up; // счёт вверх 
    TIM_TimeBaseInit(TIM4, &base_timer); 

    TIM_OCInitTypeDef oc_init; 
    TIM_OCStructInit(&oc_init);
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;   // работаем в режиме ШИМ ( PWM ) 
    oc_init.TIM_OutputState = TIM_OutputState_Enable;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;  // положительная полярность 


    // 1  
    oc_init.TIM_Pulse = 500;   // частота шим 
    TIM_OC1Init(TIM4,&oc_init);   /// заносим данные в первый канал - порт D12 
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    // 2 
    oc_init.TIM_Pulse = 50000; /// изменяем частоту шим 
    TIM_OC2Init(TIM4,&oc_init);  // настраиваем второй канал D13 
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    // 3 канал - D14 
    oc_init.TIM_Pulse = 500; 
    TIM_OC3Init(TIM4,&oc_init); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    // 4  - D15 
    oc_init.TIM_Pulse = 5000; 
    TIM_OC4Init(TIM4,&oc_init);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    TIM_ARRPreloadConfig(TIM4,ENABLE); 
    TIM_Cmd(TIM4,ENABLE);   // запускаем счёт
}

int main(void){ 
    initLeds(); 
    initTimer(); 
    while (1){ 
    } 
    return 0; 
}