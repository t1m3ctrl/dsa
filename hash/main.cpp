#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdlib.h>
#include <string>

#define N 20

using namespace std;

typedef struct tData
{
    int Data;
    // string Text;
} tData;

typedef struct StructList
{
    struct StructList *next;
    union
    {
        tData Data;
        unsigned char Digit[sizeof(tData)];
    };
} List;

int Hash(int k, int m);
void ListCheck(List *head);
void Push(List **head, int data);
void HashSearch1(int x, int m, List **s);
void ListFree(List *head);
void FillRand(int *a, int n);
void PrintMas(int *a, int n);

int main()
{
    srand(time(0));
    // string symbols = "abcdefghijklmnopqrstuvwxyz";
    int m = 11;
    int *array;
    // string *text;

    List **head = new List *[m];
    for (int i = 0; i < m; i++)
        *head = NULL;

    array = new int[N];
    // text = new string[N];
    // for (int i = 0; i < N; i++)
    // {
    //     for (int m = 0; m < 5; m++)
    //         text[i] += symbols[rand() % 27];
    // }
    // cout << "\tText:\n\t";
    // for (int i = 0; i < N; i++)
    //     cout << text[i] << " ";
    // cout << endl
    //      << endl;
    FillRand(array, N);
    PrintMas(array, N);
    for (int i = 0; i < N; i++)
    {
        int hash_id = Hash(array[i], m);
        Push(&head[hash_id], array[i]);
    }
    for (int i = 0; i < m; i++)
    {
        cout << "\n\t i = " << setw(2) << i << " ";
        ListCheck(head[i]);
    }
    HashSearch1(array[10], m, head);
    HashSearch1(array[0], m, head);
    HashSearch1(array[19], m, head);
    HashSearch1(array[20], m, head);
    for (int i = 0; i < m; i++)
        ListFree(head[i]);
    delete[] array;
    return 0;
}

void Push(List **head, int data)
{
    List *p;
    p = new List;
    p->Data.Data = data;
    p->next = *head;
    *head = p;
}

void ListCheck(List *head)
{
    List *p;
    p = head;
    cout << " ";
    while (p != NULL)
    {
        cout << setw(5) << p->Data.Data;
        p = p->next;
    }
    cout << endl;
}

int Hash(int k, int m)
{
    return k % m;
}

void HashSearch1(int x, int m, List **s)
{
    bool found = false;
    int pos = 0;
    int hash_id = Hash(x, m);
    List *p = s[hash_id];
    while (p)
    {
        if (p->Data.Data == x)
        {
            cout << "Found " << setw(3) << x << " | hash_id = " << setw(2) << hash_id << " | pos = " << pos << endl;
            found = true;
            break;
        }
        p = p->next;
        pos++;
    }
    if (!found)
        cout << "Can't find " << x << endl;
}

void ListFree(List *head)
{
    List *p, *q;
    q = p = head;
    while (p != NULL)
    {
        p = q->next;
        delete q;
        q = p;
    }
    head = NULL;
}

void FillRand(int *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

void PrintMas(int *a, int n)
{
    int i;
    cout << "\tArray:" << endl
         << "\t";
    for (i = 0; i < n; i++)
        cout << setw(4) << a[i];
    cout << endl;
}
