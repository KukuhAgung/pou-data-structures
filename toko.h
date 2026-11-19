/* file   : toko.h
   pemilik: C (Naya)
   isi    : ADT Toko (MLL Kategori -> Item) */

#ifndef TOKO_H_INCLUDED
#define TOKO_H_INCLUDED

#include "pou.h"

struct ListKulkas;   // didefinisikan di kulkas.h (milik A)

/* ===== ADT Toko (MLL) ===== */
struct Item {
    string id, nama, jenis;    // jenis: "Makanan" | "Ramuan"
    int harga, levelMin;
    int efLapar, efSehat, efEnergi, efSenang;
};

typedef struct elmItem *adrItem;

struct elmItem {
    Item info;
    adrItem next;
};

struct Kategori {
    string id, nama;
};

typedef struct elmKategori *adrKategori;

struct elmKategori {
    Kategori info;
    adrItem firstItem;
    adrKategori next;
};

struct ListToko {
    adrKategori first;
};

/* ===== primitif MLL Toko (diisi C) ===== */
void createToko(ListToko &T);
adrKategori alokasiKategori(string id, string nama);
void insertLastKategori(ListToko &T, adrKategori K);
adrKategori findKategori(ListToko T, string id);
adrItem alokasiItem(Item it);
void insertLastItem(adrKategori K, adrItem P);
adrItem findItem(ListToko T, string idItem);
void printKategori(ListToko T);
void printItemKategori(adrKategori K, int levelPou);

/* ===== subprogram utama Toko ===== */
void bukaToko(Pou &p, ListToko &T, ListKulkas &K);
/* I.S. p, T, K terdefinisi
   F.S. pemain melihat dan membeli item; koin, kulkas, atau status berubah */

/* TODO C: beliItem, cekSyaratBeli, terapkanRamuan */

#endif
