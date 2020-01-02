/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Endpoint routines
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
#include "hw_config.h"
#include "usb_desc.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t EP1_Complete;
extern __IO uint8_t EP2_Complete;
extern __IO uint8_t EP3_Complete;


extern uint8_t keyBoardOutBuf[KeyBoardOutSize+1];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
  /* Set the transfer complete token to inform upper layer that the current 
  transfer has been complete */
  EP1_Complete = 1; 
}

void EP2_IN_Callback(void)
{
	EP2_Complete = 1;
}

void EP3_IN_Callback(void)
{
	EP3_Complete = 1;
}

void EP1_OUT_Callback(void)
{
	uint8_t RecvBuf[KeyBoardOutSize];
  PMAToUserBufferCopy(RecvBuf, ENDP1_RXADDR,KeyBoardOutSize);
	SetEPRxStatus(ENDP1, EP_RX_VALID);	
	KeyBoardOutCb(RecvBuf);	
	SetEPRxStatus(ENDP1, EP_RX_VALID);
}

void EP2_OUT_Callback(void)
{
	uint8_t RecvBuf[CustomHIDOutSize];
  PMAToUserBufferCopy(RecvBuf, ENDP2_RXADDR,CustomHIDOutSize);
	SetEPRxStatus(ENDP2, EP_RX_VALID);	
	CustomOutCb(RecvBuf);
  SetEPRxStatus(ENDP2, EP_RX_VALID);
}

//void EP3_OUT_Callback(void)
//{
//	uint8_t RecvBuf[CustomHIDOutSize];
//  PMAToUserBufferCopy(RecvBuf, ENDP3_RXADDR,CustomHIDOutSize);
//	SetEPRxStatus(ENDP3, EP_RX_VALID);	
//	CustomOutCb(RecvBuf);
//  SetEPRxStatus(ENDP3, EP_RX_VALID);
//}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

