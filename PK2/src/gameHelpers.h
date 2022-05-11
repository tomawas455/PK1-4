/** @file */
#ifndef GAME_HELPERS
#define GAME_HELPERS
#define CONTESTANTS_NAME_MAX 5
#define CONTESTANTS_AMOUNT 3

/** Funkcja zamienia każdą literę hasła na "_" z wyjątkiem spacji.
 * @param password hasło do ukrycia.
 * @return ukryte hasło.
 */
char* hidePassword(char *password);

/** Funkcja wypisuje nazwy zawodników, stany ich kont oraz kto będzie kręcił kołem.
 * @param accounts tablica z kontami zawodników.
 * @param players nazwy zawodników.
 * @param turn indeks zawodnika który będzie kręcił kołem.
 */
void printContestants(int *accounts,char (*players)[CONTESTANTS_NAME_MAX],int turn);

/** Funkcja zliczająca ile jest znaczących znaków w podanym napisie.
 * @param text tekst w którym sprawdzamy ile jest niepustych znaków.
 * @param empty znak, który funkcja ma uznać za pusty.
 * @return ilość znalezionych niepustych znaków.
 */
int getTextLettersAmount(char *text,char empty);

/** Funkcja sprawdzająca jaka litera znajduje się na podanej pozycji.
 * Funkcja udaje, że pola zawierające " " nie istnieją i je pomija w obliczeniach.
 * @param text tekst do sprawdzenia.
 * @param position pozycja na której leży litera nas interesująca.
 * @return litera na podanej pozycji lub "\0" jeśli coś pójdzie nie tak jak powinno.
 */
char getLetterOnPosition(char *text,int position);

/** Funkcja wypisuje nieużyte litery alfabetu tj. pomija spacje.
 * @param alphabet zbiór spółgłosek lub samogłosek.
 */
void printNotUsedLetters(char *alphabet);

/** Funkcja sprawdza ile razy podana litera znajduje się w haśle.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param guess litera do sprawdzenia.
 * @return ile razy litera pojawiła się w haśle.
 */
int checkAgainstPassword(char *hiddenPassword,char *password,char guess);

/** Funkcja pobierająca od gracza decyzję o chęci zgadywania spółgłoski.
 * @return "y" jeśli gracz się zgodzi, "\0" jeśli nie.
 */
char getVowelDecision(void);

/** Funkcja pokazuje ekran końca rozgrywki.
 * @param accounts tablica z kontami zawodników.
 * @param names nazwy zawodników.
 * @param password hasło które zawodnicy mieli odgadnąć.
 * @param lettersLeft zmienna informująca czy na zakończenie rozgrywki wciąż były możliwe do wyboru spółgłoski
 */
void printWinners(int *accounts,char (*names)[CONTESTANTS_NAME_MAX],char *password,int lettersLeft);
#endif
