/**
 * https://www.basemu.com/mpu6050-interfacing-with-nodemcu.html
 * 
 */

// #include <ESP8266WiFi.h>
// #include <Wire.h>
// #include <Arduino.h>

// #include "ESPAsyncUDP.h"
// #include "Mpu6050.h"

// const char * ssid = "OpenWrt";
// const char * password = "1234567890";

// AsyncUDP udp;


// void setup()
// {
// 	Serial.begin(9600);
// 	// Select SDA and SCL pins for I2C communication 
// 	// const uint8_t SCL = D6;
// 	// const uint8_t SDA = D7;
// 	Wire.begin();

// 	AccGyr.mpu6050Init();
	
// 	WiFi.mode(WIFI_STA);
// 	WiFi.begin(ssid, password);
	


// 	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
// 		Serial.println("WiFi Failed");
// 		while(1) {
// 			delay(1000);
// 		}
// 	} else 
// 	    Serial.println("WiFi connected");
// 	if(udp.connect(IPAddress(192,168,1,169), 1234)) {
// 		Serial.println("UDP connected");
// 		udp.onPacket([](AsyncUDPPacket packet) {
// 			Serial.print("UDP Packet Type: ");
// 			Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
// 			Serial.print(", From: ");
// 			Serial.print(packet.remoteIP());
// 			Serial.print(":");
// 			Serial.print(packet.remotePort());
// 			Serial.print(", To: ");
// 			Serial.print(packet.localIP());
// 			Serial.print(":");
// 			Serial.print(packet.localPort());
// 			Serial.print(", Length: ");
// 			Serial.print(packet.length());
// 			Serial.print(", Data: ");
// 			Serial.write(packet.data(), packet.length());
// 			Serial.println();
// 			//reply to the client
// 			packet.printf("Got %u bytes of data", packet.length());
// 		});
// 		//Send unicast
// 		udp.print("Hello Server!");
// 	}
// }

// void loop()
// {
// 	struct Mpu6050Data data;

// 	delay(1000);

// 	AccGyr.updateValue(&data);

// 	//Ax: -0.00 Ay: -0.00 Az: -0.00 T: 36.53 Gx: -0.01 Gy: -0.01 Gz: -0.01

// 	//Ax: -0.00 Ay: -0.00 Az: -0.00 T: 36.53 Gx: -0.01 Gy: -0.01 Gz: -0.01
// 	AccGyr.printRawData();


// 	// Send broadcast on port 1234
// 	udp.broadcastTo("Anyone here?", 1234);
// }





// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t t;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);
	delay(1000);//
    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    t = t/340+36.53;
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    t = accelgyro.getTemperature();

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display tab-separated accel/gyro x/y/z values
    Serial.print("a/g/t:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.print(t); Serial.print("\t");
    Serial.println(gz);

    // blink LED to indicate activity
    // blinkState = !blinkState;
    // digitalWrite(LED_PIN, blinkState);
	delay(200);
}
