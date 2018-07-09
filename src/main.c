#include "LPC17xx.h"
#include "timers.h"
#include "config_pin.h"
#include <stdbool.h>
#include "gpio.h"

static unsigned long S_to_binary_(const char *s)
{
        unsigned long long i = 0;
        while (*s) {
                i <<= 1;
                i += *s++ - '0';
        }
        return i;
}

//void GPIO0_IRQHandler(void){					//naziv prekida pise u startup.s
//	LPC_GPIO_PIN_INT->FALL |= (1<<0);		//clear falling detection
//	
//	//prekidni potp.
//	
//	LPC_GPIO_PIN_INT->SIENF |= (0<<0);	//enable falling detection
//	return;
//}

////UART
//void uart_init(void){
//	
//	LPC_UART1->FCR |= 0x07;		// rx & tx buffer reset
//	LPC_UART1->LCR |= 0x83;		//8bit character, 1 stop bit, DLAB enabled
//	LPC_UART1->FDR |= 0x10;		//Set Multiple=1 & Divisor=0
//	LPC_UART1->DLL &= 0x0;		//set DLL to zero
//	LPC_UART1->DLL |= 0x30;		//DLL=48
//	LPC_UART1->DLM |= 0x5;		//DLM=5
//	LPC_UART1->LCR &= ~(1<<7);	//clear DLAB
//	
//	//prepare NVIC for uart interupts
//	
//	//enable uart interrupts
//	
//}

//void uart_sendChar(char ch){
//	while(!(LPC_UART1->LSR & 0x20));
//		LPC_UART1->THR=ch;
//}

int main()
{
	uint8_t i,j;
	bool ispravan_pinout[MAXPINS][MAXPINS]={false};
	bool *ispravan;
	
//	bool ocitani_pinout[MAXRED][MAXSTUPAC]={false};
//	bool *ocitani;
	
//	i=j=0;
	ispravan=&ispravan_pinout[0][0];
//	ocitani=&ocitani_pinout[0][0];
	

	SystemInit();           //Clock and PLL configuration 
	config_pin();
	timers_init();
//	uart_init();

//	// interrupt
////	LPC_SCU->PINTSEL0 |= (0x3)<<0 | (0x6)<<5;	//Gpio6[3] je odabran za interrupt0
////	LPC_GPIO_PIN_INT->ISEL |= (0<<0);					//1=low level sensitive, 0=edge sesititve; interrupt0 u PINTSEL0 registru
////	LPC_GPIO_PIN_INT->IENF |= (1<<0);					//enable interrupt on falling edge
////	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);			//brise pending da ne bi nakon Enable-a odmah usao u prekid ako je slucajno pending postavljen
////	NVIC_SetPriority(PIN_INT0_IRQn, 2);				//priority moraju biti parni brojevi, 0 najjaci
////	NVIC_EnableIRQ(PIN_INT0_IRQn);
while(1){
	for(i=0;i<5;i++){				//5 demuxa
		for(j=0;j<=7;j++){			//8 izlaza demuxa
			GPIO_PinWrite(LED_OK,1);						//zasto se sa MAXPINS=24, ne upali LED_OK, a aktivira se prvi pin i svijetli, timer opet ode u haurd fault, ali ne odmah nakon prve linije u clock updateu
			postavi_izlaz(j,i);
			ms_delay(200);
			read_inputs(i,j, i*5+j, ispravan);
		}
	GPIO_PinWrite(LED_OK,0);
	GPIO_PinWrite(OE1,1);
	GPIO_PinWrite(OE2,1);
	GPIO_PinWrite(OE3,1);
	GPIO_PinWrite(OE4,1);
	GPIO_PinWrite(OE5,1);
	ms_delay(200);
	}
}

//	while(1){
//		
//		uart_sendChar('a');
//		ms_delay(500);
//		uart_sendChar('b');
//		ms_delay(500);
//		uart_sendChar('c');
//		ms_delay(500);
//		
//	}
}
