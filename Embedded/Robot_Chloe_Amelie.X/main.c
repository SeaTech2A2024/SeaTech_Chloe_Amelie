#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"
#include "main.h"


unsigned char stateRobot;


//void OperatingSystemLoop(void) {
//    switch (stateRobot) {
//        case STATE_ATTENTE:
//            timestamp = 0;
//            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
//            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
//            stateRobot = STATE_ATTENTE_EN_COURS;
//
//        case STATE_ATTENTE_EN_COURS:
//            if (timestamp > 1000)
//                stateRobot = STATE_AVANCE;
//            break;
//
//        case STATE_AVANCE:
//            PWMSetSpeedConsigne(5, MOTEUR_DROIT);
//            PWMSetSpeedConsigne(5, MOTEUR_GAUCHE);
//            stateRobot = STATE_AVANCE_EN_COURS;
//            break;
//        case STATE_AVANCE_EN_COURS:
//            SetNextRobotStateInAutomaticMode();
//            break;
//
//        case STATE_TOURNE_GAUCHE:
//            PWMSetSpeedConsigne(10, MOTEUR_DROIT);
//            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
//            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
//            break;
//        case STATE_TOURNE_GAUCHE_EN_COURS:
//            SetNextRobotStateInAutomaticMode();
//            break;
//
//        case STATE_TOURNE_DROITE:
//            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
//            PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
//            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
//            break;
//        case STATE_TOURNE_DROITE_EN_COURS:
//            SetNextRobotStateInAutomaticMode();
//            break;
//
//        case STATE_TOURNE_SUR_PLACE_GAUCHE:
//            PWMSetSpeedConsigne(10, MOTEUR_DROIT);
//            PWMSetSpeedConsigne(-10, MOTEUR_GAUCHE);
//            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
//            break;
//        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
//            SetNextRobotStateInAutomaticMode();
//            break;
//
//        case STATE_TOURNE_SUR_PLACE_DROITE:
//            PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
//            PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
//            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
//            break;
//        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
//            SetNextRobotStateInAutomaticMode();
//            break;
//
//        default:
//            stateRobot = STATE_ATTENTE;
//            break;
//    }
//}

//unsigned char nextStateRobot = 0;

////void SetNextRobotStateInAutomaticMode() {
////    unsigned char positionObstacle = PAS_D_OBSTACLE;
////
////    //D�termination de la position des obstacles en fonction des t�l�m�tres
////    if (robotState.distanceTelemetreDroit < 30 &&
////            robotState.distanceTelemetreCentre > 20 &&
////            robotState.distanceTelemetreGauche > 30) //Obstacle � droite
////        positionObstacle = OBSTACLE_A_DROITE;
////    else if (robotState.distanceTelemetreDroit > 30 &&
////            robotState.distanceTelemetreCentre > 20 &&
////            robotState.distanceTelemetreGauche < 30) //Obstacle � gauche
////        positionObstacle = OBSTACLE_A_GAUCHE;
////    else if (robotState.distanceTelemetreCentre < 20) //Obstacle en face
////        positionObstacle = OBSTACLE_EN_FACE;
////    else if (robotState.distanceTelemetreDroit > 30 &&
////            robotState.distanceTelemetreCentre > 20 &&
////            robotState.distanceTelemetreGauche > 30) //pas d?obstacle
////        positionObstacle = PAS_D_OBSTACLE;
////    
////    //D�termination de l?�tat � venir du robot
////    if (positionObstacle == PAS_D_OBSTACLE)
////        nextStateRobot = STATE_AVANCE;
////    else if (positionObstacle == OBSTACLE_A_DROITE)
////        nextStateRobot = STATE_TOURNE_GAUCHE;
////    else if (positionObstacle == OBSTACLE_A_GAUCHE)
////        nextStateRobot = STATE_TOURNE_DROITE;
////    else if (positionObstacle == OBSTACLE_EN_FACE)
////        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
////    //
////    else if (positionObstacle == OBSTACLE_TRES_GAUCHE)
////        nextStateRobot = STATE_TOURNE_DROITE;
////    else if (positionObstacle == OBSTACLE_TRES_DROITE)
////        nextStateRobot = STATE_TOURNE_GAUCHE;
////
////    //Si l?on n?est pas dans la transition de l?�tape en cours
////    if (nextStateRobot != stateRobot - 1)
////        stateRobot = nextStateRobot;
////}


//D�termination de la position des obstacles en fonction des t�l�m�tres 

//    //--------------------------Methode 1)----------------------------------

//void SetNextRobotStateInAutomaticMode() {
//    unsigned char positionObstacle = PAS_D_OBSTACLE;
//    

//    if (robotState.distanceTelemetreDroit < 30 &&
//            robotState.distanceTelemetreCentre > 20) //Obstacle � droite
//        positionObstacle = OBSTACLE_A_DROITE;
//    else if (robotState.distanceTelemetreGauche < 30 &&
//            robotState.distanceTelemetreCentre > 20) //Obstacle � gauche
//        positionObstacle = OBSTACLE_A_GAUCHE;
//   
//    else if (robotState.distanceTelemetreCentre < 35) //Obstacle en face
//        positionObstacle = OBSTACLE_EN_FACE;
//    
//    else if (robotState.distanceTelemetreGauchePlus < 20 &&
//            robotState.distanceTelemetreGauche > 10) //Obstacle � gauche
//        positionObstacle = OBSTACLE_TRES_GAUCHE;
//    else if (robotState.distanceTelemetreDroitPlus < 20 &&
//            robotState.distanceTelemetreDroit > 10) //Obstacle � gauche
//        positionObstacle = OBSTACLE_TRES_DROITE;
// 
//    else if (robotState.distanceTelemetreDroit > 30 &&
//            robotState.distanceTelemetreCentre > 30 &&
//            robotState.distanceTelemetreGauche > 30 &&
//            robotState.distanceTelemetreDroitPlus > 30 &&
//            robotState.distanceTelemetreGauchePlus > 30) //pas d?obstacle
//        positionObstacle = PAS_D_OBSTACLE;
//    
//    //D�termination de l?�tat � venir du robot
//    if (positionObstacle == PAS_D_OBSTACLE)
//        nextStateRobot = STATE_AVANCE;
//    else if (positionObstacle == OBSTACLE_A_DROITE)
//        nextStateRobot = STATE_TOURNE_GAUCHE;
//    else if (positionObstacle == OBSTACLE_A_GAUCHE)
//        nextStateRobot = STATE_TOURNE_DROITE;
//    else if (positionObstacle == OBSTACLE_EN_FACE)
//        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
//    //
//    else if (positionObstacle == OBSTACLE_TRES_GAUCHE)
//        nextStateRobot = STATE_TOURNE_DROITE;
//    else if (positionObstacle == OBSTACLE_TRES_DROITE)
//        nextStateRobot = STATE_TOURNE_GAUCHE;
//
//    //Si l?on n?est pas dans la transition de l?�tape en cours
//    if (nextStateRobot != stateRobot - 1)
//        stateRobot = nextStateRobot;

//}
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
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
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
            PWMSetSpeedConsigne(13, MOTEUR_DROIT); // speed a tester
            PWMSetSpeedConsigne(9, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_PEU_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_PEU_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_PEU_DROITE:
            PWMSetSpeedConsigne(9, MOTEUR_DROIT);
            PWMSetSpeedConsigne(13, MOTEUR_GAUCHE); //speed a tester
            stateRobot = STATE_TOURNE_PEU_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_PEU_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}

unsigned char nextStateRobot = 0;
unsigned int sensorState = 0b00000;

void SetNextRobotStateInAutomaticMode() {
    sensorState = 0;
    if (robotState.distanceTelemetreGauchePlus < 27)
        sensorState |= 0b10000;
    if (robotState.distanceTelemetreGauche < 32)
        sensorState |= 0b01000;
    if (robotState.distanceTelemetreCentre < 32)
        sensorState |= 0b00100;
    if (robotState.distanceTelemetreDroit < 32)
        sensorState |= 0b00010;
    if (robotState.distanceTelemetreDroitPlus < 27)
        sensorState |= 0b00001;

    //def next state robot
    switch (sensorState) {
        case 0b11111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11100:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b11011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11001:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11000:
            nextStateRobot = STATE_TOURNE_PEU_DROITE; //STATE_TOURNE_DROITE
            break;
        case 0b10111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b10110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b10101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b10100:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b10011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b10010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b10001:
            nextStateRobot = STATE_AVANCE;//;STATE_TOURNE_SUR_PLACE_DROITE // tester si ca marche
            break;
        case 0b10000:
            nextStateRobot = STATE_TOURNE_PEU_DROITE;
            break;
        case 0b01111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01110:
            nextStateRobot = STATE_TOURNE_DROITE; //STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b01101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01100:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b01011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01010:
            nextStateRobot = STATE_TOURNE_DROITE;//STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b01001:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01000:
            nextStateRobot = STATE_TOURNE_PEU_DROITE;//STATE_TOURNE_DROITE;
            break;
        case 0b00111:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b00110:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b00101:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b00100:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b00011:
            nextStateRobot = STATE_TOURNE_PEU_GAUCHE;//STATE_TOURNE_GAUCHE;
            break;
        case 0b00010:
            nextStateRobot = STATE_TOURNE_PEU_GAUCHE;//STATE_TOURNE_GAUCHE;
            break;
        case 0b00001:
            nextStateRobot = STATE_TOURNE_PEU_GAUCHE;
            break;
        case 0b00000:
            nextStateRobot = STATE_AVANCE; // tester si ca marche
            break;
    }
    //Si l?on n?est pas dans la transition de l?�tape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();

    /****************************************************************************************************/
    // Configuration des entr�es sorties
    /****************************************************************************************************/
    InitIO();
    InitTimer1();
    InitTimer23();
    InitTimer4();
    InitPWM();


    InitADC1();
    //PWMSetSpeed(30,MOTEUR_GAUCHE);
    //PWMSetSpeed(30,MOTEUR_DROIT);
    PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
    PWMSetSpeedConsigne(15, MOTEUR_DROIT);


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

            //                        if(robotState.distanceTelemetreGauche < 30)
            //                            LED_ORANGE = 1;
            //                        else
            //                            LED_ORANGE = 0;
            //                        
            //                        if(robotState.distanceTelemetreDroit < 30)
            //                            LED_BLANCHE = 1;
            //                        else
            //                            LED_BLANCHE = 0;
            //            //  cod� Droit => Droit plus
            //                        
            //                        if(robotState.distanceTelemetreCentre < 30)
            //                            LED_ORANGE = 1;
            //                        else
            //                            LED_ORANGE = 0;
            // cod� centre => droite

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