#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct {//struct för kort
    char cardID[20];
    int access;
    char registrationDate[20];
} CARD;

typedef struct {//struct för lista av kort
    CARD *lista;
    int count;
} CARDLIST;

const char *currentDate() {//funktion som returnerar dagens datum
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *date = (char *)malloc(sizeof(char) * 20);
    sprintf(date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return date;
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

void fakeTestScanCard(){
    printf("Scan card: ");
    char cardNumber[20];
    GetInput("Enter card number: ", cardNumber, 10);
    printf("cardID: %s\n", cardNumber);
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
//funktion som skriver ut menyn för admin:
// return 1 if success, 0 if wrong entry
int adminAccessMenu(CARDLIST *cardList) {
    printf("CURRENTLY LAMP IS: Orange\n");
    printf("\n");
    printf("1. Add/remove access\n");
    printf("2. Back\n");
    printf("\n");

    int menuSel3;
    GetInputInt("Ange val: ", &menuSel3);

    if (menuSel3 == 1) {
        char cardNumber[20];
        GetInput("Enter card number: ", cardNumber, 10);
        printf("cardID: %s\n", cardNumber);
        int index = getCardIndex(cardList->lista, cardList->count, cardNumber);
        printf("index: %d\n", index);
        if (index == -1) {
            printf("Card not found!\n");

            char answer[4];
            while (1) {
                GetInput("Do you want to add this card to the system?:(yes/no)", answer, 4);
                if (strcmp(answer, "yes") == 0) {
                    int accessAnswer;
                    printf("The recently added card has no access by default!\n");
                    sleep(2);
                    printf("Do you want to give access to this card?\n");
                    GetInputInt("1. for access, 2. for no access, 3. Go back: ", &accessAnswer);

                    if (accessAnswer == 1) {
                        addCardToList(cardList, cardNumber, 1, currentDate(), 1);
                        printf("Access granted!\n");
                        printf("\n");
                    } else if (accessAnswer == 2) {
                        addCardToList(cardList, cardNumber, 0, currentDate(), 1);
                        printf("Access removed!\n");
                        printf("\n");
                    } else if (accessAnswer == 3) {
                        break;
                    } else {
                        printf("Wrong input!\n");
                    }

                    printf("Card added!\n");
                    printf("\n");
                    break;

                } else if (strcmp(answer, "no") == 0) {
                    printf("Card not added!\n");
                    printf("\n");
                    break;
                } else {
                    printf("Wrong input!\n");
                }

                GetInputChar("Press enter to continue", NULL);
            }
        } else {
            if (cardList->lista[index].access == 0) {
                printf("This card has no access!\n");
                int answer;
                GetInputInt("1. for access, 2. for no access: ", &answer);
                if (answer == 1) {
                    cardList->lista[index].access = 1;
                    printf("Access granted!\n");
                    printf("\n");
                } else if (answer == 2) {
                    cardList->lista[index].access = 0;
                    printf("Access removed!\n");
                    printf("\n");
                } else {
                    printf("Wrong input!\n");
                }
            } else {
                printf("This card has access!\n");
                int answer;
                GetInputInt("1. for access, 2. for no access: ", &answer);
                if (answer == 1) {
                    cardList->lista[index].access = 1;
                    printf("Access granted!\n");
                    printf("\n");
                } else if (answer == 2) {
                    cardList->lista[index].access = 0;
                    printf("Access removed!\n");
                    printf("\n");
                } else {
                    printf("Wrong input!\n");
                }
            }
        }
    } else if (menuSel3 == 2) {
        // Do nothing, go back
    } else {
        printf("Wrong input!\n");
    }
    return 1;
}

//funktion som skriver ut menyn för admin och hanterar input:
void adminMenu(CARDLIST *cardList) {
    while (1) {
        printf("Admin Menu:\n");
        printf("\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");
        printf("\n");



        int sel;

        GetInputInt("Ange val: ", &sel);//tar in input från användaren

        if (sel == 1) {//Remote open door
            printf("Currently the lamp is: GREEN\n");
            sleep(3);
            printf("Closed door\n");
            printf("\n");

        } else if (sel == 2 && cardList->count == 0) {//List all cards in system
            printf("There is not registered cards in system!\n");
        } else if (sel == 2 && cardList->count > 0) {
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

        } else if (sel == 3) 
        {//add/remove access
            adminAccessMenu(cardList);
            
        }else if (sel == 4) {//exit
            break;
        }else if(sel == 9){
            printf("Fake card reader");
        }else{
            printf("Wrong input. Try again!\n");
        }
        }
        
    }


int main() {
    printf("Current date: %s\n", currentDate());
    CARDLIST cardList;
    cardList.lista = NULL;
    cardList.count = 0;

    
    addCardToList(&cardList, "1023", 0, "2023-11-24", 1);
    addCardToList(&cardList, "1024", 1, "2023-11-24", 1);

    adminMenu(&cardList);

   // Frigör dynamiskt allokerat minne
    free(cardList.lista);

    return 0;
}
