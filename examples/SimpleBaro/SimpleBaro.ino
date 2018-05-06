#include <Wire.h>
#include <MS5637.h>

MS5637 baro = MS5637();
float temperature;
float pressure;

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
    baro.getTemperature(&temperature);
    baro.getPressure(&pressure); 
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Pressure:    ");
    Serial.println(pressure);
  }
  delay(1000);
}
