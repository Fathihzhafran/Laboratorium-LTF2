# Analog I/O dengan ESP32 

Mari menyelam lebih dalam ke I/O dengan ESP32 ◝(ᵔᗜᵔ)◜

> [!CAUTION]
> jangan menyelam terlalu dalam ya nanti tenggelam susah baliknya (ᵕ•_•)

isi dalam modul ini meliputi: 
- Tujuan Praktikum
- Teori Dasar (DIBACA)
- Overview Terkait Praktikum
- Mungkin Hint untuk tugas tantangan? (menarik ga sih??)

## Tujuan ⊹₊⟡⋆
Modul ini bertujuan untuk memahami konsep dasar Analog Input/Output (I/O) pada mikrokontroler ESP32 menggunakan modul EScope. Peserta diharapkan dapat:

- Menggunakan Digital-to-Analog Converter (DAC) untuk mengeluarkan tegangan.
- Menggunakan Analog-to-Digital Converter (ADC) untuk membaca tegangan secara akurat.
- Menggunakan INA219 untuk mengukur tegangan, arus, dan daya listrik.
- Mengimplementasikan kalibrasi ADC dan DAC untuk meningkatkan akurasi pengukuran.
- Melakukan eksperimen pengukuran Operating Point (OP) dan DC-Sweep.

---

## Teori Dasar 𓆝 𓆟 𓆞 𓆝 𓆟
### 1. Analog-to-Digital Converter (ADC)
ADC adalah komponen elektronik yang mengubah sinyal analog menjadi data digital. Pada ESP32, ADC memiliki resolusi 12-bit yang berarti dapat merepresentasikan nilai antara 0 hingga 4095. Namun, ADC ESP32 memiliki karakteristik non-linearitas pada tegangan rendah (<100mV) dan tinggi (>3100mV), sehingga perlu dilakukan kalibrasi agar hasil pengukuran lebih akurat.

**Cara Kerja ADC:**
1. Tegangan analog diterima pada salah satu pin ADC (AI0, AI1, DI0, dll.).
2. Nilai tegangan dikonversi menjadi angka digital dalam rentang 0-4095.
3. Data hasil konversi dikalibrasi agar sesuai dengan nilai sebenarnya.

```cpp
#define AD_MAX 4095
int ad_mv_max = 3210;
void setup() {
    Serial.begin(115200);
}
void loop() {
    int ad_d = analogRead(AI0);
    int ad_mv = (long) ad_d * ad_mv_max / AD_MAX;
    Serial.println(ad_mv);
    delay(500);
}
```

### 2. Digital-to-Analog Converter (DAC)
DAC adalah komponen yang mengubah data digital menjadi sinyal analog. ESP32 memiliki DAC 8-bit, yang berarti dapat menghasilkan nilai antara 0 hingga 255 dengan tegangan output 0 hingga 3.3V.

**Cara Kerja DAC:**
1. Data digital (0-255) diberikan ke DAC.
2. Tegangan keluaran dihitung berdasarkan VCC ESP32 (biasanya 3.3V).
3. Tegangan output dikalibrasi agar sesuai dengan nilai yang diinginkan.

```cpp
#define DA_MAX 255
int da_mv_max = 3270;
void setup() {
    Serial.begin(115200);
}
void loop() {
    int da_mv = 2123;
    int da_d = (long) da_mv * DA_MAX / da_mv_max;
    dacWrite(AO0, da_d);
    delay(500);
}
```

### 3. INA219 (Pengukuran Tegangan, Arus, dan Daya)
INA219 adalah modul sensor yang digunakan untuk mengukur tegangan dan arus secara akurat. INA219 berkomunikasi dengan ESP32 melalui protokol I2C dan dapat membaca:
- Tegangan suplai (Vsupply)
- Tegangan jatuh pada resistor shunt (Vshunt)
- Arus listrik yang mengalir melalui beban (Iload)
- Daya listrik yang dikonsumsi oleh beban (Pload)

```cpp
#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
void setup() {
    Serial.begin(115200);
    ina219.begin();
}
void loop() {
    float bus_v = ina219.getBusVoltage_V();
    float current_ma = ina219.getCurrent_mA();
    float power_mw = ina219.getPower_mW();
    Serial.println(bus_v);
    delay(1000);
}
```

---

## Praktikum 

### Percobaan 1: Analog Input 
**Tujuan**: Membaca tegangan dari tombol analog menggunakan ADC dan menampilkan nilainya.

Dari rangkaian bto serta harga dari setiap parameternya dengan asumsi VCC sebesar 3300, maka berikut merupakan variasi skenario yang mungkin akan dihasilkan oleh setiap button dan juga kombinasi tombol tersebut (dapat dikatakan threshold setiap button).

| Skenario Penekanan Tombol | Tegangan BTO (mV)    |
|---------------------------|----------------------|
| S0                        |         1482         |
| S1                        |         2135         |
| S2                        |         2269         | 
| S0 + S1                   |         2395         | 
| S0 + S2                   |         2478         | 
| S1 + S2                   |         2644         | 
| S0 + S1 + S2              |         2736         | 

Berikut merupakan penjelasan sekilas terkait program yang digunakan;
#### Pustaka Program & Baud Rate;
```cpp
// Pustaka untuk komunikasi serial dengan software oscilloscope (opsional)
#include <TFScope22.h>

// Pustaka untuk komunikasi I2C & OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BAUD 500000  // Kecepatan komunikasi serial

```

#### Inisiasi Serta Void Setup Program;
```cpp

// Inisialisasi objek OLED
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

void setup(void)
{
  // Inisialisasi komunikasi serial
  Serial.begin(BAUD);
  Serial.println("\nAnalog Read Button");
  
  // Inisialisasi OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED allocation failed");
    for (;;); // Jika OLED gagal, hentikan program
  }
  
  oled.setFont(); // Mengatur font default
  oled.setTextColor(WHITE); // Mengatur warna teks

  // Menampilkan instruksi di Serial Monitor
  Serial.println("\nTekan tombol berturutan, catat nilai AD-nya");
  Serial.println("BT0");
  Serial.println("BT1");
  Serial.println("BT2");
  Serial.println("BT0+BT1");
  Serial.println("BT0+BT2");
  Serial.println("BT0+BT3");
  Serial.println("BT0+BT2+BT3");  
}
```

#### Inisiasi Void Loop dalam program 
```cpp
void loop(void)
{
  // Membaca nilai ADC dari tombol BT0 beberapa kali untuk mendapatkan rata-rata
  long sum = 0;
  for (int i=0; i<11; i++) {
    sum += analogRead(BT0);
  }  
  int ad = sum / 11; // Menghitung rata-rata nilai ADC

  // Konversi nilai ADC ke milivolt (perkiraan, tidak terkalibrasi)
  // Asumsi Vmax = 3.3V
  int mv = (3300L * ad )/ AD_MAX;
  
  // Menampilkan hasil ke OLED
  oled.clearDisplay(); // Menghapus tampilan sebelumnya

  oled.setTextSize(1);
  oled.setCursor(0, 0);  // Posisi awal teks di OLED
  oled.printf("mv= %d", mv); // Menampilkan tegangan dalam milivolt

  oled.setTextSize(2);
  oled.setCursor(0, 12);
  oled.printf("AD= %d", ad); // Menampilkan nilai ADC
  
  oled.display(); // Menampilkan data pada OLED
  
  delay(200); // Delay untuk memperlambat pembaruan tampilan
}
```

> [!WARNING]
> Tolong pastikan treshold masing-masing di rentang yang sesuai agar dapat memudahkan praktikum berikutnya bahkan modul berikutnya!

> [!IMPORTANT]
> coba buat analisis mengapa kita perlu mengukur dan menentukan tegangan threshold dari setiap skenario penekanan tombol?

### Percobaan 2: ANALAOG BUTTON 
**Tujuan**: Memilah tegangan dari tombol menjadi sinyal digital yang dapat dikontrol.

Selain dari analog input, pada percobaan ini kita dapat mengonversikan nilai analog dari setiap skenario penekanan tombolnya menjadi tiga nilai digital, yang dimana dapat mengatur nyala LED pada EScope sesuai dengan nilai digitalnya. konversi tersebut dapat dilihat dalam tabel dibawah ini,

| Skenario Penekanan Tombol |     Nilai Tegangan   |      Nyala LED        |
|---------------------------|----------------------|-----------------------|
| S0                        |         001          |           L0          |
| S1                        |         010          |           L1          |
| S2                        |         100          |           L2          |
| S0 + S1                   |         011          |        L0 + L2        |
| S0 + S2                   |         101          |        L0 + L2        | 
| S1 + S2                   |         110          |        L1 + L2        |
| S0 + S1 + S2              |         111          |      L0 + L1 + L2     |

Berikut merupakan penjelasan sekilas terkait program yang digunakan;
#### Pustaka & Baud Rate yang digunakan;
```cpp
// Pustaka I2C & OLED
#include <TFScope22.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define BAUD 500000  // Kecepatan komunikasi serial
```

### Insiasi Treshold & Void Setup

> [!WARNING]
> Ubah bagian tresholdsnya, setiap Escope memiliki nilai treshold yang berbeda. kecil kemungkinan memiliki nilai yang sudah sama, dan paling memungkinkan nilainya hanya mendekati saja

```cpp
// Treshold untuk analog button, nilai ini digunakan untuk membedakan tombol yang ditekan
int ab_tresholds[] = {
  1620,2420,2580,2740,2840,3070,3210 //UBAH BAGIAN INI!
};

// Deklarasi objek untuk membaca tombol analog dan mengontrol LED
AnalogButton _btn(ab_tresholds);
MultiLED _led;

// Konfigurasi OLED --------------------------------
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

void setup(void)
{
  // Inisialisasi komunikasi serial
  Serial.begin(BAUD);
  Serial.println("\nAnalog Button");
  Serial.println("\nPress one or more buttons");
  
  // Inisialisasi OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED allocation failed");
    for (;;); // Jika gagal, berhenti di loop tanpa batas
  }
  oled.setFont();          // Menggunakan font default
  oled.setTextColor(WHITE); // Mengatur warna teks menjadi putih
}
```

### Insiasi Void Loop program 
```cpp
void loop() {
  // Membaca nilai analog dari tombol
  int bt_analog = _btn.aRead();
  
  // Konversi nilai analog menjadi digital (dalam bentuk bit)
  byte bt_bin = _btn.a2d(bt_analog); 
   
  // Menampilkan hasil pembacaan ke OLED
  oled.clearDisplay(); // Bersihkan layar OLED sebelum menampilkan data baru

  oled.setTextSize(1); // Ukuran teks kecil
  oled.setCursor(0, 0);  // Set posisi teks ke pojok kiri atas
  oled.printf("a= %d", bt_analog); // Tampilkan nilai analog yang dibaca

  oled.setTextSize(2); // Ukuran teks lebih besar
  oled.setCursor(0, 12);
  oled.print("BTN=");
  oled.print(bt_bin, BIN);  // Tampilkan nilai tombol dalam format biner
  oled.display(); // Perbarui tampilan OLED

  // Menampilkan status tombol ke LED
  for (int i = 0; i < N_LED; i++) {
    _led.write(i, (bt_bin >> i) & 1); // Menyalakan/mematikan LED sesuai tombol yang ditekan
  }
  
  delay(200); // Delay untuk stabilitas pembacaan
}
```

> [!IMPORTANT]
> coba buat analisis dari apa yang tampil pada setiap skenario penekanan tombol?


### Percobaan 4: Kalibrasi ADC & DAC
**Tujuan:** Mengkalibrasi ADC dan DAC agar pengukuran lebih akurat dengan membuat tabel lookup.

**Langkah-Langkah:**
1. Menghubungkan DAC ke AI0 ESP32.
2. Mengeluarkan tegangan dengan DAC dari 0V hingga 3.3V.
3. Membaca tegangan menggunakan ADC.
4. Membandingkan hasil pembacaan dengan nilai referensi.
5. Membuat tabel lookup untuk interpolasi linier.

```cpp
void setup() {
    Serial.begin(115200);
}
void loop() {
    int da_mv = 1000;
    int da_d = (long) da_mv * 255 / 3300;
    dacWrite(AO0, da_d);
    delay(500);
}
```

### Percobaan 5: Pengukuran Operating Point (OP)
**Tujuan:** Mengamati titik kerja suatu sistem elektronik berdasarkan tegangan dan arus.

**Langkah-Langkah:**
1. Menghubungkan sensor dengan ESP32.
2. Mengatur input tegangan tetap menggunakan DAC.
3. Membaca tegangan dan arus menggunakan INA219.
4. Menganalisis kestabilan sistem berdasarkan hasil pengukuran.

```cpp
void setup() {
    Serial.begin(115200);
}
void loop() {
    int op_mv = 1500;
    dacWrite(AO0, op_mv * 255 / 3300);
    delay(500);
}
```

### Percobaan 6: Pengukuran DC-Sweep
**Tujuan:** Melakukan pengukuran sweeping tegangan DC untuk menganalisis karakteristik input-output.

**Langkah-Langkah:**
1. Menghubungkan sensor dengan ESP32.
2. Mengatur tegangan dari 0V hingga 3.3V secara bertahap menggunakan DAC.
3. Membaca tegangan dan arus menggunakan ADC dan INA219.
4. Menyimpan hasil pengukuran untuk analisis lebih lanjut.

```cpp
void setup() {
    Serial.begin(115200);
}
void loop() {
    for (int i = 0; i <= 255; i++) {
        dacWrite(AO0, i);
        delay(100);
    }
}
```

### Percobaan 7: Kalibrasi dan Validasi Hasil Pengukuran
**Tujuan:** Memvalidasi hasil pengukuran dengan menerapkan kalibrasi yang telah dilakukan sebelumnya.

**Langkah-Langkah:**
1. Menggunakan tabel lookup dari percobaan 4.
2. Menguji keakuratan pengukuran dengan membandingkan hasil sebelum dan sesudah kalibrasi.
3. Menggunakan hasil pengukuran untuk aplikasi lebih lanjut.

```cpp
void setup() {
    Serial.begin(115200);
}
void loop() {
    int ad_d = analogRead(AI0);
    Serial.println(ad_d);
    delay(500);
}
```

---
## Tugas Tantangan (っ- ‸ - ς)
### 1. Membuat VAW Meter
**Deskripsi:**
Buat program yang menampilkan tegangan (V), arus (A), dan daya (W) ke OLED berdasarkan pengukuran dari INA219.

**Hint:**
- Gunakan `Adafruit_INA219`.
- Gunakan fungsi `display.print()` untuk menampilkan hasil.

### 2. Menghitung Rata-rata dan Standar Deviasi
**Deskripsi:**
Tambahkan fitur untuk menghitung rata-rata dan standar deviasi dari hasil pengukuran ADC dalam periode tertentu.

**Hint:**
- Gunakan array untuk menyimpan nilai pengukuran.
- Gunakan `sqrt()` untuk menghitung standar deviasi.

### 3. Analisis Regresi Linier
**Deskripsi:**
Implementasikan regresi linier pada hasil pengukuran DC-Sweep untuk menemukan hubungan antara input dan output.

**Hint:**
- Gunakan metode Least Squares.
- Hitung slope (`m`) dan intercept (`b`) dengan formula regresi linier.
---

## Referensi
- [Dokumentasi ADC ESP32](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)
- [INA219 Tutorial](https://how2electronics.com/how-to-use-ina219-dc-current-sensor-module-with-arduino/)
- [INA219 Overview](https://components101.com/modules/1na219-current-sensor-module)

