#include "LPC17xx.h"
#include "timers.h"
#include "config_pin.h"
#include <stdbool.h>
#include "gpio.h"
#include "uart.h"
#include "logic.h"

//void GPIO0_IRQHandler(void){					//naziv prekida pise u startup.s
//	LPC_GPIO_PIN_INT->FALL |= (1<<0);		//clear falling detection
//	
//	//prekidni potp.
//	
//	LPC_GPIO_PIN_INT->SIENF |= (0<<0);	//enable falling detection
//	return;
//}

int main()
{
	char odabir;
	int res, i;

	SystemInit();           //Clock and PLL configuration 
	config_pin();
	timers_init();
	uart_init(115200);

	//onemoguci sve demuxeve
	GPIO_PinWrite(OE1,1);
	GPIO_PinWrite(OE2,1);
	GPIO_PinWrite(OE3,1);
	GPIO_PinWrite(OE4,1);
	GPIO_PinWrite(OE5,1);
	
	while(1){
		odabir = uart_RxChar();
		while( odabir != 'A'  &&  odabir != 'B' &&  odabir != 'C' )
			odabir = uart_RxChar();
		if( odabir == 'A' )
			res = dodaj_novi();
		else if ( odabir == 'B' )
			res = provjeri_pinout();
		else if ( odabir == 'C' )
			res = constant_test();
		if (res && odabir != 'C')
				uart_TxChar(res + 48);
	}

}
