/** @file */
#ifndef GATE_CREATOR
#define GATE_CREATOR
#include <string>
#include "structures.h"

/** Funkcja tworzy zadaną bramkę, dołącza jej wejścia i wyjście a następnie wstawia do pozostałych bramek.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param gateConnectors wszystkie wejścia i wyjścia bramki, w takiej kolejności.
 * @param data dane z których bramka ma powstać, powinna byc tam jej nazwa i złącza.
 */
void createAndPlaceGate(gate *&gates,cableContainer *&gateConnectors,std::string data);

/** Funkcja tworzy zadaną bramkę, dołącza jej wejścia i wyjście.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param gateConnectors wszystkie wejścia i wyjścia bramki, w takiej kolejności.
 * @param data dane z których bramka ma powstać, powinna byc tam jej nazwa i złącza.
 * @return wskaźnik na bramkę którą ta funkcja stworzyła
 */
gate *createNewGate(gate *&gates,cableContainer *&gateConnectors,std::string &data);

/** Funkcja podłącza odpowiednie kable do wejść i wyjść bramki.
 * @param newGate bramka, której funkcja ma podłączyć wejścia i wyjście.
 * @param gateConnectors wszystkie wejścia i wyjścia bramki, w takiej kolejności.
 */
void addGateConnectors(gate *&newGate,cableContainer *gateConnectors);

/** Funkcja sprawdza czy funkcja ma jedno wejście.
 *
 * Funkcja sprawdza czy jest to drugie wejście oraz czy kolejne złącze istnieje
 * jeśli nie to zwraca wynik funkcji isNeg().
 *
 * @param newGate bramka która jest sprawdzana.
 * @param container potencjalne następne wejście/wyjście.
 * @param i pozwala stwierdzić które wejście/wyjście podłączamy.
 * @return true jeśli i jest równe 1 i nie ma kolejnego złącza oraz bramka jest typu NEG, false w innym przypadku.
 */
bool fasterOutput(gate *&newGate,cableContainer *&container,int &i);

/** Funkcja sprawdza czy bramka jest typu NEG.
 *
 * jeśli jest to ustawia i-te złącze na NULL i zwraca true.
 * w innym przypadku rzuca wyjątek, że bramka musi miec 2 wejścia i jedno wyjście.
 *
 * @param newGate Bramka, która jest sprawdzana.
 * @param i informuje które złącze jest sprawdzane.
 * @return true, jeśli jeśli jest typu NEG, rzuca wyjątek w innym przypadku.
 */
bool isNeg(gate *&newGate,int &i);

/** Funkcja do umieszczania bramki wśród innych bramek.
 *
 * Funkcja iteruje po wszystkich bramkach pokolei,
 * sprawdza czy dana bramka ma na wejściu wyjście bramki dodawanej,
 * jeśli tak to umieszcza ją przed nią,
 * jeśli dotrzemy do końca wszystkich bramek to umieszczamy ją na końcu.
 *
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param newGate bramka do umieszczenia.
 */
void placeGate(gate *&gates,gate *&newGate);

/** Funkcja wstawiająca i zwracająca informację czy bramka została dodana do układu.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param previousGate bramka poprzednia do bramki workingGate.
 * @param newGate bramka, którą chcemy wstawić do układu.
 * @param workingGate bramka, którą sprawdzamy.
 * @return true, jeśli bramka została dołączona do układu, false w innym przypadku
 */
bool addedGate(gate *&gates,gate *&previousGate,gate *&newGate,gate *&workingGate);

/** Funkcja dołączająca bramkę do układu
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param previousGate bramka która ma być przed newGate.
 * @param newGate bramka którą chcemy wstawić do układu.
 * @param workingGate bramka, która ma być po newGate.
 */
void insertGate(gate *&gates,gate *&previousGate,gate *&newGate,gate *&workingGate);

/** Funkcja do przejścia na kolejną bramkę do sprawdzania
 * @param previousGate bramka poprzednia do workingGate.
 * @param workingGate bramka na której pracujemy.
 * @param added pozwala zdecydować czy bramki powinny iść dalej.
 */
void updateGates(gate *&previousGate,gate *&workingGate,bool &added);
#endif
