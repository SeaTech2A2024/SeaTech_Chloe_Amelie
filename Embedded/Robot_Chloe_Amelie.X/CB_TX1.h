/* 
 * File:   CB_TX1.h
 * Author: TP_EO_6
 *
 * Created on 15 février 2024, 09:34
 */

#ifndef CB_TX1_H
#define	CB_TX1_H

void SendMessage(unsigned char*, int );
void CB_TX1_Add(unsigned char );
unsigned char CB_TX1_Get(void);
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void);
void SendOne();
unsigned char CB_TX1_IsTranmitting(void);
int CB_TX1_GetDataSize(void);
int CB_TX1_GetRemainingSize(void);

#endif	/* CB_TX1_H */

