# SmartMirror-HomeAutomation

This project was meant as a control panel for a series of 'Home automation' projects, starting with WiFi controlled, mains voltage lights.
The mirror was built from an old PC monitor, a Raspberry PI 3 and some wood panels, and the software is based on the MagicMirror (https://github.com/MichMich/MagicMirror) project.

The WiFi lights are controlled with an ESP8266 microcontroller, two relays and the necessary power source, via HTTP GET requests to the local server on the ESP8266. It accepts basic commands (What lights to turn on/off) from all the devices in the local network and can also be sent HTTP comands via Android widgets (second video link).

I have added some photos from the build process which show some of the progress.

Video:

https://youtu.be/2JbYavBpRPE - the LCD is controlled by a python script (mainly for power saving, in the future it will also use a motion sensor)

https://youtu.be/4cr4rhavo0I

https://youtu.be/KggG6liQK5w

https://youtu.be/pbkt8QCbBKg
