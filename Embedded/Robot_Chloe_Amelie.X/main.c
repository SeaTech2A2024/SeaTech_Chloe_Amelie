#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"

int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();

    /****************************************************************************************************/
    // Configuration des entrées sorties
    /****************************************************************************************************/
    InitIO();
    InitTimer1();
    InitTimer23();
    InitPWM();
    
    InitADC1();
    //PWMSetSpeed(30,MOTEUR_GAUCHE);
    //PWMSetSpeed(30,MOTEUR_DROIT);
    PWMSetSpeedConsigne(10,MOTEUR_GAUCHE);
    PWMSetSpeedConsigne(10,MOTEUR_DROIT);
    

    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;

    static int ADCValue0;
    static int ADCValue1;
    static int ADCValue2;
    
    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        if(ADCIsConversionFinished() == 1)//"ya un truc dans l'ADC"
        {
            
            ADCClearConversionFinishedFlag();//"On clear le flag software"
            unsigned int * result = ADCGetResult();
            ADCValue0 = result[0];
            ADCValue1 = result[1];
            ADCValue2 = result[2];
        }
//        LED_BLANCHE = !LED_BLANCHE;
//        LED_BLEUE = !LED_BLEUE;
//        LED_ORANGE = !LED_ORANGE;
    } // fin main
}
