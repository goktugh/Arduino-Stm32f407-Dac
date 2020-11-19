#include <Dac_STM32.h>

int Data = 0;



void setup() {

  rcc_config();
  dac_init(DAC_Channel_1);  //Set  GPIOA PIN A4
  dac_init(DAC_Channel_2);  //Set  GPIOA PIN A5
  SetDacValue(1, 0);  //Set Dac1 value clear
  SetDacValue(2, 0);  //Set Dac2 value clear

}

void loop() {



  SetDacValue(1, Data);
  SetDacValue(2, Data);




}
