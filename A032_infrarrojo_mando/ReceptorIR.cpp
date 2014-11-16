
char foo; // Esta línes está añadida por sugerencia de Internet/Google

//
// 2014 Marcos Posada Hernández
//

#include <Arduino.h>
#include "ReceptorIR.H"

// Inicialización de las constantes de la clase
const uint64_t ReceptorIR::TIME_DELTA             =   150L;
const uint64_t ReceptorIR::TIME_DELTA2            =  5000L;
const uint64_t ReceptorIR::TIME_HIGH__START       =  9000L;
const uint64_t ReceptorIR::TIME_LOW__START        =  4500L;
const uint64_t ReceptorIR::TIME_HIGH__MARK        =   560L;
const uint64_t ReceptorIR::TIME_LOW__ZERO         =   560L;
const uint64_t ReceptorIR::TIME_LOW__ONE          =  1690L;
const uint64_t ReceptorIR::TIME_LOW__FIRST_REPEAT = 38500L; //42020L; // 40000L;
const uint64_t ReceptorIR::TIME_HIGH__REPEAT      =  9000L;
const uint64_t ReceptorIR::TIME_LOW__REPEAT       =  2250L;
const uint64_t ReceptorIR::TIME_LOW__NEXT_REPEAT  = 96500L; //98190L;

void ReceptorIR::begin(int8_t irqNumber, int8_t pinNumber) {
    ReceptorIR::pinNumber = pinNumber;
    pinMode(ReceptorIR::pinNumber, INPUT);     
    ReceptorIR::hasResult = false;
    ReceptorIR::resultData.data = ~((ReceptorIR::data_t) 0);           // Ponemos todos los bist del resultado a uno
    ReceptorIR::resultRepeats = 0;
    attachInterrupt(irqNumber, ReceptorIR::interrupcionIR, CHANGE);
}

void ReceptorIR::setSensitive(const bool sensitive) {
    ReceptorIR::isSensitive = sensitive;
};

void ReceptorIR::setAlwaysPush(const bool alwaysPush) {
    ReceptorIR::isAlwaysPush = alwaysPush;
};


bool ReceptorIR::next() {
    cli();
    if ((ReceptorIR::outputIndex != ReceptorIR::inputIndex) || (ReceptorIR::queueFull)) {
        // Hay datos en el buffer, los sacamos de él
        ReceptorIR::resultData.data = 0;            // Nos aseguramos de borrar todos los bits del union
        ReceptorIR::resultData.address = ReceptorIR::queue[ReceptorIR::outputIndex].address;
        ReceptorIR::resultData.command = ReceptorIR::queue[ReceptorIR::outputIndex].command;
        ReceptorIR::resultRepeats = ReceptorIR::queue[ReceptorIR::outputIndex].repeats;
        sei();
        // Si está llena y no se ha de meter, no hace nada
        ReceptorIR::queueFull = false;
        ReceptorIR::outputIndex++;
        if (ReceptorIR::outputIndex == RECEPTOR_IR_QUEUE_SIZE)
            ReceptorIR::outputIndex = 0;
        ReceptorIR::hasResult = true;
        return true;
    }
    if (ReceptorIR::packet.repeats) {
        ReceptorIR::resultData.data = 0;            // Nos aseguramos de borrar todos los bits del union
        ReceptorIR::resultData.address = packet.address;
        ReceptorIR::resultData.command = packet.command;
        ReceptorIR::resultRepeats = packet.repeats;
        ReceptorIR::packet.repeats = 0;
        sei();
        ReceptorIR::hasResult = true;
        return true;
    }
    sei();
    // Si llega a este punto, es que no hay datos
    if (ReceptorIR::hasResult) {
        // Antes sí habián datos, así que ahora que no los hay, los "borramos" por si nos los piden
        ReceptorIR::hasResult = false;
        ReceptorIR::resultData.data = ~((ReceptorIR::data_t) 0);           // Ponemos todos los bist del resultado a uno
        ReceptorIR::resultRepeats = 0;
    }
    return false;
}


ReceptorIR::data_t ReceptorIR::getData() {
    return ReceptorIR::resultData.data;
}

ReceptorIR::repeats_t ReceptorIR::getRepeats() {
    return ReceptorIR::resultRepeats;
}

/*

                                                        |
                                                      ? |______  
                                                               | WAIT_HIGH__START
                                                               |
                                                               |
                                                               |
                           TIME_HIGH__START        9000  ______|
                                                        |        WAIT_LOW__START
                                                        |
                                                        |
                           TIME_LOW__START         4500 |______
                                                               | WAIT_HIGH__FIRST_MARK
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__BIT_START
                           TIME_LOW__ZERO           560 |______
                                                               | WAIT_HIGH__BIT_END
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__BIT_START (*)
                                                        |
                           TIME_LOW__ONE           1690 |______
                                                               | WAIT_HIGH__BIT_END (*)
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__BIT_START (*)
                                                  =================
                                                        |______
                                                               | WAIT_HIGH__BIT_END (*)
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__BIT_START (*)
                                                        |
                           TIME_LOW__ONE           1690 |______
                                                               | WAIT_HIGH__BIT_END (*)
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__LAST_MARK
                                                        |
                                                        |
                                                        |
                                                        |
                           TIME_LOW__FIRST_REPEAT 42020 |______
                                                               | WAIT_HIGH__FIRST_REPEAT_START
                                                               |
                                                               |
                           TIME_HIGH__REPEAT       9000  ______| WAIT_LOW__REPEAT_START
                                                        |
                                                        |
                           TIME_LOW__REPEAT        2250 |______ 
                                                               | WAIT_HIGH__REPEAT_END
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__REPEAT_END
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                           TIME_LOW__NEXT_REPEAT  98190 |______
                                                               | WAIT_HIGH__NEXT_REPEAT_START
                                                               |
                                                               |
                           TIME_HIGH__REPEAT       9000  ______|
                                                        |        WAIT_LOW__REPEAT_START (*)
                                                        |
                           TIME_LOW__REPEAT        2250 |______ 
                                                               | WAIT_HIGH__REPEAT_END (*)
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__REPEAT_END (*)
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                                                        |
                           TIME_LOW__NEXT_REPEAT  98190 |______
                                                               | WAIT_HIGH__NEXT_REPEAT_START (*)
                                                               |
                                                               |
                           TIME_HIGH__REPEAT       9000  ______|
                                                        |        WAIT_LOW__REPEAT_START (*)
                                                        |
                           TIME_LOW__REPEAT        2250 |______ 
                                                               | WAIT_HIGH__REPEAT_END (*)
                           TIME_HIGH__MARK          560  ______|
                                                        |        WAIT_LOW__REPEAT_END (*)
                                                        |
                                                        |
                                                        |

    (*) Ya se ha pasado por este estado anteriormente

*/

// Inicialización de los atributos estáticos de la clase
uint64_t ReceptorIR::time = 0L;
uint8_t ReceptorIR::brust = 0;
uint64_t ReceptorIR::expectedTime = 0L;
ReceptorIR::ReceptorIR_WAITING ReceptorIR::waitingFor = ReceptorIR::WAIT_HIGH__START;
uint64_t ReceptorIR::IR_tiempoInicial = 0L;

uint64_t ReceptorIR::IR_tiempoActual = 0L;
ReceptorIR::ReceptorIRrawPacket ReceptorIR::IR_data;
volatile ReceptorIR::ReceptorIRpacketQueue ReceptorIR::queue[RECEPTOR_IR_QUEUE_SIZE];
volatile ReceptorIR::ReceptorIRpacketQueue ReceptorIR::packet;
volatile uint8_t ReceptorIR::inputIndex = 0;
volatile uint8_t ReceptorIR::outputIndex = 0;
volatile bool ReceptorIR::queueFull = false;
volatile bool ReceptorIR::isAlwaysPush = true;
volatile bool ReceptorIR::isSensitive = false;
volatile uint8_t ReceptorIR::pinNumber = 0;
bool ReceptorIR::sensitive = false;
bool ReceptorIR::isEnable = true;
uint8_t ReceptorIR::IR_bits = 0;
volatile uint8_t ReceptorIR::repeats = 0;
bool ReceptorIR::hasResult;
ReceptorIR::ReceptorIRresultPacket ReceptorIR::resultData;
uint16_t ReceptorIR::resultRepeats;


bool ReceptorIR::push() {
    // Si está llena y no se ha de meter, no hace nada
    if ((ReceptorIR::queueFull) && (!ReceptorIR::isAlwaysPush))
        return false;
    ReceptorIR::queue[ReceptorIR::inputIndex].address = packet.address;
    ReceptorIR::queue[ReceptorIR::inputIndex].command = packet.command;
    ReceptorIR::queue[ReceptorIR::inputIndex].repeats = packet.repeats;
    ReceptorIR::inputIndex++;
    if (ReceptorIR::inputIndex == RECEPTOR_IR_QUEUE_SIZE)
        ReceptorIR::inputIndex = 0;
    if (ReceptorIR::queueFull) {
        // Si la cola estaba llena y se ha metido un nuevo elemento, entonces se borra el primer elemento y continúa llena la cola
        ReceptorIR::outputIndex = ReceptorIR::inputIndex;
        return true;
    }
    // Si los punteros son iguales, entonces la cola está llena
    ReceptorIR::queueFull = (ReceptorIR::inputIndex == ReceptorIR::outputIndex);
    return true;
}

void ReceptorIR::disable() {
    ReceptorIR::isEnable = false;
}

void ReceptorIR::enable() {
    ReceptorIR::isEnable = true;
}

bool ReceptorIR::inTime(uint64_t expected) {
    if (ReceptorIR::time >= TIME_LOW__FIRST_REPEAT) {
    return ((ReceptorIR::time >= (expected - TIME_DELTA2)) && (ReceptorIR::time <= (expected + TIME_DELTA2)));
    }
    return ((ReceptorIR::time >= (expected - TIME_DELTA)) && (ReceptorIR::time <= (expected + TIME_DELTA)));
}

void ReceptorIR::interrupcionIR() {
    ReceptorIR::IR_tiempoActual = (uint64_t) micros();
    
    if (!isEnable) {
        return; // Está deshabilitado
    }

    // El sensor está a nivel HIGH cuando no detecta portadora, y a nivel LOW cuando detecta la ráfaga de la portadora (brust == HIGH))
    // Vamos, que está invertido
    ReceptorIR::brust = !digitalRead(ReceptorIR::pinNumber);

    ReceptorIR::time = ReceptorIR::IR_tiempoActual - ReceptorIR::IR_tiempoInicial;
    ReceptorIR::IR_tiempoInicial = ReceptorIR::IR_tiempoActual;

    if (ReceptorIR::brust) {
        // Detecta portadora

        switch (ReceptorIR::waitingFor) {

            case WAIT_HIGH__FIRST_MARK:
                ReceptorIR::expectedTime = TIME_LOW__START;
                ReceptorIR::waitingFor = WAIT_LOW__BIT_START;
                ReceptorIR::IR_data.rawPacket = 0;
                ReceptorIR::IR_bits = 0;
                ReceptorIR::repeats = 0;
                break;

            case WAIT_HIGH__FIRST_REPEAT_START:
                ReceptorIR::expectedTime = TIME_LOW__FIRST_REPEAT;
                ReceptorIR::waitingFor = WAIT_LOW__REPEAT_START;
                ReceptorIR::sensitive = ReceptorIR::isSensitive;
                break;

            case WAIT_HIGH__REPEAT_END:
                ReceptorIR::expectedTime = TIME_LOW__REPEAT;
                ReceptorIR::waitingFor = WAIT_LOW__REPEAT_END;
                ReceptorIR::repeats++;
                if (ReceptorIR::sensitive) {
                    ReceptorIR::packet.repeats++;
                }
                else {
                    ReceptorIR::sensitive = true;
                }

                break;

            case WAIT_HIGH__NEXT_REPEAT_START:
                ReceptorIR::expectedTime = TIME_LOW__NEXT_REPEAT;
                ReceptorIR::waitingFor = WAIT_LOW__REPEAT_START;
                break;

            case WAIT_HIGH__BIT_END:
                ReceptorIR::expectedTime = 0L;      // No hay que tratar después el tiempo que ha tardado ya que se trata ahora
                if (++ReceptorIR::IR_bits == 32) {
                    // Con el actuál ya se habrán leído los 32 bits, así que después sólo queda leer la marca final
                    ReceptorIR::waitingFor = WAIT_LOW__LAST_MARK;
                }
                else {
                    // Lo siguiente será leer otro bit
                    ReceptorIR::waitingFor = WAIT_LOW__BIT_START;
                }
                ReceptorIR::IR_data.rawPacket >>= 1;           // Damos entrada al bit (por defecto es cero)
                // if ((ReceptorIR::time >= (TIME_LOW__ONE - TIME_DELTA)) && (ReceptorIR::time <= (TIME_LOW__ONE + TIME_DELTA))) {
                if (ReceptorIR::inTime(TIME_LOW__ONE)) {
                    // Recibido un uno (ponemos a uno el bit que ha entrado)
                    ReceptorIR::IR_data.rawPacket |= ((uint32_t)1 << 31);
                    break;  // Ya tenemos el bit correcto
                }
                //if ((ReceptorIR::time >= (TIME_LOW__ZERO - TIME_DELTA)) && (ReceptorIR::time <= (TIME_LOW__ZERO + TIME_DELTA))) {
                if (ReceptorIR::inTime(TIME_LOW__ZERO)) {
                    // Recibido un cero (dejamos tal cual el bit que ha entrado)
                    break;  // Ya tenemos el bit correcto
                }
                // Si llega aquí, es que hay un error, tal vez sea el inicio de otra transmisión...
                // ... así que continuamos como si se estubiera esperando ese inicio...
            case WAIT_HIGH__START:
            default:                    // Por defecto, si se ha perdido el hilo, se epera una nueva transmisión
                ReceptorIR::expectedTime = 0L;     // El tiempo transcurrido, antes de ahora, es indiferente
                ReceptorIR::waitingFor = WAIT_LOW__START;
                if (ReceptorIR::packet.repeats) {
                    ReceptorIR::push();
                    ReceptorIR::packet.repeats = 0;
                }
                break;
        }

    }
    else {
        // No hay portadora

        switch (ReceptorIR::waitingFor) {

            case WAIT_LOW__BIT_START:
                ReceptorIR::expectedTime = TIME_HIGH__MARK;
                ReceptorIR::waitingFor = WAIT_HIGH__BIT_END;
                break;

            case WAIT_LOW__LAST_MARK:
                ReceptorIR::expectedTime = TIME_HIGH__MARK;
                ReceptorIR::waitingFor = WAIT_HIGH__FIRST_REPEAT_START;
                ReceptorIR::packet.address = IR_data.address;
                ReceptorIR::packet.command = IR_data.command;
                ReceptorIR::packet.repeats = 0;
                ReceptorIR::push();
                break;

            case WAIT_LOW__REPEAT_START:
                ReceptorIR::expectedTime = TIME_HIGH__REPEAT;
                ReceptorIR::waitingFor = WAIT_HIGH__REPEAT_END;
                break;

            case WAIT_LOW__REPEAT_END:
                ReceptorIR::expectedTime = TIME_HIGH__MARK;
                ReceptorIR::waitingFor = WAIT_HIGH__NEXT_REPEAT_START;
                break;

            case WAIT_LOW__START:
            default:                    // Por defecto, si se ha perdido el hilo, se epera una nueva transmisión
                ReceptorIR::expectedTime = TIME_HIGH__START;
                ReceptorIR::waitingFor = WAIT_HIGH__FIRST_MARK;
                if (ReceptorIR::packet.repeats) {
                    ReceptorIR::push();
                    ReceptorIR::packet.repeats = 0;
                }
                break;

        }

    }

    // La siguiente condición no se cumple si se ha recibido correctamente un bit o si se espera a que se termine de recibir WAIT_HIGH__START.
    if (ReceptorIR::expectedTime != 0L) {
        // Hay que verificar el tiempo transcurrido
        //if ((ReceptorIR::time >= (ReceptorIR::expectedTime - TIME_DELTA)) && (ReceptorIR::time <= (ReceptorIR::expectedTime + TIME_DELTA))) {
            if (ReceptorIR::inTime(ReceptorIR::expectedTime)) {
            // El tiempo transcurrido es el correcto, así que continuamos
            return;
        }
        // Si se llega a este punto, es que ha habido un error en la recepción
        if (ReceptorIR::brust) {
            // Como se ha detectado un error al pasar a nivel HIGH (con portadora) esperará a ver si se trata del comienzo de una nueva transmisión
            ReceptorIR::waitingFor = WAIT_LOW__START;
        }
        else {
            // Como se ha detectado un error al pasea al nivel LOW (sin portadora) verifica si es el comienzo de una transmisión
            //if ((ReceptorIR::time >= (TIME_HIGH__START - TIME_DELTA)) && (ReceptorIR::time <= (TIME_HIGH__START + TIME_DELTA))) {
            if (ReceptorIR::inTime(TIME_HIGH__START)) {
                // El tiempo transcurrido coincide con el comienzo de una trasnmisión, así que esperamos el siguiente pasa
                ReceptorIR::waitingFor = WAIT_HIGH__FIRST_MARK;
                return;
            }

            // No es el comienzo de la transmisión, así que esperará por un nuevo comienzo
            ReceptorIR::waitingFor = WAIT_HIGH__START;
        }
    }

}

