# weather station

Weather station built for ESP32 with functional OLED screen & website

Necessary Libraries:

- Adafruit SSD1306
- DHT sensor library
- Adafruit Unified Sensor
- \+ the dependencies of these libraries

Access through http (not https)

Add file for WIFI Information:

## wlan_info.h

const char* wlan_ssid = "WIFI_NAME";

const char* wlan_psk  = "WIFI_PASSWORD";


const char* wlan_ap_ssid = "ACCESS_POINT_NAME";

const char* wlan_ap_psk  = "ACCESS_POINT_PASSWORD";

# To-Dos for future updates:

- ersetzen: zwischen Zahlenwert & Einheit schmales, geschütztes Leerzeichen (existiert in Unicode)
- seperate html, css & js
- improve frontend visuals
- clean up css and rename classes
