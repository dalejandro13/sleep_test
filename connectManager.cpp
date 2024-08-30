#include "connectManager.h"

void ConnectManager::instantiateWifi()
{
    wifiManager = new WifiManager();
}

void ConnectManager::configWifiConnection()
{
    disconnectWifi();
    wifiManager->connect(REMOTE_SSID, REMOTE_PASS);
    checkConnection();
}

void ConnectManager::disconnectWifi()
{
  wifiManager->disconnect();
}

void ConnectManager::checkConnection()
{
  while (!wifiManager->isConnected())
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("is already connected");
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