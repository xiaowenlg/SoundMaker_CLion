#ifndef _PASS_H
#define _PASS_H

#include <stdint-gcc.h>
#include "stdlib.h"
uint8_t *GetPassWord(uint8_t *chipid,uint8_t *tesid,uint8_t len);
uint8_t *Get_ChipID(void);
#endif