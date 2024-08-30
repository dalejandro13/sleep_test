#ifndef HIBERNATE_MANAGER_H
#define HIBERNATE_MANAGER_H

#include <esp_sleep.h>
#include <Ticker.h>
#include "hardware/shared_platform.h"
#include <Arduino.h>
#include "connectManager.h"

class HibernateManager{
    public:
        void start();
        void loop();
        static void enterToDeepSleep();
        static void enterToLightSleep();
        static void consult();

    private:
        ConnectManager connectManager;
        Ticker tickerSleep;
        Ticker tickerConsult;
        std::string dataSerial = std::string();
        bool isActivate = false;
        bool isActivate2 = false;
        void configBaud();
        void configPin();
        void activateTickerToSleep();
        void deactivateTickerToSleep();
        void activateTickerToConsultServer();
        void desactivateTickerToConsultServer();
        void thereIsActivity();
        void getSerialData();
        void configWifiConnection();
};


#endif