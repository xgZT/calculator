#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct STACKzn
{
    char value;
    struct STACKzn* pnext;
}STACKzn;

typedef struct STACK
{
    char value;
    struct STACK* pnext;
}STACK;

typedef struct complex_number {
    double real;
    double imag;
}COMPLEX;

#endif // !STRUCTURES_H