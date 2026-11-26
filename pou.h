/* file   : pou.h
   pemilik: A (Kukuh)
   isi    : struct Pou bersama, konstanta, ADT Ruangan (DLL),
            dan fungsi antarmodul milik A (FSD bagian 4.3) */

#ifndef POU_H_INCLUDED
#define POU_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

#define Nil NULL

/* ===== konstanta ===== */
const int STAT_MAX = 100;
const int STAT_KRITIS = 20;     // di bawah nilai ini muncul peringatan
const int XP_PER_LEVEL = 100;

/* ===== status Pou (dipakai semua modul) ===== */
struct Pou {
    string nama;
    int lapar;        // 100 = kenyang, 0 = sangat lapar
    int kesehatan;    // 0 = sakit
    int energi;
    int kesenangan;
    int koin;
    int xp;
    int level;
    int giliran;      // penghitung waktu
};

/* ===== ADT Ruangan (DLL) ===== */
struct Ruangan {
    string id, nama;
};

typedef struct elmRuangan *adrRuangan;

struct elmRuangan {
    Ruangan info;
    adrRuangan next;
    adrRuangan prev;
};

struct ListRuangan {
    adrRuangan first;
    adrRuangan last;
};

/* ===== inisialisasi dan tampilan ===== */
void initPou(Pou &p, string nama);
/* I.S. sembarang
   F.S. p berisi nilai awal sesuai FSD bagian 4.1 */

void tampilkanStatus(Pou p);
/* I.S. p terdefinisi
   F.S. status Pou tampil di layar dalam bentuk bar */

void tampilkanPerubahan(Pou sebelum, Pou sesudah);
/* I.S. sebelum dan sesudah terdefinisi
   F.S. hanya status yang berubah yang ditampilkan, contoh "Lapar 60 -> 95" */

/* ===== fungsi antarmodul milik A (boleh dipanggil B dan C) ===== */
void ubahStatus(Pou &p, int dLapar, int dSehat, int dEnergi, int dSenang);
/* F.S. status berubah sebesar delta, dijepit ke rentang 0..STAT_MAX */

void majukanWaktu(Pou &p);
/* F.S. giliran bertambah 1, status turun sesuai FSD bagian 5.1,
        lalu cekKondisi dipanggil */

bool bisaMainMinigame(Pou p);
/* mengembalikan true jika energi >= 20 dan kesehatan >= 20 */

int bacaAngka();
/* membaca satu angka dari cin; mengulang jika masukan bukan angka.
   Boleh dipakai B dan C untuk membaca menu */

/* ===== primitif DLL Ruangan (diisi A) ===== */
void createListRuangan(ListRuangan &L);
adrRuangan alokasiRuangan(string id, string nama);
void insertLastRuangan(ListRuangan &L, adrRuangan P);
adrRuangan findRuangan(ListRuangan L, string id);
void printRuangan(ListRuangan L);

/* ===== subprogram utama A ===== */
void cekKondisi(Pou p);
/* F.S. peringatan tampil untuk setiap status di bawah STAT_KRITIS */

void tampilkanPosisi(adrRuangan aktif);
/* I.S. aktif tidak Nil
   F.S. ruangan kiri, ruangan aktif, dan ruangan kanan tampil;
        "(ujung)" jika tidak ada tetangga */

void geserKiri(adrRuangan &aktif);
void geserKanan(adrRuangan &aktif);
/* F.S. aktif pindah ke prev / next; jika Nil, aktif tetap dan pesan tampil.
        Tidak memakan giliran */

void mandi(Pou &p);
void tidur(Pou &p);
/* F.S. status berubah, XP +5, lalu majukanWaktu dipanggil.
        tidur ditolak (tanpa memakan giliran) jika energi >= 90 */

#endif
