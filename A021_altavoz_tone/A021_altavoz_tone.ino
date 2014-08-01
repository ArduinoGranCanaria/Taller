/*
 * Controlar un altavoz utilizando el monitor
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
#define pinSonido 8
String cadena;
float periodo = 50;
int periodo_entero;

// Inicializacion del sistema
void setup() {
  // Inicializar el pin de sonido como salida
  pinMode(pinSonido, OUTPUT);  
  // Inicializar Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // ¿Hay datos disponibles del monitor?
  if (Serial.available()) {
    // Leer entero desde el monitor
    periodo = Serial.parseInt();
  }
  // Tocar "periodo" en pinSonido
  tone(pinSonido, periodo);
}
