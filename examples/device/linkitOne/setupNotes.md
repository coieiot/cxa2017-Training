## LinkIt One Setup for SensorThings API

### Arduino IDE, Standalone version, installation instructions:
- From [here](https://www.arduino.cc/download_handler.php?f=/arduino-1.8.2-windows.zip) download Arduino IDE 1.8.2 Windows ZIP file (NOT THE WINDOWS INSTALLER)
- Extract the downloaded zip file on Desktop
- Download USB COM port driver for Linkit One development board from [here](https://labs.mediatek.com/en/download/PfSCNbna)
- Extract the zip file and install the exe file
- From Desktop extracted folder of Arduino, open arduino.exe
- Go to Files -> Preferences
- In "Additional Boards URLs" copy this URL: http://download.labs.mediatek.com/package_mtk_linkit_index.json 
- Go to Tools -> Boards -> Boards Manager
- The very last row is "Linkit ONE by Seeed Studio and MediaTek Labs". Click on that and choose 1.1.23 for version and click Install.
- Copy and extract the followings in Desktop/arduino-1.8.2/libraries
	1. [PubSubClient-2.6.0.zip](http://downloads.arduino.cc/libraries/github.com/knolleary/PubSubClient-2.6.0.zip)
	2. [Barometer_Sensor.zip](https://github.com/Seeed-Studio/Grove_Barometer_Sensor/archive/master.zip)
	3. [Humidity_Temperature_Sensor_pro.zip](https://github.com/SeeedDocument/Grove-Temperature_and_Humidity_Sensor_Pro/raw/master/res/Humidity_Temperature_Sensor_pro.zip)
	4. [SensorThings.zip](https://github.com/coieiot/cxa2017-Training/blob/master/examples/device/linkitOne/SensorThings.zip)
