/** @file */
#ifndef MAIN_MENU
#define MAIN_MENU
#include "structures.h"
#define MENU_OPTIONS 2

/** Funkcja zajmująca się obsługą menu głównego.
 * Wypisuje menu, pobiera decyzję gracza, decyduje co z tą decyzją zrobić i zwraca opdowiednią wartość lub kontynuuje pętlę.
 *
 * @return Zwracany jest stan programu do którego należy przejść.
 */
gameStates mainMenu(void);

/** Funkcja wypisuje menu główne oraz instrukcję jego obsługi.
 * @param selectedOption jest to indeks aktualnie wybranej opcji menu głównego.
 * @param options opcje do wyboru w menu głównym.
 */
void printMenu(int selectedOption,char *options[MENU_OPTIONS]);

/** Funkcja przestawiająca wybraną opcję menu głównego.
 * @param pressed naciśnięty przez użytkownika przycisk.
 * @param selectedOption jest to indeks aktualnie wybranej opcji menu głównego.
 * @return Zwraca na jest informacja, czy coś zostało przestawione (1), czy nie (0).
 */
int changeSelected(char pressed,int *selectedOption);

/** Funkcja decydująca jaki stan programu powinno zwrócić menu główne.
 * @param selectedOption opcja zaznaczona w momencie naciśnięcia entera.
 * @return stan programu do którego należy przejść.
 */
gameStates exitMenu(int selectedOption);
#endif
