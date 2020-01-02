#include "myspi.h"
#include "sys.h" 
#include "usart.h"

char *Spi1SendBuff="tes2323232323232t";
u8 Spi1ReadBuff[1024];
u16 Spi1ReadCnt=0;
u16 Spi1SendCnt=0;

void Spi1SlaveInit(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_RXNE,ENABLE);
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设 
	
}
void SPI1_SendData(char *data)
{
	Spi1SendBuff++;
	SPI1->DR=*Spi1SendBuff;
}  

void SPI1_IRQHandler(void)  
{  
	SPI1->DR=*Spi1SendBuff;
  if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) == SET)  
  {    
			printf("spi recv data\r\n");
			Spi1ReadCnt++;    
			Spi1ReadBuff[Spi1ReadCnt] = SPI1->DR;
  }
} 


