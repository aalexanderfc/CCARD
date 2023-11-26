#include <stdio.h>
#include <string.h>
#include "safeinput.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    char cardID[20];
    int access;
    char date[20];
}CARD;

typedef struct{
    CARD *lista;
    int count;
}CARDLIST;

void adminAccessMenu(){
    printf("CURRENTLY LAMP IS: Orange\n");
    printf("\n");
    printf("1. Remote open door\n");
    printf("2. List logged in\n");
    printf("3. Add/remove access\n");
    printf("4. Back\n");
    printf("\n");
}

int getCardIndex(CARD *lista, int count, char *cardID){//returnerar indexet på kortet i listan
    for(int i = 0; i < count; i++){
        if(strcmp(lista[i].cardID, cardID) == 0){//om kortet finns i listan
            return i;
        }
    }
    return -1;//om kortet inte finns i listan
}

void adminMenu(CARD *lista, int *pcount){//lista är en pekare till en array av CARD
    int count = *pcount;
    
    while(1){
        printf("Admin Menu:\n");
        printf("\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");
        printf("\n");
        
        int sel;
        
        GetInputInt("Ange val: ", &sel);
       
        if(sel == 1){
            printf("Currently the lamp is: GREEN\n");
            sleep(3);
            printf("Closed door\n");
            printf("\n");

        }else if(sel == 2 && count == 0){
            printf("There is not registered cards in system!\n");
            }else if(sel== 2 && count > 0){
            for(int i = 0; i < count; i++){

                char accessOrNot[20];
                if(lista[i].access == 0){
                    strcpy(accessOrNot, "No access");
                }else{
                    strcpy(accessOrNot, "Access");
                }
                    
                printf("%s %s Added to system %s \n", lista[i].cardID, accessOrNot, lista[i].date);
            }
            GetInputChar("Press enter to continue", NULL);

            
        }else if(sel == 3){
            adminAccessMenu();
            char cardNumber[20];
            GetInput("Enter card number: ", cardNumber, 10);
            printf("cardID: %s\n", cardNumber);
            int index = getCardIndex(lista, count, cardNumber);
            printf("index: %d\n", index);
            if(index == -1){
                printf("Card not found!\n");
                GetInputChar("Press enter to continue", NULL);
                continue;
            }else{
                if(lista[index].access == 0){
                    printf("This card has no access!\n");
                    int answer;
                    GetInputInt("1. for access, 2. for no access: ", &answer);
                    if(answer == 1){
                        lista[index].access = 1;
                        printf("Access granted!\n");
                        printf("\n");
                        }else if(answer == 2){
                            lista[index].access = 0;
                            printf("Access removed!\n");
                            printf("\n");
                        }else{
                            printf("Wrong input!\n");
                        }
                }else{
                    printf("This card has access!\n");
                    int answer;
                    GetInputInt("1. for access, 2. for no access: ", &answer);
                    if(answer == 1){
                        lista[index].access = 1;
                        printf("Access granted!\n");
                        printf("\n");
                        }else if(answer == 2){
                            lista[index].access = 0;
                            printf("Access removed!\n");
                            printf("\n");
                        }else{
                            printf("Wrong input!\n");
                        }
                }
            }

            // if(count == 0){
            //     lista = malloc(sizeof(CARDLIST));
            //     count++;
            // }else{
            //     ++count;
            //     lista = realloc(lista, sizeof(CARDLIST)* (count));
            // }
            

        }else if(sel == 4){
             break;
            }
    }

}

int main(){
    CARD lista[] = {{"23", 0, "2023-11-24"}, {"34", 1, "2023-11-24"}};
    

    int count = 2;

    adminMenu(lista, &count);
    return 0;
}
