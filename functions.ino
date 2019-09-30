void beep() {
  digitalWrite(pin_buzzer, HIGH);
  delay(1);
  digitalWrite(pin_buzzer, LOW);
}

void switchOffLeds() {
  led_Red = false;
  led_Yellow = false;
  led_Green = false;
}

void testLeds() {
  beep();
  led_Red = true;
  delay(300);
  digitalWrite(pin_buzzer, LOW);
  delay(300);
  led_Yellow = true;
  delay(300);
  led_Green = true;
  delay(1500);
  switchOffLeds();
  delay(1000);
  led_Blue = true;
}

void buttonsService() {
  static boolean temp;
  temp = digitalRead(pin_button);
  if (temp == last_state) {
    stateButton = !temp ;
  }
  last_state = temp;
}
void ledPWMService() {
  static int RedCounter = 0;
  static int YellowCounter = 0;
  static int GreenCounter = 0;
  static int BlueCounter = 0;

  if (led_Red) {
    if (RedCounter < 100) {
      RedCounter += 10;
    }
  } else {
    if (RedCounter) {
      RedCounter -= 10;
    }
  }
  analogWrite(pin_led_Red, RedCounter);

  if (led_Yellow) {
    if (YellowCounter < 90) {
      YellowCounter += 10;
    }
  } else {
    if (YellowCounter) {
      YellowCounter -= 10;
    }
  }
  analogWrite(pin_led_Yellow, YellowCounter);

  if (led_Green) {
    if (GreenCounter < 250) {
      GreenCounter += 10;
    }
  } else {
    if (GreenCounter) {
      GreenCounter -= 10;
    }
  }
  analogWrite(pin_led_Green, GreenCounter);

  if (led_Blue) {
    if (BlueCounter < 250) {
      BlueCounter += 10;
    }
  } else {
    if (BlueCounter) {
      BlueCounter -= 10;
    }
  }
  analogWrite(pin_led_Blue, BlueCounter);

};


void pushButtonsService() {
  static int counter = 0;
  static int lastCounter = 0;
  static int offCounter = 0;

  if (offCounter) {
    offCounter--;
    if (!offCounter) {
      stateButton1 = false;
      stateButton2 = false;
    }
  }

  if (stateButton) {
    if (counter < 50) {
      counter ++;
    }
  } else {
    if (counter) {
      counter --;
    }
  }

  if (counter > 0 & counter < lastCounter) {
    // released button
    if (counter > 18) {
      stateButton1 = false;
      stateButton2 = true;
    } else {
      stateButton1 = true;
      stateButton2 = false;
    }
    counter = 0;
    offCounter = 5;
  }
  lastCounter = counter;
}
