//
// 2014 Marcos Posada Hernández
//

#include <stdint.h>

#ifndef  __RECEPTOR_IR_H__
#define  __RECEPTOR_IR_H__

#define RECEPTOR_IR_QUEUE_SIZE      6   // Tamaño de la cola que almacena las teclas/repeticiones aún no "consumidas"

class ReceptorIR {
    public:
        // Tipos
        typedef unsigned long data_t;       // Tipo que retorna ReceptorIR::getData()
        typedef unsigned int repeats_t;     // Tipo que retorna ReceptorIR::getRepeats()

        // Inicializador
        static void begin(int8_t irqNumber, int8_t pinNumber); // Inicializa el receptor (indicar interrupción asociada y pin).

        static bool next();                                    // Retorna false si no hay una nueva tecla pulsada ni ninguna nueva repetición.
                                                               // Si hay una nueva tecla pulsada, o nuevas repeticiones, retorna true
                                                               // y actualiza los valores que retorna getData() y getRepeats().

        static ReceptorIR::data_t getData();                   // Obtiene el valor de la tecla pulsada.
                                                               // Nos dará siempre el mismo resultado mientras no se invoque a next().

        static ReceptorIR::repeats_t getRepeats();             // Obtiene en número de veces que se ha repetido la pulsación.
                                                               // siempre es 0 al inicio de la pulsación.
                                                               // Nos dará siempre el mismo resultado mientras no se invoque a next().
                                                              
        static void enable();                                  // Habilita la recepción.

        static void disable();                                 // Deshabilita la recepción.
                                                              
        static void setSensitive(bool sensitive);              // Hace que sea más o menos sensible a la primera repetición, descartándola o no.
                                                               // Por defecto es 'no sensible' y la descarta.

        static void setAlwaysPush(bool alwaysPush = true);     // Si el buffer se llena, establece si lo sobreescribe (true) o no (false).
                                                               // Por defecto lo sobreescribe (true).

        union ReceptorIRresultPacket {
            ReceptorIR::data_t data;
            struct {
                uint8_t command;
                uint8_t address;
            } __attribute__ ((packed));
        } __attribute__ ((packed));

    private:
        ReceptorIR(void);               // No se puede instanciar ningún objeto se trata de una case estática

        enum ReceptorIR_WAITING {
            WAIT_HIGH__START = 0,               // 0
            WAIT_LOW__START,                    // 1
            WAIT_HIGH__FIRST_MARK,              // 2
            WAIT_LOW__BIT_START,                // 3
            WAIT_HIGH__BIT_END,                 // 4
            WAIT_LOW__LAST_MARK,                // 5
            WAIT_HIGH__FIRST_REPEAT_START,      // 6
            WAIT_LOW__REPEAT_START,             // 7
            WAIT_HIGH__REPEAT_END,              // 8
            WAIT_LOW__REPEAT_END,               // 9
            WAIT_HIGH__NEXT_REPEAT_START        // 10
        };

        union ReceptorIRrawPacket {
            uint32_t rawPacket;
            struct {
                uint8_t address;
                uint8_t inv_address;
                uint8_t command;
                uint8_t inv_command;
            } __attribute__ ((packed));
        } __attribute__ ((packed));

        struct ReceptorIRpacketQueue {
            uint8_t address;
            uint8_t command;
            uint16_t repeats;
        } __attribute__ ((packed));

        // Constantes
        static const uint64_t TIME_DELTA            ;
        static const uint64_t TIME_DELTA2           ;
        static const uint64_t TIME_HIGH__START      ;
        static const uint64_t TIME_LOW__START       ;
        static const uint64_t TIME_HIGH__MARK       ;
        static const uint64_t TIME_LOW__ZERO        ;
        static const uint64_t TIME_LOW__ONE         ;
        static const uint64_t TIME_LOW__FIRST_REPEAT;
        static const uint64_t TIME_HIGH__REPEAT     ;
        static const uint64_t TIME_LOW__REPEAT      ;
        static const uint64_t TIME_LOW__NEXT_REPEAT ;

        // Atributos usados sólo por la interrupción
        static uint64_t time;
        static uint8_t brust;
        static uint64_t expectedTime;
        static ReceptorIR_WAITING waitingFor;
        static uint64_t IR_tiempoInicial;
        static uint64_t IR_tiempoActual;
        static uint8_t IR_bits;
        static ReceptorIRrawPacket IR_data;
        static bool sensitive;
        static bool isEnable;

        // Atributos usados dentro y fuera de la interrupción (han de ser volatile)
        static volatile uint8_t repeats;
        static volatile ReceptorIRpacketQueue packet;
        static volatile ReceptorIRpacketQueue queue[RECEPTOR_IR_QUEUE_SIZE];
        static volatile uint8_t inputIndex;
        static volatile uint8_t outputIndex;
        static volatile bool queueFull;
        static volatile bool isAlwaysPush;
        static volatile bool isSensitive;
        static volatile uint8_t pinNumber;

        static bool hasResult;
        static uint16_t resultRepeats;
        static bool inTime(uint64_t expected);
        static bool push();
        static ReceptorIRresultPacket resultData;
    public:
        static void interrupcionIR();       // El método de la interrupción ha de ser público


} __attribute__ ((packed));


#endif  // __RECEPTOR_IR_H__
