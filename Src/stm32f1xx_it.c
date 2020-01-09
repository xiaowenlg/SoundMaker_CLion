/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
#include "cmsis_os.h"
#include "usart.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;

uint8_t DataIndex = 0;
uint8_t DataLen;
uint8_t ReceData[256];//接收数据缓冲区
_Bool ReceOver;
/* USER CODE BEGIN EV */
uint8_t Usart2_Index = 0;
uint8_t Usart2_Data[256];//接收数据缓冲区
uint8_t Usart2_DataLen;
_Bool Usart2_Over;
/*串口3*/
uint8_t Usart3_Index = 0;
uint8_t Usart3_Data[256];//接收数据缓冲区
_Bool Usart3_Over;//接收完毕标志
uint8_t Usart3_DataLen;


uint8_t meDatalen = 0;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 global interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */

  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */

  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

void UART1_CallBack()
{
    uint8_t tempData = 0;
    uint8_t clear = clear;
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
    {
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);   // 翻转灯
        ReceData[DataIndex] = 0;
        tempData = USART1->DR;//(USART1->DR);	//读取接收到的数据
        ReceData[DataIndex] = tempData;
        DataIndex++;
        //HAL_UART_Transmit(&huart1, ReceData, DataLen, 1000);
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);   // 翻转灯
    }
    else if (RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);   // 翻转灯
        clear = USART1->SR;
        clear = USART1->DR;
        DataLen = DataIndex;
        DataIndex = 0;
        ReceOver = 1;
        //__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    }

    __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_TC);
}
void UART2_CallBack()
{
    uint8_t tempData = 0;
    uint8_t clear = clear;
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET)
    {

        Usart2_Data[Usart2_Index] = 0;
        tempData = USART2->DR;//(USART1->DR);	//读取接收到的数据
        Usart2_Data[Usart2_Index] = tempData;
        Usart2_Index++;
        //HAL_UART_Transmit(&huart1, ReceData, DataLen, 1000);
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);   // 翻转灯
    }
    else if (RESET != __HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE))
    {

        clear = USART2->SR;
        clear = USART2->DR;
        Usart2_DataLen = Usart2_Index;
        Usart2_Index = 0;
        Usart2_Over = 1;
        //__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    }

    __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);
}
//UART3中断回调函数
void UART3_CallBack()
{
    uint8_t tempData = 0;
    uint8_t clear = clear;
    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) != RESET)
    {

        Usart3_Data[Usart3_Index] = 0;
        tempData = USART3->DR;//(USART1->DR);	//读取接收到的数据
        Usart3_Data[Usart3_Index] = tempData;
        Usart3_Index++;
        //HAL_UART_Transmit(&huart1, ReceData, DataLen, 1000);
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);   // 翻转灯
    }
    else if (RESET != __HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE))
    {

        clear = USART3->SR;
        clear = USART3->DR;
        Usart3_DataLen = Usart3_Index;
        Usart3_Index = 0;
        Usart3_Over = 1;
        //__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    }

    __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_TC);
}
void UartCallback(UART_HandleTypeDef* uartHandle,ReceMessage *meRec)   //结构体做函数的参数必须传指针
{
    static uint8_t i = 0;
    uint8_t tempData = 0;
    uint8_t clear = clear;
    if (__HAL_UART_GET_FLAG(uartHandle, UART_FLAG_RXNE) != RESET)
    {
        //meRec.redata[meRec.dataIndex] = 0;

        tempData = uartHandle->Instance->DR;	//读取接收到的数据

        meRec->redata[meRec->dataIndex] = tempData;
        meRec->dataIndex++;
        i++;

    }
    else if (RESET != __HAL_UART_GET_FLAG(uartHandle, UART_FLAG_IDLE))
    {

        clear = uartHandle->Instance->SR;
        clear = uartHandle->Instance->DR;
        i = 0;
        meRec->datalen = meRec->dataIndex;
        meRec->dataIndex= 0;
        meRec->reover = 1;
        //__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    }
    __HAL_UART_CLEAR_FLAG(uartHandle, UART_FLAG_TC);
}
/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
   ///UART1_CallBack();//---------------------------------------------
  UartCallback(&huart1,&uart1_rec);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
    UART2_CallBack();
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
    UART3_CallBack();
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
