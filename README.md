# <center> PillDispenser</center>
* Fully self-Programming pill dispenser system </br>
* product deigned for alert patient with the daily time of Medicine. </br>
* consist of 4 rooms each room take medicine with the same appointement. </br>
* appointment of each room is specified by the patient. </br>

![cropped_pill_idspenser_left](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/07dd7135-34ed-4822-b728-228beb13f7bf)

# Components

* (LCD) : for user interface  
* (Keypad) : for interacting with th system
*  (Touch sensor): for turn off alarm, </br>
* (piezo) : the actual alarm
*  (LED): to flag the speicifed room. </br>

![components](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/ebfe4ba5-587b-4a39-b328-556d0e683ff1)

<pre>
<b>External:</b>                      <b>Internal:</b></br>
- LCD                          - Arduino Uno </br>
- Keypad                       - I2C </br>
- Touch sensor                 - RTC </br>
- piezo                        - mega Breadboard </br>
- LED 
</pre>



# What's special about it?
we try to eliminate some constraints and limits that make it quiete hard to use. </br>
So, it became ease of use: </br>

![PillDispenser4](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/a00fea07-18d3-4695-8c0c-c18c7f3c1f73)

  * simple interface view represnting rooms   
  * easyily modify room's alert time.
  * easily show All times allocated to rooms (in general) & </br>
  allocated time for each room separately (in particular).
  * using friendly symbols and icon.
 
<left>![home1_resized](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/e705d143-187e-4a85-bbab-2c5ce6692f04)
</left>

  * using touch sensor instead of push button that is quiete harder </br> 
  for finger than touching.
  * ensure awareness of the patient </br> by holding on touch sensor for 2 second to turn off the alert.
  * give flag light by LED to the room where you should take your medicine from.
  * there is plastic separators in each room for easy picking different medicine and separate between them.

# Code explanation:
 you can check the code yourself </br>
 https://github.com/ahmed-kamal91/PillDispenser_System/blob/main/v10.ino
 
 <h2>__Over View______</h2>
 notice: THIS CHART EXPLAIN CODE FOR ONE ROOM:- </br>
all system depends on the equality of the alarm and real time so i began with if else statement check the equality </br>
most part of the system go through the un-equality  of  the alarm and real time and the rest of code shows alarm behavior. </br>
![chart-1](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/00b21e7d-153f-45d1-97dd-44006361cd58)

<h2>__libraries_______</h2>

<b>1-LCD:</b>
#include<LiquidCrystal_I2C.h> </br>
#include<Wire.h> </br>
LiquidCrystal_I2C lcd(0x27, 16, 2); </br>

<b>2-Keypad:</b>
#include<Keypad.h> </br>
const int ROW_NUM = 4; //four rows</br>
const int COLUMN_NUM = 3; //three columns </br>
char keys[ROW_NUM][COLUMN_NUM] = { </br>
  {'1','2','3'}, </br>
  {'4','5','6'}, </br>
  {'7','8','9'}, </br>
  {'*','0','#'}  </br>
};
byte pin_rows[ROW_NUM] = {8, 7, 6, 5}; </br>
byte pin_column[COLUMN_NUM] = {4, 3, 2}; </br>
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM ); </br>

<b>3-EEPROM:</b> </br>
#include<EEPROM.h> </br>

<b>4-RTC:</b> </br>
#include <TimeLib.h> </br>
#include <DS1307RTC.h> </br>
 
