#include <DHT.h>
#include <HomeseerSend.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_SI1145.h>
#include <Hash.h>
#include <WebSocketsServer.h>
#include "devicestatus.h"

#define MOTIONSENSOR 14 //D5
#define DHTPIN 12       // sensor's Data pin D6
#define DHTTYPE DHT22   // sensor type
#define DBG_OUTPUT_PORT Serial

const char *host = "ESP_WeatherStation";

float CurrTemperature = 0;
float CurrHumidity = 0;
float CurrUVindex = 0;
float CurrVisible = 0;
float CurrInfrared = 0;
float CurrProximity = 0;

int LastTemperature = 0;
int LastHumidity = 0;
int LastVisible = 0;
int LastUVindex = 0;
int LastInfrared = 0;
int lastClientIndex = 0;
int iSTriggerState = 0;
int LastMotionSendState = 0;
int LastNoMotionSendState = 0;
int wsClientNumber[5] = {-1, -1, -1, -1, -1};

const int max_ws_client = 5;

String oServerMessage;

unsigned long dhtStartTime = 0;
unsigned long dhtInterval = 10000; //1 minutes
unsigned long elapseTime;

//SCL = D1 GPI5
//SDA = D2 GPIO4

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SI1145 uv = Adafruit_SI1145();
HSSend HSSend(true); //initilize HomeseerSend
ESP8266WebServer web_server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void wsSendState()
{
  String json = GetDeviceStateJson();

  int numcl = 0;
  for (numcl = 0; numcl < max_ws_client; numcl++)
  {
    
    if (wsClientNumber[numcl] != -1)
    {
      webSocket.sendTXT(wsClientNumber[numcl], json); //send to socket client
    }
  }
  json = String();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{

  switch (type)
  {
  case WStype_DISCONNECTED:
    DBG_OUTPUT_PORT.printf("[%u] Disconnected!\n", num);
    break;

  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    DBG_OUTPUT_PORT.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    int index = (num % max_ws_client);
    if (index <= 0)
      index = 0;
    wsClientNumber[index] = num;
    lastClientIndex = wsClientNumber[index];
    DBG_OUTPUT_PORT.printf("Save client index %d :%un", index, num);
    oServerMessage = "Status: Connected";
    //wsSendState();
  }
  break;

  case WStype_TEXT:
    DBG_OUTPUT_PORT.printf("[%u] get Text: %s\n", num, payload);
    //wsSendState();
    break;

  case WStype_BIN:
    DBG_OUTPUT_PORT.printf("[%u] get binary length: %u\n", num, length);
    hexdump(payload, length);
    webSocket.sendBIN(num, payload, length);
    break;
  }
}

void setup()
{
  pinMode(MOTIONSENSOR, INPUT);

  Serial.begin(115200);
  while (!Serial)
  {
  }
  //===============================[ WiFiManager Wifi init]==================================================
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.setSTAStaticIPConfig(IPAddress(192, 168, 1, 57), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0)); //use local environment IP address
  wifiManager.autoConnect("AutoConnectAP");

  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.print("Connected! IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());

  //========================[ OTA init]=====================================
  //ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("ESP_WeatherStation");
  // MD5(Mist8266) = 65f6a8c5a23339c17281177d0d28bbe9
  //ArduinoOTA.setPasswordHash("65f6a8c5a23339c17281177d0d28bbe9");
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");
  });
  ArduinoOTA.begin(); /* setup the OTA server */

  if (!uv.begin())
  {
    Serial.println("Didn't find Si1145");
    while (1)
      ;
  }

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  if (MDNS.begin(host))
  {
    Serial.println("MDNS responder started");
  }

  web_server.on("/device.html", []() { //load device status page
    Serial.println("device.html");
    web_server.send(200, "text/html", PAGE_DeviceStatusPage);
  });

  web_server.onNotFound([]() {
    web_server.send(404, "text/plain", "404: Not Found");
  });

  web_server.begin();
  Serial.println("HTTP Web Server started");

  HSSend.SetHost("192.168.1.46", 80);
}

void loop()
{

  ArduinoOTA.handle();

  if (millis() - dhtStartTime > dhtInterval)
  {
    GetDHT22Values();
    GetSI1145Values();
    wsSendState();
    SendTemperature(CurrTemperature);
    SendHumidity(CurrHumidity);
    SendVisible(CurrVisible);
    SendInfrared(CurrInfrared);
    SendUltraviolet(CurrUVindex);
    dhtStartTime = millis();
  }

  if ((millis() - elapseTime) > 1000)
  {
    GetMotionState();
    wsSendState();
    elapseTime = millis();
  }

  web_server.handleClient();
  webSocket.loop();
}

String GetDeviceStateJson()
{

  String json;
  json += "{";
  json += "\"Temperature\"";
  json += ":";
  json += "\"" + String(CurrTemperature) + "\"";
  json += ",";
  json += "\"Humidity\"";
  json += ":";
  json += "\"" + String(CurrHumidity) + "\"";
  json += ",";
  json += "\"Visible\"";
  json += ":";
  json += "\"" + String(CurrVisible) + "\"";
  json += ",";
  json += "\"Infrared\"";
  json += ":";
  json += "\"" + String(CurrInfrared) + "\"";
  json += ",";
  json += "\"UltraViolet\"";
  json += ":";
  json += "\"" + String(CurrUVindex) + "\"";
  json += ",";
  json += "\"Proximity\"";
  json += ":";
  json += "\"" + String(CurrProximity) + "\"";
  json += ",";
  json += "\"Message\"";
  json += ":";
  json += "\"" + oServerMessage + "\"";
  json += "}";
  return json;
}

String GetMotionStateJson()
{
  String json;
  json += "{";
  json += "\"Proximity\"";
  json += ":";
  json += "\"" + String(CurrProximity) + "\"";
  json += ",";
  json += "\"Message\"";
  json += ":";
  json += "\"" + oServerMessage + "\"";
  json += "}";
  return json;
}

void GetSI1145Values()
{

  CurrUVindex = uv.readUV() / 100.0;
  CurrVisible = uv.readVisible();
  CurrInfrared = uv.readIR();
  //CurrProximity = uv.readProx();

  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.print("Vis: ");
  DBG_OUTPUT_PORT.println(CurrVisible);
  DBG_OUTPUT_PORT.print("IR: ");
  DBG_OUTPUT_PORT.println(CurrInfrared);
  DBG_OUTPUT_PORT.print("UV: ");
  DBG_OUTPUT_PORT.println(CurrUVindex);

}

void SendHumidity(float oCurrentHumidity)
{
  String url;
  if (oCurrentHumidity != LastHumidity)
  {

    url = HSSend.GetJsonDevCtrlURL("1242", String(oCurrentHumidity));
    HSSend.SendData(url);
    url = String();
    LastHumidity = oCurrentHumidity;
  }
}

void SendTemperature(float oCurrentTemperature)
{
  String url;
  if (oCurrentTemperature != LastTemperature)
  {

    url = HSSend.GetJsonDevCtrlURL("1240", String(oCurrentTemperature));
    HSSend.SendData(url);
    url = String();
    LastTemperature = oCurrentTemperature;
  }
}

void SendVisible(float oCurrentVisible)
{
  String url;
  if (oCurrentVisible != LastVisible)
  {

    url = HSSend.GetJsonDevCtrlURL("1241", String(oCurrentVisible));
    HSSend.SendData(url);
    url = String();
    LastVisible = oCurrentVisible;
  }
}

void SendInfrared(float oCurrentInfrared)
{
  String url;
  if (oCurrentInfrared != LastInfrared)
  {

    url = HSSend.GetJsonDevCtrlURL("1246", String(oCurrentInfrared));
    HSSend.SendData(url);
    url = String();
    LastInfrared = oCurrentInfrared;
  }
}

void SendUltraviolet(float oCurrentUVindex)
{
  String url;
  if (oCurrentUVindex != LastUVindex)
  {

    url = HSSend.GetJsonDevCtrlURL("1243", String(oCurrentUVindex));
    HSSend.SendData(url);
    url = String();
    LastUVindex = oCurrentUVindex;
  }
}

void SendNoMotion()
{
  String url;
  if (LastNoMotionSendState == 0)
  {
    url = HSSend.GetJsonDevCtrlURL("1245", "0");
    HSSend.SendData(url);
    url = String();
    LastNoMotionSendState = 1;
    LastMotionSendState = 0;
  }
}

void SendMotionDetected()
{
  String url;
  if (LastMotionSendState == 0)
  {
    url = HSSend.GetJsonDevCtrlURL("1245", "100");
    HSSend.SendData(url);
    url = String();
    LastMotionSendState = 1;
    LastNoMotionSendState = 0;
  }
}

void GetDHT22Values()
{
  float h = dht.readHumidity();
  float f = dht.readTemperature(true); // Fahrenheit
  if (isnan(h) || isnan(f))
  {
    DBG_OUTPUT_PORT.println("Failed to read from DHT sensor!");
  }
  else
  {

    DBG_OUTPUT_PORT.print("Humidity: ");
    DBG_OUTPUT_PORT.print(h);
    DBG_OUTPUT_PORT.print(" %\t");
    DBG_OUTPUT_PORT.println(" ");
    CurrHumidity = h;

    DBG_OUTPUT_PORT.print("Temperature: ");
    DBG_OUTPUT_PORT.print(f);
    DBG_OUTPUT_PORT.print(" *F\t");
    DBG_OUTPUT_PORT.println(" ");
    CurrTemperature = f;
  }
}

void GetMotionState()
{
  int val = digitalRead(MOTIONSENSOR);
  if (val == 0)
  {
    CurrProximity = 0;
    SendNoMotion();
    iSTriggerState = 0;
  }
  else if (val == 1)
  {
    CurrProximity = 100;
    SendMotionDetected();
    iSTriggerState = 1;
  }
