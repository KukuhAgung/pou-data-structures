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
   F.S. status Pou tampil di layar */

/* ===== fungsi antarmodul milik A (boleh dipanggil B dan C) ===== */
void ubahStatus(Pou &p, int dLapar, int dSehat, int dEnergi, int dSenang);
/* F.S. status berubah sebesar delta, dijepit ke rentang 0..STAT_MAX */

void majukanWaktu(Pou &p);
/* F.S. giliran bertambah 1 dan status turun sesuai FSD bagian 5.1 */

bool bisaMainMinigame(Pou p);
/* mengembalikan true jika energi >= 20 dan kesehatan >= 20 */

/* ===== primitif DLL Ruangan (diisi A) ===== */
void createListRuangan(ListRuangan &L);
adrRuangan alokasiRuangan(string id, string nama);
void insertLastRuangan(ListRuangan &L, adrRuangan P);
adrRuangan findRuangan(ListRuangan L, string id);
void printRuangan(ListRuangan L);

/* ===== subprogram utama A (diisi A) =====
   geserKiri, geserKanan, mandi, tidur, cekKondisi */

#endif
