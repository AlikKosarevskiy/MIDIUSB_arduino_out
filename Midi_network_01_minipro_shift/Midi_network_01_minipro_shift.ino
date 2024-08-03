/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
  == Example 01 - Servo Control / Node 01 - Servo motor ==
*/
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
//#include <Servo.h>
RF24 radio(9, 10); 
// RF24 radio(10, 9);               // nRF24L01 (CE,CSN)   NANO OK
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
//Servo myservo;  // create servo object to control a servo

word receiveVord;
word valueLeft;
word valueRight;
word valueRight2;

void invertAnalogWrite(int pin, int value)
{
    analogWrite(pin, value);
   TCCR1A = TCCR1A & ~B00110000; //switch off output B
   TCCR1A |= B00110000;  //switch on the B output with inverted output
}

void setup() {

Serial.begin(115200);
Serial.print("11111");
    pinMode(5, OUTPUT);   //PWM Out
    pinMode(6, OUTPUT);    //PWM Out
//    pinMode(7, OUTPUT);  //noPWM Out
    digitalWrite(5, 1);digitalWrite(6, 1);delay(400);
    digitalWrite(5, 0);digitalWrite(6, 0);delay(500);
    digitalWrite(5, 1);digitalWrite(6, 1);delay(500);
    digitalWrite(5, 0);digitalWrite(6, 0);delay(600);
    digitalWrite(5, 1);digitalWrite(6, 1); delay(500);
 for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 2) {      // sets the value (range from 0 to 255):
    analogWrite(5, fadeValue);                               // wait for 30 milliseconds to see the dimming effect
     delay(20);
  }
     for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 2) {    // sets the value (range from 0 to 255):
  analogWrite(5, fadeValue);
    delay(20);}     // wait for 30 milliseconds to see the dimming effect
digitalWrite(5, 1);

    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 2) {      // sets the value (range from 0 to 255):
    analogWrite(6, fadeValue);                               // wait for 30 milliseconds to see the dimming effect
     delay(20);
  }
     for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 2) {    // sets the value (range from 0 to 255):
  analogWrite(6, fadeValue);
    delay(20);}     // wait for 30 milliseconds to see the dimming effect
digitalWrite(6, 1);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
 // myservo.attach(3);   // (servo pin)


}
void loop() {
//   byte incomingData[2];
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
//    unsigned long incomingData; 
   
       network.read(header, &receiveVord, sizeof(receiveVord)); // Read the incoming data
  valueLeft = (receiveVord >> 8) ;
  valueRight2 = (receiveVord << 8) ;
  valueRight = (valueRight2 >> 8) ;
  //analogWrite(7,incomingData);
//  invertAnalogWrite(7, incomingData);
//  invertAnalogWrite(6,255-incomingData[0]*2);
//  analogWrite(5,255-incomingData[0]*2);
//  analogWrite(6,255-incomingData[1]*2);
analogWrite(5,255-valueLeft);
analogWrite(6,255-valueRight);
 
//  if (incomingData[0] == 0)
//  {digitalWrite(5,1);};
   
//  if (incomingData[1] == 0)
//  {digitalWrite(6,1);};
  
   Serial.print("Received packet #");
    Serial.print(valueLeft);
    Serial.print("   Received packet2 #");
    Serial.println(valueRight);
  //  Serial.print(" at ");
  //  Serial.println(incomingData.ms);
  
  }
}
