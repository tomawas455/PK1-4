/** @file */
#ifndef PLAY_GAME
#define PLAY_GAME
#include "structures.h"
#define BOT_GUESS_CHANCE 4///<użyte jako 1/BOT_GUESS_CHANCE
#define CONSONANTS 20 ///<19+'\0'

/** Funkcja zarządzająca rozgrywką. Wypisuje stan kont, pozwala wykonać akcję oraz kończy rozgrywkę kiedy trzeba.
 * @param wheel wczytane koło fortuny do użycia w rozgrywce.
 * @param maxWeight suma wag każdego pola w kole.
 * @param password wylosowane hasło do odgadnięcia.
 */
void playGame(wheelField *wheel,int maxWeight,char *password);

/** Funkcja decydująca jaką akcję dany zawodnik w danym momencie ma wykonać.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param account konto zawodnika o którego losie decydujemy.
 * @param wheel koło fortuny
 * @param maxWeight suma wag każdego pola w kole.
 * @param alphabet alfabet podzielony na samogłoski i spółgłoski
 * @param whom nazwa zawodnika o którego losie decydujemy.
 * @param isBot zmienna mówiąca, czy dany zawodnik jest botem, czy graczem.
 */
void action(char *hiddenPassword,char *password,int *account,wheelField *wheel,int maxWeight,char (*alphabet)[CONSONANTS],char *whom,int isBot);

/** Funkcja losująca na pole na którym koło się zatrzyma.
 * @param wheel koło fortuny.
 * @param weight suma wag każdego pola w kole.
 * @return wylosowane pole.
 */
wheelField* spinWheel(wheelField *wheel,int weight);

/** Funkcja decydująca co zrobić z wylosowanym polem na któreym koło się zatrzymało.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param account konto zawodnika o którego losie decydujemy.
 * @param field wylosowane pole koła.
 * @param whom nazwa zawodnika o którego losie decydujemy.
 * @param alphabet zbiór możliwych do zgadnięcia spółgłosek.
 * @param isBot zmienna mówiąca, czy dany zawodnik jest botem, czy graczem.
 * @return stan do którego akcja w grze powinna przejść.
 */
actionStates actionDecision(char *hiddenPassword,char *password,int *account,wheelField *field,char *whom,char *alphabet,int isBot);

/** Funkcja będąca efektem zatrzymania się na polu bankruta
 * @param account konto zawodnika które trzeba wyzerować.
 * @param whom nazwa zawodnika, który zbankrutował.
 */
void bankrupt(int *account,char *whom);

/** Funkcja będąca efektem zatrzymania się na polu stop.
 * @param whom nazwa zawodnika, którego kolejka jest pomijana.
 */
void stop(char *whom);

/** Funkcja pozwalająca zawodnikowi zgadywać spółgłoskę.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param account konto zawodnika o którego losie decydujemy.
 * @param field wylosowane pole koła.
 * @param whom nazwa zawodnika, który zgaduje.
 * @param alphabet zbiór możliwych do zgadnięcia spółgłosek.
 * @param isBot zmienna mówiąca, czy dany zawodnik jest botem, czy graczem.
 * @return stan do którego akcja w grze powinna przejść.
 */
actionStates guess(char *hiddenPassword,char *password,int *account,wheelField *field,char *whom,char *alphabet,int isBot);

/** Funkcja sprawdzająca ile razy zawodnik trafił literę i dodająca mu odpowiednią ilość pieniędzy.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param hitValue wartość jednej trafionej litery.
 * @param account konto zawodnika o którego losie decydujemy.
 * @param alphabet zbiór możliwych do zgadnięcia spółgłosek.
 * @param whom nazwa zawodnika, który zgaduje.
 * @param isBot zmienna mówiąca, czy dany zawodnik jest botem, czy graczem.
 * @return ile razy zawodnik trafił literę.
 */
int makeGuess(char *hiddenPassword,char *password,int hitValue,int *account,char *alphabet,char *whom,int isBot);

/** Funkcja wybiera losowo literę z możliwych do wyboru.
 * @param alphabet zbiór możliwych do zgadnięcia liter.
 * @param whom nazwa zawodnika, który zgaduje.
 * @return wylosowana litera lub "\0" w przypadku gdy nie ma już żadnej litery do wyboru.
 */
char getRandomGuess(char *alphabet,char *whom);

/** Funkcja pozwalająca graczowi wybrać literę.
 * @param alphabet zbiór możliwych do zgadnięcia liter.
 * @return wybrana litera lub znak "\0" mający informować, że zawonik nie wybrał legalnej litery.
 */
char getPlayerGuess(char *alphabet);

/** Funkcja pozwala dokonać następnego zakręcenia kołem w przypadku, gdy zawodnik trafił conajmniej raz w poprzednim przypadku.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param whom nazwa zawodnika, który decyduje.
 * @param isBot zmienna mówiąca, czy dany zawodnik jest botem, czy graczem.
 * @return stan do którego akcja w grze powinna przejść.
 */
actionStates nextGuess(char *hiddenPassword,char *password,char *whom,int isBot);

/** Funkcja decydująca, czy bot próbuje odgadnąć hasło, czy zgaduje kolejną literę.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param whom nazwa zawodnika, który decyduje.
 * @return stan do którego akcja w grze powinna przejść.
 */
actionStates processBotNextGuess(char *hiddenPassword,char *whom);

/** Funkcja pozwalająca na dokonanie zakupu samogłoski
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param account konto zawodnika, który decyduje.
 * @param alphabet zbiór możliwych do wyboru samogłosek.
 * @return stan do którego akcja w grze powinna przejść.
 */
actionStates vowelGuess(char *hiddenPassword,char *password,int *account,char *alphabet);

/** Funkcja pozwalająca graczowi zgadywać spółgłoski tak długo jak ma wystarczająco pieniędzy oraz chce.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param account konto zawodnika, który decyduje.
 * @param alphabet zbiór możliwych do wyboru samogłosek.
 * @return 1 jeśli należy zakończyć akcje danego zawodnika, 0 jeśli można przejść do zaproponowania zawodnikowi mozliwości odgadnięcia hasła.
 */
int makeVowelGuess(char *hiddenPassword,char *password,int *account,char *alphabet);

/** Funkcja wypisuje hasło i pozwala je odgadnąć zawonikowi.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param isBot zmienna mówiąca, czy dany zawodnik jest botem, czy graczem.
 */
void letSolvePuzzle(char *hiddenPassword,char *password,int isBot);

/** Funkcja losująca czy bot odgadnął hasło czy nie.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 */
void checkBotSolution(char *hiddenPassword,char *password);

/** Funkcja pozwalająca graczowi zadecydować czy chce odgadnąć hasło.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 */
void letPlayerSolvePuzzle(char *hiddenPassword,char *password);

/** Funkcja sprawdzająca czy rozwiązanie podane przez gracza jest poprawne.
 * @param hiddenPassword ukryte hasło, z odgadniętymi do tej pory literami.
 * @param password wylosowane na początku hasło.
 * @param guess rozwiązanie w opinii gracza.
 */
void checkPlayerSolution(char *hiddenPassword,char *password,char *guess);
#endif
