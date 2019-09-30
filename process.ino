void program25() {
  switchOffLeds();
  led_Yellow = true;
  led_Green = true;
  delay(300);
  switchOffLeds();
  startProcess(pomidoro25);
}

void program45() {
  switchOffLeds();
  led_Yellow = true;
  led_Red = true;
  delay(600);
  switchOffLeds();
  startProcess(pomidoro45);
}


void processInit() {
  boolean lastRed = false;

  seconds = arrayPointer[processPosition].time * 60;
  led_Red = arrayPointer[processPosition].Red;
  if (led_Red & lastRed == false) {
    beep();
  }
  led_Yellow = arrayPointer[processPosition].Yellow;
  led_Green = arrayPointer[processPosition].Green;
  lastRed = led_Red;

}

void startProcess(Item *parArrayPointer) {
  switchOffLeds();
  delay(500);
  processPosition = 0;
  arrayPointer = parArrayPointer;
  processInit();
  processRunning = true;
}


void process() {
  static byte divSec = 0;
  divSec++;
  if (divSec > 9 ) {
    divSec = 0;
    if (seconds) {
      seconds--;
    } else {
      if (processPosition < procesPosCount - 1) {
        processPosition++;
        processInit();
      } else {
        processRunning = false;
        switchOffLeds();
        flash = 0;
      }
    }
  }
}


