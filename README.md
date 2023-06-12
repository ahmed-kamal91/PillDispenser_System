# <center> PillDispenser</center>
* Fully self-Programming pill dispenser system </br>
* product deigned for alert patient with the daily time of Medicine. </br>
* consist of 4 rooms each room take medicine with the same appointement. </br>
* appointment of each room is specified by the patient. </br>

![cropped_pill_idspenser_left](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/42be9d62-cb54-48f7-a8e9-6c5dd1397727)

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
So, it is ease of use: </br>

![PillDispenser](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/aed8e1d4-397c-4357-bb99-a6f5796827fc)

  * simple interface view represnting rooms + using friendly symbols and icon.  
  * easy enter & modify room's alert time.
  * easily show All times allocated to rooms (in general) & allocated time for each room separately (in particular).
  * using real time (RTC).

![home1_resized](https://github.com/ahmed-kamal91/PillDispenser_System/assets/91970695/b7713699-e7e5-4e6b-b19c-f07f74fbb3f7)

  * using touch sensor instead of push button that is quiete harder for finger than touching.
  * ensure awareness of the patient by holding on touch sensor for 2 second to turn off the alert.
  * give flag light by LED to the room where you should take your medicine from.
  * there is plastic separators in each room for easy picking different medicine and separate between them.

# For more Details:
 comming soon, but now, you can check the code yourself </br>
 https://github.com/ahmed-kamal91/PillDispenser_System/blob/main/v10.ino
 
