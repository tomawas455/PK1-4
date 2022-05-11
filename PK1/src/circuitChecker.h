/** @file */
#ifndef CIRCUIT_CHECKER
#define CIRCUIT_CHECKER
#include "structures.h"

/** Funkcja sprawdza czy układ jest stworzony poprawnie.
 *
 * Chodzi np. o to żeby nie łączyć wyjść dwóch (lub więcej) bramek.
 *
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 */
void checkCircuit(gate *&gates,cableContainer **IO);

/** Funkcja sprawdza poprawność wyjścia bramki
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param workingGate bramka której wyjście trzeba sprawdzić
 * @param ins wejścia do układu
 */
void checkGateOut(gate *&gates,gate *&workingGate,cableContainer *ins);

/** Fnkcja sprawdza czy wyjście bramki nie jest przypadkiem wejściem do układu.
 * @param workingGate sprawdzana bramka.
 * @param ins wejścia do układu.
 */
void checkGateWithCircuitIns(gate *&workingGate,cableContainer *ins);

/** Funkcja sprawdza czy wyjście bramki nie jest przypadkiem takie samo jak wyjście jakiejkolwiek innej bramki.
 * @param gates bramki których wyjścia trzeba sprawdzić, najlepiej żeby były to bramki na liście po obecjen, bo poprzednie i tak już są sprawdzone.
 * @param workingGate sprawdzana bramka.
 */
void checkOtherGatesOuts(gate *gates,gate *&workingGate);
#endif
