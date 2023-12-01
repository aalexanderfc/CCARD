#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "adminMenu.h"
#include "funktioner.h"

void addRemoveCardAccess(CARDLIST *cardList, char *cardID, const char *date, int updateDate) {

        char cardNumber[20];
        while(1){//loop för att få rätt input
        GetInput("Enter card number: ", cardNumber, 10);
        if(convertToInt(cardNumber) == -1){
            printf("Wrong input. Try again!\n");
            sleep(1);
            
        }else{
            break;
            }
        }
        printf("cardID: %s\n", cardNumber);
        int index = getCardIndex(cardList->lista, cardList->count, cardNumber);
        
        if (index == -1) {
            printf("Card not found!\n");
            sleep(1);

            char answer[4];
            while (1) {
                GetInput("Do you want to add this card to the system?:(yes/no)", answer, 4);
                if (strcmp(answer, "yes") == 0) {
                    int accessAnswer;
                        printf("Card added!\n");
                    sleep(1);
                    printf("The recently added card has no access by default!\n");
                    sleep(1);
                    printf("Do you want to give access to this card?\n");
                    sleep(1);
                    GetInputInt("1. for access, 2. for no access, 3. Go back: ", &accessAnswer);

                    if (accessAnswer == 1) {
                        addCardToList(cardList, cardNumber, 1, currentDate(), 1);
                        printf("Access granted!\n");
                        sleep(1);
                        printf("\n");
                } else if (accessAnswer == 2) {
                        addCardToList(cardList, cardNumber, 0, currentDate(), 1);
                        printf("No access!\n");
                        sleep(1);
                        printf("\n");
                        
                } else if (accessAnswer == 3) {
                        break;
                } else {
                    printf("Wrong input. Try again!\n");
                    sleep(1);

                }                 
                    

                } else if (strcmp(answer, "no") == 0) {
                    printf("Card not added!\n");
                    GetInputChar("Press enter to continue", NULL);
                    
                    break;
                    
                } else {
                    printf("Wrong input. Try again!\n");
                    sleep(1);
                }
        }
        } else {
            if (cardList->lista[index].access == 0) {
                printf("This card has no access!\n");
                sleep(1);
                int answer;
                GetInputInt("1. for access, 2. for no access: ", &answer);
                if (answer == 1) {
                    cardList->lista[index].access = 1;
                    printf("Access granted!\n");
                    sleep(1);
                    GetInputChar("Press enter to continue", NULL);
                    printf("\n");                    
                } else if (answer == 2) {
                    cardList->lista[index].access = 0;
                    printf("Access removed!\n");
                    printf("\n");
                    sleep(1);
                } else {
                    printf("Wrong input!\n");
                    sleep(1);
                }
            } else {
                printf("This card has access!\n");
                int answer;
                GetInputInt("1. For access, 2. For no access, 3. Go back: ", &answer);
                if (answer == 1) {
                    cardList->lista[index].access = 1;
                    printf("Access granted!\n");
                    sleep(1);
                    GetInputChar("Press enter to continue", NULL);
                    printf("\n");
                    
                } else if (answer == 2) {
                    cardList->lista[index].access = 0;
                    printf("Access removed!\n");
                    sleep(1);
                    GetInputChar("Press enter to continue", NULL);
                    printf("\n");
                }else if(answer == 3){
                    //back
                }else {
                    printf("Wrong input! Try again!\n");
                    sleep(1);
                    
                }
            }
        }
    }


//funktion för att interagera med adminmenyn:
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

       while (!GetInputInt("Enter choice: ", &sel)) {
            // Handle invalid input, e.g., print an error message
            printf("Invalid input. Please enter a valid integer.\n");
        }

        if (sel == 1) {//Remote open door
            printf("Currently the lamp is: GREEN\n");
            sleep(3);
            printf("Closed door\n");
            sleep(1);
            printf("\n");

            } else if (sel == 2 && cardList->count == 0) {//List all cards in system
            printf("There is not registered cards in system!\n");
            sleep(1);

            } else if (sel == 2 && cardList->count > 0) {
            listCards(cardList);

            } else if (sel == 3) {//add/remove access
            adminAccessMenu(cardList);

            }else if (sel == 4) {//exit
            saveCardListToFile();
            printf("Exiting...\n");
            sleep(1);
            break;
            }else if(sel == 9){

            fakeTestScanCard();

            }else{
                printf("Wrong input. Try again!\n");
                sleep(1);
            
        }
    }    
}

//submeny för admin innehållande add/remove access:
    int adminAccessMenu(CARDLIST *cardList) {
    printf("CURRENTLY LAMP IS: Orange\n");
    printf("\n");
    printf("1. Add/remove access\n");
    printf("2. Back\n");
    printf("\n");

    int menuSel3;

    while (!GetInputInt("Enter choice: ", &menuSel3)) {
        printf("Invalid input. Please enter a valid integer.\n");
    }
    if (menuSel3 == 1) {
        char cardID[20];
        
        addRemoveCardAccess(cardList, cardID, currentDate(), 0);
        } else if (menuSel3 == 2) {
        //back
    } else {
        printf("Wrong input. Try again!\n");
        sleep(1);
        return adminAccessMenu(cardList);     
    }
    return 0;
}