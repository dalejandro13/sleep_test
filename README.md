# sleep_test
- This code is only to test the "deep sleep" and "light sleep" modes.
- In both modes the only way to wake up the microcontroller is to set a signal pin high, that pin is given by the WAKEUP_PIN macro. That pin is activated with a remote control.
- The code has been tested on the ESP32 microcontroller.
- In the code I have generated more processes to check if it is really going to sleep.