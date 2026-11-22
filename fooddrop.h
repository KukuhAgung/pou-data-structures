/* file   : fooddrop.h
   pemilik: B (Fikri)
   isi    : ADT Queue baris untuk minigame Food Drop (FSD bagian 6.1) */

#ifndef FOODDROP_H_INCLUDED
#define FOODDROP_H_INCLUDED

#include "pou.h"
#include "minigame.h"

/* ===== konstanta Food Drop ===== */
const int FD_JALUR = 3;          // jumlah jalur arena
const int FD_BARIS_TERLIHAT = 5; // baris yang tampil di atas Pou
const int FD_MAKS_BARIS = 30;    // sesi selesai setelah 30 baris
const int FD_NYAWA_AWAL = 3;
const int FD_SKOR_MAKANAN = 10;
const int FD_EFEK_ENERGI = -15;  // efek satu sesi ke status Pou
const int FD_EFEK_SENANG = 20;

/* ===== ADT Queue Baris ===== */
struct Baris {
    char jalur[3];    // '.' kosong, 'M' makanan, 'X' sampah
};

typedef struct elmBaris *adrBaris;

struct elmBaris {
    Baris info;
    adrBaris next;
};

struct QueueBaris {
    adrBaris head;    // baris paling bawah (paling dekat Pou)
    adrBaris tail;    // baris paling atas
};

/* ===== primitif Queue ===== */
void createQueue(QueueBaris &Q);
/* I.S. sembarang
   F.S. Q kosong: head dan tail bernilai Nil */

bool isEmptyQueue(QueueBaris Q);
/* mengembalikan true jika Q tidak memiliki baris */

adrBaris alokasiBaris(Baris b);
/* mengembalikan alamat elemen baru berisi b, dengan next = Nil */

void enqueue(QueueBaris &Q, adrBaris P);
/* I.S. Q terdefinisi (boleh kosong), P sudah dialokasi
   F.S. P menjadi tail Q (baris paling atas) */

void dequeue(QueueBaris &Q, adrBaris &P);
/* I.S. Q terdefinisi (boleh kosong)
   F.S. jika Q tidak kosong, P = head lama dan sudah dilepas dari Q;
        jika Q kosong, P = Nil */

void printQueue(adrBaris P);
/* I.S. P alamat elemen queue (boleh Nil)
   F.S. baris dari P sampai tail tercetak secara rekursif dengan urutan
        terbalik: tail paling atas, P paling bawah */

/* ===== subprogram utama Food Drop ===== */
Baris generateBaris();
/* mengembalikan baris acak berisi paling banyak 2 benda ('M' atau 'X'),
   sehingga selalu ada minimal 1 jalur tanpa 'X' */

void geserPou(int &posisi, char arah);
/* I.S. posisi jalur Pou (0..FD_JALUR-1), arah = 'a', 'd', atau 's'
   F.S. posisi bergeser satu jalur ke kiri ('a') atau kanan ('d') jika
        tidak keluar arena; 's' tidak mengubah posisi */

void cekTangkapan(Baris b, int posisi, int &skor, int &nyawa);
/* I.S. b baris yang baru sampai ke Pou, posisi jalur Pou
   F.S. jika jalur Pou berisi 'M', skor += FD_SKOR_MAKANAN;
        jika berisi 'X', nyawa berkurang 1; jika '.', tidak berubah */

void mainFoodDrop(Pou &p, ListMinigame &L);
/* I.S. p dan L terdefinisi
   F.S. jika Pou tidak bisa bermain, sesi ditolak dan p tidak berubah;
        jika bisa, satu sesi Food Drop selesai: koin dan XP bertambah,
        skor tercatat di riwayat "FD", energi -15, kesenangan +20,
        dan giliran maju 1 */

#endif
