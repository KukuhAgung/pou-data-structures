/* file   : fooddrop.h
   pemilik: B (Fikri)
   isi    : ADT Queue baris untuk minigame Food Drop */

#ifndef FOODDROP_H_INCLUDED
#define FOODDROP_H_INCLUDED

#include "pou.h"
#include "minigame.h"

/* ===== ADT Queue Baris ===== */
struct Baris {
    char jalur[3];    // '.' kosong, 'M' makanan, 'X' sampah
};

typedef struct elmBaris *adrBaris;

struct elmBaris {
    Baris info;
    adrBaris next;
};

struct QueueBaris {
    adrBaris head;    // baris paling bawah (paling dekat Pou)
    adrBaris tail;    // baris paling atas
};

/* ===== primitif Queue (diisi B) ===== */
void createQueue(QueueBaris &Q);
bool isEmptyQueue(QueueBaris Q);
adrBaris alokasiBaris(Baris b);
void enqueue(QueueBaris &Q, adrBaris P);
void dequeue(QueueBaris &Q, adrBaris &P);
void printQueue(adrBaris P);    // rekursif: head tercetak paling bawah

/* ===== subprogram utama Food Drop ===== */
void mainFoodDrop(Pou &p, ListMinigame &L);
/* I.S. p dan L terdefinisi
   F.S. satu sesi Food Drop selesai; skor, koin, XP, dan status berubah */

/* TODO B: generateBaris, geserPou, cekTangkapan */

#endif
