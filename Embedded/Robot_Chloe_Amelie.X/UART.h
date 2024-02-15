#ifndef UART_H
#define UART_H

void InitUART(void);
void SendMessageDirect(unsigned char*, int);
//void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);

#endif /* UART_H */