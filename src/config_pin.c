#include "lpc17xx.h"
#include "config_pin.h"

void config_pin(void){		//promjenit pinove, tj konf nove pinove
	
		//Pin Functions 00-gpio
	LPC_PINCON->PINSEL7 &= ~(0x3<<18);	//LED_OK  gpio P3.25
	LPC_PINCON->PINSEL7 &= ~(0x3<<20);	//LED_ERROR  P3.26
	
	LPC_PINCON->PINSEL4 &= ~(0x3<<14);	//OE1 P2.7
	LPC_PINCON->PINSEL4 &= ~(0x3<<16);	//OE2 P2.8
	LPC_PINCON->PINSEL4 &= ~(0x3<<18);	//OE3 P2.9
	LPC_PINCON->PINSEL4 &= ~(0x3<<20);	//OE4 P2.10
	LPC_PINCON->PINSEL4 &= ~(0x3<<22);	//OE5 P2.11
	
	LPC_PINCON->PINSEL0 &= ~(0x3<<0);		//A1	P0.0
	LPC_PINCON->PINSEL0 &= ~(0x3<<2);		//A2	P0.1
	LPC_PINCON->PINSEL0 &= ~(0x3<<4);		//A3	P0.2
	LPC_PINCON->PINSEL0 &= ~(0x3<<6);		//A4	P0.3
	LPC_PINCON->PINSEL0 &= ~(0x3<<8);		//A5	P0.4
	LPC_PINCON->PINSEL0 &= ~(0x3<<10); 	//A6	P0.5
	LPC_PINCON->PINSEL0 &= ~(0x3<<12);	//A7	P0.6
	LPC_PINCON->PINSEL0 &= ~(0x3<<14);	//A8	P0.7
	
	LPC_PINCON->PINSEL1 &= ~(0x3<<14);	//A9	P0.23
	LPC_PINCON->PINSEL1 &= ~(0x3<<16);	//A10	P0.24
	LPC_PINCON->PINSEL1 &= ~(0x3<<18);	//A11	P0.25
	LPC_PINCON->PINSEL1 &= ~(0x3<<20);	//A12	P0.26
	LPC_PINCON->PINSEL1 &= ~(0x3<<22);	//A13	P0.27
	LPC_PINCON->PINSEL1 &= ~(0x3<<24);	//A14	P0.28
	LPC_PINCON->PINSEL1 &= ~(0x3<<26);	//A15	P0.29
	LPC_PINCON->PINSEL1 &= ~(0x3<<28);	//A16	P0.30
	
	LPC_PINCON->PINSEL2 &= ~(0x3<<0);		//A17	P1.0
	LPC_PINCON->PINSEL2 &= ~(0x3<<2);		//A18	P1.1
	LPC_PINCON->PINSEL2 &= ~(0x3<<4);		//A19	P1.4
	LPC_PINCON->PINSEL2 &= ~(0x3<<16);	//A20	P1.8
	LPC_PINCON->PINSEL2 &= ~(0x3<<18);	//A21	P1.9
	LPC_PINCON->PINSEL2 &= ~(0x3<<20);	//A22	P1.10
	LPC_PINCON->PINSEL2 &= ~(0x3<<28);	//A23	P1.14
	//LPC_PINCON->PINSEL2 &= ~(0x3<<30);	//A24	P1.15		//warning: integer operation result is out of range
	LPC_PINCON->PINSEL2 &= 0xFFFFFFFC;	//A24	P1.15
	
	LPC_PINCON->PINSEL3 &= ~(0x3<<0);		//A25	P1.16
	LPC_PINCON->PINSEL3 &= ~(0x3<<2);		//A26	P1.17
	LPC_PINCON->PINSEL3 &= ~(0x3<<4);		//A27	P1.18
	LPC_PINCON->PINSEL3 &= ~(0x3<<6);		//A28	P1.19
	LPC_PINCON->PINSEL3 &= ~(0x3<<8);		//A29	P1.20
	LPC_PINCON->PINSEL3 &= ~(0x3<<10);	//A30	P1.21
	
	LPC_PINCON->PINSEL4 &= ~(0x3<<4);		//L1	P2.2
	LPC_PINCON->PINSEL4 &= ~(0x3<<6);		//L2	P2.3
	LPC_PINCON->PINSEL4 &= ~(0x3<<8);		//L3	P2.4
	LPC_PINCON->PINSEL4 &= ~(0x3<<10);	//L4	P2.5
	LPC_PINCON->PINSEL4 &= ~(0x3<<12);	//L5	P2.6
	
		//Pin mode
		// 10- ni pull-up ni pull-down
	LPC_PINCON->PINMODE7 |= (0x2)<<0;	//LED_OK
	LPC_PINCON->PINMODE7 |= (0x2)<<2;	//LED_ERROR
	
		//GPIO direction 0-input 1-output gpioPORT, svaki bit u tom registru je pin
	LPC_GPIO3->FIODIR |= (0x1)<<25;		//LED_OK    3.25
	LPC_GPIO3->FIODIR |= (0x1)<<26;		//LED_ERROR 3.26
	LPC_GPIO2->FIODIR |= (0x1)<<7;		//OE1 P2.7
	LPC_GPIO2->FIODIR |= (0x1)<<8;		//OE2 P2.8
	LPC_GPIO2->FIODIR |= (0x1)<<9;		//OE3 P2.9
	LPC_GPIO2->FIODIR |= (0x1)<<10;		//OE4 P2.10
	LPC_GPIO2->FIODIR |= (0x1)<<11;		//OE5 P2.11
	
	LPC_GPIO0->FIODIR |= (0x1)<<0;	//A1	P0.0
	LPC_GPIO0->FIODIR |= (0x1)<<1;	//A2	P0.1
	LPC_GPIO0->FIODIR |= (0x1)<<2;	//A3	P0.2
	LPC_GPIO0->FIODIR |= (0x1)<<3;	//A4	P0.3
	LPC_GPIO0->FIODIR |= (0x1)<<4;	//A5	P0.4
	LPC_GPIO0->FIODIR |= (0x1)<<5; 	//A6	P0.5
	LPC_GPIO0->FIODIR |= (0x1)<<6;	//A7	P0.6
	LPC_GPIO0->FIODIR |= (0x1)<<7;	//A8	P0.7
	LPC_GPIO0->FIODIR |= (0x1)<<8;	//A9	P0.23
	LPC_GPIO0->FIODIR |= (0x1)<<9;	//A10	P0.24
	LPC_GPIO0->FIODIR |= (0x1)<<10;	//A11	P0.25
	LPC_GPIO0->FIODIR |= (0x1)<<11;	//A12	P0.26
	LPC_GPIO0->FIODIR |= (0x1)<<12;	//A13	P0.27
	LPC_GPIO0->FIODIR |= (0x1)<<13;	//A14	P0.28
	LPC_GPIO0->FIODIR |= (0x1)<<14;	//A15	P0.29
	LPC_GPIO0->FIODIR |= (0x1)<<15;	//A16	P0.30
	
	LPC_GPIO1->FIODIR |= (0x1)<<0;	//A17	P1.0
	LPC_GPIO1->FIODIR |= (0x1)<<1;	//A18	P1.1
	LPC_GPIO1->FIODIR |= (0x1)<<4;	//A19	P1.4
	LPC_GPIO1->FIODIR |= (0x1)<<8;	//A20	P1.8
	LPC_GPIO1->FIODIR |= (0x1)<<9;	//A21	P1.9
	LPC_GPIO1->FIODIR |= (0x1)<<10;	//A22	P1.10
	LPC_GPIO1->FIODIR |= (0x1)<<14;	//A23	P1.14
	LPC_GPIO1->FIODIR |= (0x1)<<15;	//A24	P1.15
	LPC_GPIO1->FIODIR |= (0x1)<<16;	//A25	P1.16
	LPC_GPIO1->FIODIR |= (0x1)<<17;	//A26	P1.17
	LPC_GPIO1->FIODIR |= (0x1)<<18;	//A27	P1.18
	LPC_GPIO1->FIODIR |= (0x1)<<19;	//A28	P1.19
	LPC_GPIO1->FIODIR |= (0x1)<<20;	//A29	P1.20
	LPC_GPIO1->FIODIR |= (0x1)<<21;	//A30	P1.21
	
	LPC_GPIO2->FIODIR &= ~(0x1<<2);	//L1	P2.2		//prvo shiftaj pa onda invertiraj
	LPC_GPIO2->FIODIR &= ~(0x1<<3);	//L2	P2.3
	LPC_GPIO2->FIODIR &= ~(0x1<<4);	//L3	P2.4
	LPC_GPIO2->FIODIR &= ~(0x1<<5);	//L4	P2.5
	LPC_GPIO2->FIODIR &= ~(0x1<<6);	//L5	P2.6		//OE1 vise ne brise jer je sad 0x1 (prije 0x3 pa bi visi bit nakon shiftanja dosa na sedmo mjesto gdje je OE1)
	
		//SET GPIO to zero
	LPC_GPIO3->FIOCLR |= (0x1)<<25;
	LPC_GPIO3->FIOCLR |= (0x1)<<26;
	
	
	//SCU GPIO
  /*
	MODE - FUNC0 to FUNC7, 3b
	EPD - 0 disable pull-down, 1 enable
	EPUN - 0 enable pull-up, 1 disable
	EHS - 0 slow speed, 1 fast
	EZI - 0 disable input buffer, 1 enable
	ZIF - 0 enbale input glich filter, 1 disable
	*/	
//	//LED
//	LPC_SCU->SFSP9_4  |= (0x4)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO5[17]	LED1
//	LPC_SCU->SFSP9_3  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO4[15]	LED2

//	//IN
//	LPC_SCU->SFSP4_0  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[0]
//	LPC_SCU->SFSP4_1  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[1]
//	LPC_SCU->SFSP4_2  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[2]
//	LPC_SCU->SFSP4_3  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[3]
//	LPC_SCU->SFSP4_4  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[4]
//	LPC_SCU->SFSP4_5  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[5]
//	LPC_SCU->SFSP4_6  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[6]
//	LPC_SCU->SFSP5_7  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[7]
//	LPC_SCU->SFSP6_12 |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[8]
//	LPC_SCU->SFSP5_0  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[9]
//	LPC_SCU->SFSP5_1  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[10]
//	LPC_SCU->SFSP5_2  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[11]
//	LPC_SCU->SFSP5_3  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[12]  
//	LPC_SCU->SFSP5_4  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[13]  
//	LPC_SCU->SFSP5_5  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[14]  
//	LPC_SCU->SFSP5_6  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[15]  

//	//OUT
//	LPC_SCU->SFSP1_7  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[0]  
//	LPC_SCU->SFSP1_8  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[1]  
//	LPC_SCU->SFSP1_9  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[2]  
//	LPC_SCU->SFSP1_10 |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[3]  

//	// direction, 1 out, 0 in
//	LPC_GPIO_PORT->DIR[5] |= 1<<17 ;		//pin17 port5 je izlazni
//	LPC_GPIO_PORT->DIR[4] |= 1<<15 ;
//	LPC_GPIO_PORT->DIR[6] |= 1<<10 ;
//	LPC_GPIO_PORT->DIR[3] |= 1<<15 ;
//	
//	LPC_GPIO_PORT->DIR[2] &= ~(1<<12);	//pin12 port2 je ulazni
//	LPC_GPIO_PORT->DIR[2] &= ~(1<<13);
//	LPC_GPIO_PORT->DIR[2] &= ~(1<<14);
//	LPC_GPIO_PORT->DIR[2] &= ~(1<<15);
//	
//	LPC_GPIO_PORT->DIR[1] |= 1<<0 ;			//pin0 port1 je izlazni
//	LPC_GPIO_PORT->DIR[1] |= 1<<1 ;
//	LPC_GPIO_PORT->DIR[1] |= 1<<2 ;
//	LPC_GPIO_PORT->DIR[1] |= 1<<3 ;
//	
//	//UART
//	LPC_SCU->SFSPC_13  |= (0x2)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	//UART1_Tx
//	LPC_SCU->SFSPC_14  |= (0x2)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	//UART1_Rx
//	
}
