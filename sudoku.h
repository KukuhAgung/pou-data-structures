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

void tampilkanPapan(int papan[9][9], bool tetap[9][9], int tingkat, int sisaHint, int jumlahKosong);
/* I.S. papan, tetap, tingkat, sisaHint, dan jumlahKosong terdefinisi
   F.S. papan Sudoku 9x9, status hint/kosong, dan perintah tercetak ke layar */

bool isiAngka(int papan[9][9], bool tetap[9][9], StackLangkah &S, int b, int k, int n);
/* I.S. papan, tetap, dan S terdefinisi; b, k (1-9), dan n diberikan
   F.S. jika valid dan tidak bentrok, sel terisi n serta langkah di-push ke S; jika tidak, ditolak */

bool hapusAngka(int papan[9][9], bool tetap[9][9], StackLangkah &S, int b, int k);
/* I.S. papan, tetap, dan S terdefinisi; b dan k (1-9) diberikan
   F.S. jika bukan sel tetap dan tidak kosong, sel dikosongkan (0) serta langkah di-push ke S */

bool cekValid(int papan[9][9], int b, int k, int n, string &pesanBentrok);
/* I.S. papan, b, k (0-8), n, dan pesanBentrok terdefinisi
   F.S. mengembalikan true jika n (1-9) tidak bentrok di baris, kolom, dan kotak 3x3; jika tidak, false dan pesanBentrok terisi */

void undoLangkah(int papan[9][9], StackLangkah &S);
/* I.S. papan dan S terdefinisi
   F.S. jika S kosong tampil pesan; jika tidak, langkah teratas di-pop & didealokasi lalu nilaiLama dikembalikan */

bool beriHint(int papan[9][9], int kunci[9][9], bool tetap[9][9], StackLangkah &S, int &sisaHint);
/* I.S. papan, kunci, tetap, S, dan sisaHint terdefinisi
   F.S. jika sisaHint > 0 dan ada sel kosong, sel terisi kunci, sisaHint - 1, dan langkah di-push ke S */

bool cekSelesai(int papan[9][9], int kunci[9][9]);
/* I.S. papan dan kunci terdefinisi
   F.S. mengembalikan true jika seluruh sel 9x9 terisi dan sama persis dengan kunci */

int hitungSkorSudoku(int tingkat, int hintDipakai);
/* I.S. tingkat (1-3) dan hintDipakai terdefinisi
   F.S. mengembalikan skor dasar dikurangi 20 per hint dengan batas minimal 0 */

#endif
