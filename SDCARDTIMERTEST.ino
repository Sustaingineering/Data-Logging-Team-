double RawValue1 = 0;     // Variable for running average of analog read
double RawValue2 = 0;
double RawValue3 = 0;
double RawValueavg = 0;   // Variable for running average
double HallVoltage = 0;   // Variable for voltage reading of Hall Effect Sensor
double HallAmps = 0;      // Variable for current reading of Hall Effect Sensor
double DivVoltage = 0;    // Variable for voltage from the voltage divider
double VSource = 0; 
double RH = 969000;
double RL = 24783;
float volt;
float temp;

/*
  The circuit:
    SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
 ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
 ** CS - depends on your SD card shield or module.
     Pin 4 used here for consistency with other Arduino examples

    DS3231 attached to Arduino as follows:
 ** GND - GND on Arduino
 ** VCC - 5V on Arduino
 ** SDA - A4 on Arduino
 ** SCL - A5 on Arduino
 */

unsigned long time;
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "DS3231.h"

RTClib RTC;


File myFile;
void setup()
{
Serial.begin(9600);
Wire.begin();
 RawValue1 = analogRead(A0);   // Take one initial reading
 RawValue2 = analogRead(A0);   // Take second initial reading

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
}


void loop()
{  
  DateTime now = RTC.now();

  // Take previous three readings
 RawValue3 = RawValue2;         // Take reading at time index (n-2)
 RawValue2 = RawValue1;         // Take reading at time index (n-1)
 RawValue1 = analogRead(A0);    // Take reading at time index (n)

 // Take running average
 RawValueavg = (RawValue1+RawValue2+RawValue3) / 3;
 
 // Convert voltage value from binary to decimal
 HallVoltage = (RawValueavg / 1023.0) * 5;

 // Compute the current from the voltage reading
 HallAmps = HallVoltage/0.13720695 - 2.51/0.13720695;

 // Read Voltage at divider
 DivVoltage = analogRead(A1);
 DivVoltage = ((DivVoltage) / 1023.0) * 5;

 VSource = (DivVoltage * (RH + RL))/RL ;

 float sensorValue = analogRead(A2) ;

 // Convert the analog reading ( which goes from 0 - 1023) to a voltage (0 - 5V):
 float voltage = sensorValue *5000/1023+25;

       if(voltage > 2500)
       {
         volt = voltage-2500;//(while cold conjuction is 22 degree
         volt=  volt / 123; //(opamp amplified 150 times)
         temp = (volt)/0.041 +25  ;//( 1 degree = 0.0404 mv in K type )
         }

       else{
         volt = 2500-voltage;//(while cold conjuction is 22 degree
                            //   the voltage cross thermolcouple is 1.67v)
               volt=  volt / 123; //(opamp apmplified 150 times)

         temp = 25-(volt)/0.0404  ;//( 1 degree = 0.0404 mv in K type )

                            }
 
 // Display Raw Value
 Serial.print("Time = " );
 Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC); 
 Serial.print(" Raw Value = " );
 Serial.print(RawValueavg); 

 // Display Vout
 Serial.print("\t Vout = ");
 Serial.print(HallVoltage,2); 

 // Display current reading
 Serial.print("\t Amps = ");
 Serial.print(HallAmps,2);
 Serial.print("\t Volts = ");
 Serial.print(DivVoltage,6);
 Serial.print("\t VSource = ");
 Serial.print(VSource);
 Serial.print("\t Temperature = ");
 Serial.println(temp);


          
  myFile = SD.open("test157.txt", FILE_WRITE); // the file name testnum is just the text file we write to 
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.print("Time =  ");
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(' ');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC); 
    myFile.print("\t Raw Value = ");
    myFile.print(RawValueavg);
    myFile.print("\t Vout = ");
    myFile.print(HallVoltage);
    myFile.print("\t Amps");
    myFile.print(HallAmps);
    myFile.print("\t Volts");
    myFile.print(DivVoltage);
    myFile.print("\t VSource");
    myFile.print(VSource);
    myFile.print("\t Temperature = ");
    myFile.println(temp);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  /* \\ this code will read the data just stored on the SD Card, ensure file names match
  myFile = SD.open("test151.txt");
  if (myFile) {
    Serial.println("test151.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  */
  delay(1000);

}
