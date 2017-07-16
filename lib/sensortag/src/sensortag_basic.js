/* jslint node:true */
var SensorTag = require("sensortag");

SensorTag.discover(function(device) {
console.log('discovered device with UUID: ' + device.uuid);

device.connect(function() {

    device.discoverServicesAndCharacteristics(function() {

        device.enableBarometricPressure(function() {
            device.setBarometricPressurePeriod(2550, callback(error));
            device.on('barometricPressureChange', function(pressure) {
                console.log("press = "+ pressure);
            });
            device.notifyBarometricPressure(function() {
            });
        });

    device.enableHumidity(function() { 
        device.on('humidityChange', function(temperature, humidity) { 
        console.log("temp: " + temperature.toFixed(1) + "°C humd: " + humidity.toFixed(1));
        }); 
        device.notifyHumidity(function(){
        });
    });

    device.enableLuxometer(function() {
        device.setLuxometerPeriod(2550, function(lux));
        device.on('luxometerChange', function(lux) {
            console.log("lux: " + lux);
        });
        device.notifyLuxometer(function() {
        });
    });

    });
});
});
