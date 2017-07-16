<link rel="stylesheet" href="css/modest.css">  
# Texas Instruments SensorTag Notes CC2650  
<img src="img\sensorTag..jpg" width="20%">  
  
[Texas Instruments SensorTag](http://www.ti.com/ww/en/wireless_connectivity/sensortag2015/?INTC=SensorTag&HQS=sensortag)  
<img src="img/sensortag-back.jpg" width="50%">  
<img src="img/sensortag-front.png" width="50%">  
<img src="img/sensortag-buttons.jpg" width="50%">  
  
# Intel Edison <> TI SensorTag CC2650  
  
Device B0:B4:48:D0:2D:05 Name: CC2650 SensorTag  
  
[GATT_Server](http://processors.wiki.ti.com/images/a/a8/BLE_SensorTag_GATT_Server.pdf)  
[User_Guide](http://processors.wiki.ti.com/index.php/SensorTag_User_Guide#Sensors_2)  
[Node.js Code](https://github.com/burrsutter/ti_sensortag_node)  

```
var SensorTag = require("sensortag");
SensorTag.discover(function(device) {
console.log('discovered device with UUID: ' + device.uuid);
device.connect(function() {
    device.discoverServicesAndCharacteristics(function() {

        device.enableAccelerometer(function() {device.on('accelerometerChange', function(x, y, z) {console.log("x: " + x.toFixed(1) + " y: " + y.toFixed(1) + " z: " + z.toFixed(1));}); device.notifyAccelerometer(function(){}); });

        device.enableBarometricPressure(function() {device.on('barometricPressureChange', function(pressure) {console.log('pressure = %d ', pressure);});device.notifyBarometricPressure(function() {});});

        device.enableGyroscope(function() {device.setGyroscopePeriod(500, function() {device.on('gyroscopeChange', function(x, y, z) {console.log("x: " + x + " y: " + y + " z: " + z);});device.notifyGyroscope(function() {});});});

        device.enableIrTemperature(function() { device.on('irTemperatureChange', function(objectTemperature, ambientTemperature) { console.log("IR temp: " + objectTemperature.toFixed(1) + "°C ambient temp: " + ambientTemperature.toFixed(1) + "°C");}); device.notifyIrTemperature(function() { }); });

        device.enableLuxometer(function() {device.on('luxometerChange', function(lux) { console.log("lux: " + lux); }); device.notifyLuxometer(function() {});});

        device.enableMagnetometer(function() { device.setMagnetometerPeriod(500, function() {device.on('magnetometerChange', function(x, y, z) {console.log("x: " + x + " y: " + y + " z: " + z);}); device.notifyMagnetometer(function() {});});});

        device.on('simpleKeyChange', function(left, right) { if (left === true) { console.log("left: " + left); } if (right === true ) { console.log("right: " + right); }}); device.notifySimpleKey(function() {});

device.enableHumidity(function() { device.on('humidityChange', function(temperature, humidity) { console.log("temp: " + temperature.toFixed(1) + "°C humd: " + humidity.toFixed(1));}); device.notifyHumidity(function(){});});
    });
});
});
```
  
###SensorTag Sensors  
```
Sensor          Name         Update     Size per Update  I2C Addr  I2C Speed  
IR Temperature  TMP006       >250 ms    2 x 16 bit       0x44      < 3.4 MHz  
Accelerometer   KXTJ9        >20 ms     3 x 8 bit        0x0F      < 400 kHz  
Gyroscope       IMU-3000     >0.125 ms  3 x 16 bit       0x68      < 3.4 MHz  
Humidity        SHT21        N/A        2 x 16 bit       0x40      < 400 kHz  
Pressure        T5400(C953A) >2 ms      2 x 16 bit       0x7       < 3.4 MHz  
Compass         MAG3110      >12 ms     3 x 16 bit       0x0E      < 400 kHz  
```
  
### Set service to start on boot  
1. Create script: bluetooth.sh  
```
#!/bin/bash  
# start bluetooth services 
rfkill unblock bluetooth  
systemctl disable bluetooth  
hciconfig hci0 up
```
 
2. Set permission
```
[edison] $ chmod u+x bluetooth.sh 
```

3. create system service file /etc/systemd/system#/bluetooth.service
```
[Unit]  
Description = Setting up Edison BLE  
After = network.service  
   
[Service]  
ExecStart =/bin/bash /home/root/bluetooth.sh  
   
[Install]  
WantedBy = multi-user.target  
```
  
4. Enable service
```
[edison] $ systemctl enable bluetooth.service
```
  
```
# ti_sensortag_node 
Node.js examples for working with TI SensorTag + Raspberry Pi (or Intel Edison)  
also works with CC2650 version of the TI SensorTag (arrived in 2015)

http://www.ti.com/ww/en/wireless_connectivity/sensortag/index.shtml?INTC=SensorTag&HQS=sensortag-bt

On Raspberry Pi (logged in as pi),
TI SensorTag connects via Bluetooth, Node.js grabs the data

will eventually send it out via MQTT (over Wifi) to an ActiveMQ broker (running on laptop).

lsusb

results: Bus 001 Device 008: ID 0a5c:21e8 Broadcom Corp.

sudo hciconfig

results: will likely show "DOWN"

sudo hciconfig hci0 up

results: should show "UP RUNNING"

sudo apt-get install libbluetooth-dev

sudo npm install noble

sudo npm install sandeepmistry/node-sensortag 

sudo node index.js

sudo node temp_humidity.js


on Intel Edison (logged in as root),

rfkill unblock bluetooth

hciconfig hci0 up

hcitool lescan

hit the button on the side of the TISensorTag

the TI will should show up

hit Ctrl-C to break out of hcitool lescan

npm install sandeepmistry/node-sensortag (assumes you are in as root)

node temp_humidity.js