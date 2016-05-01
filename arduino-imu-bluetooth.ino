#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1

SoftwareSerial blueSerial(rxPin, txPin);

NXPMotionSense imu;
NXPSensorFusion filter;

void setup() {
  blueSerial.begin(9600);
  imu.begin();
  filter.begin(100);
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, heading;

  if (imu.available()) {
    // Read the motion sensors
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Update the SensorFusion filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    blueSerial.print("Orientation: ");
    blueSerial.print(heading);
    blueSerial.print(" ");
    blueSerial.print(pitch);
    blueSerial.print(" ");
    blueSerial.println(roll);
  }
}
