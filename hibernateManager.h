#ifndef HIBERNATE_MANAGER_H
#define HIBERNATE_MANAGER_H

#include "hibernateManager.h"

#include <esp_sleep.h>
#include <Ticker.h>
#include "hardware/shared_platform.h"
#include <Arduino.h>

class HibernateManager{
    public:
        void start();
        void loop();
        static void enterToDeepSleep();
        static void enterToLightSleep();

    private:
        Ticker tickerSleep;
        bool isActivate = false;
        void configBaud();
        void configPin();
        void activateTicker();
        void deactivateTicker();
};


#endif