#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "adminMenu.h"
#include "funktioner.h"

#define FILENAME "cards.txt"

CARDLIST cardList;
//funktion som returnerar dagens datum:
const char *currentDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *date = (char *)malloc(sizeof(char) * 20);
    sprintf(date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return date;
}

//funktion som sparar kortlistan till fil:
void saveCardListToFile() {
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

//funktion som läser in kortlistan från fil:
void loadCardListFromFile() {
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

//funktion som avslutar programmet:
void cleanupAndExit(int signum) {
    saveCardListToFile();
    free(cardList.lista);
    exit(0);
}

//funktion som lägger till ett kort i listan:
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

//funktion som konverterar en sträng till int:
int convertToInt(const char *str){
    int result = atoi(str);
    
    char intStr[strlen(str)+1];
    sprintf(intStr, "%d", result);
    if(strcmp(str, " ") == 0){
        return -1;
    }
  
    if(strlen(intStr) == strlen(str)){
        return result;
    }
    else {
        return -1;
        }
    }

//funktion för att lägga till eller ta bort access till ett kort:

//funktion som skriver ut alla kort i listan:
void listCards(CARDLIST *cardList){

            for (int i = 0; i < cardList->count; i++) {
                char accessOrNot[20];
                if (cardList->lista[i].access == 0) {
                    strcpy(accessOrNot, "No access");
                } else {
                    strcpy(accessOrNot, "Access");
                }
                printf("%s %s Added to system %s \n", cardList->lista[i].cardID, accessOrNot, cardList->lista[i].registrationDate);
                }
                 GetInputChar("Press enter to continue", NULL);
}

//funktion för att testa att scanna ett kort och se om det finns i listan:
void fakeTestScanCard(){
    char scanCard[10];
    GetInput("CURRENTLY LAMP IS: Off\nPlease scan card to enter or X to go back to admin menu:\n", scanCard, 10);
    if(strcmp(scanCard, "x") == 0){
        //back
    }else if(convertToInt(scanCard) == -1){
        printf("Wrong input. Try again!\n");
        sleep(1);
        fakeTestScanCard();
    }else{
        processCard(scanCard);
    }
}