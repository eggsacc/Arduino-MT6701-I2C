# Arduino MT6701 library

A simple library to read and calculate MT6701 angle values using I2C.

## Functions
1) `MT6701.initEncoder`: initialize I2C communication, zeroes starting angle. No return value
2) `MT6701.getRawValue`: read the raw 14-bit encoder output (0-16383), returns `int`
3) `MT6701.getAbsoluteAngleRadians`: calculates absolute angle in radians (0-2pi), returns `float`
4) `MT6701.getAbsoluteAngleDegrees`: calculates absolute angle in degrees (0-360), returns `float`
5) `MT6701.getAbsoluteAngleRadians`: calculates total rotation angle in radians, returns `float`
6) `MT6701.getAbsoluteAngleDegrees`: calculates total rotation angle in degrees, returns `float`
