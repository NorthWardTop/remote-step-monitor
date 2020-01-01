
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
#include <string>
#include <Wire.h>
#include <ESP8266WiFi.h>
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include "ESPAsyncUDP.h"
//加速度传和陀螺仪介绍
//http://www.starlino.com/imu_guide.html

// 网络相关///////////////////////////////////////////////////////
#define SSID            "PDCN0"
#define PASSWORD        "1234567890"
#define SERVER_PORT     1234

AsyncUDP udp;

//传感器相关///////////////////////////////////////////////////////
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

struct raw_data {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t t;
}data;



void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("\nInitializing I2C devices...");
    accelgyro.initialize();
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // WIFI 相关配置
	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PASSWORD);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("WiFi Failed");
		while(1) {
			delay(1000);
		}
	} else {
        Serial.println("WiFi connected");
    }

    // if(udp.connect(IPAddress(192,168,1,16), SERVER_PORT)) {
    //     Serial.println("UDP connected");
    // } else {
    //     Serial.println("UDP connect falied");
    // }

    //Send unicast
    udp.print("Hello Server!");

}


void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&data.ax, &data.ay, &data.az, &data.gx, &data.gy, &data.gz);
    data.t = accelgyro.getTemperature();
    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display tab-separated accel/gyro x/y/z values
    Serial.print("a/g/t:\t");
    Serial.print(data.ax); Serial.print("\t");
    Serial.print(data.ay); Serial.print("\t");
    Serial.print(data.az); Serial.print("\t");
    Serial.print(data.gx); Serial.print("\t");
    Serial.print(data.gy); Serial.print("\t");
    Serial.print(data.gz);Serial.print("\t");
    Serial.println(data.t);

    // udp.printf("Ax:%hd  Ay:%hd  Az:%hd  Gx:%hd  Gy:%hd  Gz:%hd  T:%hd", 
    //     data.ax, data.ay, data.az, data.gx, data.gy, data.gz, data.t);
    //原始数据结构体发送
    // udp.write((const uint8_t *)&data, sizeof(data));

    //通过广播发送, 一个发送端多个接收端
    udp.broadcastTo((uint8_t *)&data, sizeof(data), SERVER_PORT);

    // //发送到树莓派
    // udp.writeTo((uint8_t*)&data, sizeof(data), IPAddress(192,168,123,185), SERVER_PORT);
    
    // //发送到python udp服务器
    // udp.writeTo((uint8_t*)&data, sizeof(data), IPAddress(192,168,123,14), SERVER_PORT);

    // //发送到PDCN0路由器 udp服务器
    // udp.writeTo((uint8_t*)&data, sizeof(data), IPAddress(192,168,123,1), SERVER_PORT);



    delay(40);
}




