#include <OLED.h>
#include <MathUtil.h>

#include <OptionsMenu.h>
#include <Controls/Control.h>
#include <Watch.h>
#include <NotificationManager.h>

#include <string.h>

OLED oled = OLED(4);
Watch* watchclock;

void setup()
{
  watchclock = new Watch();


  Notification noty = {"App de teste", "Titulo", "Conteudo da notificacao"};

  Notification noty2 = {"Outra App", "Titulo", "Este texto devera dar scroll e ser legivel neste pequeno ecra de 128 pixeis horizontais"};
  watchclock->AddNotification(noty);
  watchclock->AddNotification(noty2);
  oled.Initialize(OLED_SWITCHCAPVCC, 0x3D);
  oled.Begin();

  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  
 // Serial.begin(9600);
  //Serial1.begin(9600);
}

unsigned long prevtime = 0;
bool upinput = false;
bool downinput = false;
bool enterinput = false;
bool buttoninput = false;

bool initialized = false;

char data = 0;
char bluetoothstr[101];
uint8_t bluetoothstr_c = 0;

bool receivingnotification = false;
uint8_t stage = 0;//0-app 1-title 2-content 3-done

Notification noty;
char appname[31];
char title[41];
char content[101];

void loop()
{
  int incomingByte;
/*
 if(Serial1.available() > 0)     
     {
        data = Serial1.read(); 
         Serial.println(data);
        
        bluetoothstr[bluetoothstr_c++] = data;
         
        if (data == '$')
        {
          bluetoothstr[bluetoothstr_c-1] = '\0';

          if (receivingnotification)
          {*/
             /* if (millis()-prevtime > 5000)
              {
                receivingnotification = false;
                stage = -1;
              }*/
            /*
              switch (stage)
              {
                case 0:
                  Serial.println("appname");
                  strcpy(noty.appname, bluetoothstr);
                  break;
                case 1:
                  Serial.println("title");
                  strcpy(noty.title, bluetoothstr);
                  break;
                case 2:
                  Serial.println("content");
                  strcpy(noty.content, bluetoothstr);
   
                  Serial.println(noty.appname);
                  Serial.println(noty.title);
                  Serial.println(noty.content);

                  watchclock->AddNotification(noty);
                  stage = 0;
                  break;
              }

              stage++;
          }

          if (!strcmp(bluetoothstr, "NOT"))   
          {   
              Serial.println("starting not");
              receivingnotification = true;
              prevtime = millis();
          }
              
          bluetoothstr_c = 0;    
        }
     
  

     }  
  */
  oled.Clear();
   
  watchclock->Draw(&oled);

  oled.Display();
 
  if (digitalRead(12) == LOW)
    {
      if (millis()-prevtime > 1000)
      {
        prevtime = millis();
        buttoninput = true; 
        
        watchclock->Home();
      }
    }
    else
    {
      if (buttoninput)
      {
        prevtime = 0;
        buttoninput = false;
      }
    }


  if (digitalRead(9) == LOW)
  {
      if (millis()-prevtime > 1000)
      {
        prevtime = millis();
        upinput = true;

        watchclock->Up();
      }
    }
    else
    {
      if (upinput)
      {
        prevtime = 0;
        upinput = false;
      }
    }
  
    if (digitalRead(11) == LOW)
    {
      if (millis()-prevtime > 1000)
      {
        prevtime = millis();
        downinput = true;
  
        watchclock->Down();
      }
    }
    else
    {
      if (downinput)
      {
        prevtime = 0;
        downinput = false;
      }
    }
  
    if (digitalRead(10) == LOW)
    {
      if (millis()-prevtime > 1000)
      {
        prevtime = millis();
        enterinput = true;

        watchclock->Enter();
      }
    }
    else
    {
      if (enterinput)
      {
        prevtime = 0;
        enterinput = false;
      }
    }  
}
