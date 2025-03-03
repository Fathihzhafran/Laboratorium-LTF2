// Program : Sistem Penyeberangan Jalan di Suatu Jalan Satu Arah

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

#define LED0 16
#define LED1 4
#define LED2 15

#define BT0 33


// Pewaktuan --------------------------------
// event periodik 120000 ms
#define PERIODE 10000
long _t_last;

// memulai event waktu periodik
void tReset() {
  _t_last = millis();
}


// I/O Tombol -----------------------------------
bool _bt0;       // data global penekanan tombol


// I/O LED 3 buah ------------------------------
// menggunakan array untuk permudah
#define N_LED 3

// data global LED
int _led_pins[N_LED]={LED0, LED1, LED2};
bool _led_status[N_LED]={0,0,1};

// output semua LED sesuai status
void ledWriteAll() {
  for(int i=0; i<N_LED; i++) {
    digitalWrite(_led_pins[i], _led_status[i]);
  }
}

// FSA -------------------------------------
// definisi state, bisa pakai konstanta
// #KIRI 0
// #HENTI_KIRI 1
// dst
// namun bahasa C punya cara lebih singkat pakai enum
enum {HIJAU, SIAP_HENTI, BERHENTI, SIAP_JALAN};
int _state = HIJAU;

// Fungsi-fungsi event
// Algoritma dasar, sesuai event:
// - periksa state, aksi, ganti state

void eventT() {
  switch(_state) {

    case HIJAU : ledWriteAll(); break;

    case SIAP_HENTI :
      digitalWrite(_led_pins[2], LOW);
      for (int i=0; i<10; i++) {
        digitalWrite(_led_pins[1], HIGH);
        delay(500);
        digitalWrite(_led_pins[1], LOW);
        delay(500);
        if (i==9) {
          _state = BERHENTI;
        }
      }
      break;
    
    case BERHENTI :
      digitalWrite(_led_pins[1], LOW);
      digitalWrite(_led_pins[0], HIGH);
      delay(30000);
      _state = SIAP_JALAN;
      break;
    
    case SIAP_JALAN :
      for (int i=0; i<10; i++) {
        digitalWrite(_led_pins[0], HIGH);
        delay(500);
        digitalWrite(_led_pins[0], LOW);
        delay(500);
        if (i==9) {
          _state = HIJAU;
          tReset();
        }
      }
      break;
  }
}

void eventBt0High() {
  switch(_state) {
    case HIJAU :
      _state = SIAP_HENTI;
      break;
  }
}

// Serial plotter -----------------------------
// Fungsi untuk plot data ke serial plotter
void plotData() {
  // print header dengan waktu
  Serial.printf("d0 d1 d2 bt0 state T=%lu\n", millis());
  
  // print data
  Serial.printf("%d %d %d %d %d\n",
      _led_status[0],
      _led_status[1] + 2,
      _led_status[2] + 4,
      _bt0 + 6,
      _state + 8);
}

// UTAMA ------------------------------------
void setup() {
  Serial.begin(BAUD);
  Serial.println("\nRunning LED Event Driven");
  
  // Siapkan mode I/O
  pinMode(BT0, INPUT);
  for (int i=0; i<N_LED; i++) {
    pinMode(_led_pins[i], OUTPUT);
  }

  // Header Plot
  Serial.println("d0 d1 d2 bt0 state");
}

// loop dengan algoritma event-driven
void loop() {
  // baca semua input (event)
  _bt0 = digitalRead(BT0);

  // jalankan respon sesuai event
  if (true) {
    eventT();
  }
  if ((millis()-_t_last) > PERIODE) {
    if (_bt0 == HIGH) {
      eventBt0High();
    }
  }
  
  // kirim ke serial plotter
  plotData();
  delay(50);
}
