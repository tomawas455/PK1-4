/** @file */
#ifndef STRUCTURES
#define STRUCTURES
#include <stdlib.h>

/** Stany programu.
 */
typedef enum gameStates{MENU_STATE,INITIALIZE_GAME_STATE,GAME_STATE,EXIT_STATE}gameStates;

/** Pola koła fortuny.
 * @param value wartość pola w $ lub w przypadku wartości ujemnych typ specjalnego pola.
 * @param name nazwa pola wyświetlana graczowi, w przypadku wartości pieniężnych jest to ta wartość ze znakiem $, w innym nazwa specjalnego pola.
 * @param weight waga pola, w przypadku fizycznego, okrągłego pola byłaby to poprostu szerokość danego pola w stosunku do pozostałych.
 * @param next z racji, że jest to lista jednokierunkowa to mamy wskaźnik na następny element.
 */
typedef struct wheelField
{
    int value;
    char name[100];
    size_t weight;
    struct wheelField *next;
}wheelField;

/** Stany akcji w trakcie rozgrywki.
 * W trakcie rozgrywki gracz/bot wykonuje jakąś operację i ten enum pozwala stwierdzić w jakim stanie się znajduje.
 */
typedef enum actionStates{SPIN,DECIDE,VOWEL,SOLVE,EXIT} actionStates;
#endif
