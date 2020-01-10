#include "HMI.h"

//发送接收符
void HMI_SendEnd(UART_HandleTypeDef *huart)
{
    MY_USART_SendByte(huart, 0xff);
    MY_USART_SendByte(huart, 0xff);
    MY_USART_SendByte(huart, 0xff);
}
//************************************
// 函数:    HMI_SetVal
// 函数全名:  HMI_SetVal
// 函数类型:    public
// 返回值:   void
// Qualifier: //发送数据到HMI屏
// 参数: UART_HandleTypeDef * huart
// 参数: const char * com  变量字符串 如"n0.val="
// 参数: uint32_t val    变量值
//************************************
void HMI_SetVal(UART_HandleTypeDef *huart, const char *com,uint32_t val )//发送数据到HMI屏
{
    Uart_printf(huart, "%s%d", com, val);
    HMI_SendEnd(huart);

}
void HMI_SetTxt(UART_HandleTypeDef *huart, const char *com, char *txt)//发送数据到HMI屏
{
    Uart_printf(huart, "%s\"%s\"", com, txt);
    HMI_SendEnd(huart);

}
void HMI_SetVal_n(UART_HandleTypeDef *huart,uint8_t n,uint32_t val)//发送数值到n控件
{
    Uart_printf(huart,"n%d.val=%d",n,val);
    HMI_SendEnd(huart);
}
void HMI_SetPage(UART_HandleTypeDef *huart,uint8_t page)
{
    Uart_printf(huart,"page %d",page);
    HMI_SendEnd(huart);
}