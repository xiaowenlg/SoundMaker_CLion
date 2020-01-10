#ifndef _HMI_H
#define _HMI_H

#include "stdint.h"
#include "usart.h"
void HMI_SetVal(UART_HandleTypeDef *huart, const char *com,uint32_t val );
void HMI_SetTxt(UART_HandleTypeDef *huart, const char *com, char *txt);
void HMI_SetVal_n(UART_HandleTypeDef *huart,uint8_t n,uint32_t val);
void HMI_SetPage(UART_HandleTypeDef *huart,uint8_t page);
#endif