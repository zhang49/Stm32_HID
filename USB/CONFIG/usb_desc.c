/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Descriptors for Joystick Mouse Demo
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


/* Includes ------------------------------------------------------------------*/
#include "usb_desc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize 64*/
    0x83,                       /*idVendor (0x0483)*/
    0x04,
    0x10,                       /*idProduct = 0x5710*/
    0x57,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                                  manufacturer */
    2,                          /*Index of string descriptor describing
                                                 product*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* Joystick_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
  {
	/***************ÅäÖÃÃèÊö·û***********************/
	0x09,		//bLength×Ö¶Î
	USB_CONFIGURATION_DESCRIPTOR_TYPE,		//bDescriptorType×Ö¶Î
	//wTotalLength×Ö¶Î
	JOYSTICK_SIZ_CONFIG_DESC,
	/* wTotalLength: Bytes returned */
	0x00,

	0x03,	//bNumInterfaces×Ö¶Î
	0x01,	//bConfiguration×Ö¶Î
	0x00,	//iConfigurationz×Ö¶Î
	0x80,	//bmAttributes×Ö¶Î
	0x32,	//bMaxPower×Ö¶Î

	/*******************µÚÒ»¸ö½Ó¿ÚÃèÊö·û(¼üÅÌ)*********************/
	0x09,	//bLength×Ö¶Î
	0x04,	//bDescriptorType×Ö¶Î
	0x00,	//bInterfaceNumber×Ö¶Î
	0x00,	//bAlternateSetting×Ö¶Î
	0x02,	//bNumEndpoints×Ö¶Î
	0x03,	//bInterfaceClass×Ö¶Î
	0x01,	//bInterfaceSubClass×Ö¶Î
	0x01,	//bInterfaceProtocol×Ö¶Î
	0x00,	//iConfiguration×Ö¶Î

	/******************HIDÃèÊö·û************************/
	0x09,	//bLength×Ö¶Î
	0x21,	//bDescriptorType×Ö¶Î
	0x10,	//bcdHID×Ö¶Î
	0x01,
	0x21,	//bCountyCode×Ö¶Î
	0x01,	//bNumDescriptors×Ö¶Î
	0x22,	//bDescriptorType×Ö¶Î

	//bDescriptorLength×Ö¶Î¡£
	//ÏÂ¼¶ÃèÊö·ûµÄ³¤¶È¡£ÏÂ¼¶ÃèÊö·ûÎª¼üÅÌ±¨¸æÃèÊö·û¡£
	sizeof(KeyboardReportDescriptor)&0xFF,
	(sizeof(KeyboardReportDescriptor)>>8)&0xFF,

	/**********************ÊäÈë¶ËµãÃèÊö·û***********************/
	0x07,	//bLength×Ö¶Î
	0x05,	//bDescriptorType×Ö¶Î
	0x81,	//bEndpointAddress×Ö¶Î
	0x03,	//bmAttributes×Ö¶Î
	0x10,	//wMaxPacketSize×Ö¶Î
	0x00,
	0x01,	//bInterval×Ö¶Î

	/**********************Êä³ö¶ËµãÃèÊö·û***********************/
	0x07,	//bLength×Ö¶Î
	0x05,	//bDescriptorType×Ö¶Î
	0x01,	//bEndpointAddress×Ö¶Î
	0x03,	//bmAttributes×Ö¶Î
	0x10,	//wMaxPacketSize×Ö¶Î
	0x00,
	0x01,	//bInterval×Ö¶Î

	/*******************µÚ¶þ¸ö½Ó¿ÚÃèÊö·û£¨Êó±ê£©*********************/
	0x09,	//bLength×Ö¶Î
	0x04,	//bDescriptorType×Ö¶Î
	0x01,	//bInterfaceNumber×Ö¶Î
	0x00,	//bAlternateSetting×Ö¶Î
	0x01,	//bNumEndpoints×Ö¶Î
	0x03,	//bInterfaceClass×Ö¶Î
	0x01,	//bInterfaceSubClass×Ö¶Î
	0x02,	//bInterfaceProtocol×Ö¶Î
	0x00,	//iConfiguration×Ö¶Î

	/******************HIDÃèÊö·û************************/
	0x09,	//bLength×Ö¶Î
	0x21,	//bDescriptorType×Ö¶Î
	0x10,	//bcdHID×Ö¶Î
	0x01,
	0x21,	//bCountyCode×Ö¶Î
	0x01,	//bNumDescriptors×Ö¶Î
	0x22,	//bDescriptorType×Ö¶Î
	sizeof(MouseReportDescriptor)&0xFF,		//bDescriptorLength×Ö¶Î
	(sizeof(MouseReportDescriptor)>>8)&0xFF,

	/**********************ÊäÈë¶ËµãÃèÊö·û***********************/
	0x07,	//bLength×Ö¶Î
	0x05,	//bDescriptorType×Ö¶Î
	0x82,	//bEndpointAddress×Ö¶Î
	0x03,	//bmAttributes×Ö¶Î¡£D1~D0Îª¶Ëµã´«ÊäÀàÐÍÑ¡Ôñ
	0x40,	//wMaxPacketSize×Ö¶Î
	0x00,
	0x01, 	//bInterval×Ö¶Î


	/*******************µÚÈý¸ö½Ó¿ÚÃèÊö·û£¨×Ô¶¨ÒåÓÃ×÷½ÓÊÜPCÊý¾Ý£©*********************/
	/* 09 */
	0x09,         /* bLength: Interface Descriptor size */
	USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
	0x02,         /* bInterfaceNumber: Number of Interface */
	0x00,         /* bAlternateSetting: Alternate setting */
	0x02,         /* bNumEndpoints */
	0x03,         /* bInterfaceClass: HID */
	0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
	0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
	0x00,            /* iInterface: Index of string descriptor */

	/******************HIDÃèÊö·û************************/
	0x09,         /* bLength: HID Descriptor size */
	HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
	0x10,         /* bcdHID: HID Class Spec release number */
	0x01,
	0x00,         /* bCountryCode: Hardware target country */
	0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
	0x22,         /* bDescriptorType */
	Custom_ReportDescriptor_Size,
	0x00,
		
	/**********************ÊäÈë¶ËµãÃèÊö·û***********************/
	0x07,          /* bLength: Endpoint Descriptor size */
	USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */
	0x83,
	0x03,          /* bmAttributes: Interrupt endpoint */
	0x40,//0x02,          /* wMaxPacketSize: 20 Bytes max */
	0x00,
	0x01,          /* bInterval: Polling Interval */

	/**********************Êä³ö¶ËµãÃèÊö·û***********************/
	0x07,	/* bLength: Endpoint Descriptor size */
	USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType */
	0x02,	/* bEndpointAddress */
	0x03,	/* bmAttributes: Interrupt endpoint */
	0x40,	/* wMaxPacketSize: 20 Bytes max  */
	0x00,
	0x01	/* bInterval: Polling Interval */
  }
  ; 
	//USB¼üÅÌ±¨¸æÃèÊö·ûµÄ¶¨Òå
const uint8_t KeyboardReportDescriptor[KP_ReportDescriptor_Size]=
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)	//63
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
		0x85, KeyBoardReportID, 			 //Report ID (3)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,                    //   REPORT_COUNT (5)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x03,                    //   REPORT_SIZE (3)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                           // END_COLLECTION
	//0xc0,
  }; /* Joystick_ReportDescriptor */
///////////////////////////¼üÅÌ±¨¸æÃèÊö·ûÍê±Ï////////////////////////////

//USBÊó±ê±¨¸æÃèÊö·ûµÄ¶¨Òå
uint8_t MouseReportDescriptor[Mouse_ReportDescriptor_Size]=
{
	 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	 0x09, 0x02, // USAGE (Mouse)
	 0xa1, 0x01, // COLLECTION (Application)
	 0x09, 0x01, //   USAGE (Pointer)
	 0xa1, 0x00, //   COLLECTION (Physical)
	
	 0x85, MouseMoveReportID, //Report ID (6)
	
	 0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
	 0x09, 0x30, //     USAGE (X)
	
   0x16, 0x00, 0x00,      //    LOGICAL_MINIMUM (0)	
	 0x26, MOUSEXMax&0xff, MOUSEXMax>>8,      //    LOGICAL_MAXIMUM (1920)
	 0x36, 0x00, 0x00,      //    PHYSICAL_MINIMUM (0)
	 0x46,  MOUSEXMax&0xff, MOUSEXMax>>8,      //    PHYSICAL_MAXIMUM (1920)
	
	 0x75, 0x10,            //    REPORT_SIZE (16)
	 0x95, 0x01, //     REPORT_COUNT (1)
	 0x81, 0x02,            //    INPUT (Data,Var,Abs)
	 
	 0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
	 0x09, 0x31, //     USAGE (Y)
	 
   0x16, 0x00, 0x00,      //    LOGICAL_MINIMUM (0)
	 0x26,  MOUSEYMax&0xff, MOUSEYMax>>8,      //    LOGICAL_MAXIMUM (1080)
	 0x36, 0x00, 0x00,      //    PHYSICAL_MINIMUM (0)
	 0x46,  MOUSEYMax&0xff, MOUSEYMax>>8,      //    PHYSICAL_MAXIMUM (1080)
	 
	 0x75, 0x10,            //    REPORT_SIZE (16)
	 0x95, 0x01, //     REPORT_COUNT (1)
	 0x81, 0x02,            //    INPUT (Data,Var,Abs)
	 
	 0x05, 0x01, 				//     USAGE_PAGE (Generic Desktop)
	 0x09, 0x38, 				//     USAGE (Wheel)
	 0x15, 0x81, 				//     LOGICAL_MINIMUM (-127)
	 0x25, 0x7f, 				//     LOGICAL_MAXIMUM (127)
	 0x35, 0x81, 				     //    PHYSICAL_MINIMUM (-127)
	 0x45, 0x7f,             //    PHYSICAL_MAXIMUM (127)
	 0x75, 0x08,             //    REPORT_SIZE (8)
	 0x95, 0x01,             //     REPORT_COUNT (1)
	 0x81, 0x02,            //    INPUT (Data,Var,Abs) 
	 
	 0xc0,       //   END_COLLECTION
	 0xc0,       //   END_COLLECTION
	 
	 
	 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	 0x09, 0x02, // USAGE (Mouse)
	 0xa1, 0x01, // COLLECTION (Application)
	 0x09, 0x01, //   USAGE (Pointer)
	 0xa1, 0x00, //   COLLECTION (Physical)
	 
	 0x85, MouseBtnReportID, //Report ID (5)
	 0x05, 0x09, //     USAGE_PAGE (Button)
	 0x19, 0x01, //     USAGE_MINIMUM (Button 1)
	 0x29, 0x03, //     USAGE_MAXIMUM (Button 3)
	 0x15, 0x00, //     LOGICAL_MINIMUM (0)
	 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
	 0x95, 0x03, //     REPORT_COUNT (3)
	 0x75, 0x01, //     REPORT_SIZE (1)
	 0x81, 0x02, //     INPUT (Data,Var,Abs)
	 0x95, 0x01, //     REPORT_COUNT (1)
	 0x75, 0x05, //     REPORT_SIZE (5)
	 0x81, 0x03, //     INPUT (Cnst,Var,Abs) 
	 
	 0x95, 0x01, //     REPORT_COUNT (1)
	 0x75, 0x08, //     REPORT_SIZE (8)
	 0x81, 0x03, //     INPUT (Cnst,Var,Abs)
	 
	 0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
	 0x09, 0x30, //     USAGE (X)
	 0x09, 0x31, //     USAGE (Y)
	 0x09, 0x38, //     USAGE (Wheel)
	 0x15, 0x81, //     LOGICAL_MINIMUM (-127)
	 0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
	 0x75, 0x08, //     REPORT_SIZE (8)
	 0x95, 0x03, //     REPORT_COUNT (3)
	 
	 
	 0x81, 0x06, //     INPUT (Data,Var,Rel)
	 
	 0xc0,       //   END_COLLECTION
	 0xc0        // END_COLLECTION
};

const uint8_t CustomHIDReportDescriptor[Custom_ReportDescriptor_Size] = 
{ 
	0x05, 0x8c, /* USAGE_PAGE (ST Page) */ 
	0x09, 0x01, /* USAGE (Demo Kit) */ 
	0xa1, 0x01, /* COLLECTION (Application) */ 
	
	// The Input report 
	0x09,0x03, // USAGE ID - Vendor defined 
	0x15,0x00, // LOGICAL_MINIMUM (0) 
	0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255) 
	0x75,0x08, // REPORT_SIZE (8) 
	0x95,CustomHIDInSize, // REPORT_COUNT (20) 
	0x81,0x02, // INPUT (Data,Var,Abs) 
	
	// The Output report 
	0x09,0x04, // USAGE ID - Vendor defined 
	0x15,0x00, // LOGICAL_MINIMUM (0) 
	0x26,0x00,0xFF, // LOGICAL_MAXIMUM (255) 
	0x75,0x08, // REPORT_SIZE (8) 
	0x95,CustomHIDOutSize, // REPORT_COUNT (20) 
	0x91,0x02, // OUTPUT (Data,Var,Abs) 
	//32
	0xc0 /* END_COLLECTION */ 
}; /* CustomHID_ReportDescriptor */ 


/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
  {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
  {
    JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'X', 0, 'D', 0, '5', 0, 'D', 0
  };
uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
  {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

