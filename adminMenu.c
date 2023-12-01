#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "adminMenu.h"
#include "funktioner.h"

void adminMenu(CARDLIST *cardList) {//funktion för att interagera med adminmenyn
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

        GetInputInt("Enter choice: ", &sel);//tar in input från användaren

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

    int adminAccessMenu(CARDLIST *cardList) {//submeny för admin innehållande add/remove access
    printf("CURRENTLY LAMP IS: Orange\n");
    printf("\n");
    printf("1. Add/remove access\n");
    printf("2. Back\n");
    printf("\n");

    int menuSel3;
    GetInputInt("Enter choice: ", &menuSel3);

    if (menuSel3 == 1) {
        addRemoveCardAccess(cardList, cardList->lista->cardID, cardList->lista->access, cardList->lista->registrationDate, 0);
      
    } else if (menuSel3 == 2) {
        //back
    } else {
        printf("Wrong input. Try again!\n");
        sleep(1);
        return adminAccessMenu(cardList);     
    }
    return 0;
}