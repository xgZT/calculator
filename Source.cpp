#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000
#include <string.h>
typedef struct STACKzn
{
    char value;
    struct STACKzn* pnext;
}STACKzn;
int prior(char zn)
{
    if (zn == '(')
        return 0;
    if (zn == '+' || zn == '-')
        return 1;
    if (zn == '*' || zn == '/')
        return 2;
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
int IsEmptyZn(STACKzn* phead)
{
    if (phead)
        return 0;
    return 1;
}
///////////////////////////////////���� ��� �����
typedef struct STACK
{
    char value;
    struct STACK* pnext;
}STACK;
STACK* Push(STACK* phead, char v)
{
    STACK* pnew = (STACK*)malloc(sizeof(STACK));
    pnew->pnext = phead;
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
void printStack(const STACK* head, char polsk[]) {
    STACK* polskaya = 0; int i = 0;
    while (head) {
        polskaya = Push(polskaya, head->value);
        head = head->pnext;
    }
    while (polskaya) { printf("%c", polskaya->value); polsk[i] = polskaya->value; i += 1; polskaya = polskaya->pnext; }
}

/////////////////////////////////////////
int main()
{
    // ���������� ������ ������ ����������
    FILE* input = fopen("input.txt", "rt");
    printf("Expression:\n");
    char* str = (char*)malloc(sizeof(STACK));
    fgets(str, SIZE, input);
    int len = strlen(str);
    str[len] = '\0';
    printf("%s\n", str);
    STACK* tsifri = 0;  //���� � �������
    STACKzn* znaki = 0; //���� �� ������� oper
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
        if ((str[i] >= '0' && str[i] <= '9') || (str[i]=='-' && (str[i+1] >= '0' && str[i + 1] <='9')))
        {
            if (str[i]=='-')
            {
                tsifri = Push(tsifri, str[i]);
                i += 1;
            }
            /*if (str[i + 1] < '0' || str[i + 1] >'9') 
            { tsifri = Push(tsifri, str[i]);
            tsifri = Push(tsifri, ' '); }
            else {*/
                while (str[i] >= '0' && str[i] <= '9')
                {
                    tsifri = Push(tsifri, str[i]);
                    i += 1;
                }tsifri = Push(tsifri, ' ');
            //}
        }
        if (str[i] == '(')
        {
            znaki = PushZn(znaki, '(');
            continue;
        }
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
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
            znaki = PopZn(znaki); // ����� ������
        }
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
        {
            char peremennaya[10] = { 0 };
            int p = 0;
               while (str[i]!=' ' && str[i] != '\n')// ����� �������� ���������� ����� ����������� ����� ������
                {
                   peremennaya[p] = str[i];
                   i += 1; p += 1;
                }
               for (int j = 0; j < c-1; ++j)
               {
                   int k = 0; char vvod_p[10] = { 0 };
                   while (variables[j][k] != ' ') { vvod_p[k] = variables[j][k]; k += 1; }
                   if (strcmp(peremennaya, vvod_p) == 0)
                   {
                       k += 3;
                       while (variables[j][k]!='\n' && variables[j][k] != '\0')
                       {
                           tsifri = Push(tsifri, variables[j][k]);
                           k += 1;
                       }tsifri = Push(tsifri, ' ');
                   }
               }
             //  if (strcmp(peremennaya, str2) == 0) ������ ����� ������, � ����������� �� ����� �������
               
            
        }
        //!!!!!!if (str[i] == �����-������ �����), �� (while str[i]!=' ')���������� �� � ��������� ���������� �� ������� 
        //� ���������� � ���������� �����������,  ���� ���������, �� ���������� �������� ���������� � ���� tsifri)
    }
    while (!IsEmptyZn(znaki))
    {
        tsifri = Push(tsifri, znaki->value);
        tsifri = Push(tsifri, ' ');
        znaki = PopZn(znaki);
    }
    printf("Reverse Polish Notation:\n");
    printStack(tsifri, polsk);
}