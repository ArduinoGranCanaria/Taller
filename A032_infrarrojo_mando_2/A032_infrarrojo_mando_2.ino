/* 

  Ejemplo recepci�n de infrarojos

  */

#include "ReceptorIR.H"
#include "codigos_mandos.h"

const int receptorPin = 2;   // el n�mero del pin al que est� conectado el receptor
const int receptorIRQ = 0;   // La interrupci�n 0 del Arduino UNO est� asociada al pin 2
const int ledPin =  11;      // the number of the LED pin

ReceptorIR::data_t teclaPulsada;    // valor de la tecla pulsada (En este ejemplo no se usa)

bool conRepeticion = true;
bool pausa = false;

void setup() {
    Serial.begin(9600); 
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);      
    // Inicializamos el receptor de infrarrojos (por defecto es 'no sensible' y sobreescribe el buffer)
    ReceptorIR::begin(receptorIRQ, receptorPin); 
    //ReceptorIR::setSensitive(true); 
}

void loop(){
    if (pausa) {
        delay(1000);
    }
    if (ReceptorIR::next()) { // XXX IMPORTANTE XXX Esta condici�n ha de estar sola. Hemos de asegurar que se llama s� o s�.
        if (conRepeticion || !ReceptorIR::getRepeats()) { // Comentar �true ||� para que no tenga en cuenta las repeticiones
            switch (ReceptorIR::getData()) {
                case HITACHI_RB6_REMOTE_KEY__NEXT:
                case EXAMPLE_REMOTE_KEY__TRACK_PLUS:
                case 0x8710:
                    // turn LED on:    
                    digitalWrite(ledPin, HIGH);  
                    Serial.println("ON");
                    break;
                case HITACHI_RB6_REMOTE_KEY__PREV:
                case EXAMPLE_REMOTE_KEY__TRACK_MINUS:
                case 0x871A:
                    // turn LED off:
                    digitalWrite(ledPin, LOW); 
                    Serial.println("Off");
                    break;
                case HITACHI_RB6_REMOTE_KEY__POWER:
                case EXAMPLE_REMOTE_KEY__POWER:
                case 0x8712:
                    // change LED:
                    digitalWrite(ledPin, !digitalRead(ledPin)); 
                    Serial.println("Cambio");
                    break;
                case HITACHI_RB6_REMOTE_KEY__TIME_SET:
                case EXAMPLE_REMOTE_KEY__MENU:
                case 0x8715:
                    if (!ReceptorIR::getRepeats()) { // Si se trata de una repetici�n no la tenemos en cuenta
                        // Habilitamos/deshabilitamos la repetici�n
                        conRepeticion = !conRepeticion;
                        Serial.println(conRepeticion ? "Repitiendo" : "Sin repetir");
                    }
                    break;
                case HITACHI_RB6_REMOTE_KEY__VOLUME_PLUS:
                case EXAMPLE_REMOTE_KEY__VOL_PLUS:
                case 0x870D:
                    // Sensible con la primera repetici�n
                    ReceptorIR::setSensitive(true);
                    Serial.println("Sensible");
                    break;
                case HITACHI_RB6_REMOTE_KEY__VOLUME_MINUS:
                case EXAMPLE_REMOTE_KEY__VOL_MINUS:
                case 0x870E:
                    // No sensible con la primera repetici�n
                    ReceptorIR::setSensitive(false);
                    Serial.println("Insensible");
                    break;
                case HITACHI_RB6_REMOTE_KEY__SLEEP:
                case EXAMPLE_REMOTE_KEY__MODE:
                case 0x8725:
                    // Activa/desactiva la pausa de 1 segundo
                    pausa = !pausa;
                    Serial.println(pausa ? "Esperando un segundo" : "Sin esperas");
                    break;
                default:
                    Serial.print("Tecla: 0x");
                    Serial.print(ReceptorIR::getData(), HEX);
                    if (ReceptorIR::getRepeats()) {
                        Serial.print("  Repeticiones: ");
                        Serial.print(ReceptorIR::getRepeats());
                    }
                    Serial.println("");
                    break;
            }
        }
    }
}


