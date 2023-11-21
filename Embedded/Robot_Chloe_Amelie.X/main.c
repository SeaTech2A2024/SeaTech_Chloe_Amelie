#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"

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

//    static int ADCValue0;
//    static int ADCValue1;
//    static int ADCValue2;
    
    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        if (ADCIsConversionFinished() == 1)
            {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [0])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            
            if(robotState.distanceTelemetreCentre < 30)
                LED_BLEUE = 1;
            else
                LED_BLEUE = 0;
            
            if(robotState.distanceTelemetreGauche < 30)
                LED_BLANCHE = 1;
            else
                LED_BLANCHE = 0;
            
            if(robotState.distanceTelemetreDroit < 30)
                LED_ORANGE = 1;
            else
                LED_ORANGE = 0;
            // gauche : gauche vu du robot (changement p/r code prof)
            }
        }
//        LED_BLANCHE = !LED_BLANCHE;
//        LED_BLEUE = !LED_BLEUE;
//        LED_ORANGE = !LED_ORANGE;
    } // fin main




// Partie 2.6 (dans while 1)
//if(ADCIsConversionFinished() == 1)//"ya un truc dans l'ADC"
//        {
//            
//            ADCClearConversionFinishedFlag();//"On clear le flag software"
//            unsigned int * result = ADCGetResult();
//            ADCValue0 = result[0];
//            ADCValue1 = result[1];
//            ADCValue2 = result[2];
//            if (ADCValue0 > 338)
//            {
//                LED_ORANGE = 1;
//            }
//            if (ADCValue0 < 338)
//            {
//                LED_ORANGE = 0;
//            }
//            if (ADCValue1 > 338)
//            {
//                 LED_BLEUE = 1;
//            }
//             if (ADCValue1 < 338)
//            {
//                 LED_BLEUE = 0;
//            }
//            if (ADCValue2 > 338)
//            {
//                LED_BLANCHE = 1;
//            }
//            if (ADCValue2 < 338)
//            {
//                LED_BLANCHE = 0;
//            }