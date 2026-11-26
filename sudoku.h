/* file   : sudoku.h
   pemilik: C (Naya)
   isi    : ADT Stack langkah (undo) untuk minigame Sudok */


#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include "pou.h"
#include "minigame.h"

/* ===== ADT Stack Langkah ===== */
struct Langkah {
    int baris, kolom, nilaiLama, nilaiBaru;
};

typedef struct elmLangkah *adrLangkah;

struct elmLangkah {
    Langkah info;
    adrLangkah next;
};

struct StackLangkah {
    adrLangkah top;
};

/* ===== primitif Stack (diisi C) ===== */
void createStack(StackLangkah &S);
bool isEmptyStack(StackLangkah S);
adrLangkah alokasiLangkah(Langkah l);
void push(StackLangkah &S, adrLangkah P);
void pop(StackLangkah &S, adrLangkah &P);
void clearStack(StackLangkah &S);

/* ===== subprogram utama Sudoku ===== */
void mainSudoku(Pou &p, ListMinigame &L);
/* I.S. p dan L terdefinisi
   F.S. satu sesi Sudoku selesai; skor, koin, XP, dan status berubah */

/* TODO C: tampilkanPapan, isiAngka, hapusAngka, cekValid, undoLangkah,
           beriHint, cekSelesai, hitungSkorSudoku */

#endif
