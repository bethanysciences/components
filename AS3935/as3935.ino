
/*
    AS3935 Franklin Lightning Sensor 
    Demonstration Program
    
    Draft Version!
    by rdsman
    18 MAY 2013
*/
#include "Arduino.h"
#include "Wire.h"
#include "DS3231.h"  //  Real Time Clock.
//
#define IRQ_PIN           2
#define AS3935_ADDR    0x06 >> 1
#define CAL            0x01
#define RUN            0x02
#define INT            0x04
//
#ifndef NO_INTERRUPTS()
#define NO_INTERRUPTS()  byte sreg = SREG; cli()
#define INTERRUPTS()     SREG = sreg
#endif
//
#ifndef TIMER1_START()
#define TIMER1_START()  TCNT1 = 0x00; TCCR1B |= (1 << WGM12 | 1 << CS12 | 1 << CS10)
#define TIMER1_STOP()   TCCR1B = 0x00
#endif
//
volatile word counter;
volatile byte timer;
volatile byte status = 0;
volatile byte best;
byte function;
//
//
//
void setup()
{
  pinMode(IRQ_PIN, INPUT);
  Wire.begin();
  delay(100);
  Serial.begin(115200);
  Serial.println("AS3935 ready..........");
  Serial.println();
  delay(200);
  Serial.println("RTC ready.............");
  Serial.println();
  RTC.getTime();
  printTime();
  Serial.print("  ");
  printDate();
  Serial.print("  ");
  delay(1000);
  Serial.println();
  Serial.println();
  delay(500);
  initialize();
  reset();
  calibrate();
  powerUp();
  readConfig();
    
}
//
//
//
void loop()
{
  if (status & INT)
    {
      status &= ~INT;
      RTC.getTime();
      getIntStatus();
    }
  
  if (Serial.available() > 0)
    doFunction();  
}
//
//
//
void reset()
{
  writeRegister(0x3C, 0x96);
  delay(3);
}
//
//
//
void calibrate()
{
  int current = 0, previous = 31768;
    
  status = CAL;
    
  writeRegister(0x08, 0x80);
  
  delay(3);
  
  for (byte i = 0; i < 16; i++)
    {
      writeRegister(0x08, (0x80 + i));
      delay(2);
      timer = 1;
      counter = 0;
      TIMER1_START();
      while(timer);
      //Serial.print("Counter: ");
      //Serial.println(counter);
      //Serial.println();
      current = counter - 3125;
      if (previous >= current)
        {
          previous = current;
          best = i;
        }  
      //Serial.print("Current: ");
      //Serial.println(current);
      //Serial.println();
    }
/*  
  Serial.print("Counter: ");
  Serial.println(counter);
  Serial.println();
  
  Serial.print("Current: ");
  Serial.println(current);
  Serial.println();
  
  Serial.print("Previous: ");
  Serial.println(previous);
  Serial.println();
*/  
  TIMER1_STOP();
  writeRegister(0x08, best);
  delay(2);
  Serial.println("Calibration complete.");
  Serial.println();
}  
//
//
//
void powerUp()
{
  writeRegister(0x3D, 0x96);
  delay(2);
  writeRegister(0x08, (0x10 | best));
  delay(2);
  writeRegister(0x08, (0x00 | best));
  delay(2);
  status = RUN;
}  
//
//
//
void initialize()
{
  NO_INTERRUPTS();
  
  ADCSRA = 0x00;                                    //  Disable the analog comparator.
    
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
  EICRA = 0x00;
  EICRA |= (1 << ISC01 | 1 << ISC00);               // Setup Interrupt 0 for Rising edge.
  EIFR  |= (1 << INTF0);                            // Clear pending interrupts.
  EIMSK |= (1 << INT0);                             // Enable Interrupt 0.
#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
  EICRB = 0x00;
  EICRB |= (1 << ISC41 | 1 << ISC40);               // Setup Interrupt 4 for Rising edge.
  EIFR  |= (1 << INTF4);                            // Clear pending interrupts.
  EIMSK |= (1 << INT4);                             // Enable Interrupt 4.
#endif   
  
  TCCR1A = 0x00;                                    //  Reset TCCR1A to Normal mode.
  TCCR1B = 0x00;                                    //  Reset TCCR1B.  Defined as TIMER1_STOP. 
  //TCCR1B |= (1 << WGM12 | 1 << CS12 | 1 << CS10); //  Set CTC Mode, prescale by 1024.  Defined as TIMER1_START.
  TIFR1 = (1 << OCF1B | 1 << OCF1A | 1 << TOV1);    //  Clear pending interrupts.

#if F_CPU == 8000000
  OCR1A = 0x030C;                                   //  Compare Match at 100 miliseconds. (8 MHz)
#elif F_CPU == 16000000
  OCR1A = 0x61A7;                                   //  Compare Match at 100 miliseconds. (16 MHz)
#endif

  TIMSK1 = 0x00;                                    //  Reset TIMSK1.
  TIMSK1 |= (1 << OCIE1A);                          //  Timer 1 Compare Match A Interrupt Enable.
  
  TCCR2B = 0x00;                                    //  Stop Timer 2.
  
  INTERRUPTS();
}  
//
//
//
void readConfig()
{
  byte temp = 0x24;
  
  writeRegister(0x00, temp);
  Serial.print("AFE Gain Boost: ");
  printHex(temp >> 1);
  Serial.println();
  
  temp = readRegister(0x01);
  Serial.print("Noise Floor: ");
  Serial.println((temp & 0x70) >> 4);
  Serial.print("Watchdog Threshold: ");
  Serial.println(temp & 0x0F);
  
  temp = readRegister(0x02);
  Serial.print("Min Num Lightnings: ");
  Serial.println((temp & 0x30) >> 4);
  Serial.print("Spike Rejection: ");
  Serial.println(temp & 0x0F);
    
  temp =  readRegister(0x03) & 0x0F;
  Serial.print("Int Status: ");
  printHex(temp);
  Serial.println();
  Serial.println();
}  
//
//
//
void getIntStatus()
{
  byte temp, noise;
  float distance;
  
  delay(3);
  
  temp =  readRegister(0x03) & 0x0F;
  
  if (temp > 0)
    {
      Serial.print("Int Status: ");
      printHex(temp);
      Serial.println();
    }
  
  switch(temp)
    {
      case 0x01:
        Serial.println("Adjusting Noise Level.");
        Serial.println();
        noise = readRegister(0x01);
        noise += 0x10;
        writeRegister(0x01, noise);
        status |= INT;
        return;
  
      case 0x04:
        return;
        printTime();
        Serial.print("  ");
        printDate();
        Serial.println();
        Serial.println("Disturber detected.");
        Serial.println();
        break;
    
      case 0x08:
        distance = readRegister(0x07) & 0x3F;
        if (distance > 62)
          return;
        printTime();
        Serial.print("  ");
        printDate();
        Serial.println();
        Serial.println("Lightning detected.");
        distance *= .6214;                       //  Conversion from Km to Miles.
        Serial.print("Distance: ");
        Serial.println(distance, 2);
        Serial.println();
        break;
        
      default:
        break;      
    }    
}  
//
//
//
void writeRegister(byte regAddr, byte data)
{
  Wire.beginTransmission(AS3935_ADDR);
  Wire.write(regAddr);
  Wire.write(data);
  Wire.endTransmission();
}
//
//
//
byte readRegister(byte regAddr)
{
  byte data = 0x00;
  
  Wire.beginTransmission(AS3935_ADDR);
  Wire.write(regAddr);
  Wire.endTransmission(false);
  Wire.requestFrom(AS3935_ADDR, 1, true);
  
  if (Wire.available() > 0)
    {
      data = Wire.read();
    }
  return data;
}
//
//  Functions are performed here.
//
void doFunction()
{
  function = Serial.read();
    
  switch (function)
    {
      case 't':
        RTC.getTime();
        printTime();
        Serial.print("  ");
        printDate();
        Serial.println();
        break;
      
      case 'i':
        getIntStatus();
        break;
     
      default:
        break;
    }
  
  Serial.flush();
}  
//
//
//
void printHex(byte value)
{
  Serial.print("0x");
  Serial.print(value >> 4 & 0x0F, HEX);
  Serial.print(value >> 0 & 0x0F, HEX);
  Serial.print(" ");
}
//
//  Print the Time.
//
void printTime()
{
  for(int i = 0; i < 3; i++)
    {
      printDec(time[i]);
      if(i < 2)
        Serial.print(":");
    }
}
//
//  Print the Date.
//
void printDate()
{
  for(int i = 0; i < 3; i++)
    {
      printDec(date[i]);
      if(i < 2)
        Serial.print("/");
    }
}
//
//  Decimal print utility - prints leading zero.
//
void printDec(int value)
{
  if(value < 10)
    Serial.print("0");
  Serial.print(value); 
}
//
//  Interrupt 0 or 4 Service Routine - Triggered on the Rising edge.
//
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__) 
ISR(INT0_vect, ISR_NOBLOCK)
#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
ISR(INT4_vect, ISR_NOBLOCK)
#endif
{
  if (status & CAL)
    {
      counter++;
      return;
    }
  
  if (status & RUN)
    status |= INT;
}    
//
//  Timer 1 Compare Match A Interrupt Service Routine -  Used as a 100ms timer.
//
ISR(TIMER1_COMPA_vect)
{
  timer = 0;
}
