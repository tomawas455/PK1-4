/** @file */
#ifndef CIRCUIT_CALCULATOR
#define CIRCUIT_CALCULATOR
#include <fstream>
#include "additionalUtilities.h"
#include "structures.h"

/** Funkcja oblicza stany wyjść układu z podanego pliku
 *
 * Na początku funkcja sprawdza nazwę pliku wyjściowego,
 * jeśli jest ona pusta to ustawia wyjście na standardowe wyjście,
 * jeśli nie jest pusta to ustawia wyjście na ten plik.
 * Następnie funkcja zczytuje dane z pliku linia po linii i oblicza dla podanych w niej stanów wejść stany wyjść każdej bramki aż do końca,
 * na koniec zapisuje stany wyjść do pliku.
 *
 * @param file plik ze stanami wejść.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 * @param outputFilename nazwa pliku wyjściowego.
 */
void calculateCircuitFromFile(std::ifstream &file,gate *&gates,cable *&cables,cableContainer **IO,std::string &outputFilename);

/** Funkcja ustawia bufor wyjścia na które będą przesyłane stany wyjść.
 * @param filename nazwa pliku wyjściowego.
 * @param file strumień wyjściowy do pliku, potrzebny jeśli nazwa pliku nie jest pustym stringiem.
 * @param buf bufor, który będzie ustawiany.
 */
void setOutputFileBuf(std::string &filename,std::ofstream &file,std::streambuf *&buf);

/** Funkcja ustawia bufor wyjśiowy na standardowe wyjście lub zwraca true
 *
 * Jeśli plik wyjśiowy jest pustym stringiem to funkcja ta ustawia bufor wyjściowy na standardowe wyjście,
 * w innym przypadku oznacza to, że wyjście powinno być skierowane do pliku,
 * w takim przypadku funkcja zwraca wartość true.
 *
 * @param filename nazwa pliku wyjśiowego.
 * @param buf bufor wyjściowy.
 * @return true jeśli nazwa pliku wyjśiowego nie jest pustym stringiem.
 */
bool outputFileHasName(std::string &filename,std::streambuf *&buf);

/** Funkcja ustawia wejścia układu wg danych z pliku, liczy wyjścia bramek, a następnie zapisuje stanny wyjść.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 * @param cables wskaźnik na pierwszy kabel w układzie, dostęp do kolejnych jest możliwy poprzez cables->next itd.
 * @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 * @param data wartość danej linijki w pliku ze stanami wejść.
 * @param ofile strumień wyjścia do którego trzeba wpisać stany wyjść.
 */
void calculateCircuit(gate *&gates,cable *&cables,cableContainer **IO,std::string &data,std::ostream &ofile);

/** Funkcja pobiera numer kabla oraz jego stan i ustawia wejścia układu.
 * @param ins wskaźnik na pierwszy element cableContainer zawierający wejścia układu.
 * @param data tekst danej linijki z pliku ze stanami wejść.
 */
void setCircuitIns(cableContainer *&ins,std::string &data);

/** Funkcja pobierająca numer kabla i jego stan.
 * @param data dane z których trzeba pozyskać numer kabla i jego stan.
 * @param space indeks spacji w danych.
 * @param cableNumber numer kabla, który funkcja ustawi jeśli go znajdzie.
 * @param status stan kabla, który funkcja ustawi jeśli go znajdzie.
 */
void getCableNumberAndStatus(std::string &data,int &space,int &cableNumber,bool &status);

/** Funkcja ustawia stan kabla o podanym numerze
 * @param ins wskaźnik na pierwszy element cableContainer zawierający wejścia układu.
 * @param cableNumber numer szukanego kabla.
 * @param status stan kabla na jaki ma funkcja ustawić kabel, true=1, false=0.
 */
void setCableStatus(cableContainer *ins,int &cableNumber,bool &status);

/** Funkcja sprawdzająca i zmieniająca stan kabla.
 *
 * Funkcja sprawdza czy kabel w danym kontenerze ma taki sam number jak szukany,
 * jeśli tak to ustawia go na podany stan i zwraca true.
 *
 * @param working kontener z kablem do sprawdzenia.
 * @param cableNumber numer szukanego kabla.
 * @return true jeśli kabel w working jest taki sam jak cableNumber.
 */
bool changedCable(cableContainer *&working,int &cableNumber,bool &status);

/** Funkcja iterująca po wszystkich bramkach i ustawiająca ich wyjścia.
 * @param gates wskaźnik na pierwszą bramkę w układzie, dostęp do kolejnych jest możliwy poprzez gates->next itd.
 */
void calculateGatesOuts(gate *gates);

/** Funkcja wykonuje operację bramki w zależności od jej typu
 * @param working bramka na której trzeba wykonać odpowiednią operację
 */
void calculateGate(gate *&working);

/** Funkcja zapisuje do strumienia wyjściowego obliczone stany wyjść
 * @param IO @param IO tablica dwuelementowa w pierwszym indeksie zawierająca wskaźnik na pierwsze wejście układu, a w drugim indeksie na pierwsze wyjście.
 * @param ofile strumień do którego należy przesłać dane.
 */
void printToFile(cableContainer **IO,std::string &data,std::ostream &ofile);

/** Funkcja przesyłająca stany wejść lub wyjść do strumienia.
 * @param connectors cableContainer zawierający wejścia lub wyjścia układu.
 * @param ofile strumień do którego należy przesłać dane.
 */
void printIOStatus(cableContainer *connectors,std::ostream &ofile);
#endif
