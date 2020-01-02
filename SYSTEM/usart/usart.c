#include "sys.h"
#include "usart.h"

uint8_t uartRecvBuf[UART1RECVSIZE];
int uartRecvLen=0;

////重定义fputc函数 ,输出到 USART2
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;   
	return ch;
}
//#endif 

 
 
#if EN_USART1_RX   //如果使能了接收


#endif	

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	

void USART1_Init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);                    //使能串口1 
}



void USART2_Init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//USART2_TX   GPIOA PIN2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PIN 2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART2_RX	  GPIOA PIN3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PIN 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口2接受中断
	USART_Cmd(USART2, ENABLE);                    //使能串口2 
}


void USART2_Send(char *data)                	//串口2发送
{
	while(*data!=0)
		USART2_Putc(*(data++));
}
void USART2_Putc(char ch)              	//串口2发送字符
{
	while((USART2->SR&0X40)==0);//等待发送完毕   
	USART2->DR = (u8) ch; 
}
void USART1_Send(char *data)                	//串口1发送
{
	while(*data!=0)USART1_Putc(*(data++));
}
void USART1_Putc(char ch)              	//串口1发送字符
{
	while((USART1->SR&0X40)==0);//等待发送完毕   
	USART1->DR = (u8) ch; 
}




void process_recv(uint16_t v)
{
	
}

int u1RecvLen=0;

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 recvByte;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{  
		recvByte=USART_ReceiveData(USART1);
		if(recvByte=='\n')
		{
			uartRecvLen=u1RecvLen;
			if(u1RecvLen>1 && uartRecvBuf[u1RecvLen-1]=='\r')
			{
				uartRecvLen-=1;
			}
			u1RecvLen=0;
		}else{
			if(u1RecvLen>=UART1RECVSIZE)
			{
				u1RecvLen=0;
			}
			uartRecvBuf[u1RecvLen]=recvByte;
			u1RecvLen++;
		}
		
		/*if(Usart1Recv[0]==0){
			Usart1Cursor=0;
		}
		if(recvByte!='\n'){
			Usart1Recv[Usart1Cursor++]=recvByte;
		}else{
			Usart1Recv[Usart1Cursor]=0;
		}
		*/
	}
}




void USART2_IRQHandler(void)                	//??1??????
{
	u8 recvByte;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
	{
		recvByte=USART_ReceiveData(USART1);
		
		
	}
} 




