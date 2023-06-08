#include<Keypad.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#include <string.h>
#include<EEPROM.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
//-------------keypad-parameters-----------
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte pin_rows[ROW_NUM] = {8, 7, 6, 5}; 
byte pin_column[COLUMN_NUM] = {4, 3, 2}; 
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

//-----------declare-function----------------------------------------------------------
String set_time(char);
bool validation(String);
void set_in_EEPROM(int, int, int, String);
String get_from_EEPROM(int, int);
void wait_input();
void Room_(char, int, int);
void Table();
void Time();
void txt_block(char);
void set_block(char, int, int);
void show_block(int, int);
void reset_block(int, int);
String twoDigits(int);
void alarm(int);
void Home();
//-------Global-Varibles----------------------------------------------------------------
char key; 
String str = "";
String tim_1 = get_from_EEPROM(0, 5),
       tim_2 = get_from_EEPROM(5, 10);
       
String tim_3 = get_from_EEPROM(10, 15),
       tim_4 = get_from_EEPROM(15, 20);
       
String timeNow;

int touch = 9;

int led_1 = 10;
int led_2 = 11;
int led_3 = 12;
int led_4 = 13;

int piz = A0;



void setup() 
{
  Serial.begin(9600); 
  //-------init-leds-&-piezo-------
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(touch, INPUT);
  pinMode(piz, OUTPUT);
  //--------initalize--lcd--------
  lcd.backlight();
  lcd.init();
  lcd.setCursor(6,1);
  lcd.print("WELCOME");
  delay(1500);
  lcd.clear();

}

void loop() 
{
  if(tim_1 + ":00" != timeNow   && tim_2 + ":00" != timeNow && tim_3 + ":00" != timeNow && tim_4 + ":00" != timeNow )
  {   
          key = keypad.getKey(); 
          //---------main--list------------
          Home();
          //------------------------------------------  
                         
          wait_input();
               
          switch(key)     /*Rooms*/
            {
               case '1': Room_('1', 0, 5);   break;  
               case '2': Room_('2', 5, 10);  break;   
               case '3': Room_('3', 10, 15); break;   
               case '4': Room_('4', 15, 20); break;
             //----------------------------------
               case '0': Table();          break;
               case '*': Time();           break;
             }     
      }
      else
        alarms_rooms();

}
//--------------------------------------functions-----------------------------------------------------------------

//----------------setting--time--function-------------------------------------
String set_time(char room_num)                                              //
{                                                                           //
//------interface-------                                                    //
  lcd.clear();                                                              //
  lcd.setCursor(0,1);                                                       //
  lcd.print(" *-del    #-back");                                            //
  lcd.setCursor(0,0);                                                       //
  lcd.print("Time: ");                                                      //
  lcd.setCursor(8,0);                                                       //
  lcd.print(":");                                                           //
  lcd.setCursor(6,0);                                                       //
                                                                            //
//---variable-out-loop---                                                   //
  String copier;                                                            //
//------looooop-------------------------------------------------------      //
  while(true)                                                       //      //
     {                                                              //      //
      //---variabe-inside loop---                                   //      //
      char key = keypad.getKey();                                   //      //
                                                                    //      //
      //------wait-input---------                                   //      //
      key = NO_KEY;                                                 //      //
      while(key == NO_KEY)                                          //      //
      {key = keypad.getKey();}                                      //      //
                                                                    //      //
      //-------back--------------                                   //      //
      if (key == '#')                                               //      //
        {                                                           //      //
          lcd.clear();                                              //      //
          lcd.print("ok!...");                                      //      //
          delay(500);                                               //      //
          switch(room_num)                                          //      //
          {                                                         //      //
            case '1': return(String(get_from_EEPROM(0, 5)));        //      //
            case '2': return(String(get_from_EEPROM(5, 10)));       //      //
            case '3': return(String(get_from_EEPROM(10, 15)));      //      //
            case '4': return(String(get_from_EEPROM(15, 20)));      //      //
          }                                                         //      //
        }                                                           //      //
                                                                    //      //
      //----print-&-copy---------------                             //      //
      if(key != '*')                                                //      //
      {   //-------adapt(:)------------                             //      //
          if(copier.length() != 2)                                  //      //
            {                                                       //      //
              lcd.print(key);                                       //      //
              copier = copier + key;                                //      //
            }                                                       //      //
          else                                                      //      //
            {                                                       //      //
              lcd.setCursor(9,0);                                   //      //
              lcd.print(key);                                       //      //
              copier = copier + ":" + key;                          //      //
            }                                                       //      //
      }                                                             //      //
      else if(key == '*' && copier.length() > 0)                    //      //
      {                                                             //      //
          if(copier.length() != 3)                                  //      //
          {                                                         //      //
          lcd.setCursor(copier.length()+5, 0);                      //      //
          lcd.print(" ");                                           //      //
          lcd.setCursor(copier.length()+5, 0);                      //      //
          copier.remove(copier.length()-1,1);                       //      //
          }                                                         //      //
          else                                                      //      //
          {                                                         //      //
            lcd.setCursor(copier.length()+4, 0);                    //      //
            lcd.print(" ");                                         //      //
            lcd.setCursor(copier.length()+4, 0);                    //      //
            copier.remove(copier.length()-2, 2);                    //      //
          }                                                         //      //
      }                                                             //      //
      //--condition-to-end-loop----------                           //      //
      if(copier.length() == 5)                                      //      //
        break;                                                      //      //
      }                                                             //      //
//---------end-loop---------------------------------------------------      //
  return (copier);                                                          //
}//--------------------end-of-function----------------------------------------

//----------------------validation-function-----------------------------------
bool validation(String tim)                                                 //
{                                                                           //
  String hour = tim.substring(0, 2);                                        //
  String minute = tim.substring(3, 5);                                      //
  int hour_int = hour.toInt();                                              //
  int min_int = minute.toInt();                                             //
                                                                            //
  if(hour_int  > 24 || min_int > 60 )                                       //
      return(true);                                                         //
  return (false);                                                           //
  }                                                                         //
//--------------------end-of-function----------------------------------------

//-----------set-the-time-in-EEPROM---(function)-------------------------------
void set_in_EEPROM(int start_pos, int end_pos , int extra_pos, String times) //
{                                                                            //
  for(int i = start_pos ; i < end_pos ; i++)                                 //
  {                                                                          //
    Serial.print(times[i]);                                                  //
    EEPROM.update(i, times[i - extra_pos]);                                  //
  }                                                                          //
}                                                                            //
//-----------------------------------------------------------------------------

//--------------getting-epprom-time----------------------------------------------
String get_from_EEPROM(int start_pos, int end_pos)                             //
{                                                                              //
  String tim_back;                                                             //
  for(int i = start_pos ; i < end_pos ; i++)                                   //
  {                                                                            //
    char letter = EEPROM.read(i);                                              //
    tim_back = tim_back + letter;                                              //
  }                                                                            //
                                                                               //
  return(tim_back);                                                            //
}                                                                              //
//-------------------------------------------------------------------------------

//-------------wait-input----------------------------------------------------------------
void wait_input()
{
  key = NO_KEY; /*resetKey*/
  while (key == NO_KEY)
  {
    tmElements_t tm;

    RTC.read(tm);
        
    timeNow = str + twoDigits(tm.Hour) + ':'
                  + twoDigits(tm.Minute) + ':' 
                  + twoDigits(tm.Second) ;

    Serial.println(timeNow);
    Serial.print("time roooom 2 = ");
    Serial.println(tim_2 + ":00");  
    key = keypad.getKey();
    if ( tim_1 + ":00" == timeNow || tim_2 + ":00" == timeNow || tim_3 + ":00" == timeNow || tim_4 + ":00" == timeNow  )
      { Serial.println("breaaaaak");
        break;}
  }
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------Blocks------------------------------------------------------
void Room_(char room_num, int strt, int End)                                  
{
    timeNow = str + twoDigits(hour())+':'
                    + twoDigits(minute())+':'
                    + twoDigits(second()) ;  
    while(true)
    {                                                 
                                                                 
            txt_block(room_num);  
            Serial.println("Iam Here -3");

            wait_input();

            if(tim_1 + ":00" == timeNow || tim_2 + ":00" == timeNow || tim_3 + ":00" == timeNow || tim_4 + ":00" == timeNow)
              alarms_rooms();


            switch(key)
            {case '1': set_block(room_num, strt, End);  break;  /*set*/
             case '2': show_block(strt, End);           break;  /*show*/
             case '*': reset_block(strt, End);          break;} /*reset*/
            Serial.println("Iam here -2");
            if(key == '#') /*Back*/                                          
            { lcd.clear();                                                   
              break; }                                                       
      }                                                             
  }
  
/*-------------------Set--Block---------------------*/
void set_block(char room_num, int strt, int End)
{
    lcd.clear();                        
    String e_time = set_time(room_num);   
  
    //--------validation----------------      
    while(validation(e_time))       
    {                                    
      delay(300);                            
      lcd.clear();                      
      lcd.print("    invalid !");          
      delay(600);                             
      e_time = set_time(room_num);        
    }                                               
    //------editting-EEPROM------------------     
    set_in_EEPROM(strt, End, strt, e_time);           
    //---------------------------------------

    switch(room_num)
    {
       case '1': tim_1 = get_from_EEPROM(0, 5); break;
       case '2': tim_2 = get_from_EEPROM(5, 10); break;
       case '3': tim_3 = get_from_EEPROM(10, 15); break;
       case '4': tim_4 = get_from_EEPROM(15, 20); break;
    }



     
    

          
    delay(700);                           
    lcd.clear();                        
    lcd.print("Done");            
    delay(1000);                      
    lcd.clear();                       
}
/*---------------Show-Block----------------------------------*/
void show_block(int strt, int End)
{
    lcd.clear();                    
    lcd.print("Current: ");                 
    lcd.setCursor(9,0);                       
                                               
   //---------editting-EEPROM---------------------    
   String time_back = get_from_EEPROM(strt, End);   
   //--------------------------------------------- 
                                               
    lcd.print(time_back);                     
    delay(1000);                                
}

void reset_block(int strt, int End)
{
    lcd.clear();  
    lcd.print("reset...");
    delay(1000);

   //-----editting-EEPROM-------------------      
    set_in_EEPROM(strt, End, strt, "empty");                                       
}
/*------------txt-block------------------------*/

void txt_block(char roomKey)
{ 
  lcd.clear();                                                
  lcd.print("1-Set  *-Rst  R");

  lcd.setCursor(15,0);
  lcd.print(roomKey);
                                                             
  lcd.setCursor(0,1);                          
  lcd.print("2-Show #-back ");                                    
}
//---------------making-2-digits------------------------------------------

String twoDigits(int digits)
{
  String a = "";
  String e = "";
  if(digits < 10)
  {
    a = e + '0' + digits;
    return(a); 
  }
  else
    return(String(digits));
}
//---------------------------------------------------------------------------
void alarms_rooms()
{
    lcd.clear();
  
    if( tim_1 + ":00" == timeNow )
      alarm(led_1);

    else if( tim_2 + ":00" == timeNow )
      alarm(led_2);

    else if( tim_3 + ":00" == timeNow )
      alarm(led_3);

    else if( tim_4 + ":00" == timeNow )
      alarm(led_4);
} 
//---------------------------------------------------------------

void Table()
{
  String TTab_1 = get_from_EEPROM(0, 5),
         TTab_2 = get_from_EEPROM(5, 10),
         TTab_3 = get_from_EEPROM(10, 15),
         TTab_4 = get_from_EEPROM(15, 20);

    lcd.clear();
    lcd.print(TTab_1); lcd.setCursor(11, 0); lcd.print(TTab_2);
    lcd.setCursor(0, 2);
    lcd.print(TTab_3); lcd.setCursor(11, 2); lcd.print(TTab_4);
    delay(1500);
    lcd.clear();
}
//---------------------------------------------------------------
void Time()
{
  lcd.clear();
  for (int i = 0; i < 2 ; i++)
  {
    //-------------------------------------------
      tmElements_t tm;

      RTC.read(tm);
    
    timeNow = str + twoDigits(tm.Hour) + ':'
                  + twoDigits(tm.Minute) + ':' 
                  + twoDigits(tm.Second) ;
                
    lcd.print(timeNow);
    lcd.setCursor(0, 0);
    delay(800);
    //--------------------------------------------
  }
  lcd.clear();
}



//------------------------------------------------------------------------------------------------------
void alarm(int led)
{
    while(true)
    {
        tmElements_t tm;
        RTC.read(tm);
  
        timeNow = str + twoDigits(tm.Hour) + ':'
                      + twoDigits(tm.Minute) + ':' 
                      + twoDigits(tm.Second) ;
        
        if(digitalRead(touch) == LOW)
        {
            digitalWrite(led, HIGH);
            digitalWrite(piz, HIGH);
            
            lcd.print("Alarm"); 
            delay(500);
            lcd.clear();
            lcd.setCursor(0,0);   
              
  
            digitalWrite(led, LOW);
            digitalWrite(piz, LOW);
            
            lcd.print(timeNow);
            delay(500);
            lcd.clear();
            lcd.setCursor(0,0);
  
        }
        else if(digitalRead(touch) == HIGH)
            {break;}
    }  
}
//------------------------------------------------------------


void Home()
{

// Make custom characters:
byte empty_square[] = {
  B11111, B10001, B10001, B10001,
  B10001, B10001, B10001, B11111
};
byte one[] = {
  B11111, B11011, B10011, B11011,
  B11011, B11011, B10001, B11111
};
byte two[] = {
  B11111, B10001, B10101, B11101,
  B11011, B10111, B10001, B11111
};

byte three[] = {
  B11111, B10011, B11101, B10011,
  B11101, B11101, B10011, B11111
};

byte four[] = {
  B11111, B10101, B10101, B10101,
  B10001, B11101, B11101, B11111
};
byte clocks[] = {
  B01110, B11111, B11011, B11011,
  B11001, B11111, B11111, B01110
};
byte table[] = {
  B11111, B11111, B10101, B11111,
  B10101, B11111, B10101, B11111
};

lcd.clear();
lcd.init();
lcd.backlight();

// Create a new characters:
lcd.createChar(0, empty_square);
lcd.createChar(1, one);
lcd.createChar(2, two);
lcd.createChar(3, three);
lcd.createChar(4, four);
lcd.createChar(6, clocks);
lcd.createChar(7, table);

// Clears the LCD screen:
lcd.clear();

// Print a message to the lcd:
lcd.setCursor(0, 0);
lcd.write(byte(1));
lcd.write(byte(0));
lcd.write(byte(0));
lcd.write(byte(0));

lcd.setCursor(9, 0);

lcd.write(byte(0));
lcd.write(byte(2));
lcd.write(byte(0));
lcd.write(byte(0));

lcd.setCursor(14, 0);
lcd.print("| ");
lcd.write(byte(7));
lcd.print(":0");

lcd.setCursor(14, 1);
lcd.print("|");


lcd.setCursor(0, 2);

lcd.write(byte(0));
lcd.write(byte(0));
lcd.write(byte(3));
lcd.write(byte(0));


lcd.setCursor(9, 2);

lcd.write(byte(0));
lcd.write(byte(0));
lcd.write(byte(0));
lcd.write(byte(4));


lcd.setCursor(14, 2);
lcd.print("| ");
lcd.write(byte(6));
lcd.print(":*");
}
