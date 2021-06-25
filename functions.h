#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structures.h"

int prior(char zn);
int IsEmptyZn(STACKzn* phead);
STACK* Push(STACK* tsifri, char v);
STACK* Pop(STACK* phead);
int IsEmpty(STACK* phead);
STACKzn* PushZn(STACKzn* phead, char v);
STACKzn* PopZn(STACKzn* phead);
void printStack(const STACK* head, char polsk[]);
void Zapis_imag(COMPLEX rez[], int i, int i2, char polsk[]);
void Iz_char_v_double(char polsk[], COMPLEX rez[], int i, int i2);
COMPLEX rezultat(char polsk[]);
COMPLEX complex_cos(COMPLEX num);
COMPLEX complex_tg(COMPLEX num);
double imag(COMPLEX num);
double phase(COMPLEX num);
COMPLEX addition(COMPLEX num1, COMPLEX num2); //сложение
COMPLEX subtraction(COMPLEX num1, COMPLEX num2); //вычитание
COMPLEX multiplication(COMPLEX num1, COMPLEX num2); //умножение
COMPLEX division(COMPLEX num1, COMPLEX num2); //деление
COMPLEX pow_complex(COMPLEX num, int power);
/////////////////////////////////////////////
COMPLEX complex_sin(COMPLEX num);
COMPLEX complex_ln(COMPLEX num);
double abs(COMPLEX num);
double real(COMPLEX num);
double exp(COMPLEX num);
double mag(COMPLEX num);
COMPLEX sqrt(COMPLEX num);
COMPLEX ln(COMPLEX num);
double log(COMPLEX num1, COMPLEX num2);
#endif // !FUNCTIONS_H