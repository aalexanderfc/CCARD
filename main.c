#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "adminMenu.h"
#include "main.h"
#include "funktioner.h"

#define FILENAME "cards.txt"

CARDLIST cardList;

int main() {
    signal(SIGTERM, cleanupAndExit);//signal för att avsluta programmet
    printf("Current date: %s\n", currentDate());
    
    cardList.lista = NULL;
    cardList.count = 0;
        
    loadCardListFromFile();

    adminMenu(&cardList);

   // Frigör dynamiskt allokerat minne
    free(cardList.lista);

    return 0;
}
