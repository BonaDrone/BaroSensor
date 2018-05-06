/*
 * This is a sketch for debugging any calibration issues with the MS5637 sensor.
 *
 * To use, Upload the sketch to the Arduino then open the Serial Monitor and set
 * the baud rate to 9600. A short list of calibration values and sample readings
 * will be displayed.
 */

#include <Wire.h>
#include <MS5637.h>

MS5637 baro = MS5637();

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialising sensor...");
  baro.begin();
  Serial.println("Outputting debug values:");
  baro.dumpDebugOutput();
  Serial.println("Done.");
}

void loop()
{
}
