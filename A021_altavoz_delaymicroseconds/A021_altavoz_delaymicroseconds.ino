/*
 * Controlar un altavoz utilizando un pin digital.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
#define pinSonido 8
float periodo;
int periodo_entero;

// Inicializacion del sistema
void setup() {
  // Inicializar el pin de sonido como salida
  pinMode(pinSonido, OUTPUT);  
}

// Bucle principal
void loop() {
  // Iniciamos el periodo a 50 microsegundos
  periodo = 50;
  while (periodo < 50000) {
    // Convertimos a entero el periodo. Si periodo fuera
    // entero, el aumento proporcional no se realizaria
    // correctamente, ya que se pierden los decimales.
    periodo_entero = int(periodo);
    // Activamos el pin de sonido
    digitalWrite(pinSonido, HIGH);
    // Hacemos una pausa (de t=periodo) en microsegundos
    delayMicroseconds(periodo_entero);
    // Desactivamos el pin de sonido
    digitalWrite(pinSonido, LOW);
    // Hacemos un pausa (t=periodo) en microsegundos
    delayMicroseconds(periodo_entero);
    // Aumentamos el periodo de forma proporcional
    periodo *= 1.001;
  }
}
