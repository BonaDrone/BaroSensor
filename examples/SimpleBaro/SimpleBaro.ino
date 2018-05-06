#include <Wire.h>
#include <MS5637.h>

MS5637 baro = MS5637();

void setup()
{
  Serial.begin(9600);
  baro.begin();
}

void loop()
{
  if(!baro.isOK()) {
    Serial.print("Sensor not Found/OK. Error: "); 
    Serial.println(baro.getError());
    baro.begin(); // Try to reinitialise the sensor if we can
  }
  else {
    Serial.print("Temperature: "); 
    Serial.println(baro.getTemperature());
    Serial.print("Pressure:    ");
    Serial.println(baro.getPressure());
  }
  delay(1000);
}
