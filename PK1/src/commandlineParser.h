/** @file */
#ifndef COMMANDLINE_PARSER
#define COMMANDLINE_PARSER
#include <string>

/** Funkcja analizująca argumenty przekazane do programu.
 * @param argsAmount liczba argumentów przekazanych do programu.
 * @param arguments argumenty przekazane do programu.
 * @param cFile nazwa pliku z układem.
 * @param sFile nazwa pliku ze stanami wejść.
 * @param oFile nazwa pliku wyjściowego.
 * @return true jeśli znalezione zostały nazwy plików z ukladem i stanami wejść oraz, opcjonalnie, nazwa pliku wyjściowego
 */
bool parseCommandline(int &argsAmount,char **arguments,std::string &cFile,std::string &sFile,std::string &oFile);

/** Funkcja pozyskująca nazwy plików z argumentów.
 * @param argsAmount liczba argumentów przekazanych do programu.
 * @param arguments argumenty przekazane do programu.
 * @param cFile nazwa pliku z układem.
 * @param sFile nazwa pliku ze stanami wejść.
 * @param oFile nazwa pliku wyjściowego.
 */
void getFiles(int &argsAmount,char **arguments,std::string &cFile,std::string &sFile,std::string &oFile);

/** funkcja edytująca nazwę pliku
 *
 * Funkcja sprawdza czy wskaźnik currentFile na coś wskazuje,
 * jeśli tak to podany argument staje się nazwą pliku,
 * currentFile jest następnie ustawiany na NULL i funkcja zwraca true.
 *
 * @param currentFile wskaźnik na nazwę pliku do zedytowania.
 * @param text potencjalna nazwa pliku.
 * @return true jeśli currentFile na coś wskazuje.
 */
bool editedFile(std::string *&currentFile,std::string &text);

/** Funkcja ustawia wskaźnik currentFile na nazwę pliku do zedytowania.
 *
 * Funkcja sprawdza czy wartość obecnego argumentu jest jednym z możliwych przełączników,
 * jeśli tak to ustawia currentFile na to samo miejsce w tablicy filenames,
 * na której został znaleziony przełącznik.
 *
 * @param filenames nazwy plików.
 * @param options możliwe przełączniki.
 * @param currentFile wskaźnik na obecnie edytowaną nazwe pliku.
 * @param argument argument do sprawdzenia.
 */
void setFileToEdit(std::string *filenames[],std::string options[3],std::string *&currentFile,std::string &argument);

/** Funkcja sprawdzająca czy pliki zostały podane przez użytkownika
 * @param cFile nazwa pliku z układem.
 * @param sFile nazwa pliku ze stanami wejść.
 * @param oFile nazwa pliku wyjściowego.
 * @return true jeśli pliki mają wartość inną niż pusty string.
 */
bool correctFiles(std::string &cFile,std::string &sFile);
#endif
