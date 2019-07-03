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
 for (int i = 2; i <= 10; i++) {
  pinMode(i, OUTPUT);
  }
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  
   for (int i = 2; i <= 10; i++) {
    digitalWrite(i, HIGH);
    delay(10);
  }
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);
delay(500);
    for (int i = 2; i <= 10; i++) {
    digitalWrite(i, LOW);
    delay(500);
  }
  digitalWrite(14, LOW);delay(500);
  digitalWrite(15, LOW);delay(500);
  digitalWrite(16, LOW);delay(500);
  digitalWrite(18, LOW);delay(500);
  digitalWrite(19, LOW);delay(500);
  digitalWrite(20, LOW);delay(500);
  digitalWrite(21, LOW);delay(500);
    for (int i = 2; i <= 10; i++) {
    digitalWrite(i, HIGH);
    delay(10);
  }
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
void NoteToOut (int byte2, int Note, int Out, int header) {
 
  if (byte2 == Note && header==9)
    {digitalWrite(Out, LOW);   }// turn the LED on (HIGH is the voltage level)
 if (byte2 == Note && header==8)
    {digitalWrite(Out, HIGH);}
}

void loop() {
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read(); 
NoteToOut (rx.byte2, 36, 2, rx.header);   // Lamp1
NoteToOut (rx.byte2, 37, 3, rx.header);   // Lamp2
NoteToOut (rx.byte2, 38, 4, rx.header);   // Lamp3
NoteToOut (rx.byte2, 39, 5, rx.header);   // Lamp4
NoteToOut (rx.byte2, 40, 6, rx.header);   // Lamp5
NoteToOut (rx.byte2, 41, 7, rx.header);   // Lamp6
NoteToOut (rx.byte2, 42, 8, rx.header);   // Lamp7
NoteToOut (rx.byte2, 43, 9, rx.header);   // Lamp8

NoteToOut (rx.byte2, 44, 10, rx.header);   // Lamp9
NoteToOut (rx.byte2, 45, 16, rx.header);   // Lamp10
NoteToOut (rx.byte2, 46, 14, rx.header);   // Lamp11
NoteToOut (rx.byte2, 47, 15, rx.header);   // Lamp12
NoteToOut (rx.byte2, 48, 18, rx.header);   // Lamp13
NoteToOut (rx.byte2, 49, 19, rx.header);   // Lamp14
NoteToOut (rx.byte2, 50, 20, rx.header);   // Lamp15
NoteToOut (rx.byte2, 51, 21, rx.header);   // Lamp16
 
  } while (rx.header != 0);
}
