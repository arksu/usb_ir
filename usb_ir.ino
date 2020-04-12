#include <IRremote.h>
#include "HID-Project.h"

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

unsigned long last_value;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  Keyboard.begin();
  Consumer.begin();
  System.begin();
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned long cmd = results.value;

    // main cursor Up
    if (cmd == 0x73964277 || cmd == 0x50A06280) {
      Consumer.write(MEDIA_VOLUME_UP);
    }
    // main cursor Down
    if (cmd == 0x729640E2 || cmd == 0x4DA05DC9) {

      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    // TIME
    if (cmd == 0x50B || cmd == 0xD0B) {
      Keyboard.write(KEY_UP_ARROW);
    }
    // PROG
    if (cmd == 0x529 || cmd == 0xD29) {
      Keyboard.write(KEY_DOWN_ARROW);
    }

    if (last_value != results.value) {
      // main cursor Right
      if (cmd ==  0x9C2D2175 || cmd == 0x432D56EA) {
        Consumer.write(MEDIA_NEXT);
      }
      // main cursor Left
      if (cmd == 0x772AA8A1 || cmd == 0x682FCFBE) {
        Consumer.write(MEDIA_PREVIOUS);
      }
      // main cursor Enter
      if (cmd == 0x6BD5ADFF || cmd == 0x5860F6F8) {
        Consumer.write(MEDIA_PLAY_PAUSE);
      }


      // STOP
      if (cmd == 0x536 || cmd == 0xD36) {
        Consumer.write(MEDIA_STOP);
      }
      // PLAY
      if (cmd == 0x535 || cmd == 0xD35) {
        Consumer.write(MEDIA_PLAY_PAUSE);
      }
      // PAUSE
      if (cmd == 0x530 || cmd == 0xD30) {
        Consumer.write(MEDIA_PLAY_PAUSE);
      }
      // NEXT
      if (cmd == 0x520 || cmd == 0xD20) {
        Consumer.write(MEDIA_NEXT);
      }
      // PREV
      if (cmd == 0x521 || cmd == 0xD21) {
        Consumer.write(MEDIA_PREVIOUS);
      }
      // SETUP
      if (cmd == 0x5F467150 || cmd == 0x84140D5B) {
        Keyboard.write(' ');
      }


      // POWER
      if (cmd == 0x50C || cmd == 0xD0C) {
        System.write(SYSTEM_SLEEP);
      }
    }
    last_value = results.value;
    irrecv.resume(); // Receive the next value
  }
}