/** @file */
#ifndef CIRCUIT_BUILDER
#define CIRCUIT_BUILDER
#include <string>
#include "structures.h"

/** Funkcja wczytująca układ z podanego pliku
 * @param file plik z obwodem.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 */
void loadCircuitFromFile(std::ifstream &file,gate *&gates,cable *&cables,cableContainer **IO);

/** Funkcja tworząca kable oraz bramki z danej linijki pliku wejściowego
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 * @param data linijka z danymi z pliku wejściowego.
 */
 void createCablesAndGateFromData(gate *&gates,cable *&cables,cableContainer **IO,std::string &data);

/** Funkcja zajmująca sie stworzeniam bramki
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param gateConnectors wszystkie wejścia i wyjścia bramki, w takiej kolejności.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 * @param gateName nazwa bramki lub napis mówiący, że podawane są wejścia lub wyjścia układu.
 */
void createGate(gate *&gates,cableContainer *&gateConnectors,cableContainer **IO,std::string gateName);

/** Funkcja próbująca stworzyć bramkę, zwraca treść błędu w przypadku błędu.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param gateConnectors wszystkie wejścia i wyjścia bramki, w takiej kolejności.
 * @param gateName nazwa bramki lub napis mówiący, że podawane są wejścia lub wyjścia układu.
 * @return zwraca treść błędu jeśli będzie miał miejsce, pusty string w innym przypadku.
 */
std::string tryToCreateGate(gate *&gates,cableContainer *&gateConnectors,std::string &gateName);
#endif
