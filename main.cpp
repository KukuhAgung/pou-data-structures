#include "pou.h"
#include "kulkas.h"
#include "toko.h"
#include "minigame.h"
#include "fooddrop.h"
#include "sudoku.h"

void siapkanData(ListRuangan &rumah, ListKulkas &kulkas) {
    createListRuangan(rumah);
    insertLastRuangan(rumah, alokasiRuangan("R01", "Dapur"));
    insertLastRuangan(rumah, alokasiRuangan("R02", "Kamar Mandi"));
    insertLastRuangan(rumah, alokasiRuangan("R03", "Ruang Game"));
    insertLastRuangan(rumah, alokasiRuangan("R04", "Kamar Tidur"));

    createKulkas(kulkas);

    Makanan apel;
    apel.idItem = "M01";
    apel.nama = "Apel";
    apel.nilaiLapar = 10;
    apel.nilaiSehat = 2;
    apel.jumlah = 3;
    insertLastKulkas(kulkas, alokasiMakanan(apel));

    Makanan pizza;
    pizza.idItem = "M03";
    pizza.nama = "Pizza";
    pizza.nilaiLapar = 35;
    pizza.nilaiSehat = -5;
    pizza.jumlah = 1;
    insertLastKulkas(kulkas, alokasiMakanan(pizza));
}

void tampilkanMenu(adrRuangan aktif) {
    string id = aktif->info.id;
    cout << "1. Geser kiri  2. Geser kanan  ";
    if (id == "R01") {
        cout << "3. Buka kulkas  4. Makan  ";
    } else if (id == "R02") {
        cout << "3. Mandi  ";
    } else if (id == "R03") {
        cout << "3. Food Drop  4. Sudoku  5. Riwayat skor  ";
    } else if (id == "R04") {
        cout << "3. Tidur  ";
    }
    cout << "9. Toko  0. Keluar" << endl;
}

int main() {
    Pou pou;
    ListRuangan rumah;
    ListKulkas kulkas;
    ListToko toko;
    ListMinigame riwayat;

    initPou(pou, "Pou");
    siapkanData(rumah, kulkas);
    createToko(toko);
    initRiwayat(riwayat);
    // TODO C: isi data awal toko (FSD bagian 7.2)

    adrRuangan aktif = rumah.first;   // mulai di Dapur
    int pilihan = -1;

    while (pilihan != 0) {
        cout << endl;
        tampilkanStatus(pou);
        cout << endl;
        tampilkanPosisi(aktif);
        tampilkanMenu(aktif);
        cout << "Pilihan: ";
        pilihan = bacaAngka();

        string id = aktif->info.id;
        if (pilihan == 0) {
            cout << "Sampai jumpa!" << endl;
        } else if (pilihan == 1) {
            geserKiri(aktif);
        } else if (pilihan == 2) {
            geserKanan(aktif);
        } else if (pilihan == 9) {
            bukaToko(pou, toko, kulkas);
        } else if (id == "R01" && pilihan == 3) {
            printKulkas(kulkas);
        } else if (id == "R01" && pilihan == 4) {
            makan(pou, kulkas);
        } else if (id == "R02" && pilihan == 3) {
            mandi(pou);
        } else if (id == "R03" && pilihan == 3) {
            mainFoodDrop(pou, riwayat);
        } else if (id == "R03" && pilihan == 4) {
            mainSudoku(pou, riwayat);
        } else if (id == "R03" && pilihan == 5) {
            tampilkanRiwayat(riwayat);
        } else if (id == "R04" && pilihan == 3) {
            tidur(pou);
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
    return 0;
}
