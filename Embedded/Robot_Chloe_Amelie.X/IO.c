/*
 * File:   IO.c
 */

#include <xc.h>
#include "IO.h"
#include "main.h"

void InitIO()
{
    // IMPORTANT : désactiver les entrées analogiques, sinon on perd les entrées numériques
    ANSELA = 0; // 0 desactive
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;
    ANSELG = 0;

    // Configuration des sorties

    //******* LED ***************************
    _TRISC10 = 0;  // LED Orange
    _TRISG6  = 0; //LED Blanche
    _TRISG7  = 0; // LED Bleue
    
    //****** Moteurs ************************
    _TRISB14 = 0;  // Pins B14 - MOTOR1_IN1
    _TRISB15  = 0; //Pins B15 - MOTOR1_IN2
    _TRISC6 = 0;  // Pins RC6 - MOTOR6_IN1
    _TRISC7  = 0; //Pins RC7 - MOTOR6_IN2
    
    // Configuration des entrées
    

    // Configuration des pins remappables    
    //*************************************************************
    // Unlock Registers
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & ~(1<<6)); 
    
    //Assignation des remappable pins
    _U1RXR = 0b0011000; //Remappe la RP24 sur l?éntre Rx1
    _RP36R = 0b00001; //Remappe la sortie Tx1 vers RP36

    //*************************************************************
    // Lock Registers
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON | (1<<6));
}
