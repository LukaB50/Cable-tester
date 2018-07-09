// dijelovi koda ako zatreba.

//LPC_GPIO3->FIOSET = (0x1)<<25;  
       //LPC_GPIO3->FIOSET = (0x1)<<26; 
		 	//LPC_GPIO3->FIOPIN |= 1<<25;
			//LPC_GPIO3->FIOPIN |= 1<<26;
			
//			for(i=B(000); i<=B(111); i+=B(001)){
//				a1=i&0x1;
//				a2=i&0x2;
//				a3=i&0x4;
//				GPIO_PinWrite(LED_OK,1);
//				GPIO_PinWrite(LED_ERROR,1);
//				GPIO_PinWrite(A1, a1);
//				GPIO_PinWrite(A2, a2);
//				GPIO_PinWrite(A3, a3);
//				GPIO_PinWrite(OE1,0);
//				
//				ms_delay(200);
//				
//				GPIO_PinWrite(LED_OK,0);
//				GPIO_PinWrite(LED_ERROR,0);
//				GPIO_PinWrite(OE1,1);
//				ms_delay(200);
				
       //LPC_GPIO3->FIOCLR = (0x1)<<25;
       //LPC_GPIO3->FIOCLR = (0x1)<<26;
			//LPC_GPIO3->FIOPIN &= ~(0x1)<<25;
			//LPC_GPIO3->FIOPIN &= ~(0x1)<<26;
			//GPIO_PinWrite(LED_OK, 0);
			
//void GPIO_PinWrite (uint32_t port_num, uint32_t pin_num, uint32_t val) {

//  val ? (LPC_GPIO(port_num)->SET = (1UL << pin_num)) : \
//        (LPC_GPIO(port_num)->CLR = (1UL << pin_num));
//}
