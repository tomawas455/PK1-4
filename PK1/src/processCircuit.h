/** @file */
#ifndef PROCESS_CIRCUIT
#define PROCESS_CIRCUIT
#include "structures.h"

/** Funkcja zarządzająca tworzeniem i liczeniem obwodu.
 * @param circuitFilename nazwa pliku z układem.
 * @param statusFilename nazwa pliku ze stanami wejść.
 * @param outputFilename nazwa pliku do którego mają być przekazane stany wyjść.
 */
void processCircuit(std::string &circuitFilename,std::string &statusFilename,std::string &outputFilename);

/** Funkcja otwierająca pliki z układem i stanami wejść.
 * @param files tablica zawierająca strumienie plików z układem i ze stanami wejść.
 * @param circuitFilename nazwa pliku z układem.
 * @param statusFilename nazwa pliku ze stanami wejść.
 */
void getFiles(std::ifstream *files,std::string &circuitFilename,std::string &statusFilename);

/** Funkcja sprawdzająca czy pliki są otwarte (istnieją).
 * @param files tablica zawierająca strumienie plików z układem i ze stanami wejść.
 * @return true jeśli oba pliki są w porządku, false w innym przypadku.
 */
bool filesOk(std::ifstream *files);

/** Funkcja próbująca załadować i policzyć obwód, wypisze błąd, jeśli coś będzie nie tak.
 * @param files tablica zawierająca strumienie plików z układem i ze stanami wejść.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 * @param outputFilename plik z outputFilename nazwa pliku do którego mają być przekazane stany wyjść.
 */
void tryProcessingCircuit(std::ifstream *files,gate *&gates,cable *&cables,cableContainer **IO,std::string &outputFilename);

/** Funkcja zamykająca pliki z układem i ze stanami wejść.
 * @param files tablica zawierająca strumienie plików z układem i ze stanami wejść.
 */
void closeFiles(std::ifstream *files);

/** Funkcja usuwa wszystkie elementy układu w celu bezpiecznego zakończenia programu.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 */
void deleteElements(gate *&gates,cable *&cables,cableContainer **IO);

/** Funkcja usuwa bramki obecne w układzie.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 */
void deleteGates(gate *&gates);

/** Funkcja usuwa kable obecne w układzie.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 */
void deleteCables(cable *&cables);
#endif
