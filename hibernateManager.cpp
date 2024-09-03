#include "hibernateManager.h"

static HibernateManager *globalInstance = nullptr;

void HibernateManager::configBaud()
{
    Serial.begin(115200);
}

void HibernateManager::configPin()
{
    pinMode(WAKEUP_PIN, INPUT); // Set the wakeup pin as input
}

void HibernateManager::enterToDeepSleep()
{
    esp_sleep_enable_ext0_wakeup(WAKEUP_PIN, 1);  // 1 = high level. Configure the ESP32 to wake up with a high signal in WAKEUP_PIN
    Serial.println("enter to deep sleep mode");
    globalInstance->deactivateTickerToSleep();
    globalInstance->desactivateTickerToConsultServer();
    esp_deep_sleep_start(); // enter to deep sleep mode 
    Serial.println("this message should not be displayed in deep sleep mode");
}

void HibernateManager::enterToLightSleep()
{
    esp_sleep_enable_ext0_wakeup(WAKEUP_PIN, 1); // 1 = high level. Configure the ESP32 to wake up with a high signal in WAKEUP_PIN
    Serial.println("enter to light sleep mode");
    globalInstance->deactivateTickerToSleep();
    globalInstance->desactivateTickerToConsultServer();
    delay(100);
    esp_light_sleep_start(); // enter to light sleep mode
    Serial.println("this message may possibly be displayed in light sleep mode");
    globalInstance->activateTickerToSleep();
    globalInstance->activateTickerToConsultServer();
    Serial.printf("actual counter: %d\n", globalInstance->counter);
}

void HibernateManager::activateTickerToSleep()
{
    if(!isActivate)
    {
        isActivate = true;
        // tickerSleep.attach_ms(60000, enterToDeepSleep);
        tickerSleep.attach_ms(15000, enterToLightSleep);
    }
}

void HibernateManager::activateTickerToConsultServer()
{
    if(!isActivate2)
    {
        isActivate2 = true;
        tickerConsult.attach_ms(1000, consult);
    }
}

void HibernateManager::desactivateTickerToConsultServer()
{
    if(isActivate2)
    {
        isActivate2 = false;
        tickerConsult.detach();
    }
}

void HibernateManager::deactivateTickerToSleep()
{
    if(isActivate)
    {
        isActivate = false;
        tickerSleep.detach();
    }
}

void HibernateManager::thereIsActivity()
{
    deactivateTickerToSleep();
    activateTickerToSleep(); // By default it should remain activated if you go through the "thereIsActivity" method
}

void HibernateManager::getSerialData()
{
    while (Serial.available() > 0) 
    {
        char c = Serial.read();
        dataSerial += c;
        delay(3);
    }

    if (!dataSerial.empty()) 
    {
        if(dataSerial.find("sleep") != std::string::npos)
        {
            enterToDeepSleep();
        }
        else if(dataSerial.find("show") != std::string::npos)
        {
            Serial.println("show message");
        }
        dataSerial = std::string();
    }
}

void HibernateManager::consult()
{
    globalInstance->connectManager.consultMessage();
}

void HibernateManager::start()
{
    globalInstance = this;
    configBaud();
    configPin();
    connectManager.instantiateWifi();
    // connectManager.configAccessPoint(); // for access point
    connectManager.configStationMode(); // for station mode
    activateTickerToSleep();
    activateTickerToConsultServer(); // for station mode
    delay(1000);
}

void HibernateManager::loop()
{
    getSerialData();
    counter++;
    Serial.printf("counter1: %d\n", counter);
    if(counter >= 1000){
        counter = 0;
    }
    delay(1000); // Add a small delay to avoid showing the message too many times
}