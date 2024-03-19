#include <xc.h>
#include "UART_Protocol.h"
#include "UART.h"

unsigned char checksum = 0;

unsigned char UartCalculateChecksum(int msgFunction, int msgPayloadLength, unsigned char* msgPayload) {
    //Fonction prenant entree la trame et sa longueur pour calculer le checksum
    checksum = 0;
    checksum ^= 0xFE;
    checksum ^= (unsigned char) (msgFunction >> 8);
    checksum ^= (unsigned char) (msgFunction >> 0);
    checksum ^= (unsigned char) (msgPayloadLength >> 8);
    checksum ^= (unsigned char) (msgPayloadLength >> 0);
    for (int i = 0; i < msgPayloadLength; i++) {
        checksum ^= msgPayload[i];
    }
    return checksum;
}

void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, unsigned char* msgPayload) {
    //Fonction d?encodage et d?envoi d?un message
    unsigned char msgUart[msgPayloadLength + 6];
    int pos = 0;
    msgUart[pos++] = (unsigned char) (0xFE);
    msgUart[pos++] = (unsigned char) (msgFunction >> 8);
    msgUart[pos++] = (unsigned char) (msgFunction >> 0);
    msgUart[pos++] = (unsigned char) (msgPayloadLength >> 8);
    msgUart[pos++] = (unsigned char) (msgPayloadLength >> 0);
    for (int i = 0; i < msgPayloadLength; i++) {
        msgUart[pos++] = msgPayload[i];
    }
    msgUart[pos++] = (unsigned char) (UartCalculateChecksum(msgFunction, msgPayloadLength, msgPayload));
    SendMessageDirect(msgUart, pos);


}


int msgDecodedFunction = 0;
int msgDecodedPayloadLength = 0;
unsigned char msgDecodedPayload[128];
int msgDecodedPayloadIndex = 0;

typedef enum {
    Waiting,
    FunctionMSB,
    FunctionLSB,
    PayloadLengthMSB,
    PayloadLengthLSB,
    Payload,
    CheckSum
} StateReception;

StateReception rcvState = Waiting;

void UartDecodeMessage(unsigned char c) {
    //Fonction prenant en entree un octet et servant a reconstituer les trames
    switch (rcvState) {
        case Waiting:
            if (c == 0xFE)
                rcvState = FunctionMSB;
            break;
        case FunctionMSB:
            msgDecodedFunction = c << 8;
            rcvState = FunctionLSB;
            break;
        case FunctionLSB:
            msgDecodedFunction |= c << 0;
            rcvState |= PayloadLengthMSB;
            break;
        case PayloadLengthMSB:
            msgDecodedPayloadLength = c << 8;
            rcvState = PayloadLengthLSB;

            break;
        case PayloadLengthLSB:
            msgDecodedPayloadLength |= c << 0;
            rcvState |= Payload;

            if (msgDecodedPayloadLength == 0)
                rcvState = CheckSum;
            else if (msgDecodedPayloadLength >= 256)
                rcvState = Waiting;
            else {
                rcvState = Payload;
                msgDecodedPayloadIndex = 0;
            }
            break;
        case Payload:
            msgDecodedPayload[msgDecodedPayloadIndex] = c;
            msgDecodedPayloadIndex++;
            if (msgDecodedPayloadIndex >= msgDecodedPayloadLength)
                rcvState = CheckSum;
            break;
        case CheckSum:
        {
            unsigned char receivedChecksum = c;
            unsigned char calculatedChecksum = UartCalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);

            if (calculatedChecksum == receivedChecksum) {
//                Success, on a un message valide
                //ProcessDecodedMessage(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                rcvState = StateReception.Waiting;
                //                Debug.WriteLine("Youpi!");

            } else {
                rcvState = Waiting;
                //Debug.WriteLine("Mince !");
            }
        }
            break;
        default:
            rcvState = Waiting;
            break;
    }
}
//
//void UartProcessDecodedMessage(int function,int payloadLength, unsigned char* payload)
//{
////Fonction appelee apres le decodage pour executer l?action
////correspondant au message recu
//
//}
//*************************************************************************/
//Fonctions correspondant aux messages
//*************************************************************************/
