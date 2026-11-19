/* file   : kulkas.cpp
   pemilik: A (Kukuh) */

#include "kulkas.h"

void createKulkas(ListKulkas &K) {
    K.first = Nil;
}

bool isEmptyKulkas(ListKulkas K) {
    return K.first == Nil;
}

void tambahKeKulkas(ListKulkas &K, Item it) {
    // STUB: belum menyimpan apa pun
    // TODO A: cari dengan findMakanan, tambah jumlah atau insertLastKulkas
    cout << "[Kulkas] " << it.nama << " belum bisa disimpan (stub A)." << endl;
}

void makan(Pou &p, ListKulkas &K) {
    // STUB
    cout << "[Makan] belum dibuat (A)." << endl;
}

/* TODO A: alokasiMakanan, insertLastKulkas, findMakanan, deleteMakanan, printKulkas */
