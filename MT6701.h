#ifndef MT6701_H
#define MT6701_H

#include <Arduino.h>

#define I2C_AD 0x06

#define rawToRad 0.00038349519f
#define rawToDeg 0.02197265625f
#define _2PI 6.28318530718f
#define radToDeg 57.2957795131f

class MT6701 {
  
  public:
    MT6701(int8_t dir, bool zero_angle);
    
    void initEncoder();
    int getRawAngle();
    
    float getAngle();
    float getAngleDegrees();
    
    float getAbsoluteAngle();
    float getAbsoluteAngleDegrees();

  private:
    int correctAngle();
    float calculateTotalAngle();

    int lowbyte, highbyte;
    int rawAngle;
    int startAngle;
    int offsetAngle;
    int correctedRawAngle;
    uint8_t quadrant, prevQuadrant;
    int32_t numberOfTurns;
    float totalAngle;
    int8_t _dir;
    bool _zero_angle;
};

#endif