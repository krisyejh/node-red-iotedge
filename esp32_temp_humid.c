/*
ESP32 Connecting to Node-RED Edge and Aliyun IoT. 
 */
 
#include <Arduino.h>
#include "WiFi.h"         //needed for the ESP32



// #define PHOTO_PIN 32
// int photovalue;

long randomNumberT, randomNumberH; //randoms variables for temperature and humidity for testing
const char WEBSITE[] = "192.168.125.106"; //Static IP at Node Red do not use http or https prefix

const char* MY_SSID = "712";
const char* MY_PWD =  "92861899";


void setup()
{
  Serial.begin(115200);
 
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) //not connected,  ...waiting to connect
    {
      delay(1000);
      Serial.print(".");
    }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");
}


void loop()
{
  
  //Change loop delay as you see fit
  delay(10000); //10 seconds, adjust as you like relative to sampling rate vs. service call quota

  WiFiClient client;  //Instantiate WiFi object, can scope from here or Globally
  // photovalue = analogRead(PHOTO_PIN);
  // Serial.println(photovalue);

    //Start or API service using our WiFi Client through PushingBox then relayed to Google
    if (client.connect(WEBSITE, 1880))
      { 
         
         randomNumberT = random(10, 40);
         randomNumberH = random(5, 70);
         Serial.print(" sending data package now \n");
        // client.print("GET /s?wd=google");
        // http URl format is --->   ?variable1=value&variable2=value2
         client.print("GET /weather?Uptime=" + (String)(millis() / 1000) + "&Temp=" + (String)randomNumberT
       + "&Humidity=" + (String) randomNumberH
  /*    + "&celData="      + (String) celData
       + "&fehrData="     + (String) fehrData
       + "&hicData="      + (String) hicData
       + "&hifData="      + (String) hifData */
         );

      // HTTP 1.1 provides a persistent connection, allowing multiple requests to be batched
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP32/1.0");
      client.println("Connection: close");
      client.println();
      Serial.print(" finished sending http enviroment data \n");
      }
}