/* file   : kulkas.h
   pemilik: A (Kukuh)
   isi    : ADT Kulkas (SLL) */

#ifndef KULKAS_H_INCLUDED
#define KULKAS_H_INCLUDED

#include "pou.h"
#include "toko.h"    // untuk tipe Item pada tambahKeKulkas

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
/* F.S. jika makanan sudah ada, jumlahnya +1; jika belum, elemen baru
        ditambahkan di akhir kulkas dengan jumlah 1 */

/* ===== primitif SLL Kulkas (diisi A) ===== */
void createKulkas(ListKulkas &K);
bool isEmptyKulkas(ListKulkas K);
adrMakanan alokasiMakanan(Makanan m);
void insertLastKulkas(ListKulkas &K, adrMakanan P);
adrMakanan findMakanan(ListKulkas K, string idItem);
void deleteMakanan(ListKulkas &K, string idItem);
void printKulkas(ListKulkas K);

/* ===== subprogram utama A ===== */
void makan(Pou &p, ListKulkas &K);
/* TODO A: implementasi sesuai FSD fitur A-04 */

#endif
