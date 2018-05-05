/*
 * This is a sketch for debugging any calibration issues with the MS5637 sensor.
 *
 * To use, Upload the sketch to the Arduino then open the Serial Monitor and set
 * the baud rate to 9600. A short list of calibration values and sample readings
 * will be displayed.
 */

#include <Wire.h>
#include <MS5637.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialising sensor...");
  MS5637.begin();
  Serial.println("Outputting debug values:");
  MS5637.dumpDebugOutput();
  Serial.println("Done.");
}

void loop()
{
}
