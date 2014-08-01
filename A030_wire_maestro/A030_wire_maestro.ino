/*
 * Comunicacion con dos Arduinos. Biblioteca Wire.
 * MAESTRO. Usar en conjuncion con el maestro.
 */

#include <Wire.h>
int dirEsclavo = 4;

void setup()
{
  Wire.begin();
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(dirEsclavo);
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}
