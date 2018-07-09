#include "LPC17xx.h"
#include "timers.h"
#include "config_pin.h"
#include <stdbool.h>

#define  util_GetBitMask(bit)          ((uint32_t)1<<(bit))
#define  util_BitSet(x,bit)            ((x) |=  util_GetBitMask(bit))
#define  util_BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
#define  util_BitToggle(x,bit)         ((x) ^=  util_GetBitMask(bit))
#define  util_UpdateBit(x,bit,val)     ((val)? util_BitSet(x,bit): util_BitClear(x,bit))

#define  util_GetBitStatus(x,bit)      (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitSet(x,bit)          (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)

#define MAXRED 5
#define MAXSTUPAC	5
#define MAXPINS 20		//ima mjesta za 23 pina, onda radi (provjeriti), za 24 ne radi

#define LED_OK 			P3_25
#define LED_ERROR 	P3_26

#define A1	P0_0
#define A2	P0_1
#define A3	P0_2
#define A4	P0_3
#define A5	P0_4
#define A6	P0_5
#define A7	P0_6
#define A8	P0_7
#define A9	P0_23
#define A10	P0_24
#define A11	P0_25
#define A12	P0_26
#define A13	P0_27
#define A14	P0_28
#define A15	P0_29
#define A16	P0_30
#define A17 P1_0
#define A18 P1_1
#define A19 P1_4
#define A20 P1_8
#define A21 P1_9
#define A22 P1_10
#define A23 P1_14
#define A24 P1_15
#define A25 P1_16
#define A26 P1_17
#define A27 P1_18
#define A28 P1_19
#define A29 P1_20
#define A30 P1_21

#define OE1 P2_7
#define OE2 P2_8
#define OE3 P2_9
#define OE4 P2_10
#define OE5 P2_11

#define L1 P2_2
#define L2 P2_3
#define L3 P2_4
#define L4 P2_5
#define L5 P2_6

#define B(x) S_to_binary_(#x)

typedef enum
{
    P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10,P0_11,P0_12,P0_13,P0_14,P0_15,
    P0_16,P0_17,P0_18,P0_19,P0_20,P0_21,P0_22,P0_23,P0_24,P0_25,P0_26,P0_27,P0_28,P0_29,P0_30,P0_31,

    P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10,P1_11,P1_12,P1_13,P1_14,P1_15,
    P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23,P1_24,P1_25,P1_26,P1_27,P1_28,P1_29,P1_30,P1_31,

    P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10,P2_11,P2_12,P2_13,P2_14,P2_15,
    P2_16,P2_17,P2_18,P2_19,P2_20,P2_21,P2_22,P2_23,P2_24,P2_25,P2_26,P2_27,P2_28,P2_29,P2_30,P2_31,

    P3_0, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7, P3_8, P3_9, P3_10,P3_11,P3_12,P3_13,P3_14,P3_15,
    P3_16,P3_17,P3_18,P3_19,P3_20,P3_21,P3_22,P3_23,P3_24,P3_25,P3_26,P3_27,P3_28,P3_29,P3_30,P3_31,

    P4_0, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7, P4_8, P4_9, P4_10,P4_11,P4_12,P4_13,P4_14,P4_15,
    P4_16,P4_17,P4_18,P4_19,P4_20,P4_21,P4_22,P4_23,P4_24,P4_25,P4_26,P4_27,P4_28,P4_29,P4_30,P4_31,

    P_MAX,
    P_NC = 0xff
}gpioPins_et;

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

void GPIO_PinWrite(uint8_t pinNumber, uint8_t pinValue)
{

    uint8_t portNumber;
    LPC_GPIO_TypeDef *LPC_GPIO_PORT;
	if(pinNumber < P_MAX)               	//Handle the request only if it is in range
    {
        portNumber =  (pinNumber>>5);  		//Divide the pin number by 32 go get the PORT number
        pinNumber  =   pinNumber & 0x1f;  //lower 5-bits contains the bit number of a 32bit port  

        /* Go to particular port after decoding from the pin number and 
        update the value of the specified pin*/

        LPC_GPIO_PORT = (LPC_GPIO_TypeDef*)(LPC_GPIO_BASE + ((portNumber) << 5));

        if(pinValue!=0)
        {
            util_BitSet(LPC_GPIO_PORT->FIOSET,pinNumber);        
        }
        else
        {
            util_BitSet(LPC_GPIO_PORT->FIOCLR,pinNumber); 
        }
    }
}

uint8_t GPIO_PinRead(uint8_t pinNumber)
{
    uint8_t returnStatus = 0;
    uint8_t portNumber;
    LPC_GPIO_TypeDef *LPC_GPIO_PORT; 

    if(pinNumber < P_MAX)               //Handle the request only if it is in range
    {
        portNumber =  (pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
        pinNumber  =   pinNumber & 0x1f;  //lower 5-bits contains the bit number of a 32bit port  

        /* Go to particular port after decoding from the pin number and read the pins status */

        LPC_GPIO_PORT = (LPC_GPIO_TypeDef*)(LPC_GPIO_BASE + ((portNumber) << 5));    
        returnStatus = util_IsBitSet(LPC_GPIO_PORT->FIOPIN,pinNumber);
    }

    return returnStatus;
}

void postavi_ulaze(uint8_t adresa, uint8_t demux){
	uint8_t b0,b1,b2;
	
	b0=adresa&0x1;
	b1=adresa&0x2;
	b2=adresa&0x4;

	switch(demux){
		
		case 0: 
			GPIO_PinWrite(A16, b0);
			GPIO_PinWrite(A17, b1);
			GPIO_PinWrite(A18, b2);
			break;
		
		case 1: 
			GPIO_PinWrite(A19, b0);
			GPIO_PinWrite(A20, b1);
			GPIO_PinWrite(A21, b2);
			break;
		
		case 2: 
			GPIO_PinWrite(A22, b0);
			GPIO_PinWrite(A23, b1);
			GPIO_PinWrite(A24, b2);
			break;
		
		case 3: 
			GPIO_PinWrite(A25, b0);
			GPIO_PinWrite(A26, b1);
			GPIO_PinWrite(A27, b2);
			break;
		
		case 4: 
			GPIO_PinWrite(A28, b0);
			GPIO_PinWrite(A29, b1);
			GPIO_PinWrite(A30, b2);
			break;
	}
}

void read_inputs(uint8_t demux, uint8_t adresa, uint8_t aktivni_pin, bool *p){
	int i,j;
	uint8_t ulaz;
	
	for(i=0;i<5;i++){				//5 demuxa
		for(j=0;j<=7;j++){		//8 izlaza demuxa
			postavi_ulaze(j,i);
			switch(demux){
				case 0: ulaz=L1; break;
				case 1: ulaz=L2; break;
				case 2: ulaz=L3; break;
				case 3: ulaz=L4; break;
				case 4: ulaz=L5; break;
			}
			if(GPIO_PinRead(ulaz)==true)		//provjerit sta tocno vraca PinRead, da se zna s cim treba usporedit
					*(p+aktivni_pin*MAXPINS+i*5+j)=true;
		}
	}	
	return;
}

void postavi_izlaz(uint8_t adresa, uint8_t demux){
	uint8_t b0,b1,b2;
	
	b0=adresa&0x1;
	b1=adresa&0x2;
	b2=adresa&0x4;

	switch(demux){
		
		case 0: 
			GPIO_PinWrite(A1, b0);
			GPIO_PinWrite(A2, b1);
			GPIO_PinWrite(A3, b2);
			GPIO_PinWrite(OE1,0);
			break;
		
		case 1: 
			GPIO_PinWrite(A4, b0);
			GPIO_PinWrite(A5, b1);
			GPIO_PinWrite(A6, b2);
			GPIO_PinWrite(OE2,0);
			break;
		
		case 2: 
			GPIO_PinWrite(A7, b0);
			GPIO_PinWrite(A8, b1);
			GPIO_PinWrite(A9, b2);
			GPIO_PinWrite(OE3,0);
			break;
		
		case 3: 
			GPIO_PinWrite(A10, b0);
			GPIO_PinWrite(A11, b1);
			GPIO_PinWrite(A12, b2);
			GPIO_PinWrite(OE4,0);
			break;
		
		case 4: 
			GPIO_PinWrite(A13, b0);
			GPIO_PinWrite(A14, b1);
			GPIO_PinWrite(A15, b2);
			GPIO_PinWrite(OE5,0);
			break;
	}
}

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
