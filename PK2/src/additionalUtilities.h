/** @file */
#ifndef ADDITIONAL_UTILITIES
#define ADDITIONAL_UTILITIES
#include "structures.h"
#define MAX_FILENAME_LENGTH 255

/** Funkcja pozwalająca pobrać znak z klawiatury bez czekania na enter.
 * @return pobrany znak
 */
char _getch(void);

/** Funkcja czyszcząca ekran
 */
void clearScreen(void);

/** Funkcja pobierająca nazwy plików w folderze danej ścieżki.
 * @param names miejsce gdzie umieścimy znalezione nazwy plików w formie tablicy.
 * @param path ścieżka do folderu w którym mamy znaleźć nazwy plików.
 * @return ilość znalezionych plików.
 */
int getFilesNames(char **names, char *path);

/** Funkcja zatrzymująca program, aby użytkownik mógł przeczytać co zostało wyświetlone.
 */
void _continue(void);

/** Funkcja zamienia litery napisu na małe
 * @param text tekst do zamiany
 */
void makeLowercase(char *text);

/** Funkcja zwalnia wszystkie wszystkie zaalokowane pola z koła fortuny.
 * @param wheel koło do zwolnienia.
 */
void freeWheel(wheelField *wheel);
#endif
