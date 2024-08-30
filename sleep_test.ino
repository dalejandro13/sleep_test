#include "hibernateManager.h"

HibernateManager hibernateManager;

void setup() 
{
  hibernateManager.start(); 
}

void loop() 
{
  hibernateManager.loop();
}
