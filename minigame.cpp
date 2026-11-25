#include "minigame.h"
#include <iomanip>
#include <cctype>

static string hurufBesar(string s) {
    for (int i = 0; i < (int) s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

static void cetakRiwayatMinigame(adrMinigame M) {
    cout << endl << "=== RIWAYAT " << hurufBesar(M->info.nama)
         << " (" << M->info.id << ") ===" << endl;
    cout << "Highscore: " << M->info.highscore
         << " | Jumlah main: " << M->info.jumlahMain
         << " | Tersimpan: " << nbSkor(M->skor) << "/" << MAKS_RIWAYAT << endl;
    printSkor(M->skor);
}

void tambahKoin(Pou &p, int n) {
    p.koin += n;
}

void tambahXP(Pou &p, int n) {
    p.xp += n;
    while (p.xp >= XP_PER_LEVEL) {
        p.xp -= XP_PER_LEVEL;
        p.level++;
        cout << "Pou naik ke level " << p.level << "!" << endl;
    }
}

void catatSkor(ListMinigame &L, string idGame, Skor s) {
    adrMinigame M = findMinigame(L, idGame);
    if (M == Nil) {
        cout << "Minigame " << idGame << " tidak ditemukan, skor tidak dicatat." << endl;
    } else {
        insertSortedSkor(M->skor, alokasiSkor(s));
        if (nbSkor(M->skor) > MAKS_RIWAYAT) {
            deleteLastSkor(M->skor);
        }

        M->info.jumlahMain++;
        if (s.nilai > M->info.highscore) {
            M->info.highscore = s.nilai;
        }
    }
}

void createListMinigame(ListMinigame &L) {
    L.first = Nil;
}

adrMinigame alokasiMinigame(string id, string nama) {
    adrMinigame P = new elmMinigame;
    P->info.id = id;
    P->info.nama = nama;
    P->info.highscore = 0;
    P->info.jumlahMain = 0;
    P->skor.first = Nil;
    P->skor.last = Nil;
    P->next = Nil;
    return P;
}

void insertLastMinigame(ListMinigame &L, adrMinigame P) {
    if (L.first == Nil) {
        L.first = P;
    } else {
        adrMinigame Q = L.first;
        while (Q->next != Nil) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrMinigame findMinigame(ListMinigame L, string id) {
    adrMinigame P = L.first;
    while (P != Nil && P->info.id != id) {
        P = P->next;
    }
    return P;
}

adrSkor alokasiSkor(Skor s) {
    adrSkor P = new elmSkor;
    P->info = s;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void insertSortedSkor(ListSkor &S, adrSkor P) {
    if (S.first == Nil) {
        S.first = P;
        S.last = P;
    } else if (P->info.nilai > S.first->info.nilai) {
        P->next = S.first;
        S.first->prev = P;
        S.first = P;
    } else {
        adrSkor Q = S.first;
        while (Q->next != Nil && Q->next->info.nilai >= P->info.nilai) {
            Q = Q->next;
        }
        P->next = Q->next;
        P->prev = Q;
        if (Q->next != Nil) {
            Q->next->prev = P;
        } else {
            S.last = P;
        }
        Q->next = P;
    }
}

void deleteLastSkor(ListSkor &S) {
    if (S.first != Nil) {
        adrSkor P = S.last;
        if (S.first == S.last) {
            S.first = Nil;
            S.last = Nil;
        } else {
            S.last = P->prev;
            S.last->next = Nil;
            P->prev = Nil;
        }
        delete P;
    }
}

void printSkor(ListSkor S) {
    if (S.first == Nil) {
        cout << "  (belum ada skor)" << endl;
    } else {
        cout << "  No | Skor | Koin | Giliran" << endl;
        adrSkor P = S.first;
        int no = 1;
        while (P != Nil) {
            cout << "  " << setw(2) << no
                 << " | " << setw(4) << P->info.nilai
                 << " | " << setw(4) << P->info.koinDidapat
                 << " | " << setw(7) << P->info.giliranMain << endl;
            no++;
            P = P->next;
        }
    }
}

int nbSkor(ListSkor S) {
    int n = 0;
    adrSkor P = S.first;
    while (P != Nil) {
        n++;
        P = P->next;
    }
    return n;
}

void initRiwayat(ListMinigame &L) {
    createListMinigame(L);
    insertLastMinigame(L, alokasiMinigame("FD", "Food Drop"));
    insertLastMinigame(L, alokasiMinigame("SD", "Sudoku"));
}

void hitungHadiah(int skor, int &koin, int &xp) {
    koin = skor / PEMBAGI_KOIN;
    xp = skor / PEMBAGI_XP;
}

void tampilkanRiwayat(ListMinigame L) {
    cout << endl << "Pilih riwayat (FD = Food Drop, SD = Sudoku, ALL = semua): ";
    string pilihan;
    cin >> pilihan;
    pilihan = hurufBesar(pilihan);

    if (pilihan == "ALL") {
        if (L.first == Nil) {
            cout << "Belum ada minigame terdaftar." << endl;
        }
        adrMinigame M = L.first;
        while (M != Nil) {
            cetakRiwayatMinigame(M);
            M = M->next;
        }
    } else {
        adrMinigame M = findMinigame(L, pilihan);
        if (M == Nil) {
            cout << "Pilihan tidak valid." << endl;
        } else {
            cetakRiwayatMinigame(M);
        }
    }
}
