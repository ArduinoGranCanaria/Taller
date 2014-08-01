/*
 * Osciloscopio de bajo coste. Muestra la grafica de voltaje.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
#define elementos 100
#define pinLectura 1

int valores[elementos];
int periodo;
int cols;

// Inicializarion del sistema
void setup() {
  // Inicializar Serial
  Serial.begin(9600);
}


// Bucle principal
void loop() {
  // Si hay datos para leer en el monitor, leer
  if (Serial.available()) {
    // Leemos un valor entero
    periodo = Serial.parseInt();
    // Bucle de lectura de voltaje
    for (int i = 0; i < elementos; i++) {
      // Leemos voltaje
      valores[i] = analogRead(pinLectura);
      // Realizamos una pausa. t=periodo (microsegundos)
      delayMicroseconds(periodo);
    }
    // Bucle de grafica
    for (int i = 0; i < elementos; i++) {
      // Convertir lectura de voltaje en columnas a imprimir
      cols = map(valores[i], 0, 150, 0, 50);
      // Imprimir valor
      for (int n = 0; n < cols; n++) {
        Serial.print('*');
      }
      Serial.println();
    }
  }
}