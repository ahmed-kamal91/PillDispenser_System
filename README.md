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

![chart-1](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/c0954216-c840-469f-b9f5-d9b3d45834f4)


<h2>__libraries_______</h2>

<b>1-LCD:</b> </br>
#include<LiquidCrystal_I2C.h> </br>
#include<Wire.h> </br>
LiquidCrystal_I2C lcd(0x27, 16, 2); </br>

<b>2-Keypad:</b> </br>
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
 
![chart-2](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/33581b83-099e-445b-a394-d0115bcc4e68)
</br>
![chart-3](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/88c58d96-2a75-42e0-94a1-057ac4a6ecd4)

<h2>__Functions______:</h2>

Core of the system:</br>
set_time function:</br>
First we will build what will appear in lcd (Interface) :</br>
Using : lcd.clear(), lcd.print(), lcd.setCursor():</br>
<pre>
//------interface-------                                                    

  lcd.clear();                                                             
  lcd.setCursor(0,1);                                                       
  lcd.print(" *-del	#-back");                                        	
  lcd.setCursor(0,0);                                                       
  lcd.print("Time: ");                                                      
  lcd.setCursor(8,0);                                                       
  lcd.print(":");                                                           
  lcd.setCursor(6,0);                                                       
</pre>
create variable to save the  inserted time later:</br>
<pre>
String copier;
</pre>
Making a way to wait the user with our rules(function):</br>
 <pre>
  	char key = ;

  	//------wait-input--------- 	

  	key = NO_KEY; 

  	while(key == NO_KEY)

  	{key = keypad.getKey();}

 	//-----------------------------
</pre>
We want to insert numbers from keypad for:</br>

1-add on copier variable.</br>

2-appear on LCD in the right position.</br>

So:</br>
<pre>

          	lcd.print(key);

          	copier = copier + key;
</pre>
inserting number should jump after “:” symbol so we will use length of variable  copier to do that</br>

<pre>
      	if(copier.length() != 2) {

          	lcd.print(key);

          	copier = copier + key;

        	}

      	else {  

          	lcd.setCursor(9,0);

          	lcd.print(key);

          	copier = copier + ":" + key;   }

</pre>
 before we continue we have to discuss EEPROM first </br>

![chart-4](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/a30139de-3dff-403c-8513-0495fd36e354)

2- set_in_EEPROM()

Simply, EEPROM is a non-volatile memory has 1024 place to save the data.</br>
Each place take one char, so we have 4 rooms every room has alarm time in string dtype has 5</br> chars, so we want 20 places for all rooms in EEPROM.</br>
This function made to save time alarm for each room character by character.</br>


<pre>
//-----------set-the-time-in-EEPROM---(function)-------------------------------

void set_in_EEPROM(int start_pos, int end_pos , int extra_pos, String times)

{                                                                           

  for(int i = start_pos ; i < end_pos ; i++)                         	    

  {                                                                         

	Serial.print(times[i]);                                                 

	EEPROM.update(i, times[i - extra_pos]);                                 

  }                                                                         

}                                                                           

//-----------------------------------------------------------------------------
</pre> </br>

We will notice that ( times[i - extra_pos]  ):</br>

Numbers range for EEPROM change while indices of variable not so we have to subtract from start</br> point number to begin range of numbers from 0 as indices does for any variable.</br>


3- get_from_EEPROM function </br>

Almost the same idea of set_in_EEPROM function</br>
<pre>
//--------------getting-epprom-time----------------------------------------------

String get_from_EEPROM(int start_pos, int end_pos)                       	

{                                                                             

  String tim_back;                                                            

  for(int i = start_pos ; i < end_pos ; i++)                               	

  {                                                                           

	char letter = EEPROM.read(i);                                          	

	tim_back = tim_back + letter;                                              

  }                                                                          

                                                                             

  return(tim_back);                       	                                 

}                                                                             

//------------------------------------------------------------------------------- 
</pre>


Lets return to set_time function:</br>
A way to back in case you don’t want to set time</br>
<pre>
  	//-------back--------------	
  	if (key == '#')                	
    	{                      	                        
      	lcd.clear();                                     	
      	lcd.print("ok!...");                                  	
      	delay(500);                             	           
      	switch(room_num)                                   	
      	{                                                        

        	case '1': return(String(get_from_EEPROM(0, 5)));      
        	case '2': return(String(get_from_EEPROM(5, 10)));     
        	case '3': return(String(get_from_EEPROM(10, 15)));     
        	case '4': return(String(get_from_EEPROM(15, 20)));   
      	}                                                      
    	}

 </pre>
Condition for breaking while loop:</br>
<pre>
	 if(copier.length() == 5)                              
    	break;

#finally return copier:
return (copier);
</pre>


Alarm</br>

when it set time (from user  saved in EEPROM) = real time (from RTC module) Arduino gives signals to LEDs and Piezo </br>
putting the last condition on  if condition touch button if its low () there is alarm else stop alarm</br>
