/* BaroSensor
 *
 * An Arduino library for the Freetronics BARO sensor module, using
 * the Measurement Specialties MS5637-02BA03 Altimeter/Pressure sensor
 * module
 *
 * http://www.freetronics.com/baro
 *
 * For usage example, see the example sketches under File -> Examples -> BaroSensor after
 * this library is installed.
 *
 * Copyright (C)2014 Freetronics Pty Ltd. Licensed under GNU GPLv3 as described in the LICENSE file.
 *
 * Written by Angus Gratton (angus at freetronics dot com)
 */
 
#pragma once

#include "Arduino.h"
#include "Wire.h"

/* 
  Module supports a range of lower oversampling levels, for faster
  less accurate results.

  Default is maximum accuracy.
 */
enum BaroOversampleLevel {
  OSR_256,
  OSR_512, 
  OSR_1024, 
  OSR_2048, 
  OSR_4096, 
  OSR_8192 
};


typedef enum {
  CELSIUS,
  FAHRENHEIT
} TempUnit;


class MS5637 {

  private:
    
    /* error codes */
    static const int ERR_NOREPLY      = -1;
    static const int ERR_BAD_READLEN  = -2;
    static const int ERR_NEEDS_BEGIN  = -3;

    bool initialised;
    
    int8_t err;
    
    uint16_t c1,c2,c3,c4,c5,c6; // Calibration constants used in producing results

    uint32_t takeReading(uint8_t trigger_cmd, BaroOversampleLevel oversample_level);

  public:
    
    MS5637() : initialised(false), err(ERR_NEEDS_BEGIN) { }
    
    void begin();

    /* 
      Return temperature in C or Fahrenheit 
    */
    bool getTemperature(float *temperature, TempUnit scale = CELSIUS, BaroOversampleLevel level = OSR_8192);
    
    /* 
      Return pressure in mbar 
    */
    bool getPressure(float *pressure, BaroOversampleLevel level = OSR_8192);

    /* 
      Update both temperature and pressure together. This takes less
      time than calling each function separately (as pressure result
      depends on temperature.) Returns true for success, false on an
      error 
    */
    bool getTempAndPressure(float *temperature,
                            float *pressure,
                            TempUnit tempScale = CELSIUS,
                            BaroOversampleLevel level = OSR_8192);

    inline bool isOK() { return initialised && err == 0; }
    
    inline byte getError() { return initialised ? err : ERR_NEEDS_BEGIN; }

    /* 
      Debugging function that outputs a list of debugging data to Serial 
    */
    void dumpDebugOutput();

};
