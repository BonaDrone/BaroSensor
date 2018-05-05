#include <Wire.h>
#include <MS5637.h>

void setup()
{
  Serial.begin(9600);
  MS5637.begin();
}

void loop()
{
  if(!MS5637.isOK()) {
    Serial.print("Sensor not Found/OK. Error: "); 
    Serial.println(MS5637.getError());
    MS5637.begin(); // Try to reinitialise the sensor if we can
  }
  else {
    Serial.print("Temperature: "); 
    Serial.println(MS5637.getTemperature());
    Serial.print("Pressure:    ");
    Serial.println(MS5637.getPressure());
  }
  delay(1000);
}
