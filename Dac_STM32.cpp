/*
   Dac_STM32.cpp

    Created on: Nov 17, 2020
        Author: GoktugH.
*/



#include <Dac_STM32.h>
#include <Arduino.h>
void SetDacValue(uint8_t _DAC_Channel, uint32_t Data)
{
  if (_DAC_Channel == 1) {
    DAC->DHR12R1 = Data;
  }
  else if (_DAC_Channel == 2) {

    DAC->DHR12R2 = Data;
  }


}

void rcc_config() {
  RCC->AHB1ENR |=  0x1; //SET GPIO4 PERIPHERAL

  GpioConfig(GPIOA);               // Set PA4
  GpioConfig(GPIOA);// Set PA5
  RCC->APB1ENR |= 0x20000000;  //SET DAC PERIPHERAL




}

void dac_init(uint32_t DAC_Channel)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /*---------------------------- DAC CR Configuration --------------------------*/
  /* Get the DAC CR value */
  tmpreg1 = DAC->CR;
  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  tmpreg1 &= ~(0x00000FFE << DAC_Channel);
  tmpreg2 = (0x00000000 | 0x00000000 | 0x00000000);
  /* Calculate CR register value depending on DAC_Channel */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* Write to DAC CR */
  DAC->CR = tmpreg1;
  DAC->CR |= (DAC_CR_EN1 << DAC_Channel);


}

void GpioConfig(GPIO_TypeDef * GPIOx) {
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;



  /* ------------------------- Configure the port pins ---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (0x0010 | 0x0020) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(0x00000003 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)0x03) << (pinpos * 2));

      if ((((uint32_t)0x03) == 0x01) || (((uint32_t)0x03) == 0x02))
      {
        /* Check Speed mode parameters */


        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(0x00000003 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pinpos * 2));



        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((0x00000001) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)0x00) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(0x00000003 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)0x00) << (pinpos * 2));
    }
  }
}
