# color-button-game
Sebuah permainan menggunakan Arduino Uno dan LED berwarna.

<img src="https://user-images.githubusercontent.com/82134545/209444142-6bcba5c8-4bef-47ca-bbc0-5460288ac6a1.png" alt="start_screen" width="500"/>

<img src="https://user-images.githubusercontent.com/82134545/209444146-7dd2e1d5-1d6f-4cb7-87ec-693dd5e3a69b.png" alt="press_color" width="500"/>

<img src="https://user-images.githubusercontent.com/82134545/209444176-03f4d6d5-0bc0-4c9c-b059-e513b324162e.png" alt="game_over" width="500"/>



## Deskripsi Permainan
Terdapat LCD display, tiga LED berwarna beserta tombol-tombolnya, serta sebuah tombol start. Ketika tombol start telah ditekan, lampu-lampu LED akan menyala dengan warna-warna acak yang berbeda-beda. LCD akan menampilkan salah satu warna yang menyala. Kamu sebagai pemain diberi waktu satu detik untuk menekan tombol dengan warna LED yang sesuai dengan yang diminta LCD. Jika berhasil menekan tombol yang benar, maka permainan akan lanjut ke warna berikutnya. Jika salah menekan tombol atau satu detik sudah berlalu, maka permainan akan selesai dan akan ditampilkan skor berapa kali berhasil menekan tombol yang benar.

## Komponen
* Arduino Uno
* HD44780 16x2 LCD Display
* WS2812 LED Strip
* Tombol

## Software
* [Arduino IDE](https://www.arduino.cc/en/software)
* Library:
  * wdt
  * [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel)
  * [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal)
* [SimulIDE](https://www.simulide.com/p/home.html)

## Footnote
Alat ini dibuat sebagai tugas praktikum mata kuliah Embedded System.
Tugas diberikan saat masih kuliah daring. Itulah mengapa rangkaian berupa simulasi.
Tugas tersebut untuk bab "Sistem Fault Tolerant Menggunakan Watchdog". Itulah mengapa digunakan watchdog untuk mengulang permainan.
