/** @file */
#ifndef CABLE_CONTAINER_MANAGER
#define CABLE_CONTAINER_MANAGER
#include "structures.h"

/** Funkcja dodaje kabel do zbiornika kabli.
 * @param containers wskaźnik na pierwszy element zbiornika.
 * @param cableToAdd kabel do dodania do zbiornika.
 */
void addCableContainer(cableContainer *&containers,cable *&cableToAdd);

/** Funkcja sprawdzająca czy można dodać kabel do zbiornika.
 *
 * Funkcja sprawdza czy containers nie istnieje lub nie istnieje working->next,
 * jeśli tak się stanie to tworzy nowy cableContainer i przypisuje go do containers lub working->next.
 *
 * @param containers wskaźnik na pierwszy element zbiornika.
 * @param working zbiornik sprawdzany.
 * @param cableToAdd kabel do dodania do zbiornika.
 */
bool addedContainer(cableContainer *&containers,cableContainer *&working,cable *&cableToAdd);

/** Funkcja tworzy nowy cableContainer i podpina do niego kabel.
 * @param cableToAdd kabel powiązany z tworzonym cableContainer.
 * @return wskaźnik na nowoutworzony cableContainer.
 */
cableContainer *createNewCableContainer(cable *&cableToAdd);

/** Funkcja usuwająca wszystkie elementy zbiornika.
 * @param container zbiornik który trzeba usunąć.
 */
void removeCableContainers(cableContainer *&container);
#endif
