#ifndef _PASS_H
#define _PASS_H

#include "stdint.h"
#include "stdlib.h"
uint8_t *GetPassWord(uint8_t *chipid,uint8_t len);
uint8_t *Get_ChipID(void);
uint8_t arrcamp(uint8_t *arr1,uint8_t *arr2,uint8_t len);
int insertArray(uint8_t *arr, uint16_t arrlen, uint8_t *inarr, uint16_t inarrlen,uint16_t pos);//数组中插入数组
int insertOneByte(uint8_t *arr, uint16_t arrlen, uint8_t indata, uint16_t pos);//数组中插入一个字符
#endif