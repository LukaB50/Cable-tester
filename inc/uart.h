#ifndef __UART_H
#define __UART_H

#define SBIT_WordLenght    0x00u
#define SBIT_DLAB          0x07u
#define SBIT_FIFO          0x00u
#define SBIT_RxFIFO        0x01u
#define SBIT_TxFIFO        0x02u

#define SBIT_RDR           0x00u
#define SBIT_THRE          0x05u

void uart_init(uint32_t baudrate);
void uart_TxChar(char ch);
char uart_RxChar(void);

#endif
