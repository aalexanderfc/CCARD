#include "adminMenu.h"
#include "main.h"

int getCardIndex(CARD *lista, int count, char *cardID);
void addCardToList(CARDLIST *cardList, char *cardID, int access, const char *date, int updateDate);
const char *currentDate();
void saveCardListToFile();
void processCard(char* cardNumber);
int convertToInt(const char *str);
void adminMenu(CARDLIST *cardList);
int adminAccessMenu(CARDLIST *cardList);
void listCards(CARDLIST *cardList);
void addRemoveCardAccess(CARDLIST *cardList, char *cardID, int access, const char *date, int updateDate);
int convertToInt(const char *str);
void fakeCard(CARDLIST *cardList);
void listCards(CARDLIST *cardList);
void fakeTestScanCard();
void cleanupAndExit(int signum);
void loadCardListFromFile();