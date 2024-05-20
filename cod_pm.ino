#include <Wire.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

const int led1 = 5;   // led galben variabil
const int led2 = 3;   // led rosu variabil
const int led3 = 8;   // ledul verde - tensiune in crestere
const int led4 = 12;  // ledul galben - tensiune in descrestere
const int led5 = 13;  // ledul rosu - pauza
const int water = 6;  // pompa apa
char Incoming_value = 0;

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(water, OUTPUT);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
}

void actiune(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,5);
  display.println("Creste!");
  display.display();
  display.clearDisplay();
  digitalWrite(led3, HIGH);
  digitalWrite(led5, LOW);

 for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
   analogWrite(led1, dutyCycle);
   analogWrite(led2, 255-dutyCycle);
   analogWrite(water, dutyCycle);
   delay(15); 
  }

  display.setCursor(30,40);
  display.println("Scade!");
  display.display();
  display.clearDisplay();
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);

 for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
   analogWrite(led1, dutyCycle);
   analogWrite(led2, 255-dutyCycle);
   analogWrite(water, dutyCycle); 
   delay(15); 
  }
  digitalWrite(led4, LOW);
}

void pauza(){  
  digitalWrite(water,LOW);
  display.setCursor(35,20);
  display.println("PAUZA");
  display.display();
  display.clearDisplay();
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  delay(1000);

}

void loop()
{
 if (Serial.available() > 0)
  {
    Incoming_value = Serial.read();
    Serial.print(Incoming_value);
    Serial.print("/n");
      if (Incoming_value == '1')
        actiune ();
      else if(Incoming_value == '0')
        pauza ();
  }
}