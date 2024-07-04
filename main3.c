#include"header.h"
int main()
{
				float adc_out,light;
        float vout,temp,True_voltage;
        uart0_init(9600);
        adc_init();
//        lcd_init();
        while(1)
        {
				// for the light printing
        vout=mcp3204_read(2);       //Channel 2 selected.
        True_voltage=((vout*5)/4095); //converting to the voltage correspondind value;
        light=100-((True_voltage*2)*10);
        uart0_tx_string("Light:");
        uart0_tx_float(light);
        uart0_tx('%');
        uart0_tx_string("\r\n");
//        lcd_cmd(0xC0);
//				lcd_string("LIGHT: ");
//        lcd_float(light);
//        lcd_string("V\r\n");
					
					
					
        //for the temperature printing.
        adc_out=adc_read(1); // channel 1 selected
        vout=(adc_out*3.3)/1023;
        temp=((vout-0.5)/0.01);
        uart0_tx_string("\r\nTemperature:");
        uart0_tx_float(temp);
        uart0_tx('c');
        uart0_tx_string("\r\n");
//        lcd_cmd(0x80);
//        lcd_string("TEMP:");
//        lcd_float(temp);
//        lcd_string("^C");


        delay_s(1);
//        lcd_cmd(0x01);        
				}
		
		
}
