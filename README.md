# Laboratorium-LTF2 ৻(  •̀ ᗜ •́  ৻)

Selamat datang di LTF2!!!! ଘ(੭ˊᵕˋ)੭* ੈ✩‧₊
Repository ini berisi terkait penjelasan setiap modulnya, basicly praktikum LTF2 kebanyakan ngoding jadi tolong dipersiapkan laptopnya dan logika dasarnya agar dapat memudahkan kalian selama praktikum ini berlangsung, serta berikut merupakan beberapa catatan terkait C++ dan Kotlin yang mungkin akan membantu kalian 

> [!IMPORTANT]
> Usahakan bekerja sama walaupun sebagain dari modul akan bersifat individu.

> [!TIP]
> Teliti lagi dalam membaca syntaxnya, agar kalian tidak kebingungan nantinya.

> [!WARNING]
> Jangan jadikan repository ini sebagai satu-satunya acuan kalian, perbanyak membaca dan latihan!

## Pendahuluan terkait C++ dan Kotlin (⊙ _ ⊙ )

C++ dan Kotlin adalah dua bahasa pemrograman yang sering digunakan dalam berbagai bidang. C++ dikenal sebagai bahasa tingkat menengah yang memiliki performa tinggi dan digunakan dalam pengembangan sistem, game, dan aplikasi yang membutuhkan optimasi memori. Sementara itu, Kotlin adalah bahasa modern yang banyak digunakan untuk pengembangan aplikasi Android serta dapat berjalan di JVM dan Native.

## 1. 20 Syntax Penting dalam C++ dan Kotlin ( ꩜ ᯅ ꩜;)⁭ ⁭

### C++ Syntax Penting

1. **Variabel dan Tipe Data**
   ```cpp
   int a = 10;
   float b = 5.5;
   char c = 'A';
   ```
   
2. **Input dan Output**
   ```cpp
   #include <iostream>
   using namespace std;
   int main() {
       int x;
       cout << "Masukkan angka: ";
       cin >> x;
       cout << "Anda memasukkan: " << x;
       return 0;
   }
   ```
   
3. **If-Else Statement**
   ```cpp
   if (x > 10) {
       cout << "Lebih dari 10";
   } else {
       cout << "Kurang dari atau sama dengan 10";
   }
   ```
   
4. **Switch Case**
   ```cpp
   switch(x) {
       case 1: cout << "Satu"; break;
       case 2: cout << "Dua"; break;
       default: cout << "Bukan satu atau dua";
   }
   ```
   
5. **Loop (For, While, Do-While)**
   ```cpp
   for (int i = 0; i < 5; i++) {
       cout << i << " ";
   }
   ```
   
6. **Array**
   ```cpp
   int arr[5] = {1, 2, 3, 4, 5};
   ```
   
7. **Function**
   ```cpp
   int tambah(int a, int b) {
       return a + b;
   }
   ```
   
8. **Pointer**
   ```cpp
   int x = 5;
   int *ptr = &x;
   ```
   
9. **Class dan Object**
   ```cpp
   class Mobil {
   public:
       string merk;
       void jalan() {
           cout << "Mobil berjalan";
       }
   };
   ```
   
10. **Constructor**
    ```cpp
    class Siswa {
    public:
        Siswa() {
            cout << "Objek dibuat";
        }
    };
    ```
    
11. **Destructor**
    ```cpp
    class Siswa {
    public:
        ~Siswa() {
            cout << "Objek dihancurkan";
        }
    };
    ```
    
12. **Inheritance (Pewarisan)**
    ```cpp
    class Induk {
    public:
        void pesan() {
            cout << "Halo dari Induk";
        }
    };
    class Anak : public Induk {
    };
    ```
    
13. **Polymorphism**
    ```cpp
    class Hewan {
    public:
        virtual void suara() {
            cout << "Hewan bersuara";
        }
    };
    ```
    
14. **Struct**
    ```cpp
    struct Mahasiswa {
        string nama;
        int umur;
    };
    ```
    
15. **Enum**
    ```cpp
    enum Hari {Senin, Selasa, Rabu};
    ```
    
16. **Template**
    ```cpp
    template <typename T>
    T tambah(T a, T b) {
        return a + b;
    }
    ```
    
17. **Try-Catch (Exception Handling)**
    ```cpp
    try {
        throw "Terjadi kesalahan";
    } catch (const char* e) {
        cout << e;
    }
    ```
    
18. **Lambda Expression**
    ```cpp
    auto kali = [](int x, int y) { return x * y; };
    ```
    
19. **STL (Standard Template Library - Vector)**
    ```cpp
    #include <vector>
    vector<int> angka = {1, 2, 3};
    ```
    
20. **File Handling**
    ```cpp
    #include <fstream>
    ofstream file("data.txt");
    file << "Hello, File!";
    file.close();
    ```

### Kotlin Syntax Penting

1. **Variabel dan Tipe Data**
   ```kotlin
   val a: Int = 10
   var b: Double = 5.5
   val c: Char = 'A'
   ```
   
2. **Input dan Output**
   ```kotlin
   fun main() {
       println("Masukkan angka: ")
       val x = readLine()?.toInt()
       println("Anda memasukkan: $x")
   }
   ```
   
3. **If-Else Statement**
   ```kotlin
   if (x > 10) {
       println("Lebih dari 10")
   } else {
       println("Kurang dari atau sama dengan 10")
   }
   ```
   
4. **When Statement (Pengganti Switch Case)**
   ```kotlin
   when (x) {
       1 -> println("Satu")
       2 -> println("Dua")
       else -> println("Bukan satu atau dua")
   }
   ```
   
5. **Loop (For, While, Do-While)**
   ```kotlin
   for (i in 0..4) {
       println(i)
   }
   ```
   
6. **Array**
   ```kotlin
   val arr = arrayOf(1, 2, 3, 4, 5)
   ```
   
7. **Function**
   ```kotlin
   fun tambah(a: Int, b: Int): Int {
       return a + b
   }
   ```
   
8. **Class dan Object**
   ```kotlin
   class Mobil(val merk: String) {
       fun jalan() {
           println("Mobil $merk berjalan")
       }
   }
   ```
   
9. **Constructor**
   ```kotlin
   class Siswa(val nama: String) {
       init {
           println("Siswa bernama $nama dibuat")
       }
   }
   ```
   
10. **Inheritance (Pewarisan)**
    ```kotlin
    open class Hewan {
        open fun suara() {
            println("Hewan bersuara")
        }
    }
    class Kucing : Hewan() {
        override fun suara() {
            println("Meow")
        }
    }
    ```
    
11. **Polymorphism**
    ```kotlin
    interface Kendaraan {
        fun jalan()
    }
    class Mobil : Kendaraan {
        override fun jalan() {
            println("Mobil berjalan")
        }
    }
    ```
    
12. **Data Class**
    ```kotlin
    data class Mahasiswa(val nama: String, val umur: Int)
    ```
    
13. **Lambda Expression**
    ```kotlin
    val kali = { x: Int, y: Int -> x * y }
    ```
    
14. **Try-Catch (Exception Handling)**
    ```kotlin
    try {
        val x = 10 / 0
    } catch (e: Exception) {
        println("Terjadi kesalahan: ${e.message}")
    }
    ```
    
15. **Coroutine (Asynchronous Programming)**
    ```kotlin
    import kotlinx.coroutines.*
    fun main() {
        GlobalScope.launch {
            delay(1000L)
            println("Coroutine selesai")
        }
        println("Program utama")
        Thread.sleep(2000L)
    }
    ```
    
16. **Higher-Order Function**
    ```kotlin
    fun operasi(a: Int, b: Int, op: (Int, Int) -> Int): Int {
        return op(a, b)
    }
    ```
    
17. **Extension Function**
    ```kotlin
    fun String.reverseText(): String {
        return this.reversed()
    }
    ```
    
18. **Nullable Type**
    ```kotlin
    var nama: String? = null
    ```
    
19. **Smart Casts**
    ```kotlin
    fun cetak(obj: Any) {
        if (obj is String) {
            println(obj.length)
        }
    }
    ```
    
20. **File Handling**
    ```kotlin
    import java.io.File
    val file = File("data.txt")
    file.writeText("Hello, Kotlin!")
    ```

## 2. 10 Program Sederhana dalam C++ dan Kotlin ( -_•)▄︻テحكـ━一💥

### Program Sederhana dalam C++

1. **Hello World**
   ```cpp
   #include <iostream>
   using namespace std;
   int main() {
       cout << "Hello, World!";
       return 0;
   }
   ```

2. **Kalkulator Sederhana**
   ```cpp
   #include <iostream>
   using namespace std;
   int main() {
       double a, b;
       char op;
       cout << "Masukkan operasi (contoh: 2 + 3): ";
       cin >> a >> op >> b;
       if (op == '+') cout << a + b;
       else if (op == '-') cout << a - b;
       else if (op == '*') cout << a * b;
       else if (op == '/') cout << a / b;
       else cout << "Operator tidak valid";
       return 0;
   }
   ```

3. **Menghitung Luas Lingkaran**
   ```cpp
   #include <iostream>
   using namespace std;
   int main() {
       double r;
       cout << "Masukkan jari-jari: ";
       cin >> r;
       cout << "Luas lingkaran: " << 3.14 * r * r;
       return 0;
   }
   ```

4. **Menentukan Bilangan Ganjil atau Genap**
   ```cpp
   #include <iostream>
   using namespace std;
   int main() {
       int num;
       cout << "Masukkan angka: ";
       cin >> num;
       if (num % 2 == 0) cout << "Genap";
       else cout << "Ganjil";
       return 0;
   }
   ```

5. **Menampilkan Deret Fibonacci**
   ```cpp
   #include <iostream>
   using namespace std;
   int main() {
       int n, t1 = 0, t2 = 1, nextTerm;
       cout << "Masukkan jumlah deret: ";
       cin >> n;
       for (int i = 1; i <= n; i++) {
           cout << t1 << " ";
           nextTerm = t1 + t2;
           t1 = t2;
           t2 = nextTerm;
       }
       return 0;
   }
   ```
   
### Program Sederhana dalam Kotlin

1. **Hello World**
   ```kotlin
   fun main() {
       println("Hello, World!")
   }
   ```

2. **Kalkulator Sederhana**
   ```kotlin
   fun main() {
       println("Masukkan angka pertama: ")
       val a = readLine()!!.toDouble()
       println("Masukkan operator (+, -, *, /): ")
       val op = readLine()!!
       println("Masukkan angka kedua: ")
       val b = readLine()!!.toDouble()
       val result = when (op) {
           "+" -> a + b
           "-" -> a - b
           "*" -> a * b
           "/" -> a / b
           else -> "Operator tidak valid"
       }
       println("Hasil: $result")
   }
   ```

3. **Menghitung Luas Lingkaran**
   ```kotlin
   fun main() {
       println("Masukkan jari-jari: ")
       val r = readLine()!!.toDouble()
       val luas = 3.14 * r * r
       println("Luas lingkaran: $luas")
   }
   ```

4. **Menentukan Bilangan Ganjil atau Genap**
   ```kotlin
   fun main() {
       println("Masukkan angka: ")
       val num = readLine()!!.toInt()
       if (num % 2 == 0) println("Genap") else println("Ganjil")
   }
   ```

5. **Menampilkan Deret Fibonacci**
   ```kotlin
   fun main() {
       println("Masukkan jumlah deret: ")
       val n = readLine()!!.toInt()
       var t1 = 0
       var t2 = 1
       for (i in 1..n) {
           println(t1)
           val nextTerm = t1 + t2
           t1 = t2
           t2 = nextTerm
       }
   }
   ```

## Refrensi ( •⌄• )✧
- [C++ Getting Started](https://www.w3schools.com/cpp/cpp_intro.asp)
- [C++ Introduction](https://www.geeksforgeeks.org/introduction-to-c-programming-language/)
- [Android Studio](https://developer.android.com/studio?hl=id)
- [Kotlin Getting Started](https://www.w3schools.com/kotlin/kotlin_intro.php)
- [Kotlin Introduction](https://kotlinlang.org/docs/getting-started.html)
  

