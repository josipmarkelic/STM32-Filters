#ifndef __PERIPHERAL_INIT_H
#define __PERIPHERAL_INIT_H

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern UART_HandleTypeDef huart4;

void peripheral_init();

#endif
