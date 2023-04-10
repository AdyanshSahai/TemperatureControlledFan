#include <DHT.h>
#define Type DHT11
int senseP = 2; // Sense pin (For temperature and humidity.)
DHT HT(senseP, Type);
float tempC;    // Temperature in Celsius
float dif;      // Difference
int difR;       // Difference rounded
float val;      // Value
int sped;       // Speed

const int fanP = 11; // Fan pin
const int blueP = 4; // Blue LED pin
const int redP = 7;  // Red LED pin

const int potP = 5;  // Potentiometer pin
float readVal;       // The value read from the potentiometer
int potVolt;         // The voltage from the potentiometer

int Time = 250;      // Used for delays
void setup() {
  Serial.begin(9600);
  HT.begin();
  delay(Time);
  //The fan and LEDs are outputs
  pinMode(fanP, OUTPUT);
  pinMode(blueP, OUTPUT);
  pinMode(redP, OUTPUT);
  Time = 900;         // Makes future delays longer

  Serial.println("System START"); // Aesthetics
  Serial.println(" ");
}

void loop() {
  tempC = HT.readTemperature();
  Serial.println("Temperature in °Celsius: "+String(round(tempC))+"°C"); // "Temperature in °Celcius is ___°C"
  delay(Time);                              // Provides time to read
  readVal = analogRead(potP);               // Reads value of potentiometer
  potVolt = round(readVal*(5./1023.));      // Converts value to volts (from 0 -> 5)
  Serial.println("Potentiometer value is "+String(potVolt)+" out of 5");
  delay(Time);                              // Tells us the value.
  if (tempC < 20) {                 // If the temperature is too low:
    analogWrite(fanP, 0);           // the fan turns off
    Serial.println("Temperature too low");
    Serial.println("The fan is OFF");//it says in the serial monitor
    digitalWrite(blueP, HIGH);      // and the blue LED turns on
    
  }else if (tempC>=20 && tempC<=30){// If the temperature is between the maximum and the minimum:
    dif = tempC-20;                 // it finds the difference between the minimum and the current temperature
    difR = round(dif);              // it rounds its findings
    Serial.println("The difference between the minimum temperature(20°C) and the current temperature is "+String(difR));
    delay(Time+250);                // it says its findings and gives us time to read it.
    val = (potVolt/5.)*(difR/10.)*155.;// Then, it finds the fan speed
    sped = round(val) + 100;        // It makes the fan speed readable for the motor 
    Serial.println("The motor speed is "+String(round(val))+" out of 255");
    delay(Time);                    // and reports the fan speed, giving us time to read it.

    analogWrite(fanP, sped);        // It then tells the fan what speed it should be at.
    
  }else {                                            // If the temperature is too high:
    Serial.println("The temperature is above 30°C"); // it tells us about it
    Serial.println("The motor is at full speed!");   // it tells that the motor is at full speed
    digitalWrite(redP, HIGH);                        // and puts the motor at full speed.
  }
  
  Serial.println(" ");       // It creates a new paragraph
  delay(1000);               // and gives us time to digest the information 
                             // and enjoy the sweet, possibly still, air.
  
}                            // #REPEAT...
