/* file   : minigame.h
   pemilik: B (Fikri)
   isi    : ADT Riwayat Skor (MLL Minigame -> Skor),
            koin, XP, dan fungsi antarmodul milik B (FSD bagian 4.3) */

#ifndef MINIGAME_H_INCLUDED
#define MINIGAME_H_INCLUDED

#include "pou.h"

/* ===== child: skor (DLL, terurut menurun) ===== */
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

/* ===== parent: minigame ===== */
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

/* ===== fungsi antarmodul milik B (dipakai A dan C) ===== */
void tambahKoin(Pou &p, int n);
void tambahXP(Pou &p, int n);
/* F.S. xp bertambah; selama xp >= XP_PER_LEVEL, level naik */
void catatSkor(ListMinigame &L, string idGame, Skor s);
/* F.S. s tersimpan di riwayat minigame idGame (terurut, maks 10) */

/* ===== primitif MLL Riwayat Skor (diisi B) ===== */
void createListMinigame(ListMinigame &L);
adrMinigame alokasiMinigame(string id, string nama);
void insertLastMinigame(ListMinigame &L, adrMinigame P);
adrMinigame findMinigame(ListMinigame L, string id);
adrSkor alokasiSkor(Skor s);
void insertSortedSkor(ListSkor &S, adrSkor P);
void deleteLastSkor(ListSkor &S);
void printSkor(ListSkor S);
int nbSkor(ListSkor S);

/* ===== subprogram utama B ===== */
void tampilkanRiwayat(ListMinigame L);
/* TODO B: hitungHadiah */

#endif
