#include "connectManager.h"

void ConnectManager::instantiateWifi()
{
  wifiManager = new WifiManager();
}

void ConnectManager::configStationMode()
{
  disconnectWifi();
  wifiManager->connect(REMOTE_SSID, REMOTE_PASS);
  checkConnection();
}

void ConnectManager::checkConnection()
{
  while (!wifiManager->isConnected())
  {
    Serial.print(".");
    delay(1000);
    countToDisconnect++;
    if(countToDisconnect >= 20)
    {
      countToDisconnect = 0;
      Serial.println("can't connect to the network");
      return;
    }
  }
  countToDisconnect = 0;
  Serial.println("is already connected");
}

void ConnectManager::disconnectWifi()
{
  wifiManager->disconnect();
}

void ConnectManager::consultMessage()
{
  HTTPClient http;
  http.begin(URL_SERVER);
  uint32_t httpResponseCode = http.GET();
  if (httpResponseCode == HTTP_CODE_OK)
  {
    std::string payload = std::string(http.getString().c_str());
    Serial.printf("Respuesta: %s\n", payload.c_str());
  }
  else
  {
    Serial.println("no se puede consultar");
  }
  http.end(); // close the connection
}

void ConnectManager::configAccessPoint()
{
  wifiManager->createAP(AP_SSID, AP_PASS);
}