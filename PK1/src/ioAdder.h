/** @file */
#ifndef IO_ADDER
#define IO_ADDER
#include "structures.h"

/** Funkcja Dodająca wejścia i wyjścia układu.
 * @param connectors wskaźnik na pierwsze wejście lub wyjście układu.
 * @param connectorsToAdd złącza do dodania.
 */
void addIO(cableContainer *&connectors,cableContainer *&connectorsToAdd);

/** Funkcja Sprawdza czy nie ma dodanych jeszcze żadnych złącz i dodaje je jeśli tak.
 * @param connectors wskaźnik na pierwsze wejście lub wyjście układu.
 * @param connectorsToAdd złącza do dodania.
 * @return true jeśli connectors jest puste, false w innym przypadku.
 */
bool emptyConnectors(cableContainer *&connectors,cableContainer *&connectorsToAdd);

/** Funkcja Dodaje wejście lub wyjście do listy wejść/wyjść.
 * @param connectors wskaźnik na pierwsze wejście lub wyjście układu.
 * @param connectorToAdd złącze do dodania.
 */
void addConnector(cableContainer *&connectors,cableContainer *&connectorToAdd);

/** Funkcja Dodaje wejście/wyjście na koniec lub usuwa je jeśli wejście/wyjście o takim numerze już istnieje.
 * @param previous poprzednio sprawdzane złącze.
 * @param working obecnie sprawdzane złącze.
 * @param connectorToAdd złącze do dodania.
 * @return true jeśli złącze zostało dodane/usunięte, false w innym przypadku.
 */
bool addedIO(cableContainer *&previous,cableContainer *&working, cableContainer *&connectorToAdd);

/** Funkcja Dodaje nowe złącze układu i przesuwa connectorToAdd dalej.
 * @param previous poprzednio sprawdzane złącze.
 * @param connectorToAdd złącze do dodania.
 */
void addNewConnector(cableContainer *&previous,cableContainer *&connectorToAdd);

/** Funkcja przesuwa podane złącze dalej i usuwa je.
 * @param previous poprzednio sprawdzane złącze.
 * @param connector złącze do usunięcia.
 */
void updateAndDeleteConnector(cableContainer *&connector);

/** Funkcja przesuwa previous i working dalej jeśli added jest false.
 * @param noUpdate jeśli true to funkcja nic nie robi.
 * @param previous poprzednio sprawdzane złącze.
 * @param working obecnie sprawdzane złącze.
 */
void updateContainers(bool &noUpdate,cableContainer *&previous,cableContainer *&working);
#endif
