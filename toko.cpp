/* file   : toko.cpp
   pemilik: C (Naya) */

#include "toko.h"
#include "kulkas.h"

void createToko(ListToko &T) {
    T.first = Nil;
}

void bukaToko(Pou &p, ListToko &T, ListKulkas &K) {
    if (T.first == Nil) {
        adrKategori katMakanan = alokasiKategori("MKN", "Makanan");
        adrKategori katRamuan = alokasiKategori("RMN", "Ramuan");
        insertLastKategori(T, katMakanan);
        insertLastKategori(T, katRamuan);

        Item daftarItem[8] = {
            {"M01", "Apel", "Makanan", 10, 1, 10, 2, 0, 0},
            {"M02", "Roti", "Makanan", 15, 1, 20, 0, 0, 0},
            {"M03", "Pizza", "Makanan", 30, 1, 35, -5, 0, 0},
            {"M04", "Sup Sayur", "Makanan", 25, 2, 25, 10, 0, 0},
            {"M05", "Steak", "Makanan", 50, 3, 50, 0, 0, 0},
            {"R01", "Ramuan Sehat", "Ramuan", 60, 1, 0, 50, 0, 0},
            {"R02", "Ramuan Energi", "Ramuan", 70, 2, 0, 0, 60, 0},
            {"R03", "Ramuan Bahagia", "Ramuan", 50, 2, 0, 0, 0, 40}
        };

        for (int i = 0; i < 5; i++) {
            insertLastItem(katMakanan, alokasiItem(daftarItem[i]));
        }
        for (int i = 5; i < 8; i++) {
            insertLastItem(katRamuan, alokasiItem(daftarItem[i]));
        }
    }

    bool keluarToko = false;
    bool inputAman = true;

    while (!keluarToko && inputAman) {
        cout << "\n==============================\n";
        cout << "         TOKO POU\n";
        cout << "Koin: " << p.koin << " | Level: " << p.level << "\n";
        cout << "==============================\n";
        cout << "1. Lihat Kategori & Item\n";
        cout << "2. Cari Item berdasarkan ID\n";
        cout << "3. Beli Item berdasarkan ID\n";
        cout << "0. Keluar dari Toko\n";
        cout << "Pilih menu: ";

        int pilihan;
        if (cin >> pilihan) {
            if (pilihan == 1) {
                printKategori(T);
                if (T.first != Nil) {
                    string idKat;
                    cout << "Masukkan ID Kategori (atau 'batal'): ";
                    cin >> idKat;
                    if (idKat != "batal") {
                        adrKategori katDipilih = findKategori(T, idKat);
                        printItemKategori(katDipilih, p.level);
                    }
                }
            } else if (pilihan == 2) {
                string idCari;
                cout << "Masukkan ID Item yang dicari: ";
                cin >> idCari;
                adrItem ketemu = findItem(T, idCari);
                if (ketemu == Nil) {
                    cout << "Item tidak ditemukan.\n";
                } else {
                    cout << "Ditemukan -> ID: " << ketemu->info.id
                         << " | Nama: " << ketemu->info.nama
                         << " | Jenis: " << ketemu->info.jenis
                         << " | Harga: " << ketemu->info.harga
                         << " | Min Lv: " << ketemu->info.levelMin << "\n";
                }
            } else if (pilihan == 3) {
                string idBeli;
                cout << "Masukkan ID Item yang ingin dibeli: ";
                cin >> idBeli;
                beliItem(p, T, K, idBeli);
            } else if (pilihan == 0) {
                keluarToko = true;
                cout << "Keluar dari toko.\n";
            } else {
                cout << "Pilihan menu tidak valid.\n";
            }
        } else {
            inputAman = false;
        }
    }
}

adrKategori alokasiKategori(string id, string nama) {
    adrKategori K = new elmKategori;
    if (K != Nil) {
        K->info.id = id;
        K->info.nama = nama;
        K->firstItem = Nil;
        K->next = Nil;
    }
    return K;
}

void insertLastKategori(ListToko &T, adrKategori K) {
    if (K != Nil) {
        K->next = Nil;
        if (T.first == Nil) {
            T.first = K;
        } else {
            adrKategori bantu = T.first;
            while (bantu->next != Nil) {
                bantu = bantu->next;
            }
            bantu->next = K;
        }
    }
}

adrKategori findKategori(ListToko T, string id) {
    adrKategori bantu = T.first;
    adrKategori ketemu = Nil;
    bool selesaiCari = false;

    while (bantu != Nil && !selesaiCari) {
        if (bantu->info.id == id) {
            ketemu = bantu;
            selesaiCari = true;
        } else {
            bantu = bantu->next;
        }
    }
    return ketemu;
}

adrItem alokasiItem(Item it) {
    adrItem P = new elmItem;
    if (P != Nil) {
        P->info = it;
        P->next = Nil;
    }
    return P;
}

void insertLastItem(adrKategori K, adrItem P) {
    if (K != Nil && P != Nil) {
        P->next = Nil;
        if (K->firstItem == Nil) {
            K->firstItem = P;
        } else {
            adrItem bantu = K->firstItem;
            while (bantu->next != Nil) {
                bantu = bantu->next;
            }
            bantu->next = P;
        }
    }
}

adrItem findItem(ListToko T, string idItem) {
    adrKategori kat = T.first;
    adrItem ketemu = Nil;
    bool sudahKetemu = false;

    while (kat != Nil && !sudahKetemu) {
        adrItem it = kat->firstItem;
        while (it != Nil && !sudahKetemu) {
            if (it->info.id == idItem) {
                ketemu = it;
                sudahKetemu = true;
            } else {
                it = it->next;
            }
        }
        kat = kat->next;
    }
    return ketemu;
}

void printKategori(ListToko T) {
    cout << "\n=== DAFTAR KATEGORI TOKO ===\n";
    if (T.first == Nil) {
        cout << "Belum ada kategori tersedia.\n";
    } else {
        adrKategori bantu = T.first;
        int nomor = 1;
        while (bantu != Nil) {
            cout << nomor << ". [" << bantu->info.id << "] " << bantu->info.nama << "\n";
            bantu = bantu->next;
            nomor++;
        }
    }
}

void printItemKategori(adrKategori K, int levelPou) {
    if (K == Nil) {
        cout << "Kategori tidak ditemukan.\n";
    } else {
        cout << "\n=== ITEM KATEGORI: " << K->info.nama << " (Level Pou: " << levelPou << ") ===\n";
        if (K->firstItem == Nil) {
            cout << "Belum ada item pada kategori ini.\n";
        } else {
            adrItem bantu = K->firstItem;
            int nomor = 1;
            while (bantu != Nil) {
                Item it = bantu->info;
                cout << nomor << ". [" << it.id << "] " << it.nama;
                if (levelPou < it.levelMin) {
                    cout << " [terkunci]";
                }
                cout << " | Harga: " << it.harga
                     << " | Min Lv: " << it.levelMin << "\n";
                cout << "   Efek -> Lapar: " << it.efLapar
                     << ", Kesehatan: " << it.efSehat
                     << ", Energi: " << it.efEnergi
                     << ", Kesenangan: " << it.efSenang << "\n";
                bantu = bantu->next;
                nomor++;
            }
        }
    }
}

bool beliItem(Pou &p, ListToko T, ListKulkas &K, string idItem) {
    adrItem target = findItem(T, idItem);
    bool sukses = false;

    if (target == Nil) {
        cout << "Item tidak ditemukan.\n";
    } else {
        string alasan;
        if (!cekSyaratBeli(p, target->info, alasan)) {
            cout << "Gagal membeli: " << alasan << "\n";
        } else {
            int koinSebelum = p.koin;
            p.koin = p.koin - target->info.harga;
            cout << "Koin: " << koinSebelum << " -> " << p.koin << "\n";

            if (target->info.jenis == "Ramuan") {
                terapkanRamuan(p, target->info);
            } else {
                tambahKeKulkas(K, target->info);
                cout << target->info.nama << " masuk ke kulkas.\n";
            }
            sukses = true;
        }
    }

    return sukses;
}

bool cekSyaratBeli(Pou p, Item it, string &alasan) {
    bool boleh = true;
    alasan = "";

    if (p.level < it.levelMin) {
        boleh = false;
        alasan = "Level Pou belum mencukupi.";
        cout << "Minimal level yang dibutuhkan: " << it.levelMin << "\n";
    } else if (p.koin < it.harga) {
        boleh = false;
        alasan = "Koin tidak cukup.";
        cout << "Harga item: " << it.harga << " koin\n";
    }

    return boleh;
}

void terapkanRamuan(Pou &p, Item it) {
    Pou sebelum = p;
    ubahStatus(p, it.efLapar, it.efSehat, it.efEnergi, it.efSenang);
    cout << "Ramuan " << it.nama << " diminum.\n";
    tampilkanPerubahan(sebelum, p);
}
