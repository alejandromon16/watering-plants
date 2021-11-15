#include <Servo.h>
#include <SoftwareSerial.h>

int pos = 0;
int statusO[2];
boolean statusF = false;
//prueba
int num;
int led = 8;
//prueba
Servo servoX;
Servo servoY;
SoftwareSerial BT(4,6);

void setup()
{
  servoX.attach(2);
  servoY.attach(3);
  pinMode(led, OUTPUT);
  BT.begin(38400);
}

void startPos()
{
  servoX.write(90);
  delay(10);
}
void moveXY(char type,char dir,int minAng,int maxAng, int velocity)
{
  if(type == 'I')
  {
    for (pos = minAng; pos <= maxAng; pos += 1) 
      {
        if(dir == 'X')
        {
           servoX.write(pos);
           delay(velocity);
        }
        else
        {
           servoY.write(pos);
           delay(velocity);
        }
      }
  }
  else if(type == 'D')
  {
    for (pos = maxAng; pos >= minAng; pos -= 1) 
    {
      if(dir == 'X')
      {
         servoX.write(pos);
         delay(velocity); 
      }
      else
      {
         servoY.write(pos);
         delay(velocity);
      } 
    }
    
  }
      
}

void moveXY(int minAng,int maxAng)
{
    moveXY('I','Y',25,45,160);
    moveXY('I','X',minAng,maxAng,80);
    moveXY('D','Y',25,45,160);
    moveXY('D','X',minAng,maxAng,80);
}

int timeConvert(int t)
{
    t = t*60*1000;
    return t;
}

void checkBT()
{
  if (BT.available()>0)
  {
    char data =  BT.read();
    switch(data)
    {  
      case '0': statusF = true; break;
      case '1': statusO[0]= 1;  break;
      case 'A': statusO[1]= 30; break;
      case 'B': statusO[1]= 45; break;
      case 'C': statusO[1]= 60; break;
      default : break;
    }
  } 
}


void loop()
{
  checkBT();
  if (statusO[0] == 1 && statusO[1]>=30)
  {
    unsigned long tiempoF = timeConvert(statusO[1]) ;
    unsigned long tiempoI = millis();
    while (millis() < tiempoF+tiempoI) {
        startPos();
        moveXY(30,150);
        checkBT();
        if (statusF) break;
            
    }
    startPos();
    statusO[0]= 5;
    statusO[1]= 0;
   }   
                                                                              
}
