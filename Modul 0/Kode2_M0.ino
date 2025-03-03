int counter = 0;
void setup(){
  Serial.begin(9600); // mulai komunikasi USB dengan baud=9600
  Serial.println("Hello World!"); // kirim via USB
  }
void loop() {
  Serial.print("Saya sudah berjalan sebanyak: ");
  Serial.print(counter); // baca counter, kirim ke USB
  Serial.println(" kali");
  counter++; // menaikkan 1 nilai dari nilai sebelumnya
  Serial.print("Saya sudah jalan selama: ");
  Serial.print(millis()); // baca waktu, kirim ke USB
  Serial.println(" milidetik"); delay(1000);
  }
