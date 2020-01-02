#include "sys.h"
#include "joystick.h"
#include "hw_config.h"
#include "delay.h"
#include "usart.h"

void  Joystick_Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC2通道时钟
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	//AD1 A0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//AD1 A1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//AD1 A2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//AD1 A3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//AD1 A4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//AD1 A5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//使能复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束	
	ADC_StartCalibration(ADC1);	 //开启AD校准 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束 
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5 );
//	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//使能指定的ADC2的软件转换启动功能

}		

//获得ADC值
u16 Get_Adc1(u8 ch)   
{
	//设置指定ADC的规则组通道，一个序列，采样时间
	//ADC2,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC2的软件转换启动功能	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC2规则组的转换结果
}

u16 *Get_Axis_abs(u16 *num)
{
	
	num[1]=Get_Adc1(ADC_Channel_0);
	delay_ms(1);
	num[0]=Get_Adc1(ADC_Channel_1);
	delay_ms(1);
	num[2]=Get_Adc1(ADC_Channel_2);
	delay_ms(1);
	num[5]=Get_Adc1(ADC_Channel_3);
	delay_ms(1);
	num[4]=Get_Adc1(ADC_Channel_4);
	delay_ms(1);
	num[3]=Get_Adc1(ADC_Channel_5);
	delay_ms(1);
	
	return num;
}

/*
* Button GPIO, Axis ADC Init
*/
void Joystick_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	//使能时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//禁用jtag，需要使能AFIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	Joystick_Adc_Init();
}

void ButtonGronp1_Scan(){
	u8 i=0;
	u8 bit=0;
	Joystick_SaveBtnGroup(BTN_GROUP1,0);
	/* btn 0 - 4*/
	for(i=12;i<=15;i++){
		if(PBin(i)==0){
			Joystick_SaveBtn(BTN_GROUP1, bit, 1);
		}
		bit++;
	}
	/* btn 5 - 7 */
	for(i=3;i<=6;i++){
		if(PBin(i)==0){
			Joystick_SaveBtn(BTN_GROUP1, bit, 1);
		}
		bit++;
	}
}


void ButtonGronp2_Scan(){
	u8 i=0;
	u8 bit=0;
	Joystick_SaveBtnGroup(BTN_GROUP2,0);
		
	/* btn 8 - 10 */
	for(i=7;i<=9;i++){
		if(PBin(i)==0){
			Joystick_SaveBtn(BTN_GROUP2, bit, 1);
		}
		bit++;
	}
	/* btn 11 */
	if(PBin(0)==0){
		Joystick_SaveBtn(BTN_GROUP2, bit, 1);
	}
	bit++;
	/* btn 12 */
	if(PBin(1)==0){
		Joystick_SaveBtn(BTN_GROUP2, bit, 1);
	}
	bit++;
	/* btn 13 */
	if(PBin(10)==0){
		Joystick_SaveBtn(BTN_GROUP2, bit, 1);
	}
	bit++;
	/* btn 14 */
	if(PBin(11)==0){
		Joystick_SaveBtn(BTN_GROUP2, bit, 1);
	}
	bit++;
	/* btn 15 */
	if(PAin(8)==0){
		Joystick_SaveBtn(BTN_GROUP2, bit, 1);
	}
	bit++;
}

uint8_t Get_Button16(){
	return PBin(14);
}

void joystick_calibration(){
	int i,j,k;
	u16 axis[6];
		for(k=0;k<3;k++){
			for(i=0;i<6;i++)
				axis[i]=0;
			Joystick_SaveAxisArray(axis);
			Joystick_Send();
			delay_ms(20);
			j=4096;
			while(j>=0){
				for(i=0;i<6;i++)
					axis[i]=4096-j;
				Joystick_SaveAxisArray(axis);
				Joystick_Send();
				delay_ms(50);
				j-=100;
			}
			
			j=4096;
			while(j>=0){
				for(i=0;i<6;i++)
					axis[i]=j;
				Joystick_SaveAxisArray(axis);
				Joystick_Send();
				delay_ms(50);
				j-=100;
			}
		}
		for(i=0;i<6;i++)
			axis[i]=2048;
		Joystick_SaveAxisArray(axis);
		Joystick_Send();
		delay_ms(800);
		delay_ms(800);
}

