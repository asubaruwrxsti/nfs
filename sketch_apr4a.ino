int x;

int display1_pins[] = {2, 3, 4, 5};
int display2_pins[] = {6, 7, 8, 9};
int display3_pins[] = {10, 11, 12, 13};

void dec_to_BCD(int digit) {
  int i, rem, bcd = 0;
  for (i = 0; digit != 0; i++) {
    rem = digit % 10;
    digit /= 10;
    bcd += rem << (4 * i);
  }
  bcd_to_pins(bcd);
}

void bcd_to_pins(int bcd) {
  int i, pin;

  for (i = 0; i < 4; i++) {
    pin = bcd & 0x0001;
    digitalWrite(display1_pins[i], pin);
    bcd >>= 1;
  }

  for (i = 0; i < 4; i++) {
    pin = bcd & 0x0001;
    digitalWrite(display2_pins[i], pin);
    bcd >>= 1;
  }

  for (i = 0; i < 4; i++) {
    pin = bcd & 0x0001;
    digitalWrite(display3_pins[i], pin);
    bcd >>= 1;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);

  int i;
  for (i = 0; i < 4; i++) {
    pinMode(display1_pins[i], OUTPUT);
    pinMode(display2_pins[i], OUTPUT);
    pinMode(display3_pins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    x = Serial.parseInt();
    dec_to_BCD(x);
  }
}
