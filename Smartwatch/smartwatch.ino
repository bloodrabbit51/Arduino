

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(3,10);


const int dischg =  2;
const int play =  3;
const int next =  4;
int buttonState = 0;



Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 7, 6);
const int blPin = 9;
int h=0,m=0;
int minute=0,hour=0;
String data="";
String temp="";
String alarm="00:00";
String x="News Service  updating soon";
String y="";
String z="";



#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()   {
  pinMode(dischg, INPUT);
  pinMode(play, INPUT);
  pinMode(next, INPUT);
  
  Serial.begin(9600);
  BT.begin(9600);
  display.begin();
 

  display.setContrast(50);
  analogWrite(blPin, 255);

  display.display(); 
  delay(2000);
  display.clearDisplay();  


 
  
  display.setTextSize(1.5);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Jaipur");
  display.setCursor(0,13);
  display.println("Thursday");
  display.drawLine(0, display.height()/2, display.width()-1, display.height()/2, BLACK);

}
  





void loop() {
    show_time();
    
}

void show_time(){
  
  display.setTextSize(1.5);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Jaipur");
  display.setCursor(0,13);
  display.println("Thursday");
  display.drawLine(0, display.height()/2, display.width()-1, display.height()/2, BLACK);
  
  boolean state = false;
  while(1){
    if(state == true)
      break;
    int i=0;
    if(minute==60)
    {
      minute=0;
      hour++;
    }
    if(hour==24)
      hour=0;
    
    
    display.setCursor(0,display.height()/2+5);
    display.setTextSize(2);
    if(hour<10)
    {
      display.print(0);
    }
    display.setTextColor(BLACK, WHITE);
    display.print(hour);
    display.print(" "); 
      if(minute<10)
      {
         display.print(0);
      }
      display.setTextColor(BLACK, WHITE);
      display.print(minute);
  
    
    while(i<60)
    {
      buttonState = digitalRead(dischg);
      if(buttonState == HIGH){
          i=22;
          state =true;
          break;
      }
      
      
      
        while (BT.available()){  
        delay(10); 
        char c = BT.read(); 
        data += c;
        }
        
        if(data[0]=='t'){
          i=11;
          temp = data.substring(1,3);
          data="";
        }
        
        if(data[0]=='a'){
          i=22;
          alarm = data.substring(1,6);
          data="";
        }
       
            
        
        write_temp(); 
        display.setTextSize(1);
        display.setCursor(display.width()/2+24,display.height()/2+5);
        display.setTextColor(BLACK, WHITE);
        if(i<10)
        {
          display.print(0);
        }
        display.print(i);
        display.setTextSize(2);
        display.setCursor(display.width()/2-18,display.height()/2+5);
        if(i%2==0)
          display.print(":");
        else
          display.print(" ");
        i++;
        delay(1000);
        display.display();
    }
    if(i==60)
      minute++;
}
show_alarm();
}



void show_alarm(){
  while(1){
   display.display(); // show splashscreen
   delay(2000);
   display.clearDisplay();  // clears the screen and buffer
    
    display.setTextSize(1.5);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("Alarm");
    
    if(alarm=="00:00")
    {
      display.setCursor(0,13);
      display.println("off");
    }
    else
    {
      display.setCursor(0,13);
      display.println("on");
    }
    
    display.setCursor(0,display.height()/2+5);
    display.setTextSize(2);
    display.setTextColor(BLACK, WHITE);
    display.print(alarm);
      buttonState = digitalRead(dischg);
      if(buttonState == HIGH){
        show_news();
      }
      
      
      
        while (BT.available()){  
        delay(10); 
        char c = BT.read(); 
        data += c;
        }
        
        if(data[0]=='t'){
          temp = data.substring(1,3);
          data="";
        }
        
        if(data[0]=='a'){
          alarm = data.substring(1,3)+":"+data.substring(3,6);
          data="";
        }
}
}

void show_news(){
   display.display(); // show splashscreen
   delay(2000);
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(BLACK);
   display.setCursor(0,0);
   
   display.print(x);
   delay(5000);
   
   display.display(); // show splashscreen
   delay(2000);
   display.clearDisplay();
   
   show_time();
   
   
}



void write_temp(){
  display.setTextSize(2);
  display.setCursor(60,0);
  display.print(temp); 
}


void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, BLACK);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, BLACK);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, BLACK);
    display.display();
  }
  for (int8_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, BLACK);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, BLACK);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, BLACK);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, BLACK);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, BLACK); 
    display.display();
  }
  delay(250);
}
