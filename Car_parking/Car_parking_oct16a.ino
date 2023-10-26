#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //a4 a5

const int ECHO_PIN = 10;
const int TRIG_PIN = 9;

Servo myservo;  
int IR1 = 5;
int IR2 = 6;

void setup() {
   Serial.begin(9600);
   pinMode(ECHO_PIN, INPUT);
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(IR1,INPUT);
   pinMode(IR2,INPUT);
    
   myservo.attach(11);
   myservo.write(0); 
   
   lcd.init();
   lcd.backlight();
}

void loop() {
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);

   float dura = pulseIn(ECHO_PIN, HIGH);
   float dista = 0.017 * dura;
   
   Serial.println(dista);

   int ir1_val = digitalRead(IR1);
   int ir2_val = digitalRead(IR2);

   lcd.clear();
   
if (ir1_val == LOW) {
      lcd.setCursor(1, 0);
      lcd.print("Slot 1 is full");
      delay(500);  
   } else {
      lcd.setCursor(1, 0);
      lcd.print("Slot 1 is empty");
      delay(500);  
   } 

   if (ir2_val == LOW) {
      lcd.setCursor(1,1);
      lcd.print("Slot 2 is full");
      delay(500);  
   } else {
      lcd.setCursor(1,1);
      lcd.print("Slot 2 is empty");
      delay(500);  
   }
   if (ir1_val == HIGH || ir2_val == HIGH) {
      lcd.clear();
      lcd.setCursor(0,1);
      delay(500);  
   } else if (ir1_val == LOW || ir2_val == LOW) {
      lcd.clear();
       lcd.setCursor(0,1);
     lcd.print("Slots are full");
      delay(500);  
   }

   if (dista < 10 ) {
     if (ir1_val == HIGH || ir2_val == HIGH)
     { myservo.write(180);
      delay(15);
      }
   } else if (dista > 5) {
      myservo.write(0);
      delay(15);
   }

}

// Connections

// Arduino > Lcd
// 5v > Vcc
// Gnd > Gnd
// SCL >
// SDA
// Arduino > Ir
// Arduino > Servo
