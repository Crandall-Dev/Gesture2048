/*
  Sketch: PAJ7620-Sensor-Serial-Generator
  Package: RevEng_PAJ7620

  Copyright (c) 2020 Aaron S. Crandall
  Author        : Aaron S. Crandall <crandall@gonzaga.edu>
  Modified Time : December 2020

  Description: This demo can recognize 9 gestures and output the result,
    including move up, move down, move left, move right, move forward,
    move backward, circle-clockwise, circle-counter clockwise, and wave.

  License: Same as package under MIT License (MIT)
*/

// Includes enum definition of GES_* return values from readGesture()
#include "RevEng_PAJ7620.h"

// Create gesture sensor driver object
RevEng_PAJ7620 sensor = RevEng_PAJ7620();

// Last seen number of waves pulled from sensor
int curr_wave_count = 0;

// *********************************************************************
void setup()
{
  Serial.begin(115200);

  // Serial.println("PAJ7620 sensor demo: Recognizing all 9 gestures.");

  if( !sensor.begin() )           // return value of 0 == success
  {
    Serial.println("{\"state\": \"error no device\"}");
    while(true) { }
  }

  sensor.setGestureEntryTime(500);
  sensor.setGestureExitTime(800);

  Serial.println("{\"state\": \"OK\"}");
}

// *********************************************************************
void send_gesture(char* val)
{
  Serial.println("{\"gesture\": \"" + String(val) + "\"}");
}

// *********************************************************************
void loop()
{
  Gesture gesture;                  // Gesture is an enum type from RevEng_PAJ7620.h
  gesture = sensor.readGesture();   // Read back current gesture (if any) of type Gesture

  switch (gesture)
  {
    case GES_FORWARD:       send_gesture("GES_FORWARD"); break;
    case GES_BACKWARD:      send_gesture("GES_BACKWARD"); break;
    case GES_LEFT:          send_gesture("GES_LEFT"); break;
    case GES_RIGHT:         send_gesture("GES_RIGHT"); break;
    case GES_UP:            send_gesture("GES_UP"); break;
    case GES_DOWN:          send_gesture("GES_DOWN"); break;
    case GES_CLOCKWISE:     send_gesture("GES_CLOCKWISE"); break;
    case GES_ANTICLOCKWISE: send_gesture("GES_ANTICLOCKWISE"); break;
    case GES_WAVE:          send_gesture("GES_WAVE"); break;
    case GES_NONE:                                    break;
  }

  int new_wave_count = 0;
  new_wave_count = sensor.getWaveCount();     // Query for new wave count

  if( new_wave_count != curr_wave_count ) {   // Only print if a new value happens
    curr_wave_count = new_wave_count;
    Serial.println("{\"wave_count\": " + String(curr_wave_count) + "}");
  }

  delay(50);
}
