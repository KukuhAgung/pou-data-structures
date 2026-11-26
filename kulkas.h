/* file   : kulkas.h
   pemilik: A (Kukuh)
   isi    : ADT Kulkas (SLL) */

#ifndef KULKAS_H_INCLUDED
#define KULKAS_H_INCLUDED

#include "pou.h"
#include "toko.h"

/* ===== ADT Kulkas (SLL) ===== */
struct Makanan {
    string idItem, nama;
    int nilaiLapar, nilaiSehat, jumlah;
};

typedef struct elmMakanan *adrMakanan;

struct elmMakanan {
    Makanan info;
    adrMakanan next;
};

struct ListKulkas {
    adrMakanan first;
};

/* ===== fungsi antarmodul milik A (dipakai C) ===== */
void tambahKeKulkas(ListKulkas &K, Item it);
/* I.S. K dan it terdefinisi
   F.S. jika makanan dengan id yang sama sudah ada, jumlahnya +1;
        jika belum, elemen baru ditambahkan di akhir kulkas dengan jumlah 1 */

/* ===== primitif SLL Kulkas (diisi A) ===== */
void createKulkas(ListKulkas &K);
/* F.S. kulkas kosong (K.first = Nil) */

bool isEmptyKulkas(ListKulkas K);
/* mengembalikan true jika K.first = Nil */

adrMakanan alokasiMakanan(Makanan m);
/* mengembalikan alamat elemen baru berisi m, next = Nil */

void insertLastKulkas(ListKulkas &K, adrMakanan P);
/* I.S. P sudah dialokasikan
   F.S. P berada di akhir list */

adrMakanan findMakanan(ListKulkas K, string idItem);
/* mengembalikan alamat makanan dengan idItem, atau Nil jika tidak ada */

adrMakanan findMakananKe(ListKulkas K, int n);
/* mengembalikan elemen ke-n (mulai dari 1), atau Nil jika n di luar jangkauan */

void deleteMakanan(ListKulkas &K, string idItem);
/* I.S. K mungkin kosong
   F.S. elemen dengan idItem dihapus dan didealokasi; tidak terjadi apa-apa
        jika tidak ditemukan */

void printKulkas(ListKulkas K);
/* F.S. isi kulkas tampil bernomor, atau "Kulkas kosong." */

/* ===== subprogram utama A ===== */
void makan(Pou &p, ListKulkas &K);
/* I.S. p dan K terdefinisi
   F.S. jika kulkas kosong atau lapar >= 95, ditolak tanpa memakan giliran.
        Jika berhasil: status berubah, jumlah makanan -1 (node dihapus jika 0),
        XP +5, lalu majukanWaktu dipanggil */

#endif
