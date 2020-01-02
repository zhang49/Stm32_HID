#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"   
#include "usb_bot.h" 
#include "usb_desc.h"


enum ERequestType {
	Req_SetMouseAbsLimit,
	Req_KP,
	Req_Mouse
};


enum EMouseEventOperator {
	LeftBtn_Down,
	LeftBtn_Up,
	LeftBtn_Click,
	RightBtn_Down,
	RightBtn_Up,
	RightBtn_Click,
	MoveAbs
};

enum EKeyBoardEventOperator {
	KeyDown,
	KeyUp,
	KeyClick
};
#define CHIDBUFSIZE 20

typedef struct {
	u8 data[CHIDBUFSIZE][CustomHIDOutSize];
	u32 head;
	u32 tail;
}CHIDRecvQueue;

CHIDRecvQueue CHIDRecvBuf;


extern __IO uint32_t bDeviceState;
 __IO uint8_t EP1_Complete = 1;
 __IO uint8_t EP2_Complete = 1;
 __IO uint8_t EP3_Complete = 1;
 __IO uint8_t EP1_Free = 1;
 
 uint8_t keyBoardOutBuf[KeyBoardOutSize+1];
 
const u8 MouseBtnSize=MouseBtnInSize + 1;
const u8 MouseMoveSize=MouseMoveInSize + 1;
const u8 keyBoardReportLen=KeyBoardInSize + 1;

u8 keyBoardRecvBuf[KeyBoardOutSize+1];
u8 CustomHIDRecvBuf[CustomHIDOutSize+1];

u8 keyBoardBuf[keyBoardReportLen];

u8 testFlag = 1;


u8 btnBuf[MouseBtnSize];
u8 moveBuf[MouseMoveSize];

u8 KPTable[255];

double mouseX_Precent = MOUSEYMax / (double)1920;
double mouseY_Precent = MOUSEYMax / (double)1080;

void InitKPTable()
{
	int i=0;
	// a - z
	for(i=0;i<26;i++)
	{
		KPTable[0x41+i]=0x04 + i;
	}
	// 1 - 0
	for(i=0;i<9;i++)KPTable[0X30+i]=0x1e + i;
	KPTable[0X30+i]=0x1e + i;
	// F1 - F12
	for(i=0;i<12;i++)KPTable[0x70+i]=0x3a + i;
	// F13 - F24
	for(i=0;i<12;i++)KPTable[0x7C+i]=0x68 + i;
	
	KPTable[91]=0x2f;// [
	KPTable[92]=0x31;// 反斜杠
	KPTable[93]=0x30;// ]
	
	KPTable[45]=0x2d;// -
	KPTable[43]=0x2e;// +
	
	KPTable[44]=0x36;// ,
	KPTable[46]=0x37;// .
	KPTable[47]=0x38;// /
	
	KPTable[13]=0x28;// 回车
	KPTable[27]=0x29;// ESC
	
	KPTable[32]=0x2c;// 空格键
	KPTable[9]=0x2b;// 制表符
	
	
	//shift ctrl alt等按键在keyBoardBuf[1]设置按下，释放
}

void KeyBoardOutRecv(u8 *buf)
{
	printf("KeyBoard Get.\r\n");
}

//void clearBtnBuf()
//{
//	int i=0;
//	for(i=0;i<MouseBtnSize;i++)
//	{
//		btnBuf[i]=0;
//	}
//}

void leftBtnDown()
{
	btnBuf[0]=MouseBtnReportID;
	btnBuf[1]|=0x01;
	Mouse_Send(btnBuf,MouseBtnSize);
}

void leftBtnUp()
{
	btnBuf[0]=MouseBtnReportID;
	btnBuf[1]&=0xfe;
	Mouse_Send(btnBuf,MouseBtnSize);
}

void rightBtnDown()
{
	btnBuf[0]=MouseBtnReportID;
	btnBuf[1]|=0x02;
	Mouse_Send(btnBuf,MouseBtnSize);
}

void rightBtnUp()
{
	btnBuf[0]=MouseBtnReportID;
	btnBuf[1]&=0xfd;
	Mouse_Send(btnBuf,MouseBtnSize);
}

void MouseMoveAbs(uint16_t x,uint16_t y)
{
	uint16_t realX,realY;
	moveBuf[0]=MouseMoveReportID;
	realX=mouseX_Precent*x;
	realY=mouseY_Precent*y;
	moveBuf[1]=realX;
	moveBuf[2]=realX>>8;
	moveBuf[3]=realY;
	moveBuf[4]=realY>>8;
	moveBuf[5]=0;//wheel
	Mouse_Send(moveBuf,MouseMoveSize);
}


void KP_CtrlDown()
{
	keyBoardBuf[1] |= 0x01;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}

void KP_CtrlUp()
{
	keyBoardBuf[1] &= 0xfe;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	

}

void KP_ShiftDown()
{
	keyBoardBuf[1] |= 0x02;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}

void KP_ShiftUp()
{
	keyBoardBuf[1] &= 0xfd;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}

void KP_AltDown()
{
	keyBoardBuf[1] |= 0x04;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}

void KP_AltUp()
{
	keyBoardBuf[1] &= 0xfb;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}


void KeyBoardDown(uint8_t code)
{
	int i=0;
	for(i=2;i<keyBoardReportLen;i++)keyBoardBuf[i]=0;
	keyBoardBuf[0]=KeyBoardReportID;
	keyBoardBuf[3]=KPTable[code];
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}

void KeyBoardUp(uint8_t code)
{
	int i=0;
	for(i=2;i<keyBoardReportLen;i++)keyBoardBuf[i]=0;
	keyBoardBuf[0]=KeyBoardReportID;
	KeyBoard_Send(keyBoardBuf,keyBoardReportLen);	
}


void HandleCustomMouse(u8 *buf)
{
	switch(buf[1])
	{
		case LeftBtn_Down:
			printf("LeftBtn_Down\r\n");
			leftBtnDown();
			break;
		case LeftBtn_Up:
			leftBtnUp();
			break;
		case LeftBtn_Click:
			printf("LeftBtn_Click\r\n");
			leftBtnDown();
			delay_ms(5);
			leftBtnUp();
			break;
		case RightBtn_Down:
			printf("RightBtn_Down\r\n");
			rightBtnDown();
			break;
		case RightBtn_Up:
			printf("RightBtn_Up\r\n");
			rightBtnUp();
			break;
		case RightBtn_Click:
			printf("RightBtn_Click\r\n");
			rightBtnDown();
			delay_ms(5);
			rightBtnUp();
			break;
		case MoveAbs:
		{
			u16 x,y;
			x=buf[2]+(buf[3]<<8);
			y=buf[4]+(buf[5]<<8);
			printf("MoveAbs(%d,%d)\r\n",x,y);
			MouseMoveAbs(x,y);
		}
			break;
	}
	//Mouse_Send(buf+1, btnReportLen);
}


/*
* 0				Report ID
*	1 			ctrl - gui
*	2				填充
* 3 - 6		一般按键
*/
void HandleCustomKeyBoard(u8 *buf)
{
	int code = buf[2];
	switch(code)
	{
		case 16:		//shift
			if(buf[1]==KeyDown)KP_ShiftDown();
			else if(buf[1]==KeyUp)KP_ShiftUp();
			break;
		case 17:		//ctrl
			if(buf[1]==KeyDown)KP_CtrlDown();
			else if(buf[1]==KeyUp)KP_CtrlUp();			
			break;
		case 18:		//alt
			if(buf[1]==KeyDown)KP_AltDown();
			else if(buf[1]==KeyUp)KP_AltUp();			
			break;
	}
	if(code == 16 || code == 17 || code == 18)
	{
		return;
	}
	switch(buf[1])
	{
		case KeyDown:
			KeyBoardDown(code);
		break;
		case KeyUp:
			KeyBoardUp(code);
		break;
		case KeyClick:
			printf("KeyClick. code: %d\r\n",code);
			KeyBoardDown(code);
			delay_ms(10);
			KeyBoardUp(code);
		break;
	}		
}
void HandleSetMouseAbsLimit(u8 *buf)
{
	u16 x,y;
	x=buf[2]+(buf[3]<<8);
	y=buf[4]+(buf[5]<<8);	
	mouseX_Precent=MOUSEYMax/(double)x;
	mouseY_Precent=MOUSEYMax/(double)y;	
}


void CutomHIDOutRecv(u8 *buf)
{
	int index=CHIDRecvBuf.tail%CHIDBUFSIZE;	
	memcpy(CHIDRecvBuf.data[index],buf,CustomHIDOutSize);
	CHIDRecvBuf.tail++;	
}

/*
*	Buffer: Byte 0 ERequestType
*/
void HandleCoustomRecvBuf()
{
	if(CHIDRecvBuf.head<CHIDRecvBuf.tail)
	{
		int index=CHIDRecvBuf.head%CHIDBUFSIZE;
		u8 *buf=CHIDRecvBuf.data[index];
		switch(buf[0])
		{
			case Req_SetMouseAbsLimit:
				HandleSetMouseAbsLimit(buf);
				break;
			case Req_Mouse:
				//printf("Req_Mouse\t");
				HandleCustomMouse(buf);
				break;
			case Req_KP:
				HandleCustomKeyBoard(buf);
				break;
		}
		CHIDRecvBuf.head++;
		if(CHIDRecvBuf.head>0xfffffff0)
		{
			u32 temp = CHIDRecvBuf.head/CHIDBUFSIZE*CHIDBUFSIZE;
			CHIDRecvBuf.head-=temp;
			CHIDRecvBuf.tail-=temp;			
		}
	}
}

int main(void)
{
	u8 i;
	uint16_t x,y;
	uint32_t recvLen;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 		//延时函数初始化	 
	LED_Init();							//初始化与LED连接的硬件接口
	//调试串口
	USART1_Init(115200);
 	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();
 	USB_Init();
	printf("Start.\n");
	CustomOutCb=CutomHIDOutRecv;
	KeyBoardOutCb=KeyBoardOutRecv;
	CHIDRecvBuf.head=0;
	CHIDRecvBuf.tail=0;
	for(i=0;i<MouseBtnSize;i++)btnBuf[i]=0;
	for(i=0;i<MouseMoveSize;i++)moveBuf[i]=0;
	for(i=0;i<keyBoardReportLen;i++)keyBoardBuf[i]=0;
	keyBoardBuf[0]=KeyBoardReportID;
	
	InitKPTable();	
	while(1)
	{	
		//必须等待设备枚举完后再开始发送数据
		if(bDeviceState!=CONFIGURED)
		{
			delay_ms(800);
			delay_ms(800);
			delay_ms(800);
			continue;
		}
		HandleCoustomRecvBuf();
		
		if(uartRecvLen>0)
		{
			uartRecvLen=0;
			switch(uartRecvBuf[0])
			{
				case '0':
				
					break;
					break;				
			}
		}
		delay_ms(5);//每条指令间隔时间
		continue;

	}
}



