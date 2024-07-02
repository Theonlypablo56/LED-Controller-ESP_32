// pragma once prevents the file to be included twice
#pragma once
// #include ...
#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// all other includes stays here in the .h file

// vars need to be extern
extern String myName;
extern AsyncWebServer server;
extern AsyncWebSocket ws; // access at ws://[esp ip]/ws
extern AsyncEventSource events; // event source (Server-Sent events)

class ezSerial{
  public:
    void log(String headerName, String headerValue);
};
// prototypes don't need named attributes in the .h file
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

void createDir(fs::FS &fs, const char * path);

void removeDir(fs::FS &fs, const char * path);

void readFile(fs::FS &fs, const char * path);

void writeFile(fs::FS &fs, const char * path, const char * message);

void appendFile(fs::FS &fs, const char * path, const char * message);

void renameFile(fs::FS &fs, const char * path1, const char * path2);

void deleteFile(fs::FS &fs, const char * path);

void testFileIO(fs::FS &fs, const char * path);

void weirdFileFunction();