/* file   : kulkas.cpp
   pemilik: A (Kukuh) */

#include "kulkas.h"
#include "minigame.h"   // untuk tambahXP (milik B)

void createKulkas(ListKulkas &K) {
    K.first = Nil;
}

bool isEmptyKulkas(ListKulkas K) {
    return K.first == Nil;
}

adrMakanan alokasiMakanan(Makanan m) {
    adrMakanan P = new elmMakanan;
    P->info = m;
    P->next = Nil;
    return P;
}

void insertLastKulkas(ListKulkas &K, adrMakanan P) {
    if (isEmptyKulkas(K)) {
        K.first = P;
    } else {
        adrMakanan Q = K.first;
        while (Q->next != Nil) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrMakanan findMakanan(ListKulkas K, string idItem) {
    adrMakanan P = K.first;
    while (P != Nil) {
        if (P->info.idItem == idItem) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

adrMakanan findMakananKe(ListKulkas K, int n) {
    if (n < 1) {
        return Nil;
    }
    adrMakanan P = K.first;
    int i = 1;
    while (P != Nil && i < n) {
        P = P->next;
        i++;
    }
    return P;
}

void deleteMakanan(ListKulkas &K, string idItem) {
    adrMakanan P = K.first;
    adrMakanan prec = Nil;
    while (P != Nil && P->info.idItem != idItem) {
        prec = P;
        P = P->next;
    }
    if (P == Nil) {
        return;
    }
    if (prec == Nil) {
        K.first = P->next;
    } else {
        prec->next = P->next;
    }
    P->next = Nil;
    delete P;
}

void printKulkas(ListKulkas K) {
    if (isEmptyKulkas(K)) {
        cout << "Kulkas kosong." << endl;
        return;
    }
    cout << "Isi kulkas:" << endl;
    adrMakanan P = K.first;
    int i = 1;
    while (P != Nil) {
        cout << "  " << i << ". " << P->info.nama << " (x" << P->info.jumlah
             << ")  Lapar +" << P->info.nilaiLapar;
        if (P->info.nilaiSehat != 0) {
            cout << ", Kesehatan ";
            if (P->info.nilaiSehat > 0) {
                cout << "+";
            }
            cout << P->info.nilaiSehat;
        }
        cout << endl;
        P = P->next;
        i++;
    }
}

void tambahKeKulkas(ListKulkas &K, Item it) {
    adrMakanan P = findMakanan(K, it.id);
    if (P != Nil) {
        P->info.jumlah++;
    } else {
        Makanan m;
        m.idItem = it.id;
        m.nama = it.nama;
        m.nilaiLapar = it.efLapar;
        m.nilaiSehat = it.efSehat;
        m.jumlah = 1;
        insertLastKulkas(K, alokasiMakanan(m));
    }
}

void makan(Pou &p, ListKulkas &K) {
    if (isEmptyKulkas(K)) {
        cout << "Kulkas kosong." << endl;
        return;
    }
    if (p.lapar >= 95) {
        cout << "Pou sudah kenyang." << endl;
        return;
    }

    printKulkas(K);
    cout << "Pilih nomor makanan (0 = batal): ";
    int pilih = bacaAngka();
    if (pilih == 0) {
        return;
    }
    adrMakanan P = findMakananKe(K, pilih);
    if (P == Nil) {
        cout << "Nomor makanan tidak valid." << endl;
        return;
    }

    Pou awal = p;
    ubahStatus(p, P->info.nilaiLapar, P->info.nilaiSehat, 0, 0);
    cout << "Pou makan " << P->info.nama << ". (+5 XP)" << endl;
    P->info.jumlah--;
    if (P->info.jumlah == 0) {
        cout << P->info.nama << " habis, dihapus dari kulkas." << endl;
        deleteMakanan(K, P->info.idItem);
    }
    tambahXP(p, 5);
    tampilkanPerubahan(awal, p);
    majukanWaktu(p);
}
