#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <iomanip>

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
int *HashQuadAppend(int *a, int m, int data, int *collisionQuad);
int *HashLinearAppend(int *a, int m, int data, int *collisionLinear);
void HashQuadSearch(int *a, int m, int x);
void HashLinearSearch(int *a, int m, int x);

void ListCheck(List *head);
void Push(List **head, int data);
void ListFree(List *head);
void FillRand(int *a, int n);
void PrintMas(int *a, int n);

int main()
{
    srand(time(0));
    // int m = N / log2(N);
    int m = 19;
    int *array;
    int *hash_QuadTable = new int[m];
    int *hash_LinearTable = new int[m];
    int collisionQuad = 0;
    int collisionLinear = 0;

    array = new int[N];
    FillRand(array, N);
    PrintMas(array, N);
    for (int i = 0; i < m; i++)
    {
        hash_LinearTable[i] = 0;
        hash_QuadTable[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        hash_QuadTable = HashQuadAppend(hash_QuadTable, m, array[i], &collisionQuad);
        hash_LinearTable = HashLinearAppend(hash_LinearTable, m, array[i], &collisionLinear);
    }
    cout << "\n\tQuad hash table : " << endl
         << "\n\t";
    for (int i = 0; i < m; i++)
        cout << setw(4) << i;
    cout << "\n\t";
    for (int i = 0; i < m; i++)
        cout << setw(4) << hash_QuadTable[i];
    cout << endl;

    cout << "\n\tLinear hash table : " << endl
         << "\n\t";
    for (int i = 0; i < m; i++)
        cout << setw(4) << i;
    cout << "\n\t";
    for (int i = 0; i < m; i++)
        cout << setw(4) << hash_LinearTable[i];

    cout << endl;
    cout << endl;

    cout << "\t|   m   |"
         << "   N   |"
         << "   Collisions    |" << endl;
    cout << "\t|       |"
         << "       |"
         << " Linear |  Quad  |" << endl;
    cout << "\t|" << setw(7) << m << "|" << setw(7) << N << "|" << setw(8) << collisionLinear << "|" << setw(8) << collisionQuad << "|" << endl;

    cout << endl;
    cout << endl;

    HashQuadSearch(hash_QuadTable, m, array[0]);
    HashQuadSearch(hash_QuadTable, m, array[10]);
    HashQuadSearch(hash_QuadTable, m, 99999);

    HashLinearSearch(hash_LinearTable, m, array[0]);
    HashLinearSearch(hash_LinearTable, m, array[10]);
    HashLinearSearch(hash_LinearTable, m, 99999);

    delete[] array;
    delete[] hash_QuadTable;
    delete[] hash_LinearTable;
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

int *HashQuadAppend(int *a, int m, int data, int *collisionQuad)
{
    int hash_id = Hash(data, m);
    int d = 1;
    while (true)
    {
        if (a[hash_id] == 0)
        {
            a[hash_id] = data;
            break;
        }
        else
            (*collisionQuad)++;

        if (d >= m)
        {
            cout << "Hash Table overload!" << endl;
            break;
        }
        hash_id += d;
        if (hash_id >= m)
            hash_id -= m;
        d += 2;
    }
    return a;
}

void HashQuadSearch(int *a, int m, int x)
{
    int hash_id = Hash(x, m);
    int d = 1;
    while (true)
    {
        if (a[hash_id] == x)
        {
            cout << "Found " << x << " | ID = " << hash_id << endl;
            break;
        }
        if (d >= m)
        {
            cout << "Can't find " << x << "! Hash table overload" << endl;
            break;
        }
        hash_id += d;
        if (hash_id >= m)
            hash_id -= m;
        d += 2;
    }
}

int *HashLinearAppend(int *a, int m, int data, int *collisionLinear)
{
    int hash_id = Hash(data, m);
    int i = 1;
    while (true)
    {
        if (a[hash_id] == 0)
        {
            a[hash_id] = data;
            break;
        }
        else
            (*collisionLinear)++;

        if (i >= m)
        {
            cout << "Hash Table overload!" << endl;
            break;
        }
        hash_id++;
        if (hash_id >= m)
            hash_id -= m;
        i++;
    }
    return a;
}

void HashLinearSearch(int *a, int m, int x)
{
    int hash_id = Hash(x, m);
    int i = 1;
    while (true)
    {
        if (a[hash_id] == x)
        {
            cout << "Found " << x << " | ID = " << hash_id << endl;
            break;
        }
        if (i >= m)
        {
            cout << "Can't find " << x << "! Hash table overload" << endl;
            break;
        }
        hash_id++;
        if (hash_id >= m)
            hash_id -= m;
        i++;
    }
}