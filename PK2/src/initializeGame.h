/** @file */
#ifndef INITIALIZE_GAME
#define INITIALIZE_GAME
#include "structures.h"
#include <stdio.h>

/** Funkcja odpowiedzialna za załadowanie koła frotuny i wyboru hasła.
 * @param wheel miejsce gdzie ma trafić pierwszy element wczytanego koła fortuny.
 * @param maxWeight suma wag każdego pola w kole.
 * @param password miejsce gdzie trafi wybrane hasło.
 * @return stan programu do którego należy przejść
 */
gameStates initializeGame(wheelField **wheel,int *maxWeight,char *password);

/** Funkcja czyści koło, jeśli jest ono inne niż NULL.
 * @param wheel pierwszy element koła do wyczyszczenia.
 * @param suma wag każdego pola w kole.
 */
void clearWheel(wheelField **wheel,int *maxWeight);

/** Funkcja pobiera pliki pól koła, czyta je oraz tworzy kolejne pola.
 * @param wheel tworzone koło.
 * @param maxWeight suma wag każdego pola w kole.
 * @return 0 jeśli coś poszło nie tak, 1 jeśli wszystko się udało.
 */
int createWheel(wheelField **wheel,int *maxWeight);

/** Funkcja otwiera plik o podanej nazwie i wstawia nowe pole w kole.
 * @param filename nazwa pliku do przeczytania.
 * @param wheel pierwszy element koła.
 * @param maxWeight suma wag każdego pola w kole.
 * @return 1 jeśli plik został przeczytany, 0 jeśli coś poszło nie tak
 */
int processFile(char *filename,wheelField **wheel,int *maxWeight);

/** Funkcja czyta plik i ustawia wartości podanego pola koła.
 * @param file plik do czytania.
 * @param field pole, którego wartości ustawiamy.
 * @return 0 jeśli coś pójdzie nie tak, 1 jeśli wszystko w  porządku.
 */
int readFile(FILE *file,wheelField *field);

/** Funkcja ustawia pole koła podane w ustawionej linijce pliku.
 * @param name nazwa zmiennej pola do ustawienia.
 * @param field pole, którego wartości ustawiamy.
 * @return 0 jeśli coś pójdzie nie tak, 1 jeśli wszystko w  porządku.
 */
int loadNameAndValue(char *name,wheelField *field);

/** Funkcja rozdziela podaną linię tekstu na nazwę zmiennej i wartość  pola.
 * @param name linia tekstu, modyfikujemy ją, żeby pozostała w tej zmiennej tylko nazwa zmiennej.
 * @param value wartość, którą ma przyjąć zmienna w polu koła.
 */
void getNameAndValue(char *name,int *value);

/** Funkcja ustawia zmienną w polu koła o podanej nazwie na podaną wartość.
 * @param field pole, którego wartości ustawiamy.
 * @param name nazwa zmiennej pola do ustawienia.
 * @param value wartość, którą ma przyjąć zmienna w polu koła.
 * @return 0 jeśli coś pójdzie nie tak, 1 jeśli wszystko w  porządku.
 */
int setWheelField(wheelField *field,char *name,int value);

/** Funkcja ustawia nazwę pola na podstawie jego wartości
 * @param field pole, którego nazwę ustawiamy.
 * @return 0 jeśli coś pójdzie nie tak, 1 jeśli wszystko w  porządku.
 */
int setFieldName(wheelField *field);

/** Funkcja otwiera plik z hasłami i wybiera losowe hasło z tego pliku.
 * @param pass miejsce gdzie trafi wylosowane hasło.
 * @return 0 jeśli coś pójdzie nie tak, 1 jeśli wszystko w  porządku.
 */
int getPassword(char *pass);

/** Funkcja pobiera nazwy plików z hasłami w folderze z hasłami i wybiera losowy z nich.
 * @param filename miejsce gdzie ma trafić nazwa wylosowanego pliku (a właściwie to ścieżka do pliku).
 */
void getPasswordFilename(char *filename);

/** Funkcja czyta wszystkie hasła w podanym pliku
 * @param file plik do czytania.
 * @param passwords miejsce gdzie mają trafić hasła.
 * @return ilość wczytanych haseł.
 */
int readPasswordsFromFile(FILE *file,char **passwords);

/** Funkcja wypisująca wszystkie wczytane pola wczytanego koła
 * @param wheel wskaźnik na pierwszy element listy zawierającej koło.
 */
void printWheel(wheelField *wheel);
#endif
