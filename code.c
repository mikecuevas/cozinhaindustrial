#include <LiquidCrystal.h>
#include <Servo.h>
#define led 10
#define buzzer 13
#define gate 9
#define sensor A2

int gas = 0;
int pessoas = 0;

float temp;
float vout;
float vout1;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

Servo servo;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(gate, OUTPUT);
  pinMode(buzzer,OUTPUT); 
  pinMode(led, OUTPUT);
  
  lcd_1.begin(16, 2);
  lcd_1.setCursor(2, 0); 
  lcd_1.print("Cozinha");
  lcd_1.setCursor(2, 1);
  lcd_1.print("Industrial");
  delay(2000);
  
  servo.attach(7);
  servo.write(0);
  
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
  pinMode(A1, INPUT);  
}

void loop()
{
  gas = analogRead(sensor);
  vout=analogRead(A1);
  vout1=(vout/1023)*5000;
  temp=(vout1-500)/10;
  
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Pessoas:");
  lcd_1.print(pessoas);
  
  if (analogRead(A0)){
    while(analogRead(A0) && pessoas <20){
      pessoas+=1;
   	  lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Pessoas:");
      lcd_1.setCursor(9,0);
      lcd_1.print(pessoas);
   	  servo.write(180);
      delay(1000);
      servo.write(0);
      delay(1000);
      servo.write(180);
    }
    lcd_1.setCursor(0, 0);
    lcd_1.print("Capacidade Max");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Pessoas:");
    lcd_1.setCursor(9,1);
    lcd_1.print(pessoas);
  }
  if (analogRead(A5) && pessoas != 0){
   lcd_1.clear();
   lcd_1.setCursor(0, 0);
   lcd_1.print("Pessoas:");
   lcd_1.setCursor(9,0);
   lcd_1.print(pessoas);
   pessoas-=1;
   servo.write(180);
   delay(1000);
   servo.write(0);
   delay(1000);
   servo.write(180);
  }
  if(pessoas != 0){
  	digitalWrite(led, HIGH);
  }else{
  	digitalWrite(led, LOW);
  }
  if(temp>70){
    digitalWrite(gate, HIGH); 
    delay(1000);
  }else{
    digitalWrite(gate, LOW);
  }
  if( gas >= 116){
    tone(buzzer,300);
  }else{
    noTone(buzzer);
  }
  delay(1000);

}
