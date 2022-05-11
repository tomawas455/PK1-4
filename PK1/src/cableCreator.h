/** @file */
#ifndef CABLE_CREATOR
#define CABLE_CREATOR
#include <string>
#include "structures.h"

/** Funkcja zajmująca się tworzeniem kabli i dodawaniem ich do zbioru złącz potencjalnej bramki.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param gateConnectors miejsce na złącza bramki.
 * @param data dane z których funkcja ma stworzyć okablowanie.
 */
void createCables(cable *&cables,cableContainer *&gateConnectors,std::string data);

/** Funkcja pozyskuje numer kabla z otrzymanych danych.
 * @param data dane z których funkcja ma pozyskać numer kabla.
 * @param space indeks pierwszej spacji w danych.
 * @return numer znalezionego kabla.
 */
int getCableNumber(std::string &data,int &numberBegin);

/** Funkcja dodająca kabel do zbioru już istniejących kabli.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param gateConnectors miejsce na złącza bramki.
 * @param cableNumber numer tworzonego kabla
 */
void addCable(cable *&cables,cableContainer *&gateConnectors,int &cableNumber);

/** Funkcja sprawdzająca i dodająca kabel do zioru wszystkich kabli
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param previousCable kabel potencjalnie poprzedni w stosunku do nowego.
 * @param workingCable kabel obecnie sprawdzany.
 * @param gateConnectors miejsce na złącza bramki.
 * @param cableNumber numer tworzonego kabla.
 * @return true, jeśli kabel został dodany.
 */
bool addedCable(cable *&cables,cable *&previousCable,cable *&workingCable,cableContainer *&gateConnectors,int &cableNumber);

/** Funkcja umieszczająca nowy kabel w zbiorze kabli, jeśli jest to konieczne.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param previousCable kabel potencjalnie poprzedni w stosunku do nowego.
 * @param newCable kabel do umieszczenia w zbiorze.
 * @param gateConnectors miejsce na złącza bramki.
 * @param cableNumber numer tworzonego kabla.
 */
void placeCable(cable *&cables,cable *&previousCable,cable *&newCable,cableContainer *&gateConnectors,int &cableNumber);

/** Funkcja sprawdzająca czy nowy kabel istnieje i jest umieszczony w zbiorze.
 *
 * Funkcja sprawdza czy funkcja placeCable() otrzymała newCable czy jest on równy NULL,
 * w przypadku gdy jest on równy NULL to ta funkcja tworzy nowy kabel.
 *
 * @param newCable kabel do umieszczenia w zbiorze.
 * @param cableNumber numer nowego kabla.
 * @return false, jeśli newCable jest NULLem.
 */
bool cableIsPlaced(cable *&newCable,int &cableNumber);

/** Funkcja tworząca bramkę o podanym numerze.
 * @param cableNumber numer tworzonej bramki.
 * @return wskaźnik na nowoutworzony kabel.
 */
cable *createNewCable(int &cableNumber);

/** Umieszcza nowy kabel w zbiorze wszystkich kabli.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param previousCable kabel potencjalnie poprzedni w stosunku do nowego.
 * @param newCable kabel do umieszczenia w zbiorze.
 */
void insertNewCable(cable *&cables,cable *&previousCable,cable *&newCable);

/** Funkcja przesuwa previousCable i workingCable na następny kabel
 * @param previousCable kabel potencjalnie poprzedni w stosunku do nowego.
 * @param workingCable kabel, który przed chwilą był sprawdzany.
 */
void updateCables(cable *&previousCable,cable *&workingCable,bool &added);
#endif
