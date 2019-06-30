#include "MIDIUSB.h"

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
//  Serial.begin(115200); 
 for (int i = 2; i <= 9; i++) {
  pinMode(i, OUTPUT);
  }
   for (int i = 2; i <= 9; i++) {
    digitalWrite(i, HIGH);
    delay(10);
  }
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
 if (rx.byte2 == 36 && rx.header==9)
    {digitalWrite(2, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 36 && rx.header==8)
    {digitalWrite(2, HIGH);}

 if (rx.byte2 == 37 && rx.header==9)
    {digitalWrite(3, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 37 && rx.header==8)
    {digitalWrite(3, HIGH);}

 if (rx.byte2 == 38 && rx.header==9)
    {digitalWrite(4, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 38 && rx.header==8)
    {digitalWrite(4, HIGH);}

 if (rx.byte2 == 39 && rx.header==9)
    {digitalWrite(5, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 39 && rx.header==8)
    {digitalWrite(5, HIGH);}

 if (rx.byte2 == 40 && rx.header==9)
    {digitalWrite(6, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 40 && rx.header==8)
    {digitalWrite(6, HIGH);}

 if (rx.byte2 == 41 && rx.header==9)
    {digitalWrite(7, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 41 && rx.header==8)
    {digitalWrite(7, HIGH);}

 if (rx.byte2 == 42 && rx.header==9)
    {digitalWrite(8, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 42 && rx.header==8)
    {digitalWrite(8, HIGH);}

 if (rx.byte2 == 43 && rx.header==9)
    {digitalWrite(9, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (rx.byte2 == 43 && rx.header==8)
    {digitalWrite(9, HIGH);}

  } while (rx.header != 0);
}
