#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H
#include "platform_config.h"
#include "usb_type.h" 

typedef void(*HIDOUT_CALLBACK)(uint8_t *buf);

extern HIDOUT_CALLBACK CustomOutCb;
extern HIDOUT_CALLBACK KeyBoardOutCb;

//USB通用代码函数声明
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void USB_Port_Set(u8 enable);
void IntToUnicode (u32 value,u8 *pbuf,u8 len);
void Get_SerialNum(void);

void Mouse_Send(uint8_t *buf,uint8_t bLen);
void KeyBoard_Send(uint8_t *buf,uint8_t bLen);
void CustomHID_Send(uint8_t *buf,uint8_t bLen);

uint32_t KeyBoard_Get(uint8_t *buf);
uint32_t CustomHID_Get(uint8_t *buf);

//不同USB功能添加的函数声明 
void Led_RW_ON(void);
void Led_RW_OFF(void);
void USB_NotConfigured_LED(void);

#endif  
























