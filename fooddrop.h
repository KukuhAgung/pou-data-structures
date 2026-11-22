

#ifndef FOODDROP_H_INCLUDED
#define FOODDROP_H_INCLUDED

#include "pou.h"
#include "minigame.h"


const int FD_JALUR = 3;          
const int FD_BARIS_TERLIHAT = 5; 
const int FD_MAKS_BARIS = 30;    
const int FD_NYAWA_AWAL = 3;
const int FD_SKOR_MAKANAN = 10;
const int FD_EFEK_ENERGI = -15; 
const int FD_EFEK_SENANG = 20;


struct Baris {
    char jalur[3];    
};

typedef struct elmBaris *adrBaris;

struct elmBaris {
    Baris info;
    adrBaris next;
};

struct QueueBaris {
    adrBaris head;    
    adrBaris tail;    
};


void createQueue(QueueBaris &Q);
bool isEmptyQueue(QueueBaris Q);
adrBaris alokasiBaris(Baris b);
void enqueue(QueueBaris &Q, adrBaris P);
void dequeue(QueueBaris &Q, adrBaris &P);
void printQueue(adrBaris P);
Baris generateBaris();
void geserPou(int &posisi, char arah);
void cekTangkapan(Baris b, int posisi, int &skor, int &nyawa);
void mainFoodDrop(Pou &p, ListMinigame &L);


#endif
