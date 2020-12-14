#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
CRGB colour = CRGB::Green;

// Define Trig and Echo pin:
#define trigPin 3
#define echoPin 2

// Define variables:
long duration;
int distance;
int counter;

#define limit 80 // distance to determine red or green light


void setup() {
   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  counter = 0;
  // Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
}


void loop() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(5);

 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distance = duration*0.034/2;

if (distance < limit ) {
    colour = CRGB::Red;
    counter = 30;
}
else {
   if (counter == 0){
    colour = CRGB::Green;
   }
}

  for ( int mijnledje=0;mijnledje<NUM_LEDS;mijnledje++) {
    leds[mijnledje] = colour;
    FastLED.show();
  }
  if (counter > 0){
    counter--;
  }
  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("counter = " );
  Serial.print(counter);
  Serial.print("  Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100);
}
