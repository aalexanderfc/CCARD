#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "adminMenu.h"
#include "main.h"

#define FILENAME "cards.txt"

CARDLIST cardList;

const char *currentDate() {//funktion som returnerar dagens datum
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *date = (char *)malloc(sizeof(char) * 20);
    sprintf(date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return date;
}

void saveCardListToFile() {//funktion som sparar kortlistan till fil
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < cardList.count; i++) {
        fprintf(file, "%s %d %s\n", cardList.lista[i].cardID, cardList.lista[i].access, cardList.lista[i].registrationDate);
    }

    fclose(file);
}

void loadCardListFromFile() {//funktion som läser in kortlistan från fil
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        while (!feof(file)) {
            char cardID[20];
            int access;
            char date[20];

            if (fscanf(file, "%s %d %s", cardID, &access, date) == 3) {
                addCardToList(&cardList, cardID, access, date, 0);
            }
        }

        fclose(file);
    }

}

void cleanupAndExit(int signum) {//funktion som avslutar programmet
    saveCardListToFile();
    free(cardList.lista);
    exit(0);
}

//funktion som lägger till ett kort i listan
void addCardToList(CARDLIST *cardList, char *cardID, int access, const char *date, int updateDate) {
    int count = cardList->count;

    cardList->lista = realloc(cardList->lista, sizeof(CARD) * (count + 1));

    strcpy(cardList->lista[count].cardID, cardID);
    cardList->lista[count].access = access;

    if(updateDate){//if updateDate is true
    const char *currentDateStr = currentDate();
        strcpy(cardList->lista[count].registrationDate, currentDateStr);
        free((void *)currentDateStr);
    }else{
        strcpy(cardList->lista[count].registrationDate, date);
    }
    cardList->count++;
}

//funktion som returnerar indexet för ett kort i listan:
int getCardIndex(CARD *lista, int count, char *cardID) {
    for (int i = 0; i < count; i++) {
        if (strcmp(lista[i].cardID, cardID) == 0) {
            return i;
        }
    }
    return -1;
}

void processCard(char* cardNumber){//funktion som hanterar scanning av kort
    int index = getCardIndex(cardList.lista, cardList.count, cardNumber);
    if(index == -1){
        printf("CURRENTLY LAMP IS: Red\n");
        sleep(1);
        printf("\n");
    }else{
        if(cardList.lista[index].access == 0){
            printf("CURRENTLY LAMP IS: Red\n");
            sleep(1);
            printf("\n");
        }else{
            printf("CURRENTLY LAMP IS: Green\n");
            sleep(1);
            printf("\n");
        }
   
    }
}

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
