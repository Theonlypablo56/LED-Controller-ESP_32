#include <Arduino.h>
#include <WiFi.h>
#include <htmlShit.h>
#include <ArduinoOTA.h>
#include "FS.h"
#include <LittleFS.h>
#include "extraFunctions.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "--";  // Enter your SSID here
const char* password = "-------";  //Enter your Password here
ezSerial ezSrl;

int redPin = 26;
int greenPin = 27;
int bluePin = 25;

const int ledPin = 2;

int freq = 11500;
const int redChannel = 1;
const int blueChannel = 2;
const int greenChannel = 3;
const int resolution = 8;

// custom configuration variables
bool wifiLight = true;
int totalBrightness = 100;
//

String HTML = "";
int rgb[3] = {0, 0, 0};
bool on = true;

void rgbSetup(){
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);

  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);
}

void rgbSet(int red, int green, int blue) {
  ledcWrite(redChannel, red);
  ledcWrite(greenChannel, green);
  ledcWrite(blueChannel, blue);
}

void handle_root(AsyncWebServerRequest *request) {
  request->send(200, "text/html", HTML);
} 

void sendXML(AsyncWebServerRequest *request) {
  String XML = "<?xml version = '1.0'?>\n<Data>\n</Data>\n"; // could add current rgb data later
  request->send(200, "text/xml", XML);
}

void rgbSplitter(String rgbString) {
  int firstCom = rgbString.indexOf(",");
  int secondCom = rgbString.indexOf(",", firstCom+1);

  int r = (rgbString.substring(0, firstCom)).toInt();
  int g = (rgbString.substring(firstCom + 1, secondCom)).toInt();
  int b = (rgbString.substring(secondCom + 1, rgbString.length())).toInt();
  
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
  //Serial.print("R:");
  //Serial.println(r);
  //Serial.print("G:");
  //Serial.println(g);
  //Serial.print("B:");
  //Serial.println(b);
}

void updateRGB(AsyncWebServerRequest *request) {


}

void weOn(){
  rgbSet(43,61,22);
  delay(300);
  rgbSet(23,41,2);
  delay(300);
  rgbSet(43,61,22);
  delay(300);
  rgbSet(23,41,2);
  delay(300);
  rgbSet(0,0,0);
}

void OnOff(){
  int time = millis();
  if (on == true){
    if (time % 1000 == 0){
      on = !on;
    }
    digitalWrite(ledPin, on);
  }
}

void blinkStat(AsyncWebServerRequest *request){
  String onOrOff = request->arg("Value");
  request->send(200, "text/plain", "");
  if (onOrOff == "false"){
    on = false;
  } else {
    onOrOff = true; 
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);

  WiFi.setHostname("Board56");
  ArduinoOTA.setHostname("Board56");
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  HTML = secondPage;
  Serial.begin(115200);
  rgbSetup();
  

  Serial.println("");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
  
  server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", secondPage);
  });

  server.on("/updatedRGB", HTTP_POST, [](AsyncWebServerRequest *request){
      String selectedRGB = request->getParam("rgb")->value();
      request->send(200, "text/plain", "We good.\n");
      rgbSplitter(selectedRGB);
      rgbSet(rgb[0], rgb[1], rgb[2]);
  });
  
  server.on("/updatedHertz", HTTP_POST, [](AsyncWebServerRequest *request){
      int selectedHertz = request->getParam("Hertz")->value().toInt();
      if (selectedHertz > 0 && isdigit(selectedHertz)){
        freq = selectedHertz;
        ledcChangeFrequency(redChannel, freq, resolution);
        ledcChangeFrequency(greenChannel, freq, resolution);
        ledcChangeFrequency(blueChannel, freq, resolution);
        request->send(200, "text/plain", "We good.\n");
      }
  });

  server.begin();
  delay(50);
  
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  
  ArduinoOTA.begin();
  ledcRead(redChannel);
  ledcReadFreq(redChannel); // remember to usee theseee
}

void loop() {
  ArduinoOTA.handle();
}

