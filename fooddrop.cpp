

#include "fooddrop.h"
#include <cstdlib>   
#include <ctime>     



static void cetakBarisArena(Baris b) {
    cout << " |";
    for (int i = 0; i < FD_JALUR; i++) {
        cout << " " << b.jalur[i] << " |";
    }
    cout << endl;
}

static void tampilkanArena(QueueBaris Q, int posisi, int skor, int nyawa, int baris) {
    cout << endl;
    cout << "=== FOOD DROP | Skor " << skor
         << " | Nyawa " << nyawa << "/" << FD_NYAWA_AWAL
         << " | Baris " << baris << "/" << FD_MAKS_BARIS << " ===" << endl;

    printQueue(Q.head);

    Baris barisPou;
    for (int i = 0; i < FD_JALUR; i++) {
        barisPou.jalur[i] = '.';
    }
    barisPou.jalur[posisi] = 'P';
    cetakBarisArena(barisPou);

    cout << "a=kiri  d=kanan  s=diam  q=berhenti" << endl;
}



void createQueue(QueueBaris &Q) {
    Q.head = Nil;
    Q.tail = Nil;
}

bool isEmptyQueue(QueueBaris Q) {
    return Q.head == Nil;
}

adrBaris alokasiBaris(Baris b) {
    adrBaris P = new elmBaris;
    P->info = b;
    P->next = Nil;
    return P;
}

void enqueue(QueueBaris &Q, adrBaris P) {
    P->next = Nil;
    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

void dequeue(QueueBaris &Q, adrBaris &P) {
    if (isEmptyQueue(Q)) {
        P = Nil;
    } else {
        P = Q.head;
        Q.head = P->next;
        if (Q.head == Nil) {
            Q.tail = Nil;
        }
        P->next = Nil;
    }
}

void printQueue(adrBaris P) {
    if (P != Nil) {
        printQueue(P->next);
        cetakBarisArena(P->info);
    }
}


Baris generateBaris() {
    Baris b;
    for (int i = 0; i < FD_JALUR; i++) {
        b.jalur[i] = '.';
    }


    int jumlahBenda = rand() % 3;   
    int terisi = 0;
    while (terisi < jumlahBenda) {
        int j = rand() % FD_JALUR;
        if (b.jalur[j] == '.') {
            if (rand() % 2 == 0) {
                b.jalur[j] = 'M';
            } else {
                b.jalur[j] = 'X';
            }
            terisi++;
        }
    }
    return b;
}

void geserPou(int &posisi, char arah) {
    if (arah == 'a') {
        if (posisi > 0) {
            posisi--;
        } else {
            cout << "Pou sudah di jalur paling kiri." << endl;
        }
    } else if (arah == 'd') {
        if (posisi < FD_JALUR - 1) {
            posisi++;
        } else {
            cout << "Pou sudah di jalur paling kanan." << endl;
        }
    }
    
}

void cekTangkapan(Baris b, int posisi, int &skor, int &nyawa) {
    char isi = b.jalur[posisi];
    if (isi == 'M') {
        skor += FD_SKOR_MAKANAN;
        cout << "Nyam! Pou menangkap makanan (+" << FD_SKOR_MAKANAN << " skor)." << endl;
    } else if (isi == 'X') {
        nyawa--;
        cout << "Aduh! Pou terkena sampah (nyawa -1)." << endl;
    }
}

void mainFoodDrop(Pou &p, ListMinigame &L) {
    if (!bisaMainMinigame(p)) {
        cout << "Pou terlalu lelah/sakit untuk bermain." << endl;
        return;    
    }

    srand(time(NULL));

    
    QueueBaris Q;
    createQueue(Q);
    for (int i = 0; i < FD_BARIS_TERLIHAT; i++) {
        enqueue(Q, alokasiBaris(generateBaris()));
    }

    int posisi = FD_JALUR / 2;    
    int skor = 0;
    int nyawa = FD_NYAWA_AWAL;
    int baris = 0;                
    bool berhenti = false;

    while (nyawa > 0 && baris < FD_MAKS_BARIS && !berhenti) {
        tampilkanArena(Q, posisi, skor, nyawa, baris);
        cout << "Perintah: ";

        string perintah;
        if (!(cin >> perintah)) {
            berhenti = true;      
        } else {
            char c = ' ';
            if (perintah.length() == 1) {
                c = perintah[0];
                if (c >= 'A' && c <= 'Z') {
                    c = c - 'A' + 'a';
                }
            }

            if (c == 'q') {
                berhenti = true;
            } else if (c == 'a' || c == 'd' || c == 's') {
                geserPou(posisi, c);

      
                adrBaris P;
                dequeue(Q, P);
                cekTangkapan(P->info, posisi, skor, nyawa);
                delete P;
                baris++;

               
                enqueue(Q, alokasiBaris(generateBaris()));
            } else {
                cout << "Perintah tidak valid. Gunakan a, d, s, atau q." << endl;
            }
        }
    }

  
    adrBaris P;
    while (!isEmptyQueue(Q)) {
        dequeue(Q, P);
        delete P;
    }

    
    int koin, xp;
    hitungHadiah(skor, koin, xp);

    cout << endl << "=== HASIL FOOD DROP ===" << endl;
    if (nyawa <= 0) {
        cout << "Nyawa habis!" << endl;
    } else if (baris >= FD_MAKS_BARIS) {
        cout << "Semua " << FD_MAKS_BARIS << " baris selesai!" << endl;
    } else {
        cout << "Permainan dihentikan." << endl;
    }
    cout << "Skor : " << skor << endl;
    cout << "Koin : +" << koin << endl;
    cout << "XP   : +" << xp << endl;

    Skor s;
    s.nilai = skor;
    s.koinDidapat = koin;
    s.giliranMain = p.giliran;

    tambahKoin(p, koin);
    tambahXP(p, xp);
    catatSkor(L, "FD", s);

   
    ubahStatus(p, 0, 0, FD_EFEK_ENERGI, FD_EFEK_SENANG);
    majukanWaktu(p);
}
