/*                                                                                     **** Connections ****

     || Servo Motors ||                                                           || Buttons ||                                                 || TCS3200 color recognition sensor ||  
   ----------------------                                     ---------------------------------------------------                             ------------------------------------------
   Servo       Arduino                                                                                                                           Color Sensor           Arduino
                                                                Button1- { pin1- arduino(2) + 5V with resistor                                 
   Orange       8,7,6                                                      pin3- GND }                                                             VCC                     5V
   Brown        GND                                                                                                                                GND                     GND
   Red          5V                                              Button2- { pin1- arduino(3) + 5V with resistor                                     s0                      13
                                                                           pin3- GND }                                                             s1                      12
                                                                                                                                                   s2                      10
                                                                Button3- { pin1- arduino(4) + 5V with resistor                                     s3                      11
                                                                           pin3- GND }                                                             OUT                     9                   
                                                                                                                                                   OE                      GND
                                                                Button4- { pin1- arduino(5) + 5V with resistor
                                                                           pin3- GND }
*/

 
#include<Servo.h>

Servo servo1,servo2,servo3;
const int bpin1 = 2;
const int bpin2 = 3;
const int bpin3 = 4;
const int bpin4 = 5;
int bstate1;
int bstate2;
int bstate3;
int bstate4;
int angle,angle1,angle2;
const int s0 = 13;
const int s1 =12;
const int s2 = 10;
const int s3 = 11;
const int out = 9;
int red = 0;  
int green = 0;  
int blue = 0;  
    
void setup()   
{  
  Serial.begin(9600); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);
  servo1.attach(6);
  servo2.attach(7);
  servo3.attach(8);
  pinMode(bpin1, INPUT);
  pinMode(bpin2, INPUT);
  pinMode(bpin3, INPUT); 
  pinMode(bpin4, INPUT);
  servo1.write(0);
  servo2.write(170);
  servo3.write(0);
}

void loop()
{ bstate1 = digitalRead(bpin1);
  bstate2 = digitalRead(bpin2);
  bstate3 = digitalRead(bpin3);
  bstate4 = digitalRead(bpin4);

  if (bstate1 == LOW) 
  { 
    for(angle =0,angle1 =170 ; angle <= 170,angle1 >0 ; angle += 1,angle1 -=1)
     {
      servo1.write(angle);
      delay(20);
      servo2.write(angle1);
      delay(20);
     }
  }

  else if (bstate3 == LOW)
  { color();
   Serial.print("R Intensity:");
   Serial.print(red, DEC);
   Serial.print(" G Intensity: ");
   Serial.print(green, DEC);
   Serial.print(" B Intensity : ");
   Serial.print(blue, DEC);

   if( (red>=0 && red<=5) && (green>=3 && green<=7) && (blue>=2 && blue<=6) )
   { Serial.println(" - White");
     delay(100); }

   else
   if( (red>=6 && red<=13) && (green>=18 && green<=23) && (blue>=15 && blue<=20) )
   { Serial.println(" - Red");
     delay(100); }

   else
   if( (red>=3 && red<=7) && (green>=5 && green<=11) && (blue>=7 && blue<=11) )
   { Serial.println(" - Light Yellow");
     delay(10);
     for(angle2 = 0; angle2 <= 90; angle2 += 1)
     { servo3.write(angle2);
       delay(30); }
    }
   
   else
   if( (red>=4 && red<=7) && (green>=7 && green<=11) && (blue>=9 && blue<=11) )
   { Serial.println(" - Orange Yellow");
     delay(10); 
     for(angle2 = 0; angle2 <= 90; angle2 += 1)
     { servo3.write(angle2);
       delay(30); }
    }
   
   else
   if( (red>=6 && red<=10) && (green>=7 && green<=10) && (blue>=9 && blue<=12) )
   { Serial.println(" - Green");
     delay(100); }
  
   else
   if( (red>=13 && red<=24) && (green>=19 && green<=34) && (blue>=17 && blue<=26) )
   { Serial.println(" - Blue");
     delay(10); 
     for(angle2 = 0; angle2 <= 90; angle2 += 1)
     { servo3.write(angle2);
       delay(30); }
     }
  
   else
   if( (red>=4 && red<=6) && (green>=6 && green<=10) && (blue>=7 && blue<=10) )
   { Serial.println(" - Light Orange");
     delay(100); }
  
   else
   if( (red>=13 && red<=16) && (green>=17 && green<=22) && (blue>=15 && blue<=18) )
   { Serial.println(" - Brown");
     delay(10);
     for(angle2 = 0; angle2 <= 90; angle2 += 1)
     { servo3.write(angle2);
       delay(30); }
     }

   else
    { Serial.println();
      delay(100); }

   delay(300);
 }

 else if (bstate2 == LOW)
  {
    for(angle =170,angle1 =0 ; angle >=0,angle1 <= 170 ; angle -= 1,angle1 += 1)
    {
     servo1.write(angle);
     delay(25);
     servo2.write(angle1);
     delay(25);
    } 
  }

 else if (bstate4 == LOW)
   {
    for(angle2 = 90; angle2 >= 0; angle2 -= 1)
     { servo3.write(angle2);
       delay(20); } 
   }
}
    
void color()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
