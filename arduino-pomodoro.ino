/*
arduino pomodoro - a trivial pomodoro timer for arduino
Written in 2015 by Joel Krebs <joel.krebs@sv.cmu.edu>.

To the extent possible under law, the author(s) have dedicated all copyright and
related and neighboring rights to this software to the public domain worldwide.
This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with
this software. If not, see http://creativecommons.org/publicdomain/zero/1.0/
 */

#include <Arduino.h>
#include <TimerOne.h>

#include <SPI.h>
#include "lcd.h"

#define BUZZER      3
#define WORK_TIME   2
#define BREAK_TIME  1

bool is_break;
bool flash = true;
unsigned int seconds;
unsigned int minutes;
unsigned int pomodoros = 0;

void setup() {
  lcdBegin(false);

  start_productive();

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(handler);
}

void handler() {
  if (seconds > 0) {
    seconds -= 1;
  } else {
    if(minutes > 0) {
      minutes -= 1;
      seconds = 59;
    } else {
      handle_timeout();
    }
  }
}

void handle_timeout() {
  tone(BUZZER, 440, 1000);
  if (is_break) {
    start_productive();
  } else {
    start_break();
  }
  update_pomodoro();
  flash = true;
}

void update_pomodoro() {
  for(int i = 0; i < pomodoros; i++) {
    setCircle(4 + i * 12, 40, 4, BLACK, 4);
  }
}

void update_time() {
  char array[10];
  sprintf(array, "%02u:%02u", minutes, seconds);
  setStr(array, 0, 26, BLACK);
}

void start_productive() {
  clearDisplay(WHITE);
  is_break = false;
  minutes = WORK_TIME;
  seconds = 0;
  setStr("POMODORO TIMER", 0, 0, BLACK);
  setStr("BE PRODUCTIVE", 0, 14, BLACK);
}

void start_break() {
  clearDisplay(WHITE);
  is_break = true;
  pomodoros += 1;
  minutes = BREAK_TIME;
  seconds = 0;
  setStr("POMODORO TIMER", 0, 0, BLACK);
  setStr("HAVE A BREAK", 0, 14, BLACK);
}

void loop() {
  update_time();
  updateDisplay();
  if (flash) {
    for(int i = 0; i < 4; i++) {
      setBacklight(i % 2);
      delay(500);
    }
    flash = false;
  }
}
