/*
 * Ejemplo Display LCD. Usa la mochila LCD 1602 con teclado (keypad), o bien la
 * pantalla LCD EL-1602A.
 * 2014. Arduino Gran Canaria.
 */

#include <LiquidCrystal.h>

// LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Mochila
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // EL-1602A

// Inicializacion del sistema
void setup() {
  // Inicializacion de Serial
  Serial.begin(9600);
  // Inicializacion del LCD (16 columnas y 2 filas)
  lcd.begin(16,2);
}

// Bucle principal
void loop() {
  // ¿Hay datos de monitor Serial?
  if (Serial.available()) {
    // Si hay datos, leerlos
    String datos = Serial.readString();
    // Mostrar datos en LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(datos);
  }
}
