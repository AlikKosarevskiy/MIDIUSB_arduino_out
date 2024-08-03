/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
  == Example 01 - Servo Control / Node 00 - Potentiometer ==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
//RF24 radio(10, 9);               // nRF24L01 (CE,CSN)

#include "MIDIUSB.h"
RF24 radio(6, 9);

RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;

bool nodeswitch36 = 0;
bool nodeswitch37 = 0;
word powerlight = 0;
byte volume1 = 0;
byte volume2 = 0;

void setup() {

  //    Serial.begin(115200);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
}

void loop() {

  network.update();
  midiEventPacket_t rx;

  do {
    rx = MidiUSB.read();

    if (rx.byte2 == 36 && rx.header == 9)
   { nodeswitch36 = 1 ;
          volume1 = rx.byte3;
/* Serial.print("volume1 on header 9 = "); Serial.println(volume1);
 Serial.print("nodeswitch36 = "); Serial.println(nodeswitch36);  */
    }

    if (rx.header == 11 && nodeswitch36 == 1)
   {       volume1 = rx.byte3;
// Serial.print("volume1 on B = "); Serial.println(volume1);
    }

    if (rx.byte2 == 36 && rx.header == 8)
   { nodeswitch36 = 0 ;
          volume1 = rx.byte3;
// Serial.print("volume1 on header 8 = "); Serial.println(volume1);
// Serial.print("nodeswitch36 = "); Serial.println(nodeswitch36);
    }

    if (rx.byte2 == 37 && rx.header == 9)
   { nodeswitch37 = 1 ;
          volume2 = rx.byte3;
// Serial.print("volume1 on header 9 = "); Serial.println(volume1);
// Serial.print("nodeswitch37 = "); Serial.println(nodeswitch37);
    }

    if (rx.header == 11 && nodeswitch37 == 1)
   {       volume2 = rx.byte3;
// Serial.print("volume1 on B = "); Serial.println(volume1);
    }

    if (rx.byte2 == 37 && rx.header == 8)
   { nodeswitch37 = 0 ;
          volume2 = rx.byte3;
// Serial.print("volume1 on header 8 = "); Serial.println(volume1);
// Serial.print("nodeswitch37 = "); Serial.println(nodeswitch37);
    }

    powerlight = (volume1 << 8) + volume2;


 //  HERE I need a filter for notes 
 //if (rx.header != 0) {                 // Here place fore the filter
   if (rx.byte2 == 36 || rx.byte2 == 37 || rx.header == 11) {
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool ok = network.write(header, &powerlight, sizeof(powerlight));   // Send the data
 //  Serial.print(rx.header);Serial.print("sended powerlight = "); Serial.println(powerlight);
// }

  //       if (rx.header != 0) {
 /*             Serial.print("Received: ");
              Serial.print(rx.header, HEX);
             Serial.print("-");
            Serial.print(rx.byte1, HEX);
              Serial.print("-");
          Serial.print(rx.byte2, HEX);
          Serial.print("-");
          Serial.print(rx.byte3, HEX);
           Serial.print("---");
           Serial.print(nodeswitch36); Serial.print("---"); Serial.println(nodeswitch37);
 */           }

  } while (rx.header != 0);

}
