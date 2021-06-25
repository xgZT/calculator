#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536

int prior(char zn)
{
    if (zn == '(')
        return 0;
    if (zn == '+' || zn == '-')
        return 1;
    if (zn == '*' || zn == '/')
        return 2;
}

int IsEmptyZn(STACKzn* phead)
{
    if (phead)
        return 0;
    return 1;
}

STACK* Push(STACK* tsifri, char v)
{
    STACK* pnew = (STACK*)malloc(sizeof(STACK));
    pnew->pnext = tsifri;
    pnew->value = v;
    return pnew;
}

STACK* Pop(STACK* phead)
{
    STACK* pnew = phead->pnext;
    free(phead);
    return pnew;
}

int IsEmpty(STACK* phead)
{
    if (phead)
        return 0;
    return 1;
}

STACKzn* PushZn(STACKzn* phead, char v)
{
    STACKzn* pnew = (STACKzn*)malloc(sizeof(STACKzn));
    pnew->pnext = phead;
    pnew->value = v;
    return pnew;
}

STACKzn* PopZn(STACKzn* phead)
{
    STACKzn* pnew = phead->pnext;
    free(phead);
    return pnew;
}

void printStack(const STACK* head, char polsk[])
{
    STACK* polskaya = 0; int i = 0;
    while (head) {
        polskaya = Push(polskaya, head->value);
        head = head->pnext;
    }
    while (polskaya)
    {
        printf("%c", polskaya->value); polsk[i] = polskaya->value; i += 1; polskaya = polskaya->pnext;
    }
}



void Zapis_imag(COMPLEX rez[], int i, int i2, char polsk[])
{
    i += 1;
    if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
        rez[i2].imag = (int)polsk[i] - 48; i += 1;

        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].imag = rez[i2].imag * 10 + ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            double z = 0.1;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {

                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].imag = rez[i2].imag + x;
        }
    }
    else
    {
        rez[i2].imag = -((int)polsk[i] - 48); i += 1;
        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].imag = rez[i2].imag * 10 - ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            double z = 0.1;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {

                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].imag = rez[i2].imag - x;
        }
    }
}

void Iz_char_v_double(char polsk[], COMPLEX rez[], int i, int i2)
{
    if (polsk[i] == '-')i += 1;
    if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
        rez[i2].real = (int)polsk[i] - 48; i += 1;

        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].real = rez[i2].real * 10 + ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {
                double z = 0.1;
                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].real = rez[i2].real + x;
        }
    }
    else
    {
        rez[i2].real = -((int)polsk[i] - 48); i += 1;
        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].real = rez[i2].real * 10 - ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {
                double z = 0.1;
                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].real = rez[i2].real - x;
        }
    }
    i2 += 1;
    if (polsk[i] == '+' || polsk[i] == '-' || polsk[i] == '/' || polsk[i] == '*')
    {
        i -= 1;
    }
}

COMPLEX rezultat(char polsk[])
{
    COMPLEX rez[1000] = { 0 };//массив подсчета результата
    int i = 0;
    int i2 = 0;
    while (polsk[i] != '\0')
    {
        if (polsk[i] == '+')
        {
            rez[i2 - 2].real = rez[i2 - 2].real + rez[i2 - 1].real;
            rez[i2 - 1].real = 0;
            rez[i2 - 2].imag = rez[i2 - 2].imag + rez[i2 - 1].imag;
            rez[i2 - 1].imag = 0;
            i2 -= 1;
        }
        if (polsk[i] == '-' && polsk[i + 1] == ' ')
        {
            rez[i2 - 2].real = rez[i2 - 2].real - rez[i2 - 1].real;
            rez[i2 - 1].real = 0;
            rez[i2 - 2].imag = rez[i2 - 2].imag - rez[i2 - 1].imag;
            rez[i2 - 1].imag = 0;
            i2 -= 1;
        }
        if (polsk[i] == '*')
        {
            if (rez[i2 - 1].imag != 0 && rez[i2 - 2].imag != 0)
            {
                rez[i2 - 2] = multiplication(rez[i2 - 1], rez[i2 - 2]);
                rez[i2 - 1].real = 0;
                rez[i2 - 1].imag = 0;
            }
            else {
                rez[i2 - 2].real = rez[i2 - 2].real * rez[i2 - 1].real;
                rez[i2 - 1].real = 0;
                rez[i2 - 2].imag = rez[i2 - 2].imag * rez[i2 - 1].imag;
                rez[i2 - 1].imag = 0;
            }
            i2 -= 1;
        }
        if (polsk[i] == '/')
        {
            if (rez[i2 - 1].imag != 0 && rez[i2 - 2].imag != 0)
            {
                rez[i2 - 2] = division(rez[i2 - 1], rez[i2 - 2]);
                rez[i2 - 1].real = 0;
                rez[i2 - 1].imag = 0;
            }
            else {
                rez[i2 - 2].real = rez[i2 - 2].real / rez[i2 - 1].real;
                rez[i2 - 1].real = 0;
            }
            i2 -= 1;
        }
        if (polsk[i] >= '0' && polsk[i] <= '9')
        {
            // Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
                rez[i2].real = (int)polsk[i] - 48; i += 1;

                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2].real = rez[i2].real * 10 + ((int)polsk[i] - 48); i += 1;
                }
                if (polsk[i] == '.')
                {
                    i += 1;
                    double x = 0;
                    double z = 0.1;
                    while (polsk[i] >= '0' && polsk[i] <= '9')
                    {

                        x = x + ((int)polsk[i] - 48) * z;
                        i += 1;
                        z = z / 10;
                    }
                    rez[i2].real = rez[i2].real + x;
                }
                if (polsk[i] == '+' || polsk[i] == '-')
                {
                    Zapis_imag(rez, i, i2, polsk);
                    while (polsk[i - 1] != ' ') i += 1;
                }
            }
            else
            {
                rez[i2].real = -((int)polsk[i] - 48); i += 1;
                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2].real = rez[i2].real * 10 - ((int)polsk[i] - 48); i += 1;
                }
                if (polsk[i] == '.')
                {
                    i += 1;
                    double x = 0;
                    double z = 0.1;
                    while (polsk[i] >= '0' && polsk[i] <= '9')
                    {

                        x = x + ((int)polsk[i] - 48) * z;
                        i += 1;
                        z = z / 10;
                    }
                    rez[i2].real = rez[i2].real - x;
                }
                if (polsk[i] == '+' || polsk[i] == '-')
                {
                    Zapis_imag(rez, i, i2, polsk);
                    while (polsk[i - 1] != ' ') i += 1;
                }
            }
            i2 += 1;
            if (polsk[i] == '+' || polsk[i] == '-' || polsk[i] == '/' || polsk[i] == '*')
            {
                i -= 1;
            }
        }
        if (polsk[i] == 's' && polsk[i + 1] == 'i' && polsk[i + 2] == 'n')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i - 1] != ' ') i += 1;
                //            complex_sin(rez[i2]);
            }
            else rez[i2].real = sin(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'c' && polsk[i + 1] == 'o' && polsk[i + 2] == 's')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i - 1] != ' ') i += 1;
                complex_cos(rez[i2]);
            }
            else
                rez[i2].real = cos(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 't' && polsk[i + 1] == 'g')
        {
            i += 2;
            Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i - 1] != ' ') i += 1;
                complex_tg(rez[i2]);
            }
            else
                rez[i2].real = tan(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'l' && polsk[i + 1] == 'o' && polsk[i + 2] == 'g')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i - 1] != ' ') i += 1;
                //                complex_log(rez[i2]);
            }
            else
                rez[i2].real = log(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'l' && polsk[i + 1] == 'n')
        {
            i += 2;
            Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i - 1] != ' ') i += 1;
                //               complex_ln(rez[i2]);
            }
            else
                rez[i2].real = sin(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 's' && polsk[i + 1] == 'q' && polsk[i + 2] == 'r' && polsk[i + 3] == 't')
        {
            i += 4;
            Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i - 1] != ' ') i += 1;
                //               Complex_sqrt(rez[i2]);
            }
            else
                rez[i2].real = sqrt(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'a' && polsk[i + 1] == 'b' && polsk[i + 2] == 's')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            if (rez[i2].real < 0) { rez[i2].real = -(rez[i2].real); }
            i2 += 1;
        }
        if (polsk[i] == 'e' && polsk[i + 1] == 'x' && polsk[i + 2] == 'p')
        {
            i += 3;

            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2].real = exp(rez[i2].real);
            i2 += 1;
        }
        i += 1;
    }
    return rez[0];
}

COMPLEX complex_cos(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = cos(num.real) * cosh(num.imag);
    result.imag = -1 * sin(num.real) * sinh(num.imag);
    return result;
}

COMPLEX complex_tg(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = sin(2 * num.real) / (cos(2 * num.real) + cosh(2 * num.imag));
    result.imag = sinh(2 * num.imag) / (cos(2 * num.real) + cosh(2 * num.imag));
    return result;
}

double imag(COMPLEX num)
{
    return num.imag;
}

double phase(COMPLEX num)
{
    if (num.imag < 0)
        return -1 * (atan2(num.imag, num.real) * 180) / M_PI;
    return (atan2(num.imag, num.real) * 180) / M_PI;
}

COMPLEX addition(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = num1.real + num2.real;
    result.imag = num1.imag + num2.imag;
    return result;
}

COMPLEX subtraction(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = num1.real - num2.real;
    result.imag = num1.imag - num2.imag;
    return result;
}

COMPLEX multiplication(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = num1.real * num2.real - num1.imag * num2.imag;
    result.imag = num1.real * num2.imag + num1.imag * num2.real;
    return result;
}

COMPLEX division(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = (num1.real * num2.real + num1.imag * num2.imag) / (num2.real * num2.real + num2.imag * num2.imag);
    result.imag = (num1.imag * num2.real - num1.real * num2.imag) / (num2.real * num2.real + num2.imag * num2.imag);
    return result;
}

COMPLEX pow_complex(COMPLEX num, int power)
{
    COMPLEX result = { 0 };
    for (int i = 0; i < power - 1; ++i)
    {
        result = multiplication(num, num);
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////////
COMPLEX complex_sin(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = sin(num.real) * cosh(num.imag);
    result.imag = cos(num.real) * sinh(num.imag);
    return result;
}

COMPLEX complex_ln(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = log(sqrt(num.real * num.real + num.imag * num.imag));
    result.imag = atan(num.imag / num.real); 
    return result;
}

double abs(COMPLEX num)
{
    return sqrt(num.real * num.real + num.imag * num.imag);
}

double real(COMPLEX num)
{
    return num.real;
}

double exp(COMPLEX num)
{
    return (exp(num.real)*(cos(num.imag)+sin(num.imag)));
}

double mag(COMPLEX num)
{
    return sqrt(num.real * num.real + num.imag * num.imag);
}

COMPLEX sqrt(COMPLEX num)
{
    double argz = 0;
    COMPLEX result = { 0 };
    if (num.real > 0)
    {
        if (num.imag >= 0)
        {
            argz = atan(num.imag / num.real);
        }
        else
            if (num.imag < 0)
            {
                argz = (2*M_PI - tan(num.imag / num.real));
            }
    }
    else 
        if (num.real < 0)
        {
            if (num.imag >= 0)
            {
                argz = M_PI - atan(num.imag / num.real);
            }
            else
                if (num.imag < 0)
                {
                    argz = (M_PI + tan(num.imag / num.real));
                }
        }
        else 
            if (num.real == 0)
            {
                if (num.imag > 0)
                {
                    argz = M_PI/2;
                }
                else
                    if (num.imag < 0)
                    {
                        argz = (3 * M_PI)/ 2;
                    }
            }
    result.real = ((sqrt(sqrt(num.real * num.real + num.imag * num.imag))) * cos(argz / 2));
    result.imag = ((sqrt(sqrt(num.real * num.real + num.imag * num.imag))) * sin(argz / 2));
    return result;
}

COMPLEX ln(COMPLEX num)
{
    double argz = 0;
    COMPLEX result = { 0 };
    if (num.imag == 0)
    {
        result.real = log(num.real);
    }
    else
    {
        if (num.real > 0)
        {
            if (num.imag >= 0)
            {
                argz = atan(num.imag / num.real);
            }
            else
                if (num.imag < 0)
                {
                    argz = (2 * M_PI - tan(num.imag / num.real));
                }
        }
        else
            if (num.real < 0)
            {
                if (num.imag >= 0)
                {
                    argz = M_PI - atan(num.imag / num.real);
                }
                else
                    if (num.imag < 0)
                    {
                        argz = (M_PI + tan(num.imag / num.real));
                    }
            }
            else
                if (num.real == 0)
                {
                    if (num.imag > 0)
                    {
                        argz = M_PI / 2;
                    }
                    else
                        if (num.imag < 0)
                        {
                            argz = (3 * M_PI) / 2;
                        }
                }
        result.real = log(sqrt(num.real * num.real + num.imag * num.imag));
        result.imag = argz;
    }
    return result;
}   

double log(COMPLEX num1, COMPLEX num2)
{
    return (log(num1.real) / log(num2.real));
}