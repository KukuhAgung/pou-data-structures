/* file   : pou.cpp
   pemilik: A (Kukuh) */

#include "pou.h"
#include "minigame.h"

/* fungsi bantu: menjepit nilai ke rentang 0..STAT_MAX.
   static = hanya terlihat di file ini, tidak bentrok dengan file lain */
static int jepit(int nilai) {
    if (nilai < 0) {
        return 0;
    }
    if (nilai > STAT_MAX) {
        return STAT_MAX;
    }
    return nilai;
}

int bacaAngka() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukan harus angka, ulangi: ";
    }
    cin.ignore(1000, '\n');
    return x;
}

/* ================= STATUS POU ================= */

void initPou(Pou &p, string nama) {
    p.nama = nama;
    p.lapar = 70;
    p.kesehatan = 80;
    p.energi = 70;
    p.kesenangan = 60;
    p.koin = 100;
    p.xp = 0;
    p.level = 1;
    p.giliran = 0;
}

static void tampilkanBar(string label, int nilai) {
    cout << label << "[";
    int isi = nilai / 10;
    for (int i = 0; i < 10; i++) {
        if (i < isi) {
            cout << "#";
        } else {
            cout << "-";
        }
    }
    cout << "] " << nilai;
    if (nilai < STAT_KRITIS) {
        cout << " !";
    }
    cout << endl;
}

void tampilkanStatus(Pou p) {
    cout << "=== Giliran " << p.giliran << " | Level " << p.level
         << " | XP " << p.xp << "/" << XP_PER_LEVEL
         << " | Koin " << p.koin << " ===" << endl;
    tampilkanBar("Lapar      ", p.lapar);
    tampilkanBar("Kesehatan  ", p.kesehatan);
    tampilkanBar("Energi     ", p.energi);
    tampilkanBar("Kesenangan ", p.kesenangan);
}

void tampilkanPerubahan(Pou sebelum, Pou sesudah) {
    if (sebelum.lapar != sesudah.lapar) {
        cout << "  Lapar      " << sebelum.lapar << " -> " << sesudah.lapar << endl;
    }
    if (sebelum.kesehatan != sesudah.kesehatan) {
        cout << "  Kesehatan  " << sebelum.kesehatan << " -> " << sesudah.kesehatan << endl;
    }
    if (sebelum.energi != sesudah.energi) {
        cout << "  Energi     " << sebelum.energi << " -> " << sesudah.energi << endl;
    }
    if (sebelum.kesenangan != sesudah.kesenangan) {
        cout << "  Kesenangan " << sebelum.kesenangan << " -> " << sesudah.kesenangan << endl;
    }
}

void ubahStatus(Pou &p, int dLapar, int dSehat, int dEnergi, int dSenang) {
    p.lapar = jepit(p.lapar + dLapar);
    p.kesehatan = jepit(p.kesehatan + dSehat);
    p.energi = jepit(p.energi + dEnergi);
    p.kesenangan = jepit(p.kesenangan + dSenang);
}

void cekKondisi(Pou p) {
    if (p.kesehatan <= 0) {
        cout << "! Pou sakit, beri ramuan!" << endl;
    } else if (p.kesehatan < STAT_KRITIS) {
        cout << "! Kesehatan Pou rendah!" << endl;
    }
    if (p.lapar < STAT_KRITIS) {
        cout << "! Pou lapar!" << endl;
    }
    if (p.energi < STAT_KRITIS) {
        cout << "! Pou lelah, ayo tidur!" << endl;
    }
    if (p.kesenangan < STAT_KRITIS) {
        cout << "! Pou sedih, ajak bermain!" << endl;
    }
}

void majukanWaktu(Pou &p) {
    p.giliran++;
    ubahStatus(p, -4, 0, -3, -2);
    if (p.lapar < STAT_KRITIS) {
        ubahStatus(p, 0, -5, 0, 0);   // kelaparan menurunkan kesehatan
    }
    cekKondisi(p);
}

bool bisaMainMinigame(Pou p) {
    return p.energi >= 20 && p.kesehatan >= 20;
}

/* ================= DLL RUANGAN ================= */

void createListRuangan(ListRuangan &L) {
    L.first = Nil;
    L.last = Nil;
}

adrRuangan alokasiRuangan(string id, string nama) {
    adrRuangan P = new elmRuangan;
    P->info.id = id;
    P->info.nama = nama;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void insertLastRuangan(ListRuangan &L, adrRuangan P) {
    if (L.first == Nil) {
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

adrRuangan findRuangan(ListRuangan L, string id) {
    adrRuangan P = L.first;
    while (P != Nil) {
        if (P->info.id == id) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

void printRuangan(ListRuangan L) {
    adrRuangan P = L.first;
    while (P != Nil) {
        cout << P->info.nama;
        if (P->next != Nil) {
            cout << " <-> ";
        }
        P = P->next;
    }
    cout << endl;
}

void tampilkanPosisi(adrRuangan aktif) {
    cout << "< ";
    if (aktif->prev != Nil) {
        cout << aktif->prev->info.nama;
    } else {
        cout << "(ujung)";
    }
    cout << "  |  [ " << aktif->info.nama << " ]  |  ";
    if (aktif->next != Nil) {
        cout << aktif->next->info.nama;
    } else {
        cout << "(ujung)";
    }
    cout << " >" << endl;
}

void geserKiri(adrRuangan &aktif) {
    if (aktif->prev == Nil) {
        cout << "Tidak ada ruangan di sebelah kiri." << endl;
    } else {
        aktif = aktif->prev;
        cout << "Pindah ke " << aktif->info.nama << "." << endl;
    }
}

void geserKanan(adrRuangan &aktif) {
    if (aktif->next == Nil) {
        cout << "Tidak ada ruangan di sebelah kanan." << endl;
    } else {
        aktif = aktif->next;
        cout << "Pindah ke " << aktif->info.nama << "." << endl;
    }
}

/* ================= AKSI PERAWATAN ================= */

void mandi(Pou &p) {
    Pou awal = p;
    ubahStatus(p, 0, 25, 0, 5);
    tambahXP(p, 5);
    cout << "Pou mandi. (+5 XP)" << endl;
    tampilkanPerubahan(awal, p);
    majukanWaktu(p);
}

void tidur(Pou &p) {
    if (p.energi >= 90) {
        cout << "Pou belum mengantuk." << endl;
        return;
    }
    Pou awal = p;
    ubahStatus(p, -10, 0, 50, 0);
    tambahXP(p, 5);
    cout << "Pou tidur. (+5 XP)" << endl;
    tampilkanPerubahan(awal, p);
    majukanWaktu(p);
}
