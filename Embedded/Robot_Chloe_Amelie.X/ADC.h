/* 
 * File:   ADC.h
 * Author: TP-EO-1
 *
 * Created on 16 novembre 2023, 10:24
 */

#ifndef ADC_H
#define	ADC_H

void InitADC1(void);
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void);
void ADC1StartConversionSequence();
void ADCClearConversionFinishedFlag(void);
unsigned int * ADCGetResult(void);
unsigned char ADCIsConversionFinished(void);

#endif	/* ADC_H */

