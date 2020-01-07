#ifndef _PASS_H
#define _PASS_H

#include "stdint.h"
#include "stdlib.h"
uint8_t *GetPassWord(uint8_t *chipid,uint8_t len);
uint8_t *Get_ChipID(void);
uint8_t arrcamp(uint8_t *arr1,uint8_t *arr2,uint8_t len);
#endif