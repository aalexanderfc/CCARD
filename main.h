#include "adminMenu.h"



int getCardIndex(CARD *lista, int count, char *cardID);
void addCardToList(CARDLIST *cardList, char *cardID, int access, const char *date, int updateDate);
const char *currentDate();
void saveCardListToFile();
void processCard(char* cardNumber);