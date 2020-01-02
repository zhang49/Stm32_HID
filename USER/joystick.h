#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "sys.h"
void Joystick_Init(void);
u16 *Get_Axis_abs(u16 *num);
void ButtonGronp1_Scan(void);
void ButtonGronp2_Scan(void);
uint8_t Get_Button16(void);
void joystick_calibration(void);
#endif
