void Interrupt() {
  static int divider1 = 0;
  static int divider2 = 0;
  static int divider3 = 0;

  divider1 ++;
  if (divider1 > 9) {
    divider1 = 0;
    if (processRunning) {
      process();
    }
  }

  divider2++;
  if (divider1 > 3) {
    divider2 = 0;
    pushButtonsService();

  }

  divider3 ++;
  if (divider3 > 250) {
    divider3 = 0;
  }
  digitalWrite(pin_led_alive, divider3 < 3);

  buttonsService();
  ledPWMService();

}


