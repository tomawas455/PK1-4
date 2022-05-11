/** @file */
#ifndef GATES_LOGIC
#define GATES_LOGIC
#include "structures.h"
/** Funkcja realizująca funkcję bramki NOT.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool NEG(gate *&calculationGate);

/** Funkcja realizująca funkcję bramki AND.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool AND(gate *&calculationGate);

/** Funkcja realizująca funkcję bramki NAND.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool NAND(gate *&calculationGate);

/** Funkcja realizująca funkcję bramki OR.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool OR(gate *&calculationGate);

/** Funkcja realizująca funkcję bramki NOR.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool NOR(gate *&calculationGate);

/** Funkcja realizująca funkcję bramki XOR.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool XOR(gate *&calculationGate);

/** Funkcja realizująca funkcję bramki XNOR.
 * @param calculationGate bramka na której ma być wykonana operacja.
 * @return zwraca stan bramki po realizacji operacji.
 */
bool XNOR(gate *&calculationGate);
#endif
