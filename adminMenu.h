#include <stdio.h>

#pragma once//för att inte inkludera filen flera gånger

typedef struct {//struct för kort
    char cardID[20];
    int access;
    char registrationDate[20];
}CARD;

typedef struct {//struct för lista av kort
    CARD *lista;
    int count;
}CARDLIST;

int convertToInt(const char *str);
void adminMenu(CARDLIST *cardList);
int adminAccessMenu(CARDLIST *cardList);