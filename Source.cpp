#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000
#include <string.h>
#include "structures.h"
#include "functions.h"


int main()
{
    // добавляйте пустую строку пожалуйста
    FILE* input = fopen("input.txt", "rt");
    printf("Expression:\n");
    //char* str = (char*)malloc(sizeof(STACK));
    char str[100] = { 0 };
    fgets(str, SIZE, input);
    int len = strlen(str);
    str[len] = '\0';
    printf("%s\n", str);
    STACK* tsifri = NULL;  //стек с числами
    STACKzn* znaki = 0; //стек со знаками oper
    char polsk[100] = { 0 };
    char vivod[100];
    char variables[30][100] = { 0 };
    int c = 0;
    while (!feof(input))
    {
        fgets(variables[c], 100, input);
        int varlen = strlen(variables[c]);
        variables[c++][varlen - 1] = '\0';
    }
    for (int i = 0; i < len; i++)
    {
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9')))
        {
            if (str[i] == '-')
            {
                tsifri = Push(tsifri, str[i]);
                i += 1;
            }
            if ((str[i + 1] < '0' || str[i + 1] >'9') && str[i + 1] != '.')
            {
                tsifri = Push(tsifri, str[i]);
                tsifri = Push(tsifri, ' ');
            }
            else {
                while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '+' || str[i] == '-')
                {
                    tsifri = Push(tsifri, str[i]);
                    i += 1;
                }tsifri = Push(tsifri, ' ');
            }

        }
        if (str[i] == '(')
        {
            znaki = PushZn(znaki, '(');
            continue;
        }
        if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && str[i + 1] == ' ')
        {
            if (IsEmptyZn(znaki) || prior(str[i]) > prior(znaki->value))
            {
                znaki = PushZn(znaki, str[i]);
                continue;
            }
            else
            {
                while (!IsEmptyZn(znaki) && prior(str[i]) <= prior(znaki->value))
                {
                    tsifri = Push(tsifri, znaki->value);
                    tsifri = Push(tsifri, ' ');
                    znaki = PopZn(znaki);
                }
                znaki = PushZn(znaki, str[i]);
                continue;
            }
        }
        if (str[i] == ')')
        {
            while (znaki->value != '(')
            {
                tsifri = Push(tsifri, znaki->value);
                tsifri = Push(tsifri, ' ');
                znaki = PopZn(znaki);
            }
            znaki = PopZn(znaki); // минус скобка
        }
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
        {
            char peremennaya[10] = { 0 };
            int p = 0;
            if (str[i - 1] == '-')
            {
                tsifri = Push(tsifri, str[i - 1]);
                // i += 1;
            }
            while (str[i] != ' ' && str[i] != '\n')// после названия переменной пусть обязательно будет пробел
            {
                peremennaya[p] = str[i];
                i += 1; p += 1;
            }
            if ((strcmp(peremennaya, "sin") == 0) || (strcmp(peremennaya, "cos") == 0) || (strcmp(peremennaya, "tg") == 0)
                || (strcmp(peremennaya, "log") == 0) || (strcmp(peremennaya, "ln") == 0) || (strcmp(peremennaya, "sqrt") == 0)
                || (strcmp(peremennaya, "pow") == 0) || (strcmp(peremennaya, "abs") == 0) || (strcmp(peremennaya, "exp") == 0)
                || (strcmp(peremennaya, "real") == 0) || (strcmp(peremennaya, "imag") == 0) || (strcmp(peremennaya, "mag") == 0)
                || (strcmp(peremennaya, "phase") == 0))
            {
                int r = 0;
                while (peremennaya[r])
                {
                    tsifri = Push(tsifri, peremennaya[r]);
                    r += 1;
                }

            }
            for (int j = 0; j < c - 1; ++j)
            {
                int k = 0; char vvod_p[10] = { 0 };
                while (variables[j][k] != ' ') { vvod_p[k] = variables[j][k]; k += 1; }
                if (strcmp(peremennaya, vvod_p) == 0)
                {

                    k += 3;
                    while (variables[j][k] != '\n' && variables[j][k] != '\0')
                    {
                        tsifri = Push(tsifri, variables[j][k]);
                        k += 1;
                    }tsifri = Push(tsifri, ' ');
                }
            }
            //  if (strcmp(peremennaya, str2) == 0) сравню потом циклом, в зависимости от части Арсения


        }
        //!!!!!!if (str[i] == какой-нибудь букве), то (while str[i]!=' ')записываем ее в отдельную переменную до пробела 
        //и сравниваем с введенными переменными,  если совпадает, то записываем значение переменной в стек tsifri)
    }
    while (!IsEmptyZn(znaki))
    {
        tsifri = Push(tsifri, znaki->value);
        tsifri = Push(tsifri, ' ');
        znaki = PopZn(znaki);
    }
    printf("Reverse Polish Notation:\n");
    printStack(tsifri, polsk);
    polsk[strlen(polsk)] = '\0';
    COMPLEX itog = rezultat(polsk);
    printf("\nResult:\n%.2lf %.2lfj", itog.real, itog.imag);
}