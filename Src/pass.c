#include "pass.h"
#include "MainConfig.h"

uint8_t *GetPassWord(uint8_t *chipid,uint8_t *tesid,uint8_t len)
{
    uint8_t res[] = {0};
    for (int i = 0; i <len ; ++i) {
        res[i] = chipid[i]^tesid[i];
    }
    return  res;   // 返回数组指针
}

uint8_t *Get_ChipID(void)
{

    uint32_t ChipUniqueID[3];
    uint8_t temp[12];
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