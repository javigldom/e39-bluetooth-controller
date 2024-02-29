/*
example IBUS message:
50 04 68 32 11 1F (volume up button pressed on the steering wheel)
|  |  |  |  |  | 
|  |  |  |  |  checksum (xorsum of all previous bytes)
|  |  |  |  one or more data fields
|  |  |  message type/command type
|  |  destination address
|  length of message (including destination address and checksum)
source address 
*/


// this example shows how to interpret all messages related to the steering wheel controls

#include <IbusTrx.h> // include the IbusTrx library

IbusTrx ibusTrx; // create a new IbusTrx instance

int periodo = 400;
unsigned long TiempoAhora = 0;

void setup(){
  ibusTrx.begin(Serial); // begin listening for messages
    pinMode(13, OUTPUT);

    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
}

void loop(){
  if (ibusTrx.available()) {    
    IbusMessage m = ibusTrx.readMessage(); // grab incoming messages

    if (m.source() == M_MFL) { 
      switch (m.b(0)) {
        case 0x32: // volume controls
          if (m.b(1) & 0x01) {
            // volume up pressed
          }
          else {
            // volume down pressed
          }
          break;
        case 0x3B: // other controls
          if (m.b(1) & 0x10) {
            if (m.b(1) & 0x01) { 
              // track up (held down for 1 second)
            }
            else if (m.b(1) & 0x08) {
              // track down (held down for 1 second)
            }
            else if (m.b(1) & 0x80) {
              // talk (held down for 1 second)
            }
          }
          else if (m.b(1) & 0x20) { 
            if (m.b(1) & 0x01) {
              // track up (released)
              digitalWrite(4, HIGH);
            }
            else if (m.b(1) & 0x08) {
              // track down (released)
              digitalWrite(5, HIGH);

            }
            else if (m.b(1) & 0x80) {
              // talk (released)
                            digitalWrite(6, HIGH);

            }
          }
          else{
            if (m.b(1) & 0x01) {
              // track up (pressed)
            }
            else if (m.b(1) & 0x08) {
              // track down (pressed)
            }
            else if (m.b(1) & 0x80) {
              // talk (pressed)
            }
          }
          break;
      }
    }
  }

  if(millis() > TiempoAhora + periodo){
        TiempoAhora = millis();
              digitalWrite(4, LOW);
              digitalWrite(5, LOW);
              digitalWrite(6, LOW);
    }

  // remember to never use a blocking function like delay() in your program,
  // always use millis() or micros() if you have to implement a delay somewhere
}
