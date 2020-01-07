#include "pass.h"
#include "MainConfig.h"
#include "usart.h"
#include "string.h"
uint8_t tesid[TESTLEN] = TEST_P;
uint8_t *GetPassWord(uint8_t *chipid,uint8_t len)
{
    static uint8_t res[12];                             //必须声明成静态的
    for (int i = 0; i <len ; ++i) {
        res[i] = chipid[i]^tesid[i];

    }
    return  res;   // 返回数组指针
}

uint8_t *Get_ChipID(void)           //读取芯片ID
{

    uint32_t ChipUniqueID[3];
    //uint8_t temp[12];
    static uint8_t temp[12] ;                           //必须声明成静态的
    uint32_t temp0,temp1,temp2;
    temp0=*(__IO uint32_t*)(0x1FFFF7E8);    //产品唯一身份标识寄存器（96位）
    temp1=*(__IO uint32_t*)(0x1FFFF7EC);
    temp2=*(__IO uint32_t*)(0x1FFFF7F0);
    temp[0] = (uint8_t)(temp0 & 0x000000FF);
    temp[1] = (uint8_t)((temp0 & 0x0000FF00)>>8);
    temp[2] = (uint8_t)((temp0 & 0x00FF0000)>>16);
    temp[3] = (uint8_t)((temp0 & 0xFF000000)>>24);
    temp[4] = (uint8_t)(temp1 & 0x000000FF);
    temp[5] = (uint8_t)((temp1 & 0x0000FF00)>>8);
    temp[6] = (uint8_t)((temp1 & 0x00FF0000)>>16);
    temp[7] = (uint8_t)((temp1 & 0xFF000000)>>24);
    temp[8] = (uint8_t)(temp2 & 0x000000FF);
    temp[9] = (uint8_t)((temp2 & 0x0000FF00)>>8);
    temp[10] = (uint8_t)((temp2 & 0x00FF0000)>>16);
    temp[11] = (uint8_t)((temp2 & 0xFF000000)>>24);

    return temp;
}

uint8_t arrcamp(uint8_t *arr1,uint8_t *arr2,uint8_t len)            //判断两个数组前len个数据是否相等
{
    uint8_t res = 0;
    for (int i = 0; i < len; ++i) {
        if(arr1[i]!=arr2[i])
            return 1;
    }
    return 0;
}

int insertArray(uint8_t *arr, uint16_t arrlen, uint8_t *inarr, uint16_t inarrlen,uint16_t pos)
{
    int res = -2;
    uint16_t i = 0;
    if ((arrlen + inarrlen) < 65536)
    {
        //memcpy(&buf_date[bufdateIndex], resdate, resdatelen);
        memcpy(&arr[pos + inarrlen], &arr[pos], arrlen - pos + 1);//数组从pos后，后移inarrlen位
        memcpy(&arr[pos], inarr, inarrlen);

        res = arrlen + inarrlen;
    }
    else
        res = -1;
    return res;
}
//插入一个字符
int insertOneByte(uint8_t *arr, uint16_t arrlen, uint8_t indata, uint16_t pos)
{
    int res = -2;
    int i = 0;
    if ((arrlen + 1) < 65536)
    {
        for (i = arrlen; i >= pos; i--)
        {
            arr[i + 1] = arr[i];
        }
        arr[pos] = indata;
        res = arrlen + 1;
    }
    else
        res = -1;
    return res;
}