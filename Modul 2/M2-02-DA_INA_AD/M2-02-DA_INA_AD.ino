/* Program : DA_INA_AD
 * DA mengeluarkan sinyal ramp
 * INA dan AD mengukur
 * Print ke Serial Monitor, format siap sbg array
 * (c) Eko M. Budi, 2022
 */

// pustaka
#include <Wire.h>
#include <Adafruit_INA219.h>

#define BAUD 500000

// Pin Standar kit ESCOPE 2020 ESP32
#define DO0 13
#define DO1 12
#define DO2 14
#define DO3 27
#define DO4 33

#define DI0 32
#define DI1 35
#define DI2 34
#define DI3 39
#define DI4 36

#define AO0 26
#define AO1 25

#define LED0 5
#define BT0 4
#define BT1 16
#define BT2 17

#define DA_MAX 255
#define AD_MAX 4095

// definisi pin, taruh di array
#define N_AD 2
int p_ad[N_AD] = {DI0, DI1};
int p_da = AO0;

// pesan obyek INA219
Adafruit_INA219 ina219;

// data
int da_out; 
int ad_in;
int ina_mv;

// Fungsi untuk print data ke serial monitor
void printData() {
  char buff[40];
  // format ke spreadsheet
  sprintf(buff,"%4d, %4d, %4d", ad_in, ina_mv, da_out);
  // format ke array
  // sprintf(buff,"{%4d, %4d, %4d},",  ad_in, ina_mv, da_out);
  Serial.println(buff);
}

// UTAMA
void setup() {
  // Siapkan serial, tunggu sampai terkoneksi
  Serial.begin(BAUD);
  while (!Serial) {}
  Serial.println("\nAnalog I/O");  

  // siapkan INA219
  if (!ina219.begin()) {
    while (1) { delay(100); }
  }  
}

void loop() {
  // Header Plot
  Serial.println("AD  Vi+(mV) DA");

  // mengeluarkan output ramp untuk kalibrasi
  for (da_out=0; da_out<=DA_MAX; da_out++) {
    // keluarkan sinyal ke DA
    dacWrite(AO0, da_out);
    delay(10);    // tunggu tunak

    // baca AD
    ad_in = analogRead(DI0);

    // baca INA 
    float shunt_mv = ina219.getShuntVoltage_mV();
    float bus_v = ina219.getBusVoltage_V();    

    // konversi bacaan ina ke tegangan (mV)
    ina_mv = bus_v; // INI MASIH SALAH !!!
    
    printData();    
  }
  
  // tunggu sampai dikirimi sesuatu dari Serial monitor
  Serial.println("Kirim sembarang huruf untuk ukur lagi");
  while(!Serial.available());
  while(Serial.available()) Serial.read();
}
