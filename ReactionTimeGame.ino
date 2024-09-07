#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

#define MAXROUND 5

int start, end, time, rounds = 0, sum = 0;
unsigned long delaystart, enddelay;
double average;

void checkscore(int average) {	
	lcd.setCursor(4, 0);
  	lcd.print("All Done!");
 	delay(2000);
  	lcd.clear();
    
    lcd.setCursor(0, 0);
  	lcd.print("Average: " + String(average) + " ms");
  
  	lcd.setCursor(0, 1);
  
  if (average < 150) {
    lcd.print("Insanely Fast!");
  }
  else if (average >= 150 && average < 200) {
    lcd.print("Now That's Quick");
  }
  else if (average >= 200 && average < 300) {
    lcd.print("Could do better");
  }
  else {
    lcd.print("Very Slow");    
  }
    
    delay(4000);
    lcd.clear();  	
}

void setup()
{
  lcd.begin(16, 2);
  
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  
  randomSeed(analogRead(A0)); 
  Serial.begin(9600);  
}

void loop()
{ 
  
  if (rounds == MAXROUND) {
    average =(double) (sum / rounds);
    
    checkscore(average);
    
    rounds = 0;
    sum = 0;
  }
  
  while(rounds == 0 && digitalRead(3) == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Press button to");
    lcd.setCursor(5, 1);
    lcd.print("start!");
  }
  
  lcd.clear();
  
  lcd.setCursor(3, 0);
  lcd.print("Get Ready!");
  
  lcd.setCursor(3, 1);  
  lcd.print(String(rounds) + "/" + String(MAXROUND) + " rounds");
  
  delay(500);
  
  enddelay = random(1, 6) * 1000;  
  delaystart = millis();
    
  while (millis() - delaystart < enddelay) {
    
  	if (digitalRead(3) == HIGH) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Too Soon");      
      lcd.setCursor(3, 1);
      lcd.print("Try again");
      delay(1000);
      lcd.clear();
      
      return;
    }
    delay(10); 
  }  
  
  digitalWrite(2, HIGH);
  start = millis();
  
  while (digitalRead(3) == LOW) {  
  }
    
  end = millis();   
  time = end - start;
  sum += time;
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Your score is:");
  lcd.setCursor(5, 1);
  lcd.print(String(time) + " ms");
      
  digitalWrite(2, LOW);
  delay(3000);
  
  lcd.clear();
  rounds++;
}