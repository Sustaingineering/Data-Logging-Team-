float inPin = 0;// pushbutton connected to digital pin
float inPin2 = 1;
float inPin3 = 2;
float inPin4 = 3;
float inPin5 = 4;
float DigPin = 8;
float val = 0;       // variable to store the read value
float val2 = 0;
float val3 = 0;
float val4 = 0;
float val5 = 0;
float val6 = 0;
unsigned long time;
float mySensVals[7] ;
#include <SPI.h>
#include <SD.h>

File myFile;
void setup()
{
Serial.begin(9600);
  pinMode(inPin, INPUT);        // sets the digital pin 7 as input
  pinMode(DigPin, INPUT);
  pinMode(inPin2, INPUT);
  pinMode(inPin3, INPUT);
  pinMode(inPin4, INPUT);
  pinMode(inPin5, INPUT);
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
  val = 0;   
  val3 = 0; 
  val4 = 0;   
  val5 = 0;   
  val6 = 0;     
  time = millis();
  for(int i = 0; i<5; i++)
  {
   val2 += analogRead(inPin);     
   val3 += analogRead(inPin2);
   val4 += analogRead(inPin3); 
   val5 += analogRead(inPin4);
   val6 += analogRead(inPin5);
   delay(1000);    
  }
  val2 = val2/500;   
  val3 = val3/500; 
  val4 = val4/500;   
  val5 = val5/500;   
  val6 = val6/500;     
  val = digitalRead(DigPin);
   
  Serial.print(time/1000);
  Serial.print(',');
  Serial.print(val);
  Serial.print(',');
  Serial.print(val2);
  Serial.print(',');
  Serial.print(val3);
  Serial.print(',');
  Serial.print(val4);
  Serial.print(',');
  Serial.print(val5);
  Serial.print(',');
  Serial.print(val6);
  Serial.print('\n');
  mySensVals[0] = {time/1000};
  mySensVals[1] = {val};
  mySensVals[2] = {val2};
  mySensVals[3] = {val3};
  mySensVals[4] = {val4};
  mySensVals[5] = {val5};
  mySensVals[6] = {val6};
          
  myFile = SD.open("test28.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.print(mySensVals[0]);
    myFile.print(',');
    myFile.print(mySensVals[1]);
    myFile.print(',');
    myFile.print(mySensVals[2]);
    myFile.print(',');
    myFile.print(mySensVals[3]);
    myFile.print(',');
    myFile.print(mySensVals[4]);
    myFile.print(',');
    myFile.print(mySensVals[5]);
    myFile.print(',');
    myFile.println(mySensVals[6]);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test28.txt");
  if (myFile) {
    Serial.println("test28.txt:");

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

}
