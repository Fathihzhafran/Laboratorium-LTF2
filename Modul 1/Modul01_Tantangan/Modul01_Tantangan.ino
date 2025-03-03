#define BAUD 500000

// Pin Standar kit ESCOPE 2022 ESP32
#define AO0 26
#define AO1 25

#define DO0 12
#define DO1 14
#define DO2 27
#define DO3 13

#define AI0 36
#define AI1 39

#define DI0 34
#define DI1 35
#define DI2 32
#define DI3 17

#define RED_LED 16
#define YELLOW_LED 4
#define GREEN_LED 15

#define BT0 33

// Pewaktuan --------------------------------
#define RED_PERIOD 30000
#define BLINK_PERIOD 10000
#define GREEN_PERIOD 120000
long t_last; // waktu aksi sebelumnya

// I/O Tombol ----------------
bool bt0;
bool bt_state;

// I/O LED ------------
#define N_LED 3
int led_pins[N_LED] = {RED_LED, YELLOW_LED, GREEN_LED};
bool led_status[N_LED] = {0,0,0};
enum {RED, YELLOW, GREEN};

// FSA -----------
enum {JALAN, SIAP_HENTI, BERHENTI, SIAP_JALAN};
int state = JALAN;

// Deklarasi fungsi --------------
// Reset time
void tReset();

// LED
void lightUp(int LED);
void blink(int LED, int freq);
void ledWriteAll();

// state
void stateJalan();
void stateSiapHenti();
void stateBerhenti();
void stateSiapJalan();

// UTAMA -------------------
void setup() {
  Serial.begin(BAUD);
  
  // Siapkan mode I/O
  pinMode(BT0, INPUT);
  for (int i=0; i<N_LED; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  // siapkan waktu
  tReset();

  // Header Plot
  Serial.println("d0 d1 d2 bt0 state");
}

void loop() {
  bt0 = digitalRead(BT0);
  if (!bt_state) bt_state = bt0;

  switch(state) {
    case JALAN : stateJalan(); break;
    case SIAP_HENTI : stateSiapHenti(); break;
    case BERHENTI : stateBerhenti(); break;
    case SIAP_JALAN : stateSiapJalan(); break;
  }
}

// Implementasi fungsi ------------------
void tReset() {
  t_last = millis();
}

void lightUp(int LED) {
  for (int i=0; i<N_LED; i++) {
    led_status[i] = 0;
  }
  led_status[LED] = 1;
  ledWriteAll();
}

void blink(int LED, int freq) {
  for (int i=0; i<N_LED; i++) {
    led_status[i] = 0;
  }

  static unsigned int blinkMillis = millis();
  if ((millis() - blinkMillis) > freq) {
    led_status[LED] = !(digitalRead(led_pins[LED]));
    ledWriteAll();
    blinkMillis = millis();
  }
}

void ledWriteAll() {
  for (int i=0; i<N_LED; i++) {
    digitalWrite(led_pins[i], led_status[i]);
  }
}

void stateJalan() {
  lightUp(GREEN);

  if ((millis() - t_last) > GREEN_PERIOD) {
    if (bt_state) {
      state = SIAP_HENTI;
      tReset();
    }
  }
}

void stateSiapHenti() {
  bt_state = 0;

  if ((millis() - t_last) < BLINK_PERIOD) {
    blink(YELLOW, 1000);
  } else {
    state = BERHENTI;
    tReset();
  }
}

void stateBerhenti() {
  if ((millis() - t_last) < RED_PERIOD) {
    lightUp(RED);
  } else {
    state = SIAP_JALAN;
    tReset();
  }
}

void stateSiapJalan() {
  if ((millis() - t_last) < BLINK_PERIOD) {
    blink(RED, 1000);
  } else {
    state = JALAN;
    tReset();
  }
}