#include "lpc17xx.h"
#include "logic.h"
#include "gpio.h"
#include "uart.h"
#include "timers.h"

uint8_t ocitani_pinout[MAXPINS][MAXPINS] = {0};
uint8_t ispravan_pinout[MAXPINS][MAXPINS] = {0};

void posalji_matricu (uint8_t* p){
	int i, j, flag;
	int stanje;
	
	uart_TxChar('$');									//pocetak
	for(i = 0; i < MAXPINS; i++){
		flag = 0;
		
		for(j = 0; j < MAXPINS; j++){
			
			stanje = *( p + i * MAXPINS + j );
			if(stanje){
				
				//ako postoji aktivirani pin, onda tek posalji ime tog reda
				if(!flag){
					uart_TxChar( i + '0' );
					uart_TxChar( '-' );
					flag = 1;
				}
				
				//posalji aktivirani pin
				uart_TxChar( j + '0' );
				uart_TxChar(',');
			}
		}
		if(flag){
			uart_TxChar( '#' );
		}
	}
	uart_TxChar( '\n' );
	uart_TxChar( '&' );			//zavrsetak
	return;
}

int dodaj_novi(void){
	
	uint8_t i,j;
	uint8_t ispravan_pinout[MAXPINS][MAXPINS] = {0};
	uint8_t *ispravan;
	
	ispravan = &ispravan_pinout[0][0];
	
	//saznaj ispravan pinout
	for(i = 0; i < 5; i++){					//5 demuxa
		for(j = 0; j < 8 ; j++){			//8 izlaza demuxa - adresa
			GPIO_PinWrite(LED_OK, 1);
			postavi_izlaz(i, j);
			//ms_delay( 1 );
			procitaj_ulaze(i * 8 + j, ispravan);
		}
	GPIO_PinWrite(LED_OK,0);
	GPIO_PinWrite(OE1,1);
	GPIO_PinWrite(OE2,1);
	GPIO_PinWrite(OE3,1);
	GPIO_PinWrite(OE4,1);
	GPIO_PinWrite(OE5,1);
	//ms_delay(1);
	}

	posalji_matricu(ispravan);
	
	uart_TxChar('.');
	uart_TxChar('.');
	uart_TxChar('.');
	uart_TxChar('\n');
	
	return 1;
	
}

void saznaj_ocitani(void){
	
	uint8_t i,j;
	uint8_t* ocitani;
	ocitani = &ocitani_pinout[0][0];
	
	//reset ocitane matrice na nula
	for(i = 0; i < MAXPINS; i++)
		for(j = 0; j < MAXPINS ; j++)
			*(ocitani + i * MAXPINS + j)=0;
	
	//saznaj ocitani pinout					//traje 40*80ms=3200ms=3,2sec
	for(i = 0; i < 5; i++){					//5 demuxa
		for(j = 0; j < 8 ; j++){			//8 izlaza demuxa - adresa
			GPIO_PinWrite(LED_OK, 1);
			postavi_izlaz(i, j);
			//ms_delay( 1 );
			procitaj_ulaze(i * 8 + j, ocitani);		//traje 80ms
		}
	GPIO_PinWrite(LED_OK,0);
	GPIO_PinWrite(OE1,1);
	GPIO_PinWrite(OE2,1);
	GPIO_PinWrite(OE3,1);
	GPIO_PinWrite(OE4,1);
	GPIO_PinWrite(OE5,1);
	//ms_delay(1);
	}
	return;
}

void primi_ispravan(void){
	
	char znak;
	uint8_t i, j;
	uint8_t red = 0, stupac = 0;
	uint8_t* ispravan;
	ispravan = &ispravan_pinout[0][0];
	
	//reset ispravne matrice na nula
	for(i = 0; i < MAXPINS; i++)
		for(j = 0; j < MAXPINS ; j++)
			*(ispravan + i * MAXPINS + j) = 0;
	
	//cekaj pocetak
	znak = uart_RxChar();
	while(znak != '$'){
		znak = uart_RxChar();
	}
	
	znak = uart_RxChar();			//dohvati znak nakon '$'
	red = znak - 48;					//prvi znak je neki red
	
	znak = uart_RxChar();
	while(znak != '&'){
		if (znak == '-'){
			znak = uart_RxChar();
			stupac = znak - 48;
		}
		else if (znak ==','){
			znak = uart_RxChar();
			if (znak != '#')
				stupac = znak - 48;
			else{
				znak = uart_RxChar();
				if (znak == '\n' || znak == '&')
					return;
				else{
					red = znak - 48;
					znak = uart_RxChar();
					continue;								//ako je znak red, onda ne upisuj dok ne pronadjes stupac
				}
			}
		}
		*(ispravan + red * MAXPINS + stupac) = 1;
		znak = uart_RxChar();
	}
	return;
}

int provjeri_pinout(void){
	
	uint8_t i,j,k;
	int rez = 1;
	uint8_t* ispravan;
	uint8_t* ocitani;
	ispravan = &ispravan_pinout[0][0];
	ocitani = &ocitani_pinout[0][0];
	
	primi_ispravan();
	
	for( k = 0; k < 1; k++){						// sporo !  cca 4sec za k=1, 36sec za k=10
		GPIO_PinWrite(LED_ERROR, 1);
		saznaj_ocitani();									// traje 3,2sec
	
		for(i = 0; i < MAXPINS; i++){
			for(j = 0; j < MAXPINS; j++){
				if ( (*(ispravan + i * MAXPINS + j)) != (*(ocitani + i * MAXPINS + j)) ){
					rez = 0;
					uart_TxChar(rez + 48);
					if( *(ocitani + i * MAXPINS + j) == 0 ){
						//no connection
						uart_TxChar('C');
						uart_TxChar( i + 1 );
						uart_TxChar( j + 1 );
					}
					else if( *(ocitani + i * MAXPINS + j) == 1 ){
						//short
						uart_TxChar('D');
						uart_TxChar( i + 1 );
						uart_TxChar( j + 1 );
					}
				}
			}
		}
		if (rez == 0){
			uart_TxChar('&');
			break;
		}
		GPIO_PinWrite(LED_ERROR, 0);
	}
	
	return rez;
}

int constant_test(void){			//ne detektira kratko odspajanje
	int i,j, rez;
	uint8_t* ispravan;
	uint8_t* ocitani;
	ispravan = &ispravan_pinout[0][0];
	ocitani = &ocitani_pinout[0][0];
	
	primi_ispravan();
	
	while(1){
	
	saznaj_ocitani();
	rez = 1;
	GPIO_PinWrite(LED_OK, 0);
	//usporedi i posalji greske
	for(i = 0; i < MAXPINS; i++){
			for(j = 0; j < MAXPINS; j++){
				if ( (*(ispravan + i * MAXPINS + j)) != (*(ocitani + i * MAXPINS + j)) ){
					if(rez != 0)
						uart_TxChar(0 + 48);
					rez = 0;
					if( *(ocitani + i * MAXPINS + j) == 0 ){
						//no connection
						uart_TxChar('C');
						uart_TxChar( i + 1 );
						uart_TxChar( j + 1 );
					}
					else if( *(ocitani + i * MAXPINS + j) == 1 ){
						//short
						uart_TxChar('D');
						uart_TxChar( i + 1 );
						uart_TxChar( j + 1 );
					}
				}
			}
	}
	GPIO_PinWrite(LED_OK, 1);
	if( rez == 0 ){
			GPIO_PinWrite(LED_OK, 0);
			GPIO_PinWrite(LED_ERROR, 1);
			uart_TxChar('&');
			break;
	}
	}
	
	return 0;
}
