# Analog I/O dengan ESP32 𝑴𝒆𝒐𝒘. ฅ(•- •マ

## Tujuan
Modul ini bertujuan untuk memahami konsep dasar Analog Input/Output (I/O) pada mikrokontroler ESP32 menggunakan modul EScope. Peserta diharapkan dapat:

- Menggunakan Digital-to-Analog Converter (DAC) untuk mengeluarkan tegangan.
- Menggunakan Analog-to-Digital Converter (ADC) untuk membaca tegangan secara akurat.
- Menggunakan INA219 untuk mengukur tegangan, arus, dan daya listrik.
- Mengimplementasikan kalibrasi ADC dan DAC untuk meningkatkan akurasi pengukuran.
- Melakukan eksperimen pengukuran Operating Point (OP) dan DC-Sweep.

---

## Teori Dasar 
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
**Tujuan:** Membaca tegangan dari tombol analog menggunakan ADC dan menampilkan nilainya.

**Langkah-Langkah:**
1. Tekan tombol S0, S1, atau S2.
2. ESP32 membaca tegangan dari tombol menggunakan ADC.
3. Hasil ditampilkan pada Serial Monitor dan OLED.

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

### Percobaan 2: Analog Button
**Tujuan:** Memilah tegangan dari tombol menjadi sinyal digital yang dapat dikontrol.

**Langkah-Langkah:**
1. Menghubungkan tombol ke ESP32.
2. Menggunakan library AnalogButton untuk mendeteksi tombol yang ditekan.
3. Menampilkan hasil pada OLED dan Serial Monitor.

```cpp
void setup() {
    Serial.begin(115200);
}
void loop() {
    int ad_mv = analogRead(AI0);
    if (ad_mv > 2000) Serial.println("Tombol S1 ditekan");
    delay(500);
}
```

### Percobaan 3: DAC & INA219
**Tujuan:** Menggunakan DAC untuk menghasilkan sinyal tegangan dan membacanya menggunakan INA219.

**Langkah-Langkah:**
1. Menghubungkan DAC ke INA219.
2. Menghasilkan sinyal DAC bertingkat dari 0 hingga 3.3V.
3. Mengukur tegangan yang dihasilkan menggunakan INA219.

```cpp
#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
void setup() {
    Serial.begin(115200);
    ina219.begin();
}
void loop() {
    for (int da_out = 0; da_out <= 255; da_out++) {
        dacWrite(AO0, da_out);
        delay(10);
        Serial.println(ina219.getBusVoltage_V());
    }
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


