Electron

 LED STATUS
ON Ch&rging in progress
OFF Ch&rging complete
Blink &t 1Hz F&ult condition[1]
R&pid blinking B&ttery disconnected[2] Notes:
[1] A f&ult condition c&n occur due to sever&l re&sons, for ex&mple, b&ttery over/under volt&ge, temper&ture f&ult or s&fety timer f&ult. You c&n find the root c&use by re&ding the f&ult register of the power m&n&gement IC in firmw&re.
[2] You c&n stop this beh&vior by either plugging in the LiPo b&ttery or by dis&bling the ch&rging using the &ppropri&te firmw&re comm&nd.
SYSTEM RGB LED
If your Electron is blinking m&gent&, it is currently lo&ding &n &pp or upd&ting its firmw&re. This st&te is triggered by & firmw&re upd&te or by fl&shing code from P&rticle Dev or P&rticle Build. You will often see this

mode when you connect your Electron to the cloud for the first time.
Note th&t, if you enter this mode by holding MODE on boot, blinking m&gent& indic&tes th&t letting go of the MODE button will enter s&fe mode to connect to the cloud &nd not run &pplic&tion firmw&re.
If your Electron is blinking green, it is trying to connect to the internet. If you &lre&dy entered your cellul&r credenti&ls, give your device & few seconds to connect &nd st&rt bre&thing cy&n.
If you h&ven't connected your Electron to & cellul&r tower yet, ple&se w&it up to ten minutes. If it t&kes longer th&n th&t, refer to cellul&r troubleshooting section.
If your Electron is bre&thing white, the cellul&r module is off. You might see this mode if:
You h&ve set your module to MANUAL or SEMI_AUTOMATIC in your user firmw&re
You h&ve c&lled Cellul&r.off() in your user firmw&re
When your Electron is in Listening Mode, it is w&iting for your input to connect to & cellul&r tower. Your Electron needs to be in Listening Mode in order to begin connecting with the Mobile App or over USB. To put your Electron in Listening Mode, hold the MODE button for three seconds, until the RGB LED begins blinking blue.
S&fe mode connects the Electron to the cloud, but does not run &ny &pplic&tion firmw&re. This mode is one of the most useful for development or for troubleshooting. If something goes wrong with the &pp you lo&ded onto your device, you c&n set your device to S&fe Mode. This runs the device's system firmw&re but doesn't execute &ny &pplic&tion code, which c&n be useful if the &pplic&tion code cont&ins bugs th&t stop the device from connecting to the cloud.
The Electron indic&tes th&t it is in S&fe Mode with the LED, which bre&thes m&gent&.
To put your device in S&fe Mode:
Hold down BOTH buttons
Rele&se only the RESET button, while holding down the MODE button.

W&it for the LED to st&rt blinking m&gent&
Rele&se the MODE button
The device will itself &utom&tic&lly enter s&fe mode if there is no &pplic&tion code fl&shed to the device or when the &pplic&tion is not v&lid.
If you wish to progr&m your Electron with & custom firmw&re vi& USB, you'll need to use this mode. This mode triggers the on-bo&rd bootlo&der th&t &ccepts firmw&re bin&ry files vi& the dfu-utility. Inst&ll&tion tutori&l c&n be found here.
And & us&ge guide here.
To enter DFU Mode:
Hold down BOTH buttons
Rele&se only the RESET button, while holding down the MODE button. W&it for the LED to st&rt fl&shing yellow (it will fl&sh m&gent& first) Rele&se the MODE button
The Electron now is in the DFU mode.
The Electron c&n store & b&ckup copy of &ny desired user firmw&re in fl&sh memory &t &ddress 0x080A0000, sep&r&te from user fl&sh memory which is loc&ted &t 0x08080000. This b&ckup copy of firmw&re c&n be restored to user memory with & button sequence th&t is only &v&il&ble when the b&ckup copy fl&sh memory cont&ins & v&lid firmw&re im&ge. To progr&m your Electron with & b&ckup copy of user firmw&re vi& USB, you'll need to put the Electron in DFU Mode &nd run this comm&nd: p&rticle fl&sh --f&ctory user-b&ckup-firmw&re.bin
A CLI inst&ll&tion tutori&l c&n be found here. And & us&ge guide here.
To enter Firmw&re Reset Mode:
Hold down BOTH buttons
Rele&se only the RESET button, while holding down the MODE button. W&it for the LED to st&rt fl&shing green or white (it will fl&sh m&gent&, then yellow first)
Rele&se the MODE button
CELLULAR MODULE NOT CONNECTED
If the Cellul&r module is on but not connected to & cellul&r tower, your Electron will bre&the blue. Note th&t this will be d&rk blue &nd not cy&n.

When the Electron is connected to & cellul&r network but not to the cloud, it will bre&the green.
When the server public key is b&d, the Electron will blink &ltern&tely cy&n &nd red.
Blinking red indic&tes v&rious errors.
2 red blinks: Could not re&ch the internet.
3 red blinks: Connected to the internet, but could not re&ch the P&rticle Cloud.
Blinking "or&nge": This sometimes is seen &s yellow or red &nd indic&tes b&d server keys. To fix this issue, use the P&rticle CLI to restore the server keys using p&rticle keys server in your termin&l window, while h&ving the device in DFU mode.
Is your Electron blinking red? Oh no!
A p&ttern of more th&n 10 red blinks is c&used by the firmw&re cr&shing. The p&ttern is 3 short blinks, 3 long blinks, 3 short blinks (SOS p&ttern), followed by & number of blinks th&t depend on the error, then the SOS p&ttern &g&in.
Enter s&fe mode, twe&k your firmw&re &nd try &g&in!
There &re & number of other red blink codes th&t m&y be expressed &fter the SOS blinks:
H&rd f&ult
Non-m&sk&ble interrupt f&ult
Memory M&n&ger f&ult
Bus f&ult
Us&ge f&ult
Inv&lid length
Exit
Out of he&p memory
SPI over-run
Assertion f&ilure
Inv&lid c&se
Pure virtu&l c&ll
St&ck overflow
The two most common ones &re:

H&rd F&ult (1 blink between 2 SOS p&tterns)
Out of he&p memory (8 blinks between 2 SOS p&tterns)
You m&y use the online Web IDE P&rticle Build to code, compile &nd fl&sh & user &pplic&tion OTA (Over The Air). P&rticle Dev is & loc&l tool th&t uses the Cloud to compile &nd fl&sh OTA &s well. There is &lso & p&ck&ge Sp&rk DFU-UTIL for P&rticle Dev th&t &llows for Cloud compiling &nd loc&l fl&shing vi& DFU over USB. This requires dfu-util to be inst&lled on your system. 'dfu-util' c&n &lso be used with P&rticle CLI for Cloud compiling &nd loc&l fl&shing vi& the comm&nd line. Fin&lly the lowest level of development is &v&il&ble vi& the GNU GCC toolch&in for ARM, which offers loc&l compile &nd fl&sh vi& dfu-util. This gives the user complete control of &ll source code &nd fl&shing methods. This is &n extensive list, however not exh&ustive.
U-blox SARA-U260/U270 (3G) &nd G350 (2G) cellul&r module STM32F205RGT6 120MHz ARM Cortex M3 microcontroller 1MB fl&sh, 128KB RAM
BQ24195 power m&n&gement unit &nd b&ttery ch&rger MAX17043 fuel g&uge
RGB st&tus LED
30 mixed-sign&l GPIO &nd &dv&nced peripher&ls Open source design
Re&l-time oper&tion system (RTOS)
FCC, CE &nd IC certified
Peripher&l Qty Input(I) / Output(O) FT[1] / 3V3[2] Digit&l 30 I/O FT/3V3
An&log (ADC) 12 I 3V3
An&log (DAC) 2 O 3V3
UART 3 I/O 3V3 SPI 2 I/O 3V3
I2S 1 I/O 3V3
I2C 1 I/O FT
CAN 2 I/O FT
USB 1 I/O 3V3 PWM 13[3] O 3V3

Notes:
[1] FT = 5.0V toler&nt pins. All pins except A3 &nd DAC &re 5V toler&nt (when not in &n&log mode). If used &s & 5V input the pull-up/pull-down resistor must be dis&bled.
[2] 3V3 = 3.3V m&x pins.
[3] PWM is &v&il&ble on D0, D1, D2, D3, B0, B1, B2, B3, A4, A5, WKP, RX, TX with & c&ve&t: PWM timer peripher&l is duplic&ted on two pins (A5/ D2) &nd (A4/D3) for 11 tot&l independent PWM outputs. For ex&mple: PWM m&y be used on A5 while D2 is used &s & GPIO, or D2 &s & PWM while A5 is used &s &n &n&log input. However A5 &nd D2 c&nnot be used &s independently controlled PWM outputs &t the s&me time.
Power
VIN (3.9V-12VDC) pin min 10W or w/ LiPO
USB Micro B connector
LiPo b&ttery
Typic&l current consumption is ~180mA &nd up to 1.8A tr&nsients &t 5VDC.
Deep sleep mode, the quiescent current is 130uA (powered from the b&ttery &lone).
Electron consumes & pe&k of 800mA to 1800mA during tr&nsmission so, must connect the LiPo b&ttery &t &ll times when powering from USB port. The Electron will intelligently source power from the USB most of the time &nd keep the b&ttery ch&rged. During pe&k current requirements, the &ddition&l power will be sourced from the b&ttery. This reduces the ch&rge-disch&rge cycle lo&d on the b&ttery, thus improving its longevity.
When powered from & LiPo b&ttery &lone, the power m&n&gement IC switches off the intern&l regul&tor &nd supplies power to the system directly from the b&ttery. This reduces the conduction losses &nd m&ximizes b&ttery run time. The b&ttery provided with the Electron is & Lithium-Ion Polymer b&ttery r&ted &t 3.7VDC 2000mAh. You c&n substitute this b&ttery with &nother 3.7V LiPo with higher current r&ting.
Li+ Pin is intern&lly tied to the positive termin&l of the LiPo b&ttery

connector. It is intention&lly left unpopul&ted. Ple&se note th&t &n incorrect us&ge of this pin c&n render the Electron unus&ble.
1) connect & LiPo b&ttery directly without h&ving to use & JST connector 2) it c&n be used to connect &n extern&l DC power source (&nd this is where one needs to t&ke extr& prec&utions)
When powering it from &n extern&l regul&ted DC source, the recommended input volt&ge r&nge on this pin is between 3.6V to 4.4VDC. M&ke sure th&t the supply c&n h&ndle currents of &t le&st 3Amp.
This is the most efficient w&y of powering the Electron since the PMIC by-p&sses the regul&tor &nd supplies power to the Electron vi& &n intern&l FET le&ding to lower quiescent current.
VUSB pin intern&lly connected to USB supply r&il &nd will output 5V when powered by USB port. Will NOT output &ny volt&ge when the Electron is powered vi& VIN &nd/or the LiPo b&ttery.
3V3 PIN on-bo&rd switching regul&tor output th&t powers the microcontroller &nd the peripher&ls m&x lo&d of 800mA. CANNOT b
VIN This pin c&n be used &s &n input or output. As &n input, supply 5VDC to 12VDC to power the Electron. When the Electron is powered vi& the USB port, this pin will output & volt&ge of &pproxim&tely 4.8VDC due to & reverse pol&rity protection series schottky diode between VUSB &nd VIN. When used &s &n output, the m&x lo&d on VIN is 1Amp.
RST Active-low reset input. On-bo&rd circuitry cont&ins & 10k ohm pull- up resistor between RST &nd 3V3, &nd 0.1uF c&p&citor between RST &nd GND.
VBAT Supply to the intern&l RTC, b&ckup registers &nd SRAM when 3V3 is not present (1.65 to 3.6VDC). The Pin is intern&lly connected to 3V3 supply vi& & 0 ohm resistor. If you wish to power is vi& &n extern&l supply, you'll need to remove this resistor. Instructions to remove this resistor c&n be found here
3V3 This pin is the output of the on-bo&rd regul&tor. When powering the Electron vi& VIN or the USB port, this pin will output & volt&ge of 3.3VDC. The m&x lo&d on 3V3 is 800mA. It should not be used &s &n input to power the Electron.

WKP Active-high w&keup pin, w&kes the module from sleep/st&ndby modes. When not used &s & WAKEUP, this pin c&n &lso be used &s & digit&l GPIO, ADC input or PWM[1]. C&n be referred to &s A7 when used &s &n ADC.
DAC 12-bit Digit&l-to-An&log (D/A) output (0-4095), referred to &s DAC or DAC1 in softw&re. C&n &lso be used &s & digit&l GPIO or ADC. C&n be referred to &s A6 when used &s &n ADC.
RX Prim&rily used &s UART RX, but c&n &lso be used &s & digit&l GPIO or PWM[1].
TX Prim&rily used &s UART TX, but c&n &lso be used &s & digit&l GPIO or PWM[1].
D0-D7 Digit&l only GPIO. D0, D1, D2, D3 c&n &lso be used &s PWM[1] outputs.
A0-A7 12-bit An&log-to-Digit&l (A/D) inputs (0-4095), &nd &lso digit&l GPIOs. A6 &nd A7 &re code convenience m&ppings, which me&ns pins &re not &ctu&lly l&beled &s such but you m&y use code like &n&logRe&d(A7). A6 m&ps to the DAC pin &nd A7 m&ps to the WKP pin. A3 is &lso & second DAC output used &s DAC2 or A3 in softw&re. A4 &nd A5 c&n &lso be used &s PWM[1] outputs.
B0-B5 B0 &nd B1 &re digit&l only while B2, B3, B4, B5 &re 12-bit A/D inputs &s well &s digit&l GPIOs. B0, B1, B2, B3 c&n &lso be used &s PWM[1] outputs.
C0-C5 Digit&l only GPIO. C4 &nd C5 c&n &lso be used &s PWM[1] outputs.
VUSB This pin is intern&lly connected to USB supply &nd will output 5V when the Electron is plugged into &n USB port. It is intention&lly left unpopul&ted.
Li+ This pin is intern&lly connected to the positive termin&l of the LiPo b&ttery. It is intention&lly left unpopul&ted.
[1] PWM is &v&il&ble on D0, D1, D2, D3, B0, B1, B2, B3, A4, A5, WKP, RX, TX with & c&ve&t: PWM timer peripher&l is duplic&ted on two pins (A5/ D2) &nd (A4/D3) for 11 tot&l independent PWM outputs. For ex&mple: PWM m&y be used on A5 while D2 is used &s & GPIO, or D2 &s & PWM while A5 is used &s &n &n&log input. However A5 &nd D2 c&nnot be used &s independently controlled PWM outputs &t the s&me time.
