#ifndef CONNECT_MANAGER_H
#define CONNECT_MANAGER_H

#include <WifiManager.h>
#include <WiFiClientSecure.h>
#include "hardware/shared_hardware.h"
#include <HTTPClient.h>

class ConnectManager{
    public:
        void instantiateWifi();
        void configWifiConnection();
        void consultMessage();

    private:
        WifiManager *wifiManager;
        void checkConnection();
        void disconnectWifi();
};


#endif