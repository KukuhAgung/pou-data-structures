/* file   : kulkas.h
   pemilik: A (Kukuh)
   isi    : ADT Kulkas (SLL) */

#ifndef KULKAS_H_INCLUDED
#define KULKAS_H_INCLUDED

#include "pou.h"
#include "toko.h"

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

void tambahKeKulkas(ListKulkas &K, Item it);
void createKulkas(ListKulkas &K);
bool isEmptyKulkas(ListKulkas K);
adrMakanan alokasiMakanan(Makanan m);
void insertLastKulkas(ListKulkas &K, adrMakanan P);
adrMakanan findMakanan(ListKulkas K, string idItem);
adrMakanan findMakananKe(ListKulkas K, int n);
void deleteMakanan(ListKulkas &K, string idItem);
void printKulkas(ListKulkas K);
void makan(Pou &p, ListKulkas &K);

#endif
