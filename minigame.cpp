/* file   : minigame.cpp
   pemilik: B (Fikri) */

#include "minigame.h"

void tambahKoin(Pou &p, int n) {
    p.koin += n;
}

void tambahXP(Pou &p, int n) {
    // STUB: belum menaikkan level
    // TODO B: naik level selama xp >= XP_PER_LEVEL, tampilkan pesan
    p.xp += n;
}

void catatSkor(ListMinigame &L, string idGame, Skor s) {
    // STUB: belum menyimpan skor
    // TODO B: findMinigame, insertSortedSkor, perbarui highscore & jumlahMain
    cout << "[Riwayat] skor " << s.nilai << " untuk " << idGame
         << " belum disimpan (stub B)." << endl;
}

void createListMinigame(ListMinigame &L) {
    L.first = Nil;
}

void tampilkanRiwayat(ListMinigame L) {
    // STUB
    cout << "[Riwayat skor] belum dibuat (B)." << endl;
}

/* TODO B: alokasiMinigame, insertLastMinigame, findMinigame, alokasiSkor,
           insertSortedSkor, deleteLastSkor, printSkor, nbSkor */
