#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "adminMenu.h"
#include "funktioner.h"

#define FILENAME "cards.txt"

CARDLIST cardList;

int main() {
    //signal(SIGTERM, cleanupAndExit);//signal för att avsluta programmet
    printf("Current date: %s\n", currentDate());//skriver ut dagens datum
    
    cardList.lista = NULL;
    cardList.count = 0;
        
    loadCardListFromFile();//laddar in kortlistan från fil

    adminMenu(&cardList);//kör adminmenyn

   // Frigör dynamiskt allokerat minne
    free(cardList.lista);

    return 0;
}
