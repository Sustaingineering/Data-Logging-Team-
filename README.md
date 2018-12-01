# Data Logging System

## Overview
  The data logging system is designed to record sensor information including time, voltage, current, and temperature and write it to an SD card. Once written on the SD card the data can be accessed by a technician in order to monitor pump performance and perform troubleshooting. This data is also shared with the GSM and GUI teams in order to send it over the network so the pumps can be monitored remotely and seen in a graphical representation.
  
## Data format 
  The data is currently being stored as combination of strings and doubles with the string describing the attribute being recorded and the double being the numerical value (ex. Volts = 2.50). The formatting will be need to be changed to be JSON to assist the GSM and GUI teams. The data logging will also work in conjunction with the GSM network to send sensor reading over the network at set intervals. The exact details of the timing and statistical methods used to generate an accurate value are still being worked out. We expect to send instantaneous values every half hour while also recording the number of times the sensor reads values over certain thresholds in that period. Using instantaneous values instead of an average prevents outliers from being erased once the average is applied, and gives a more accurate view of performance at a given time. However, we will also be recording the number of times values are over a certain threshold in each interval in order to record whenever the pump is not functioning correctly. Once the methods and timing have been decided upon, the data logging system will need to be updated to function in that way.

  
## JSON formatting
  As mentioned before, the SD card data needs to be recorded in JSON format. While there does not seem to be anyway to directly write a JSON object onto the SD card, the formatting can be replicated using strings. This is important for the GUI team as this format is easier to work with when creating visual representations of recorded data. While Arduino has a library to work with JSON objects, the TI Piccolo may not. 

  
## Sensors Values
  The data logging system records data from three sensors and records time, voltage, current, and temperature. The temperature sensor records the instantaneous temperature value at intervals of one second. The current and voltage sensors average the value of the last three readings and then record that value every one second. In fact, a single raw value is read and then the program computes both current and voltage from that. A similar process is used to record temperature from a voltage reading. For now, the system records the time in seconds since it has started running, however once we implement a clock IC the time recorded will be the exact time and date. Recording time with the data will be extremely important in order to synchronize SD card recordings with the data being sent over the GSM network. 

  
## Transferring Microcontrollers
  Another issue that will need to be addressed is transferring the data logging code from Arduino to TI Piccolo. It is easy to write to an SD card using the Arduino SD library, however this will not work for the Piccolo. Either a new library will need to be found or more effort will need to be put into understanding how data can be written to an SD. 

If you are reading this you are likely already on the github page, if not, you can find it here at: [https://github.com/Sustaingineering/Data-Logging-Team-](https://github.com/Sustaingineering/Data-Logging-Team-)
