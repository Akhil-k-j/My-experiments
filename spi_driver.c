#include"header.h"

#define CS0 (1<<7)
#define SPIF ((S0SPSR>>7)&1)

void spi0_init(void)
{
	PINSEL0|=0x1500;     	//SPI0 pin functionality selected
	IODIR0|=CS0;					//Since we are using 1 GPIO, We need to set DIRECTION first
	IOSET0=CS0;						//When Direction is set, Automatically the pin become low, So we explicitely push to high using IOSET. Since we don't need to make the communiocation now.
	S0SPCR=0x20;					//CPOL=CPHA=0,Master mode,MSB,SPIO Intr disabled.
	S0SPCCR=15;	          //Clock set to 1 mbps // !!CLOCK SETTING SHOULD BE BASED ON CONSIDERING THE SLAVE MAX SUPPORTED SPEED!!
}	

u8 spi0(u8 data)
{
		S0SPDR=data;      //M->S
		while(SPIF==0);
		return S0SPDR;   //Will read and return the data  S->M
}

u32 mcp3204_read(u8 ch_num)
{
	u32 result=0;          //To store the 12 bit ADC result
	u8 byteH=0,byteL=0;		
	ch_num<<=6;           //Set the channel number to 6th and 7th bit.
	
	IOCLR0=CS0;         //CS0=0;
	spi0(0x6);					
	byteH=spi0(ch_num);
	byteL=spi0(0);
	IOSET0=CS0;       //CS0=1;
	
	byteH&=0x0F;      //=> byteH=byteH&0x0F;  Masking the required part
	result=(byteH<<8)|byteL;   //Merging the 12 bit result
	return result;
}
