#include "lpc17xx.h"
#include <stdbool.h>
#include "gpio.h"

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
