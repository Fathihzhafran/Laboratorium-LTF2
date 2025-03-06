/*
 * Action Operating Condition
 */

void opPrintHeader() {
  Serial.println("VDA  Vi+  V0   V1   V2");
}

void opPlot() {
  char buff[40];
  sprintf(buff, "%4d %4d %4d %4d %4d", 
    da_mv, ina_mv, ad_mv[0], ad_mv[1], ad_mv[2]);
  Serial.println(buff);  
}

// Melaksanakan prosedur OP
// Kirim output tertentu ke DA
// lalu ukur dan print ke Serial sebanyak ndata
// lalu hitung rata-rata
void opAction(int op_mv) {

  opPrintHeader();

  da_mv = op_mv;   // simpan op ke data global
    
  // output 
  dacWriteMv(p_da, da_mv);
  delay(100); // tunggu tunak

  for (int i=0; i<ndata; i++) {
    // baca
    ina_mv = inaReadLoadMv();
    for(int i=0; i<N_DA; i++) {
      ad_mv[i] = analogReadMv(p_ad[i]);
    }

    // tulis baris
    opPlot();
  }  

  // Tambahkan proses hitung rata-rata & stdev
  // tampilkan di sini
}
