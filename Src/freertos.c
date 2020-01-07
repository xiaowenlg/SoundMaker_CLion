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
#include "stm32f1xx_it.h"
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
uint8_t  eeprom_Ble_addr[READLEN] = {0};//蓝牙地址
uint8_t endflg[8] = { "-N" };	//结尾标志
uint8_t readflg[8] = {0};		//读到的标志位

uint8_t str[4] = { 0 };
uint8_t str1[4] = "MAC";
uint8_t adr_MAC[MAC_LENGTH] = { 0 };

uint8_t recount = 0;//记录接收次数

//串口接收参数

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
           }
           else{
               //发送ChipId到HMI屏
               while(1)
               {
                   //等待蓝牙信息
               }
           }
        }
    }

    //取蓝牙地址
    STMFLASH_Read(BLE_ADRESS , (uint16_t *)eeprom_Ble_addr, MAC_LENGTH/2+1);//先读一次

    memset(readflg, 0, 6);
    memcpy(readflg, &eeprom_Ble_addr[17], 2);
    if(strcmp(endflg,readflg)==0)
    {
        Uart_printf(DEBUG_UART,"The Same=====!");
        memset(adr_MAC, 0, MAC_LENGTH);
        memcpy(adr_MAC, &eeprom_Ble_addr[0], 17);//取内存中的蓝牙地址
    } else
    {
        Uart_printf(DEBUG_UART, "\r\nNo Same");
      osDelay(500);//等待蓝牙稳定
        MY_USART_chars(BLE_UART, "+++a");
       // MY_USART_chars(BLE_UART, "AT+ENTM\r\n");
        while (1)
        {

            if (Usart2_Over == 1)
            {
                recount++;
                Usart2_Over = 0;
                Uart_printf(&huart1,Usart2_Data);
               // MY_USART_chars(BLE_UART, "AT+MAC?\r\n");
               if (recount>=2)
                {
                   memset(str, 0, 4);
                    memcpy(str, &Usart2_Data[3], 3);
                    Uart_printf(&huart1,str);
                    if (strcmp(str1, str) == 0)
                    {

                        MY_USART_chars(BLE_UART, "AT+ENTM\r\n");
                        memset(adr_MAC, 0, MAC_LENGTH);
                        memcpy(adr_MAC, &Usart2_Data[7], Usart2_DataLen - 12);//取蓝牙地址

                        for (int i = 1; i < 6; i++)							//蓝牙地址中插入":"
                        {
                            if (i == 1)
                                insertOneByte(adr_MAC, MAC_LENGTH, ':', i * 2);
                            else
                                insertOneByte(adr_MAC, MAC_LENGTH, ':', i * 2 + (i - 1));

                        }
                        insertArray(adr_MAC, MAC_LENGTH - 2, "-N", 2, MAC_LENGTH-2);
                       // STMFLASH_Write(BLE_ADRESS, (uint16_t *)adr_MAC, MAC_LENGTH);            //把蓝牙地址写入内存
                        //Uart_printf(&huart1, "addr:%s", adr_MAC);//-------------------------------------------------------
                        break; //推出while循环
                    }
                    memset(Usart2_Data, 0, Usart2_DataLen);

                }
                else
                    MY_USART_chars(BLE_UART, "AT+MAC?\r\n");
            }

            osDelay(5);
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
      HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_2);
    osDelay(100);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
