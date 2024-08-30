#include "hibernateManager.h"

static HibernateManager *globalInstance = nullptr;

void HibernateManager::configBaud()
{
    Serial.begin(115200);
}

void HibernateManager::configPin()
{
    pinMode(WAKEUP_PIN, INPUT); // Configura el pin de despertador como entrada
}

void HibernateManager::enterToDeepSleep()
{
    esp_sleep_enable_ext0_wakeup(WAKEUP_PIN, 1);  // 1 = high level. Configure the ESP32 to wake up with a high signal in WAKEUP_PIN
    Serial.println("enter to deep sleep");
    esp_deep_sleep_start(); // Entra en deep sleep
    Serial.println("this message should not be displayed");
}

void HibernateManager::enterToLightSleep()
{
    esp_sleep_enable_ext0_wakeup(WAKEUP_PIN, 1); // 1 = high level. Configure the ESP32 to wake up with a high signal in WAKEUP_PIN
    Serial.println("enter to light sleep");
    esp_light_sleep_start(); 
    Serial.println("this message may possibly be displayed in light sleep mode");
    globalInstance->deactivateTicker();
}

void HibernateManager::activateTicker()
{
    if(!isActivate)
    {
        isActivate = true;
        tickerSleep.once_ms(10000, enterToDeepSleep);
        // tickerSleep.attach_ms(10000, enterToLightSleep);
    }
}

void HibernateManager::deactivateTicker()
{
    if(isActivate)
    {
        isActivate = false;
        tickerSleep.detach();
    }
}

void HibernateManager::start()
{
    globalInstance = this;
    configBaud();
    configPin();
    activateTicker();
}

void HibernateManager::loop()
{
    Serial.println("program executing");
    delay(1000); // Add a small delay to avoid showing the message too many times
}