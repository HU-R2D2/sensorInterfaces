# sensorInterfaces

**NOTICE:**
If you would like to implement this library and use it on a Raspberry Pi, or even compile this code. It is highly recommended to get in touch with Mathijs van Bremen or Stephan Vivie as of right now. Since not all dependencies are ready yet there's no "easy fix".

**IMPORTANT NOTE:** This version is based on an older version from [ADT_Clock_merge](https://github.com/HU-R2D2/ADT_Clock_Merge/tree/develop) and the CMakeLists.txt works with "adt-all.cc" that includes all ADT files we use in our project. This file should be saved under "../deps/adt/source/" :-). For questions, just ask the people from sensorInterfaces! 

adt-all.cc
```
#include "src/Acceleration.cpp"
#include "src/Angle.cpp"
#include "src/Box.cpp"
#include "src/Coordinate.cpp"
#include "src/Duration.cpp"
#include "src/Force.cpp"
#include "src/Length.cpp"
#include "src/Mass.cpp"
#include "src/Moment.cpp"
#include "src/Speed.cpp"
#include "src/Translation.cpp"
#include "src/Rotation.cpp"
#include "src/Attitude.cpp"

#include "src/TimeStamp.cpp" // need a specific version from clock merge library
#include "src/Clock.cpp" // need a specific version from clock merge library

```

**IMPORTANT NOTE 2:**
This version uses the last version of [Polarview](https://github.com/HU-R2D2/Polarview) and the CMakeList.txt works with "polarview-all.cc" that includes all the Polarview files we use in our project. This file should be saved under "../deps/polarview/source/"
polarview-all.cc
```
#include "src/MapPolarView.cpp"
#include "src/DistanceReading.cpp"
```
