/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "stmflash.h"
#include "MainConfig.h"
#include "pass.h"
#include "string.h"
osThreadId StartTaskHandle;
osThreadId MessageTank;
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void MessageHandler(void const * argument);  //消息处理任务
void StartTask03(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Pre/Post sleep processing prototypes */
void PreSleepProcessing(uint32_t *ulExpectedIdleTime);
void PostSleepProcessing(uint32_t *ulExpectedIdleTime);
const uint8_t TEXT_Buffer[]={"STM32F103 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)
uint8_t datatemp[SIZE]={0};
uint8_t eeprom_pass[TESTLEN] = {0};
uint8_t wrcount[0] = {0};
uint8_t  texstr[TESTLEN] = TEST_P;
/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN PREPOSTSLEEP */
__weak void PreSleepProcessing(uint32_t *ulExpectedIdleTime)
{
/* place for user code */ 
}

__weak void PostSleepProcessing(uint32_t *ulExpectedIdleTime)
{
/* place for user code */
}
/* USER CODE END PREPOSTSLEEP */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  osThreadDef(startTask, StartDefaultTask, 1, 0, 128);
    StartTaskHandle = osThreadCreate(osThread(startTask), NULL);
}
void App_Init()
{
    osThreadDef(messagetank, MessageHandler, 2, 0, 128);
    MessageTank = osThreadCreate(osThread(messagetank), NULL);

    /* definition and creation of myTask03 */
    osThreadDef(myTask03, StartTask03,3, 0, 128);
    myTask03Handle = osThreadCreate(osThread(myTask03), NULL);
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
    uint8_t decount = 0;
    uint8_t mmc[12]="xiaowenlg123";
    static uint8_t *temppass;
    uint8_t tp[TESTLEN] = {0};
    STMFLASH_Read(EEPROM_BEGIN_ADRR,(uint16_t *)datatemp,1);
    datatemp[0] = datatemp[0]+1;
    temppass = GetPassWord(Get_ChipID(),TESTLEN);//计算密码
   //---------------------------------------------------------------- STMFLASH_Read(PASS_ADRESS,(uint16_t *)eeprom_pass,TESTLEN/2);//读密码
   /* for (int j = 0; j <TESTLEN ; ++j) {
        Uart_printf(&huart1,"eeprom_pass:%d\r\n",eeprom_pass[j]);
    }*/
    while(1)     //判断运行次数
    {
        if(datatemp[0]<TEST_USECOUNT){
            osDelay(100);
            STMFLASH_Write(EEPROM_BEGIN_ADRR,(uint16_t *)datatemp,1);
            Uart_printf(&huart1,"System Run Count%d",datatemp[0]);
            break;
        }
        else{
            STMFLASH_Read(PASS_ADRESS,(uint16_t *)eeprom_pass,TESTLEN/2);
           if(arrcamp(temppass,eeprom_pass,TESTLEN)==0)
           {
               Uart_printf(&huart1,"The Same to EEPROM\r\n");
               datatemp[0] = 0;
               STMFLASH_Write(EEPROM_BEGIN_ADRR,(uint16_t *)datatemp,1);
               break;
           } else{
               //发送ChipId到HMI屏
               //等待蓝牙信息
           }
        }
    }
    taskENTER_CRITICAL();
    App_Init();
    vTaskDelete(StartTaskHandle);
    taskEXIT_CRITICAL();

}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the ledtank thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void MessageHandler(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
     // Uart_printf(&huart1,"Data:%d\r\n",datatemp[0]);
      //Uart_printf(&huart1,"eeprompass:%s",eeprom_pass);
      HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1);
      osDelay(500);

  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
      //Uart_printf(&huart1,"Task3");
    osDelay(100);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
