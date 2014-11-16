/* 

  Ejemplo recepción de infrarojos

  */

#include "ReceptorIR.H"
#include "codigos_mandos.h"

const int receptorPin = 2;   // el número del pin al que está conectado el receptor
const int receptorIRQ = 0;   // La interrupción 0 del Arduino UNO está asociada al pin 2
const int ledPin =  11;

ReceptorIR::data_t teclaPulsada;    // valor de la tecla pulsada

void setup() {
    pinMode(ledPin, OUTPUT);      
    ReceptorIR::begin(receptorIRQ, receptorPin); // Inicializamos el receptor de IR
}

void loop(){
    // Averiguar si ha una tecla pendiente de tratar
    if (ReceptorIR::next()) { // XXX IMPORTANTE XXX Esta condición ha de estar sola. Hemos de asegurar que se llama sí o sí.
        if (!ReceptorIR::getRepeats()) {  // Nos aseguramos que no sea una repetición
            teclaPulsada = ReceptorIR::getData();    // valor de la tecla pulsada

            if (teclaPulsada == HITACHI_RB6_REMOTE_KEY__NEXT) {     
                // turn LED on:    
                digitalWrite(ledPin, HIGH);  
            } 
            else if (teclaPulsada == HITACHI_RB6_REMOTE_KEY__PREV) {
                // turn LED off:
                digitalWrite(ledPin, LOW); 
            }
        }
    }
}


