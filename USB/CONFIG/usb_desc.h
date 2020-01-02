/**
  ******************************************************************************
  * @file    usb_desc.h
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Descriptor Header for Joystick Mouse Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#define KeyBoardReportID				 0x02
#define MouseBtnReportID		 		 0x05
#define MouseMoveReportID 	 		 0x06
#define CustomHIDReportID				 0x00

#define KeyBoardInSize					 8
#define KeyBoardOutSize					 1
#define MouseInSize					 		 5

#define MouseBtnInSize			 		 5
#define MouseMoveInSize			 		 5

#define CustomHIDInSize					 22
#define CustomHIDOutSize				 22

#define MOUSEXMax								 4095
#define MOUSEYMax								 4095


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05


#define HID_DESCRIPTOR_TYPE                     0x21
#define JOYSTICK_SIZ_HID_DESC                   0x09

#define JOYSTICK_SIZ_DEVICE_DESC                18

/********************** HID 描述符在CONFIG_DESC中的偏移值 ******************************/
#define KP_OFF_HID_DESC													18
#define Mouse_OFF_HID_DESC											50
#define Custom_OFF_HID_DESC											75


#define JOYSTICK_SIZ_CONFIG_DESC                98
#define KP_ReportDescriptor_Size								65
#define Mouse_ReportDescriptor_Size 						136
#define Custom_ReportDescriptor_Size 						33

#define JOYSTICK_SIZ_STRING_LANGID              4
#define JOYSTICK_SIZ_STRING_VENDOR              38
#define JOYSTICK_SIZ_STRING_PRODUCT             10
#define JOYSTICK_SIZ_STRING_SERIAL              26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC];
extern const u8 Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC];

/*******************************************************************************/
extern const u8 KeyboardReportDescriptor[KP_ReportDescriptor_Size];
extern u8 MouseReportDescriptor[Mouse_ReportDescriptor_Size];
extern const u8 CustomHIDReportDescriptor[Custom_ReportDescriptor_Size];
/*******************************************************************************/

extern const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID];
extern const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR];
extern const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT];
extern uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
