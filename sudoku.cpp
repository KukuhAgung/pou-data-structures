/* file   : sudoku.cpp
   pemilik: C (Naya) */

#include "sudoku.h"
#include <iostream>
using namespace std;

// ==================== PRIMITIF STACK ====================

void createStack(StackLangkah &S) {
    S.top = Nil;
}

bool isEmptyStack(StackLangkah S) {
    if (S.top == Nil) {
        return true;
    } else {
        return false;
    }
}

adrLangkah alokasiLangkah(Langkah l) {
    adrLangkah P = new elmLangkah;
    if (P != Nil) {
        P->info.baris = l.baris;
        P->info.kolom = l.kolom;
        P->info.nilaiLama = l.nilaiLama;
        P->info.nilaiBaru = l.nilaiBaru;
        P->next = Nil;
    }
    return P;
}

void push(StackLangkah &S, adrLangkah P) {
    if (P != Nil) {
        P->next = S.top;
        S.top = P;
    }
}

void pop(StackLangkah &S, adrLangkah &P) {
    if (isEmptyStack(S)) {
        P = Nil;
    } else {
        P = S.top;
        S.top = S.top->next;
        P->next = Nil;
    }
}

void clearStack(StackLangkah &S) {
    adrLangkah P;
    while (!isEmptyStack(S)) {
        pop(S, P);
        delete P;
    }
}

// ==================== SUBPROGRAM SUDOKU ====================

void mainSudoku(Pou &p, ListMinigame &L) {
    if (!bisaMainMinigame(p)) {
        cout << "Pou terlalu lelah/sakit untuk bermain\n";
        return;
    }

    int tingkat = 0;
    while (tingkat < 1 || tingkat > 3) {
        cout << "\n=== PILIH TINGKAT SUDOKU ===\n";
        cout << "1. Mudah (Skor dasar 100)\n";
        cout << "2. Sedang (Skor dasar 200)\n";
        cout << "3. Sulit (Skor dasar 300)\n";
        cout << "Pilih (1-3): ";
        tingkat = bacaAngka();
        if (tingkat < 1 || tingkat > 3) {
            cout << "Pilihan tidak valid.\n";
        }
    }

    int papan[9][9];
    int kunci[9][9];
    bool tetap[9][9];

    int soalMudah[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int kunciMudah[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    int soalSedang[9][9] = {
        {1, 5, 3, 0, 7, 0, 0, 0, 0},
        {2, 6, 0, 1, 9, 5, 0, 0, 0},
        {3, 0, 9, 8, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int kunciSedang[9][9] = {
        {1, 5, 3, 6, 7, 2, 8, 9, 4},
        {2, 6, 8, 1, 9, 5, 7, 3, 4},
        {3, 7, 9, 8, 4, 1, 5, 6, 2},
        {8, 9, 1, 7, 6, 4, 2, 5, 3},
        {4, 2, 6, 8, 5, 3, 9, 1, 7},
        {7, 3, 5, 9, 2, 8, 4, 1, 6},
        {9, 6, 4, 5, 3, 7, 2, 8, 1},
        {6, 8, 7, 4, 1, 2, 3, 9, 5},
        {4, 1, 2, 3, 8, 6, 1, 7, 9}
    };

    int soalSulit[9][9] = {
        {0, 0, 0, 6, 0, 0, 4, 0, 0},
        {7, 0, 0, 0, 0, 3, 6, 0, 0},
        {0, 0, 0, 0, 9, 1, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 0, 1, 8, 0, 0, 0, 3},
        {0, 0, 0, 3, 0, 6, 0, 4, 5},
        {0, 4, 0, 2, 0, 0, 0, 6, 0},
        {9, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 1, 0, 0}
    };

    int kunciSulit[9][9] = {
        {5, 8, 1, 6, 7, 2, 4, 3, 9},
        {7, 9, 2, 8, 4, 3, 6, 5, 1},
        {3, 6, 4, 5, 9, 1, 7, 8, 2},
        {4, 3, 8, 9, 5, 7, 2, 1, 6},
        {2, 5, 6, 1, 8, 4, 9, 7, 3},
        {1, 7, 9, 3, 2, 6, 8, 4, 5},
        {8, 4, 5, 2, 1, 9, 3, 6, 7},
        {9, 1, 3, 7, 6, 8, 5, 2, 4},
        {6, 2, 7, 4, 3, 5, 1, 9, 8}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tingkat == 1) {
                papan[i][j] = soalMudah[i][j];
                kunci[i][j] = kunciMudah[i][j];
            } else if (tingkat == 2) {
                papan[i][j] = soalSedang[i][j];
                kunci[i][j] = kunciSedang[i][j];
            } else {
                papan[i][j] = soalSulit[i][j];
                kunci[i][j] = kunciSulit[i][j];
            }

            if (papan[i][j] != 0) {
                tetap[i][j] = true;
            } else {
                tetap[i][j] = false;
            }
        }
    }

    Pou awal = p;
    p.giliran++;
    ubahStatus(p, 0, 0, -15, 20);

    StackLangkah S;
    createStack(S);
    int sisaHint = 3;
    bool selesai = false;
    bool menyerah = false;
    bool inputAman = true;

    while (!selesai && !menyerah && inputAman) {
        int kosong = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (papan[i][j] == 0) {
                    kosong++;
                }
            }
        }
        tampilkanPapan(papan, tetap, tingkat, sisaHint, kosong);

        string cmd;
        cout << "> ";
        if (cin >> cmd) {
            if (cmd == "isi") {
                int b, k, n;
                cin >> b >> k >> n;
                isiAngka(papan, tetap, S, b, k, n);
            } else if (cmd == "hapus") {
                int b, k;
                cin >> b >> k;
                hapusAngka(papan, tetap, S, b, k);
            } else if (cmd == "undo") {
                undoLangkah(papan, S);
            } else if (cmd == "hint") {
                beriHint(papan, kunci, tetap, S, sisaHint);
            } else if (cmd == "cek") {
                int sisaKosong = 0;
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        if (papan[i][j] == 0) {
                            sisaKosong++;
                        }
                    }
                }
                cout << "Jumlah sel yang masih kosong: " << sisaKosong << "\n";
            } else if (cmd == "menyerah") {
                menyerah = true;
                cout << "Kamu menyerah dari permainan Sudoku. Tidak ada hadiah dan skor tidak dicatat.\n";
            } else {
                cout << "Perintah tidak dikenali.\n";
            }

            if (!menyerah && cekSelesai(papan, kunci)) {
                selesai = true;
            }
        } else {
            inputAman = false;
        }
    }

    if (selesai) {
        int hintDipakai = 3 - sisaHint;
        int skor = hitungSkorSudoku(tingkat, hintDipakai);
        int koin = 0;
        int xp = 0;
        hitungHadiah(skor, koin, xp);

        cout << "\nSelamat! Sudoku selesai!\n";
        cout << "Skor: " << skor << " | Koin +" << koin << " | XP +" << xp << "\n";

        tambahKoin(p, koin);
        tambahXP(p, xp);
        tampilkanPerubahan(awal, p);

        Skor catatan;
        catatan.nilai = skor;
        catatan.koinDidapat = koin;
        catatan.giliranMain = p.giliran;
        catatSkor(L, "SD", catatan);
    }

    clearStack(S);
}

void tampilkanPapan(int papan[9][9], bool tetap[9][9], int tingkat, int sisaHint, int jumlahKosong) {
    string labelTingkat = "Tidak Diketahui";
    if (tingkat == 1) {
        labelTingkat = "Mudah";
    } else if (tingkat == 2) {
        labelTingkat = "Sedang";
    } else if (tingkat == 3) {
        labelTingkat = "Sulit";
    }

    int hitungKosong = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (papan[i][j] == 0) {
                hitungKosong++;
            }
        }
    }

    int hintTerpakai = 3 - sisaHint;
    cout << "\n=== SUDOKU (" << labelTingkat << ") | Hint "
         << hintTerpakai << "/3"
         << " | Kosong " << hitungKosong << " ===\n";
    cout << "    1 2 3   4 5 6   7 8 9\n";
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            cout << "  +-------+-------+-------+\n";
        }
        cout << (i + 1) << " | ";
        for (int j = 0; j < 9; j++) {
            if (papan[i][j] == 0) {
                cout << ". ";
            } else {
                cout << papan[i][j];
                if (tetap[i][j]) {
                    cout << "*";
                } else {
                    cout << " ";
                }
            }
            if ((j + 1) % 3 == 0) {
                cout << "| ";
            }
        }
        cout << "\n";
    }
    cout << "  +-------+-------+-------+\n";
    cout << "Perintah: isi <b> <k> <n> | hapus <b> <k> | undo | hint | cek | menyerah\n";
    cout << "(Angka bertanda '*' adalah angka bawaan soal)\n";
}

bool isiAngka(int papan[9][9], bool tetap[9][9], StackLangkah &S, int b, int k, int n) {
    int idxB = b - 1;
    int idxK = k - 1;

    if (idxB < 0 || idxB >= 9 || idxK < 0 || idxK >= 9) {
        cout << "Koordinat baris/kolom tidak valid (gunakan 1-9).\n";
        return false;
    }
    if (tetap[idxB][idxK]) {
        cout << "Sel (" << b << ", " << k << ") adalah angka bawaan soal dan tidak bisa diubah.\n";
        return false;
    }
    if (n < 1 || n > 9) {
        cout << "Angka di luar rentang (harus 1-9).\n";
        return false;
    }

    string pesanBentrok;
    if (!cekValid(papan, idxB, idxK, n, pesanBentrok)) {
        return false;
    }

    int nilaiLama = papan[idxB][idxK];
    papan[idxB][idxK] = n;

    Langkah step;
    step.baris = idxB;
    step.kolom = idxK;
    step.nilaiLama = nilaiLama;
    step.nilaiBaru = n;

    adrLangkah P = alokasiLangkah(step);
    if (P != Nil) {
        push(S, P);
    }
    cout << "Berhasil mengisi angka " << n << " di (" << b << ", " << k << ").\n";
    return true;
}

bool hapusAngka(int papan[9][9], bool tetap[9][9], StackLangkah &S, int b, int k) {
    int idxB = b - 1;
    int idxK = k - 1;

    if (idxB < 0 || idxB >= 9 || idxK < 0 || idxK >= 9) {
        cout << "Koordinat baris/kolom tidak valid (gunakan 1-9).\n";
        return false;
    }
    if (tetap[idxB][idxK]) {
        cout << "Sel (" << b << ", " << k << ") adalah angka bawaan soal dan tidak bisa dihapus.\n";
        return false;
    }
    if (papan[idxB][idxK] == 0) {
        cout << "Sel (" << b << ", " << k << ") memang sudah kosong.\n";
        return false;
    }

    int nilaiLama = papan[idxB][idxK];
    papan[idxB][idxK] = 0;

    Langkah step;
    step.baris = idxB;
    step.kolom = idxK;
    step.nilaiLama = nilaiLama;
    step.nilaiBaru = 0;

    adrLangkah P = alokasiLangkah(step);
    if (P != Nil) {
        push(S, P);
    }
    cout << "Isian pada (" << b << ", " << k << ") berhasil dikosongkan.\n";
    return true;
}

bool cekValid(int papan[9][9], int b, int k, int n, string &pesanBentrok) {
    if (b < 0 || b >= 9 || k < 0 || k >= 9) {
        cout << "Posisi baris atau kolom di luar rentang (1-9)." << endl;
        pesanBentrok = "Koordinat tidak valid";
        return false;
    }
    if (n < 1 || n > 9) {
        cout << "Nilai angka harus berada pada rentang 1-9." << endl;
        pesanBentrok = "Angka tidak valid";
        return false;
    }

    for (int j = 0; j < 9; j++) {
        if (j != k && papan[b][j] == n) {
            cout << "Angka " << n << " bentrok di baris " << (b + 1)
                 << " (kolom " << (j + 1) << ")." << endl;
            pesanBentrok = "Bentrok di baris";
            return false;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (i != b && papan[i][k] == n) {
            cout << "Angka " << n << " bentrok di kolom " << (k + 1)
                 << " (baris " << (i + 1) << ")." << endl;
            pesanBentrok = "Bentrok di kolom";
            return false;
        }
    }

    int awalBaris = (b / 3) * 3;
    int awalKolom = (k / 3) * 3;
    int nomorKotak = (b / 3) * 3 + (k / 3) + 1;
    for (int i = awalBaris; i < awalBaris + 3; i++) {
        for (int j = awalKolom; j < awalKolom + 3; j++) {
            if ((i != b || j != k) && papan[i][j] == n) {
                cout << "Angka " << n << " bentrok di kotak 3x3 ke-" << nomorKotak
                     << " (baris " << (i + 1) << ", kolom " << (j + 1) << ")." << endl;
                pesanBentrok = "Bentrok di kotak 3x3";
                return false;
            }
        }
    }

    pesanBentrok = "";
    return true;
}

void undoLangkah(int papan[9][9], StackLangkah &S) {
    if (isEmptyStack(S)) {
        cout << "Tidak ada langkah untuk dibatalkan\n";
        return;
    }

    adrLangkah P;
    pop(S, P);
    if (P != Nil) {
        int b = P->info.baris;
        int k = P->info.kolom;
        int nilaiLama = P->info.nilaiLama;
        papan[b][k] = nilaiLama;

        if (nilaiLama == 0) {
            cout << "Undo berhasil: sel (" << (b + 1) << ", " << (k + 1) << ") kembali ke kosong.\n";
        } else {
            cout << "Undo berhasil: sel (" << (b + 1) << ", " << (k + 1) << ") kembali ke " << nilaiLama << ".\n";
        }
        delete P;
    }
}

bool beriHint(int papan[9][9], int kunci[9][9], bool tetap[9][9], StackLangkah &S, int &sisaHint) {
    if (sisaHint <= 0) {
        cout << "Jatah hint sudah habis (maksimal 3 kali).\n";
        return false;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!tetap[i][j] && papan[i][j] == 0) {
                int jawaban = kunci[i][j];
                papan[i][j] = jawaban;
                sisaHint--;

                Langkah step;
                step.baris = i;
                step.kolom = j;
                step.nilaiLama = 0;
                step.nilaiBaru = jawaban;

                adrLangkah P = alokasiLangkah(step);
                if (P != Nil) {
                    push(S, P);
                }
                cout << "Hint mengisi sel (" << (i + 1) << ", " << (j + 1)
                     << ") dengan angka " << jawaban << ". Sisa hint: " << sisaHint << "\n";
                return true;
            }
        }
    }

    cout << "Tidak ada sel kosong untuk diberi hint.\n";
    return false;
}

bool cekSelesai(int papan[9][9], int kunci[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (papan[i][j] == 0 || papan[i][j] != kunci[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int hitungSkorSudoku(int tingkat, int hintDipakai) {
    int dasar = 0;
    if (tingkat == 1) {
        dasar = 100;
    } else if (tingkat == 2) {
        dasar = 200;
    } else if (tingkat == 3) {
        dasar = 300;
    }

    int skor = dasar - (hintDipakai * 20);
    if (skor < 0) {
        return 0;
    }
    return skor;
}
