# MS5637 Library

This is an Arduino Library for the Freetronics BARO module, which is based around the Measurement Specialties MS5637-02BA03 Altimeter/Pressure sensor.

For help downloading and installing this Library, see our guide [How to Install Arduino Libraries](http://www.freetronics.com/pages/how-to-install-arduino-libraries).

For a simple example sketch that prints the temperature and pressure, launch Arduino IDE and choose File -> Examples -> BaroSensor -> SimpleBaro.


# Known Issues

* When using Arduino Due or compatible under Arduino 1.5, up to and including version 1.5.6, the Wire library does not return error codes for bad i2c communications. This is not a problem on other AVR-based Arduinos. On the Due platform you should check responses to make sure they're within expected ranges. We expect this bug to be fixed in the next Arduino 1.5 beta release after 1.5.6.

# All Available Functions

Assuming the class has been instantiated and given the name `baro`:

    MS5637 baro = MS5637();

## begin()

Usage:

    baro.begin()

Call this in the `setup()` part of your sketch to initialise the BARO module. If the module later returns any errors for some reason, calling `begin()` again will reset it.

## getTemperature()

Takes a temperature reading and assigns it as the value of the reference passed as argument. Returns `true` if the reading was successful and `false` otherwise.

### Function signature:

    bool getTemperature(float * temperature, TempUnit scale = CELSIUS,
                         BaroOversampleLevel level = OSR_8192);

### Basic Usage:

    float temperature;
    baro.getTemperature(& temperature);

### Advanced Usage:

    float temperature;
    baro.getTemperature(& temperature, FAHRENHEIT, OSR_1024);

### Arguments:

* `& temperature` is a reference to the variable where the temperature value
  will be stored.
* `scale` default to CELSIUS but can be set to FAHRENHEIT if needed.
* `level` specifies the oversampling level of the sensor. Higher
  oversampling means higher accuracy but a slower reading. OSR_8192 is
  the default and gives highest accuracy, however
  a temperature reading takes 17 milliseconds. OSR_256 is the lowest
  accuracy, a temperature reading takes 1 millisecond. Intermediate
  values are OSR_512, OSR_1024, OSR_2048, OSR_4096.

### Returns

A boolean value. `true` if the reading was successful and `false` otherwise.

## getPressure()

Takes a pressure reading and assigns it as the value of the reference passed as argument. Returns `true` if the reading was successful and `false` otherwise.

### Function signature:

    float getPressure(float * pressure, BaroOversampleLevel level = OSR_8192);

### Basic Usage:

    float pressure;
    baro.getPressure(& pressure);

### Advanced Usage:

     float pressure;
     baro.getPressure(& pressure, OSR_8192);

### Arguments

* `& pressure` references the address where the pressure value is to be stored.
* `level` specifies the oversampling level of the sensor. Higher
  oversampling means higher accuracy but a slower reading. OSR_8192 is
  the default and gives highest accuracy, however a pressure reading
  takes 34 milliseconds. OSR_256 is the lowest accuracy, a pressure
  reading takes 2 milliseconds. Intermediate values are OSR_512,
  OSR_1024, OSR_2048, OSR_4096.

### Returns

A boolean value. `true` if the reading was successful and `false` otherwise.

## getTempAndPressure()

This function allows you to read both temperature and pressure in one
pass. This saves some overhead because a call to `getPressure()` has
to read the temperature as well, but this value is not usually
returned.

Execution time is roughly the same as the `getPressure` function.

The temperature and pressure variables are passed in as pointers to
the function. The result of the function is a boolean value, `true` for
success.

### Function Signature

     bool getTempAndPressure(float *temperature,
                             float *pressure,
                             TempUnit tempScale = CELSIUS,
                             BaroOversampleLevel level = OSR_8192);

### Basic Usage

    float temp;
    float pressure;
    if(!MS5637.getTempAndPressure(&temp, &pressure) {
      Serial.print("Error: ");
      Serial.println(MS5637.getError());
    } else {
      Serial.print("Temp: ");
      Serial.println(temp);
      Serial.print("Pressure: ");
      Serial.println(pressure);
    }
    

## isOK() / getError()

### Function Signatures:

    bool isOK();
    byte getError();

### Basic Usage:

    if(!MS5637.isOK()) {
      Serial.print("Sensor error occurred. Error number: "); 
      Serial.println(MS5637.getError());
      MS5637.begin(); // Try to reinitialise the sensor if we can
    }

### Returns

`isOK()` returns true if the sensor is working properly (after
`begin()` has been called.) In this working state, `getError()` will
return zero.

`getError()` can otherwise return any of these error values:

* 0 = No error, sensor working fine.
* 2 = Received NACK on transmit of address (sensor may not be connected/powered properly.)
* 3 = Received NACK on transmit of data (sensor connections may not be good enough quality.)
* 4 = Other "Wire" library i2c error.
* -3 = `begin()` hasn't been called yet.
* -2 = Failed to read back values from sensor (sensor connections may not be good enough quality.)

