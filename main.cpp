/* file   : main.cpp
   pemilik: A (Kukuh), dikerjakan bersama saat integrasi
   isi    : loop utama program. Hanya memanggil subprogram utama,
            tidak berisi logika ADT. */

#include "pou.h"
#include "kulkas.h"
#include "toko.h"
#include "minigame.h"
#include "fooddrop.h"
#include "sudoku.h"

int main() {
    Pou pou;
    ListRuangan rumah;
    ListKulkas kulkas;
    ListToko toko;
    ListMinigame riwayat;

    initPou(pou, "Pou");
    createListRuangan(rumah);
    createKulkas(kulkas);
    createToko(toko);
    createListMinigame(riwayat);

    // TODO: isi data awal (4 ruangan, isi kulkas, item toko, 2 minigame)

    int pilihan = -1;
    while (pilihan != 0) {
        cout << endl;
        tampilkanStatus(pou);
        cout << "1. Makan  2. Food Drop  3. Sudoku  4. Riwayat skor  9. Toko  0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        // TODO A: ganti menu sementara ini dengan menu per ruangan (FSD bagian 8)
        if (pilihan == 1) {
            makan(pou, kulkas);
        } else if (pilihan == 2) {
            mainFoodDrop(pou, riwayat);
        } else if (pilihan == 3) {
            mainSudoku(pou, riwayat);
        } else if (pilihan == 4) {
            tampilkanRiwayat(riwayat);
        } else if (pilihan == 9) {
            bukaToko(pou, toko, kulkas);
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    cout << "Sampai jumpa!" << endl;
    return 0;
}
