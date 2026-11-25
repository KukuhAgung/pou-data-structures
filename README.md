# pou-data-structures

Tugas Besar Struktur Data: replikasi mekanik game **Pou** sebagai aplikasi console C++.
Siklus intinya: rawat Pou → main minigame untuk mendapat koin → belanja di toko → rawat Pou lagi.

## Game sumber

**Pou** (Zakeh, 2012) adalah game *virtual pet*: pemain merawat makhluk bernama Pou dengan memberinya
makan, memandikan, menidurkan, dan mengajaknya bermain. Proyek ini menyederhanakan tiga mekaniknya
menjadi program berbasis menu teks dan giliran:

1. Perawatan Pou dan navigasi ruangan
2. Minigame **Food Drop**
3. Minigame **Sudoku**

Fitur pendukung: kulkas, toko, koin, XP dan level, serta riwayat skor minigame.
Data hanya disimpan selama program berjalan.

## Daftar fitur

| Bagian | Fitur |
| ------ | ----- |
| Kehidupan Pou | Geser ruangan (Dapur ⇄ Kamar Mandi ⇄ Ruang Game ⇄ Kamar Tidur), lihat status, buka kulkas, makan, mandi, tidur, peringatan kondisi |
| Food Drop | Pou di 3 jalur menghindari sampah (`X`) dan menangkap makanan (`M`); 3 nyawa, maksimal 30 baris |
| Riwayat skor | 10 skor tertinggi per minigame, highscore, jumlah main, lihat per minigame atau semua |
| Koin, XP, level | Hadiah minigame: koin = skor / 5, XP = skor / 10; level naik setiap 100 XP |
| Sudoku | Isi angka, hapus, undo, hint, cek validitas baris/kolom/kotak |
| Toko | Lihat katalog per kategori (Makanan, Ramuan), cari item, beli item sesuai level |

## Struktur data

Semua ADT dibuat sendiri dengan pointer; tidak memakai container STL (`vector`, `list`, `stack`, `queue`, `map`, dll.).

| Struktur data | Dipakai untuk | Alasan |
| ------------- | ------------- | ------ |
| Doubly Linked List | Ruangan rumah | Geser kiri (`prev`) dan kanan (`next`) |
| Singly Linked List | Isi kulkas | Hanya ditelusuri satu arah |
| Queue | Baris arena Food Drop | Benda yang muncul lebih dulu sampai ke Pou lebih dulu (FIFO) |
| Stack | Undo langkah Sudoku | Langkah terakhir dibatalkan lebih dulu (LIFO) |
| Multi Linked List | Katalog toko (kategori → item) | Item dikelompokkan per kategori |
| Multi Linked List | Riwayat skor (minigame → skor) | Tiap minigame punya daftar skor sendiri, terurut menurun |

## Struktur file

```text
main.cpp              loop utama dan menu
pou.h / pou.cpp       status Pou, DLL ruangan
kulkas.h / .cpp       SLL kulkas
fooddrop.h / .cpp     Queue dan minigame Food Drop
minigame.h / .cpp     MLL riwayat skor, koin, XP, level
sudoku.h / .cpp       Stack dan minigame Sudoku
toko.h / .cpp         MLL katalog toko
```

## Cara menjalankan

**Code::Blocks**

1. Buka `pou-data-structures.cbp`.
2. Pilih *Build and run* (F9).

**Terminal (g++)**

```bash
git clone https://github.com/KukuhAgung/pou-data-structures.git
cd pou-data-structures
g++ *.cpp -o pou
./pou            # Windows: pou.exe
```

## Anggota tim

| Peran | Nama | NIM | Bagian |
| ----- | ---- | --- | ------ |
| A | Kukuh | ... | Kehidupan Pou, ruangan, kulkas |
| B | Fikri | ... | Food Drop, riwayat skor, koin, XP, level |
| C | Naya | ... | Sudoku, toko |
