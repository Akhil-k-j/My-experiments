#include"header.h"
int main()
{
	u32 temp,vout,light;
	lcd_init();
	spi0_init();
	while(1)
	{
	temp=mcp3204_read(2);
	vout=(temp*5)/4095;
	light=(5-vout)*100;
		lcd_cmd(0x80);
		lcd_string("Light:");
		lcd_data(temp);
		lcd_data('%');
		
	temp=mcp3204_read(0);
	vout=(temp*5)/4095;
		
		lcd_cmd(0xC0);
		lcd_string("Voltage:");
		lcd_float(temp);
		lcd_data('V');
		lcd_cmd(0x01);
	}
}


/*

#include"header.h"
#define LED (7<<17)
int main()
{
        u32 adc_out,i,light;
        float vout,temp,True_voltage;
        uart0_init(9600);
        adc_init();
        lcd_init();
        while(1)
        {
        //for the temperature printing.
        adc_out=adc_read(1); // channel 1 selected
        vout=(adc_out*3.3)/1023;
        temp=((vout-0.5)/0.01);
        uart0_tx_string("\r\nTemperature:");
        uart0_tx_float(temp);
        uart0_tx('c');
        uart0_tx_string("\r\n");
        lcd_cmd(0x80);
        lcd_string("TEMP:");
        lcd_float(temp);
        lcd_string("^C");

        // for the light printing
        vout=mcp3204_read(2);       //Channel 2 selected.
        True_voltage=((vout*5)/4095); //converting to the voltage correspondind value;
        light=(5-True_voltage)*100;
        uart0_tx_string("Light:");
        uart0_tx_float(light);
        uart0_tx('%');
        uart0_tx_string("\r\n");
        lcd_cmd(0xC0);
				lcd_string("LIGHT: ");
        lcd_float(light);
        lcd_string("V\r\n");
        delay_s(1);
        lcd_cmd(0x01);
        }
}
*/