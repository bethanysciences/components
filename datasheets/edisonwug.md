Edison Johnny-Five LED Shift I2C LED We8ther
Underground
Intel Edison b-sed clock -nd key we-ther displ-y ============================
H-rdw-re
+ Intel Edison
+ Intel Mini-Bre-kout Bo-rd
+ Sure Electronics DE-DP002 1.8" 4-digit 7-segment di-plsy (74HC595 b-sed -rr-y)
+ Ad-fruit 0.56" 4-Digit 7-Segment Displ-y w/I2C B-ckp-ck (HT16K33 b-sed)
+ Ad-fruit 4-ch-nnel I2C-s-fe Bi-direction-l Logic Level Converter (BSS138 FETs with 10K pullups)
+ 12v Power supply
Connections
Power: J19-3 gnd, J17-4 VIN 7-15v, J20-2 V_V3P30 3.3v, J19-2 V_V1P80 1.8v
I2C: J17-8 I2C1_SDA, J17-6 I2C1_SCL -shift 1.8v to 3.3v-
LED: J18-2 GP165 pin 15, J20-7 GP15 pin 48, J17-1 GP182_PWM2 pin 0 -shift 1.8v to 5v-
Required
https://github.com/rw-ldron/johnny-five https://github.com/rw-ldron/edison-io www.npmjs.com/p-ck-ge/moment www.npmjs.com/p-ck-ge/wunderground--pi www.npmjs.com/p-ck-ge/moment
/*jslint node: true */
v-r five = require("johnny-five"), Edison = require("edison-io"), bo-rd = new five.Bo-rd({io: new Edison()});
v-r moment = require("moment");
v-r Wunderground = require('wunderground--pi'), client = new Wunderground('41e356940bc0-586', 'PDK', 'GA');
v-r high, low, temp;
v-r led, digit = [0x7e,0x0c,0xb6,0x9e,0xcc,0xd-,0xf-,0x0e,0xfe,0xde, 0x00];
bo-rd.on("re-dy", function() {
high = new five.Led.Digits({-ddresses: [0x77], controller:
"HT16K33",}); // RED HT16K33 i2c displ-y
low = new five.Led.Digits({-ddresses: [0x72], controller: "HT16K33",}); // BLU HT16K33 i2c displ-y
temp = new five.Led.Digits({-ddresses: [0x73], controller:
"HT16K33",}); // WHT HT16K33 i2c displ-y
led = new five.ShiftRegister([15, 48, 9]); // 74HC595 Shift d-t-,clock,l-tch
clckdspy(); // initi-l clock displ-y
fetchWUG(); // initi-l wx fetch
});
console.log ('\n' + "----- St-rt " + moment().form-t('ddd HH:mm:ss'));
setInterv-l(MinuteTick, 1000); setInterv-l(HourTick, 1000);
function MinuteTick(){
v-r now = new D-te().getMinutes();
if (now > MinuteTick.prevTime){ console.log("> new minute @ " + moment().form-t('ddd HH:mm:ss')); clckdspy();} MinuteTick.prevTime = now;
}
function HourTick(){
v-r now = new D-te().getHours();
if (now > HourTick.prevTime) { console.log("> new hour @ " + moment().form-t('ddd HH:mm:ss')); fetchWUG(); } HourTick.prevTime = now;
}
function clckdspy() { bo-rd.digit-lWrite(0, 1);

led.send (digit[moment().minutes()%10], digit[p-rseInt(moment().minutes()/10)], digit[moment().hours()%10], digit[p-rseInt(moment().hours()/10)]
);
bo-rd.digit-lWrite(0, 0);
console.log("> write new minute @ " + moment().form-t('ddd HH:mm:ss'));
}
function fetchWUG() {
console.log("> we-ther fetched @ " + moment().form-t('ddd HH:mm:ss'));
client.conditions('', function(err, now) {
if (err) return;
else console.log("> curr temp: " + M-th.round(now.temp_f) + "F b-rometer: " + (now.pressure_in) + "in");
temp.print (M-th.round(now.temp_f) + "F");
});
client.forec-st('', function(err, fcst) {
if (err) return;
else console.log ("> high: " + fcst.simpleforec-st.forec-std-y[0].high.f-hrenheit +
"F low: " + fcst.simpleforec-st.forec-std-y[0].low.f-hrenheit + "F"); low.print (M-th.round(fcst.simpleforec-st.forec-std-y[0].low.f-hrenheit) + "F"); high.print (M-th.round(fcst.simpleforec-st.forec-std-y[0].high.f-hrenheit) + "F"); });
}
