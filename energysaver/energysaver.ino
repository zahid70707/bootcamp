#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


#define PIR_PIN 2
#define IR1_PIN 3
#define IR2_PIN 4
#define LED_PIN 8
#define LIGHT_PIN A0

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int people = 0;

int state = 0;


unsigned long sequenceStart = 0;
const unsigned long TIMEOUT = 2000;

void setup() {

  pinMode(PIR_PIN, INPUT);
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  if (!display.begin(0x3C, true)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  display.setTextSize(2);
  display.setCursor(5, 10);
  display.println("SMART");

  display.setCursor(5, 35);
  display.println("CLASS");

  display.display();

  delay(2000);
}

void loop() {

  int pir = digitalRead(PIR_PIN);
  int ir1 = digitalRead(IR1_PIN);
  int ir2 = digitalRead(IR2_PIN);
  int lightValue = analogRead(LIGHT_PIN);

  
  if (state == 0) {

    
    if (ir1 == HIGH && ir2 == LOW) {

      state = 1;
      sequenceStart = millis();
    }


    else if (ir2 == HIGH && ir1 == LOW) {

      state = 2;
      sequenceStart = millis();
    }
  }


  else if (state == 1) {

    if (ir2 == HIGH) {

      people++;

      state = 3;
    }

    if (millis() - sequenceStart > TIMEOUT) {
      state = 0;
    }
  }


  else if (state == 2) {

    if (ir1 == HIGH) {

      if (people > 0) {
        people--;
      }

      state = 3;
    }

  
    if (millis() - sequenceStart > TIMEOUT) {
      state = 0;
    }
  }



  else if (state == 3) {

    if (ir1 == LOW && ir2 == LOW) {
      state = 0;
    }
  }

  

  bool dark = (lightValue < 500);
  bool occupied = (people > 0);

  if (occupied && dark) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }



  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  
  display.setTextSize(1);
  display.setCursor(15, 0);
  display.println("SMART CLASSROOM");

  display.drawLine(0, 10, 127, 10, SH110X_WHITE);

  
  display.setTextSize(2);
  display.setCursor(0, 14);
  display.print("TOTAL: ");
  display.println(people);

  
  display.setTextSize(1);
  display.setCursor(0, 35);

  if (occupied) {
    display.print("ROOM: OCCUPIED");
  }
  else {
    display.print("ROOM: EMPTY");
  }

  
  display.setCursor(0, 45);

  if (dark) {
    display.print("LIGHT: DARK");
  }
  else {
    display.print("LIGHT: BRIGHT");
  }

  
  display.setCursor(0, 55);

  if (pir == HIGH) {
    display.print("MOTION: YES");
  }
  else {
    display.print("MOTION: NO");
  }

  display.display();

  delay(50);
}

