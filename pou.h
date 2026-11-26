#ifndef POU_H_INCLUDED
#define POU_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

#define Nil NULL

const int STAT_MAX = 100;
const int STAT_KRITIS = 20;
const int XP_PER_LEVEL = 100;

struct Pou {
    string nama;
    int lapar;        // 100 = kenyang, 0 = sangat lapar
    int kesehatan;    // 0 = sakit
    int energi;
    int kesenangan;
    int koin;
    int xp;
    int level;
    int giliran;
};

/* ADT Ruangan (DLL) */
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

void initPou(Pou &p, string nama);
void tampilkanStatus(Pou p);
void tampilkanPerubahan(Pou sebelum, Pou sesudah);
void ubahStatus(Pou &p, int dLapar, int dSehat, int dEnergi, int dSenang);
void majukanWaktu(Pou &p);
bool bisaMainMinigame(Pou p);
int bacaAngka();

void createListRuangan(ListRuangan &L);
adrRuangan alokasiRuangan(string id, string nama);
void insertLastRuangan(ListRuangan &L, adrRuangan P);
adrRuangan findRuangan(ListRuangan L, string id);
void printRuangan(ListRuangan L);

void cekKondisi(Pou p);
void tampilkanPosisi(adrRuangan aktif);
void geserKiri(adrRuangan &aktif);
void geserKanan(adrRuangan &aktif);
void mandi(Pou &p);
void tidur(Pou &p);

#endif
