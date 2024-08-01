#ifndef MT6701_H
#define MT6701_H

#include <Arduino.h>

class MT6701 {
  
  public:
    MT6701();
    
    void initEncoder();
    int getRawAngle();
    
    float getAbsoluteAngleDegrees();
    float getAbsoluteAngleRadians();
    
    float getTotalAngleDegrees();
    float getTotalAngleRadians();


  private:
    int correctAngle();
    float calculateTotalAngle();

    int lowbyte, highbyte;
    int rawAngle;
    int startAngle;
    int correctedRawAngle;
    uint8_t quadrant, prevQuadrant;
    int numberOfTurns;
    float totalAngle;
};

#endif