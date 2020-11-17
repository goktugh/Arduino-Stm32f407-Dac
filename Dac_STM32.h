#ifndef __DAC_STM32_H__
#define __DAC_STM32_H__
#include <Arduino.h>

#define DAC_Channel_1                      ((uint32_t)0x00000000)
#define DAC_Channel_2                      ((uint32_t)0x00000010)

void GpioConfig(GPIO_TypeDef * GPIOx);
void rcc_config();
void dac_init(uint32_t DAC_Channel);
void SetDacValue(uint8_t _DAC_Channel, uint32_t Data);

#endif
