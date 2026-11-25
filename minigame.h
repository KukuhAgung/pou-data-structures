#ifndef MINIGAME_H_INCLUDED
#define MINIGAME_H_INCLUDED

#include "pou.h"

struct Skor {
    int nilai, koinDidapat, giliranMain;
};

typedef struct elmSkor *adrSkor;

struct elmSkor {
    Skor info;
    adrSkor next;
    adrSkor prev;
};

struct ListSkor {
    adrSkor first;
    adrSkor last;
};

struct Minigame {
    string id, nama;
    int highscore, jumlahMain;
};

typedef struct elmMinigame *adrMinigame;

struct elmMinigame {
    Minigame info;
    ListSkor skor;
    adrMinigame next;
};

struct ListMinigame {
    adrMinigame first;
};

void tambahKoin(Pou &p, int n);
void tambahXP(Pou &p, int n);
void catatSkor(ListMinigame &L, string idGame, Skor s);

void createListMinigame(ListMinigame &L);
adrMinigame alokasiMinigame(string id, string nama);
void insertLastMinigame(ListMinigame &L, adrMinigame P);
adrMinigame findMinigame(ListMinigame L, string id);
adrSkor alokasiSkor(Skor s);
void insertSortedSkor(ListSkor &S, adrSkor P);
void deleteLastSkor(ListSkor &S);
void printSkor(ListSkor S);
int nbSkor(ListSkor S);

void tampilkanRiwayat(ListMinigame L);

#endif
