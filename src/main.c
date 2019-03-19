#include "LPC17xx.h"
#include "timers.h"
#include "config_pin.h"
#include <stdbool.h>
#include "gpio.h"
#include "uart.h"
#include "logic.h"

int main()
{
	char odabir;
	int res, i;

	SystemInit();           //Clock and PLL configuration 
	config_pin();
	timers_init();
	uart_init(115200);
	
		// interrupt
	LPC_SC->EXTINT = (1<<2);									//clear pending interrupts
	LPC_SC->EXTMODE |= (1<<2);								//edge sensitive interrupt EINT2
	LPC_SC->EXTPOLAR &= ~(1<<2);							//falling edge enable on P2.12
	NVIC_EnableIRQ(EINT2_IRQn);    						//Enable the EINT2 interrupt

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
