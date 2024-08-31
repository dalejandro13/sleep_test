#ifndef CONNECT_MANAGER_H
#define CONNECT_MANAGER_H

#include <WifiManager.h>
#include <WiFiClientSecure.h>
#include "hardware/shared_hardware.h"
#include <HTTPClient.h>

class ConnectManager{
    public:
        void instantiateWifi();
        void configStationMode();
        void consultMessage();
        void disconnectWifi();
        void configAccessPoint();
    private:
        WifiManager *wifiManager;
        void checkConnection();
        uint8_t countToDisconnect = 0;
};


#endif