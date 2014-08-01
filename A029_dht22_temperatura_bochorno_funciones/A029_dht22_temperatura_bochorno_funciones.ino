x//*
 * Lectura de temperatura y humedad con el sensor DHT-22. Avisa del bochorno.
 * 2014. Arduino Gran Canaria.
 */
#include <LiquidCrystal.h>
#include "DHT.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DHT dht(2, DHT22);
 
char buffer[10];
 
// Inicializacion del sistema
void setup() {
  lcd.begin(16, 2); // Inicializa LCD
  dht.begin(); // Inicializa sensor
}

// Bucle principal
void loop() {
  // Leer temperatura y humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Mostrar datos en LCD
  lcd.setCursor(0, 0);
  lcd.print(String("Humedad: ") + String(int(h)) + String("%")); 
  lcd.setCursor(0, 1);
  dtostrf(t, 3, 1, buffer); // Convertir temperatura en char
  lcd.print(String("Temp: ") + buffer + "C");
  
  // Aviso de bochorno
  float b = bochorno(t, h);
  if (b > 27.0) {
    lcd.setCursor(14, 1);
    lcd.print("B!");
  }
}

// Funcion bochorno
float bochorno(float t, float h) {
  // Formula extraida de: http://www.ehow.com/how_2090115_compute-heat-index.html
  // La sensacion de bochorno se da en condiciones de alta humedad y temperatura.
  // Hay cuatro niveles de bochorno: 27-32 (precaucion), 32-41, 41-54, >54 (extremo peligro).
  // Esta formula no es nada precisa. En http://en.wikipedia.org/wiki/Heat_index#Formula
  // hay otra mas precisa, pero bastante mas compleja. Para el presente ejercicio, usamos
  // esta.
  float p = ((6.112 * 10) * (7.5 * t) / (237.7 + t)) * (h/100);
  float hi = t + (5 / 9) * (p - 10); // Heat index (C)

  return hi;
}
