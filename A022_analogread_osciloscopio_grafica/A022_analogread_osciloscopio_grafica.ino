/*
 * Osciloscopio de bajo coste. Muestra la grafica de voltaje.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
#define elementos 100
#define pinLectura 1
#define pinSonido 11

int valores[elementos];
int periodo;
int cols;
float voltaje;

// Inicializarion del sistema
void setup() {
  // Inicializar Serial
  Serial.begin(9600);
  // Inicializar pin Sonido
  pinMode(pinSonido, OUTPUT);
  // Tocar 
  analogWrite(pinSonido, 230);
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
    // Bucle de grafica. Muestra una barra de astericos en el
    // monitor, junto al valor leido por la entrada analogica
    for (int i = 0; i < elementos; i++) {
      // Convertir lectura de voltaje en columnas a imprimir
      cols = map(valores[i], 0, 1023, 0, 80);
      // Imprimir valor
      for (int n = 0; n < cols; n++) {
        Serial.print('*');
      }
      Serial.print(' ');
      Serial.print(valores[i]);
      Serial.println();
    }
  }
}
