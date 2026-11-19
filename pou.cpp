/* file   : pou.cpp
   pemilik: A (Kukuh) */

#include "pou.h"

/* fungsi bantu: menjepit nilai ke rentang 0..STAT_MAX */
int jepit(int nilai) {
    if (nilai < 0) {
        return 0;
    }
    if (nilai > STAT_MAX) {
        return STAT_MAX;
    }
    return nilai;
}

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

void tampilkanStatus(Pou p) {
    // TODO A: ganti dengan tampilan bar status sesuai FSD bagian 5.3
    cout << "=== Giliran " << p.giliran << " | Level " << p.level
         << " | XP " << p.xp << "/" << XP_PER_LEVEL
         << " | Koin " << p.koin << " ===" << endl;
    cout << "Lapar      : " << p.lapar << endl;
    cout << "Kesehatan  : " << p.kesehatan << endl;
    cout << "Energi     : " << p.energi << endl;
    cout << "Kesenangan : " << p.kesenangan << endl;
}

void ubahStatus(Pou &p, int dLapar, int dSehat, int dEnergi, int dSenang) {
    p.lapar = jepit(p.lapar + dLapar);
    p.kesehatan = jepit(p.kesehatan + dSehat);
    p.energi = jepit(p.energi + dEnergi);
    p.kesenangan = jepit(p.kesenangan + dSenang);
}

void majukanWaktu(Pou &p) {
    // STUB: baru menambah giliran
    // TODO A: lapar -4, energi -3, kesenangan -2, kesehatan -5 jika lapar < 20
    p.giliran++;
}

bool bisaMainMinigame(Pou p) {
    // STUB: sementara selalu boleh bermain
    // TODO A: return energi >= 20 dan kesehatan >= 20
    return true;
}

void createListRuangan(ListRuangan &L) {
    L.first = Nil;
    L.last = Nil;
}

/* TODO A: alokasiRuangan, insertLastRuangan, findRuangan, printRuangan */
