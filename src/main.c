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
	int res;

	SystemInit();           //Clock and PLL configuration 
	config_pin();
	timers_init();
	uart_init(9600);

//	// interrupt
////	LPC_SCU->PINTSEL0 |= (0x3)<<0 | (0x6)<<5;	//Gpio6[3] je odabran za interrupt0
////	LPC_GPIO_PIN_INT->ISEL |= (0<<0);					//1=low level sensitive, 0=edge sesititve; interrupt0 u PINTSEL0 registru
////	LPC_GPIO_PIN_INT->IENF |= (1<<0);					//enable interrupt on falling edge
////	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);			//brise pending da ne bi nakon Enable-a odmah usao u prekid ako je slucajno pending postavljen
////	NVIC_SetPriority(PIN_INT0_IRQn, 2);				//priority moraju biti parni brojevi, 0 najjaci
////	NVIC_EnableIRQ(PIN_INT0_IRQn);


	//onemoguci sve demuxeve
	GPIO_PinWrite(OE1,1);
	GPIO_PinWrite(OE2,1);
	GPIO_PinWrite(OE3,1);
	GPIO_PinWrite(OE4,1);
	GPIO_PinWrite(OE5,1);
	
	while(1){
		odabir = uart_RxChar();
		while( odabir != 'A'  &&  odabir != 'B' )
			odabir = uart_RxChar();
		if( odabir == 'A' )
			res = dodaj_novi();
		else if ( odabir == 'B' )
			res = provjeri_pinout();
			uart_TxChar(res + 48);
	}

}
