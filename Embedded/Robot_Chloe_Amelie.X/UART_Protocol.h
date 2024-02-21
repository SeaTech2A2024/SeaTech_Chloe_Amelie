/* 
 * File:   UART_Protocol.h
 * Author: TP_EO_6
 *
 * Created on 21 février 2024, 16:45
 */

#ifndef UART_PROTOCOL_H
#define	UART_PROTOCOL_H

unsigned char UartCalculateChecksum(int,int , unsigned char* );
void UartEncodeAndSendMessage(int,int , unsigned char*);
void UartDecodeMessage(unsigned char );
void UartProcessDecodedMessage(int ,int , unsigned char* );

#endif	/* UART_PROTOCOL_H */

