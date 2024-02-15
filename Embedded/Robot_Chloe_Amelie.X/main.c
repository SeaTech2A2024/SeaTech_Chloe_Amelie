#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"
#include "main.h"
#include "UART.h"
#include "CB_TX1.h"
#include "CB_RX1.h"


unsigned char stateRobot;





//------------------------------------------------------------------------------

// ------------------------------ Methode 2 ------------------------------------

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;
            

        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;

        case STATE_AVANCE:
            PWMSetSpeedConsigne(25, MOTEUR_DROIT);
            PWMSetSpeedConsigne(25, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            timestampBloc = timestamp;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            timestampBloc = timestamp;
            break;

        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(10, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(10, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-10, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(-10, MOTEUR_DROIT);
            PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_PEU_GAUCHE:
            PWMSetSpeedConsigne(15, MOTEUR_DROIT); // speed a tester
            PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_PEU_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_PEU_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_PEU_DROITE:
            PWMSetSpeedConsigne(10, MOTEUR_DROIT);
            PWMSetSpeedConsigne(15, MOTEUR_GAUCHE); //speed a tester
            stateRobot = STATE_TOURNE_PEU_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_PEU_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
            
        case STATE_IMPASSE:
            
            PWMSetSpeedConsigne(-12, MOTEUR_DROIT);
            PWMSetSpeedConsigne(12, MOTEUR_GAUCHE);
            
           
        
             if ((timestamp-timestampTourne) > 1000){
                  stateRobot = STATE_AVANCE;
                }
            break;
       
                    
        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}

unsigned char nextStateRobot = 0;
unsigned int sensorState = 0b000000;

void SetNextRobotStateInAutomaticMode() {
    sensorState = 0;
    if (robotState.distanceTelemetreGauchePlus < 29)
        sensorState |= 0b100000;
    if (robotState.distanceTelemetreGauche < 32)
        sensorState |= 0b010000;
    if (robotState.distanceTelemetreCentre < 32)
        sensorState |= 0b001000;
    if (robotState.distanceTelemetreDroit < 32)
        sensorState |= 0b000100;
    if (robotState.distanceTelemetreDroitPlus < 29)
        sensorState |= 0b000010;
    if ((timestamp-timestampBloc) >= 4000){
        sensorState |= 0b000001;
        timestampTourne = timestamp;
    }

    //def next state robot
    switch (sensorState) {
        case 0b111110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b111100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b111010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b111000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b110110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b110100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b110010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b110000:
            nextStateRobot = STATE_TOURNE_DROITE; //STATE_TOURNE_PEU_DROITE; //STATE_TOURNE_DROITE
            break;
        case 0b101110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b101100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b101010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b101000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b100110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b100100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b100010:
            nextStateRobot = STATE_AVANCE;//;STATE_TOURNE_SUR_PLACE_DROITE // tester si ca marche
            break;
        case 0b100000:
            nextStateRobot = STATE_TOURNE_PEU_DROITE;
            break;
        case 0b011110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b011100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE; //STATE_TOURNE_DROITE; //STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b011010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b011000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
            
        case 0b010110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b010100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;//STATE_TOURNE_DROITE;//STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b010010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b010000:
            nextStateRobot = STATE_TOURNE_DROITE; //STATE_TOURNE_PEU_DROITE;//STATE_TOURNE_DROITE;
            break;
        case 0b001110:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b001100:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b001010:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b001000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b000110:
            nextStateRobot = STATE_TOURNE_GAUCHE; //STATE_TOURNE_PEU_GAUCHE;//STATE_TOURNE_GAUCHE;
            break;
        case 0b000100:
            nextStateRobot = STATE_TOURNE_GAUCHE;//STATE_TOURNE_PEU_GAUCHE;//STATE_TOURNE_GAUCHE;
            break;
        case 0b000010:
            nextStateRobot = STATE_TOURNE_PEU_GAUCHE;
            break;
        case 0b000000:
            nextStateRobot = STATE_AVANCE; // tester si ca marche
            break;
            
        // impasse
        case 0b111111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b111101:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b111011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b111001:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b110111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b110101:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b110011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b110001:
            nextStateRobot = STATE_IMPASSE; //STATE_TOURNE_DROITE
            break;
        case 0b101111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b101101:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b101011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b101001:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b100111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b100101:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b100011:
            nextStateRobot = STATE_IMPASSE;//;STATE_TOURNE_SUR_PLACE_DROITE // tester si ca marche
            break;
        case 0b100001:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b011111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b011101:
            nextStateRobot = STATE_IMPASSE; //STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b011011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b011001:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b010111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b010101:
            nextStateRobot = STATE_IMPASSE;//STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b010011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b010001:
            nextStateRobot = STATE_IMPASSE;//STATE_TOURNE_DROITE;
            break;
        case 0b001111:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b001101:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b001011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b001001:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b000111:
            nextStateRobot = STATE_IMPASSE;//STATE_TOURNE_GAUCHE;
            break;
        case 0b000101:
            nextStateRobot = STATE_IMPASSE;//STATE_TOURNE_GAUCHE;
            break;
        case 0b000011:
            nextStateRobot = STATE_IMPASSE;
            break;
        case 0b000001:
            nextStateRobot = STATE_IMPASSE; // tester si ca marche
            break;   
            
    }
    //Si l?on n?est pas dans la transition de l?étape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
    
    //Si le robot est bloqué
   
    
}

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
    InitTimer4();
    InitPWM();


    InitADC1();
    
    InitUART();
    //PWMSetSpeed(30,MOTEUR_GAUCHE);
    //PWMSetSpeed(30,MOTEUR_DROIT);
    PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
    PWMSetSpeedConsigne(15, MOTEUR_DROIT);


    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;


    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [1])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [4])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [3])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauchePlus = 34 / volts - 5;
            volts = ((float) result [0])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroitPlus = 34 / volts - 5;    
        }
//        SendMessage((unsigned char*) "hi",2);
////        SendMessageDirect((unsigned char*) "Bonjour", 7);
//        __delay32(4000000);
        
        int i;
        for(i=0; i< CB_RX1_GetDataSize(); i++)
        {
            unsigned char c = CB_RX1_Get();
            SendMessage(&c,1);
        }
        __delay32(10000);
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