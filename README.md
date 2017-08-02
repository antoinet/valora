# VALORA - WiFi Tracker Confuser

This project is a little Arduino sketch for  [ESP8266](https://github.com/esp8266/Arduino) enabled devices. It generates a stream of 802.11 probe requests with random source MAC address and random SSID. Its purpose is to confuse WiFi tracking systems, which are used in stores, e.g. for indoor positioning or client tracking in shopping malls.

The software was only tested on the ESP8266 embedded in the [2016 Area41 Security Conference Badge](http://area41.io/badge/). However, it should work as well on any [NodeMcu](http://nodemcu.com/index_en.html), which is available for as less as 5$.

_Update:_ the sketch works without modification on NodeMcu.
