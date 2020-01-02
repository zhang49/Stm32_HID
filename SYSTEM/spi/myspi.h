#ifndef _MYSPI_H
#define _MYSPI_H
#include "sys.h"

extern u16 Spi1ReadCnt;
void Spi1SlaveInit(void);
void SPI1_SendData(char *data);
#endif

