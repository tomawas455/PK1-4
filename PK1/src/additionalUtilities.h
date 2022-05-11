/** @file */
#ifndef ADDITIONAL_UTILITIES
#define ADDITIONAL_UTILITIES
#define WHITESPACES " \n\r\t\f\v"
#include <fstream>
#include <string>

/** Funkcja usuwająca podane znaki po lewej stronie podanego stringa.
 * @param str string z którego należy usunąć znaki.
 * @param characters string zawierający co trzeba usunąć ze stringa (domyślnie białe spacje).
 * @return zedytowany string.
 */
std::string &ltrim(std::string &str,const std::string characters=WHITESPACES);

/** Funkcja usuwająca podane znaki po prawej stronie podanego stringa.
 * @param str string z którego należy usunąć znaki.
 * @param characters string zawierający co trzeba usunąć ze stringa (domyślnie białe spacje).
 * @return zedytowany string.
 */
std::string &rtrim(std::string &str,const std::string characters=WHITESPACES);

/** Funkcja usuwająca podane znaki po obu stronach podanego stringa.
 * @param str string z którego należy usunąć znaki.
 * @param characters string zawierający co trzeba usunąć ze stringa (domyślnie białe spacje).
 * @return zedytowany string.
 */
std::string &trim(std::string &str,const std::string characters=WHITESPACES);

/** Funkcja sprawdzająca czy podany tekst zaczyna się od podanego prefiksu.
 * @param text tekst którego początek będzie sprawdzany.
 * @param prefix interesujący nas początek napisu.
 * @return true, jeśli text zaczyna się od podanego prefiksu.
 */
bool startsWith(std::string &text,std::string prefix);

/** Funkcja przeształcająca podanego stringa na taki sam string składający się z małych liter.
 * @param text tekst, w którym trzeba zmienić znaki.
 * @return ten sam napis, ale tylko z małymi literami.
 */
std::string toLowercase(std::string &text);

/** Funkcja przekształcająca podany znak na jego małoliterową wersję.
 * @param c znak do zmiany.
 * @return ten sam znak pomniejszony.
 */
char toLowercase(char c);

/** Funkcja stara się otworzyć plik w trybie odczytu, jeśli plik nie istnieje to poda stosowny komunikat.
 * @param filename nazwa pliku do otwarcia.
 * @return strumień wejścia do zadanego pliku.
 */
std::ifstream openFile(std::string &filename);

/** Funkcja pozyskuje linijkę z podanego pliku oraz obcina białe spacje na jej początku i końcu.
 * @param file plik z którego funkcja ma czytać.
 * @return zwraca obciętą z białych spacji linijkę.
 */
std::string getDataFromFile(std::ifstream &file);
#endif
