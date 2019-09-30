#include <MsTimer2.h>

// pin definitions
int pin_led_alive = 13;
int pin_led_Red = 9;
int pin_led_Yellow = 10;
int pin_led_Green = 6;
int pin_led_Blue = 5;
int pin_button = 12;
int pin_buzzer = 8;
enum ledState  { Off, On, Flash };

const int procesPosCount = 3;

typedef struct Item {
  ledState Red;
  ledState Yellow;
  ledState Green;
  int time;
} ItemsArray[procesPosCount];

ItemsArray pomidoro25 {
  { Off, Off, On, 23 },
  { Off, On, Off, 2 },
  { On, Off, Off, 5 }
};

ItemsArray pomidoro45 {
  { Off, Off, On, 42 },
  { Off, On, Off, 3 },
  { On, Off, Off, 10 }
};

volatile Item *arrayPointer;
volatile boolean last_state;
volatile boolean stateButton;
volatile boolean stateButton1 = false; // short push button
volatile boolean stateButton2 = false; // long push button

volatile boolean led_Red = false;
volatile boolean led_Yellow = false;
volatile boolean led_Green = false;
volatile boolean led_Blue = false;
volatile boolean processRunning = false;

volatile int seconds = 0;
volatile int processPosition;

void setup() {
  pinMode(pin_led_alive, OUTPUT);
  pinMode(pin_led_Red, OUTPUT);
  pinMode(pin_led_Yellow, OUTPUT);
  pinMode(pin_led_Green, OUTPUT);
  pinMode(pin_led_Blue, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(pin_button, INPUT_PULLUP);

  MsTimer2::set(10, Interrupt); // period (ms)
  MsTimer2::start();

  testLeds();

}

int flash = 0;


void loop() {
  const int maxFlash = 20 * 2 * 60; // ~20 min
  static boolean pop = false;
  static byte i = 0;

  if (!processRunning) {
    if (++i > 9 & flash < maxFlash) {
      i = 0;
      led_Yellow = !led_Yellow;
      flash++;
    }
    if (flash == maxFlash) {
      led_Yellow = false;
    }
    delay(50);

    if (stateButton1) {
      program25();
    }
    if (stateButton2) {
      program45();
    }

  } else {
    if (stateButton1 || stateButton2) {
      processRunning = false;
      flash = maxFlash;
      switchOffLeds();
      delay(500);
    }
    delay(50);
  }
}




