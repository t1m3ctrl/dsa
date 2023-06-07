#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <iomanip>
#include "../include/graphic.h"

using namespace std;

#define N 20 // 700 - max how can i fix this?

typedef struct {
    int id;
    long long number;
    string surname;
    string name;
} telephone;

void FillInc(int* a, int n);
void FillDec(int* a, int n);
void FillRand(int* a, int n);

int CheckSum(int* a, int n);
int RunNumber(int* a, int n);

void PrintMas(int* a, int n);

void swap(int* a, int* b);

float MiddleSerial(int* a, int n, int length);

int SelectSort(int* a, int n);
int BubbleSort(int* a, int n);
int ShakerSort(int* a, int n);
int InsertSort(int* a, int n);
int ShellSort(int* a, int n, int* h, int m_size);

int BSearch1(int* a, int n, int x);
int BSearch2(int* a, int n, int x);
int BSearchAll1(int* a, int n, int x);
int BSearchAll2(int* a, int n, int x);

void BSearch1Pos(int* a, int n, int x);
void BSearch2Pos(int* a, int n, int x);
void BSearchAll1Pos(int* a, int n, int x);
void BSearchAll2Pos(int* a, int n, int x);

void BSearchAll2Number(telephone* a, int* index_sorted, int n, long long x);
void BSearchAll2Name(telephone* a, int* index_sorted, int n, string x);

void StructLineOutput(telephone x);
void HeaderOutput();
bool less_tel1(telephone x, telephone y);
bool less_tel2(telephone x, telephone y);

int main()
{
    srand(time(NULL));
    telephone telephones[N];
    int tmp;
    string name_arr[10]
            = {"Mike",
               "Alex",
               "David",
               "Sam",
               "Paul",
               "Tommy",
               "Walter",
               "Jessie",
               "Steve",
               "Michael"};
    string surname_arr[10]
            = {"Montana",
               "Middleson",
               "Black",
               "White",
               "Smith",
               "Ocean",
               "Downey",
               "Biden",
               "Trump",
               "Anderson"};
    int sorted_1[N];
    int sorted_2[N];
    int i, j;

    long long number_to_find = 0;
    string name_to_find;

    for (i = 0; i < N; i++) {
        sorted_1[i] = i;
        sorted_2[i] = i;
        telephones[i].id = i + 1;
        telephones[i].number = rand();
        telephones[i].name = name_arr[rand() % 10];
        telephones[i].surname = surname_arr[rand() % 10];
    }

    cout << "\n\tOur struct \n";
    HeaderOutput();
    for (i = 0; i < N; i++)
        StructLineOutput(telephones[i]);

    for (i = 1; i < N; i++) {
        tmp = sorted_1[i];
        j = i - 1;
        while ((j >= 0)
               && (less_tel1(telephones[tmp], telephones[sorted_1[j]]))) {
            sorted_1[j + 1] = sorted_1[j];
            j--;
        }
        sorted_1[j + 1] = tmp;
    }
    cout << "\n\n\tSorted struct 1 (by number in ascending order)\n";
    HeaderOutput();
    for (i = 0; i < N; i++)
        StructLineOutput(telephones[sorted_1[i]]);

    for (i = 1; i < N; i++) {
        tmp = sorted_2[i];
        j = i - 1;
        while ((j >= 0)
               && (less_tel2(telephones[tmp], telephones[sorted_2[j]]))) {
            sorted_2[j + 1] = sorted_2[j];
            j--;
        }
        sorted_2[j + 1] = tmp;
    }
    cout << "\n\n\tSorted struct 2 (by names then names by number in ascending "
            "order)\n";
    HeaderOutput();
    for (i = 0; i < N; i++)
        StructLineOutput(telephones[sorted_2[i]]);

    cout << "\n\tOur struct \n";
    HeaderOutput();
    for (i = 0; i < N; i++)
        StructLineOutput(telephones[i]);

    cout << "\n\tEnter number to find (enter 0 to exit)\n\t";
    cin >> number_to_find;
    while (number_to_find != 0) {
        HeaderOutput();
        BSearchAll2Number(telephones, sorted_1, N, number_to_find);
        cout << "\n\tEnter number to find (enter 0 to exit)\n\t";
        cin >> number_to_find;
    }

    cout << "\n\tEnter name to find (enter 0 to exit)\n\t";
    cin >> name_to_find;
    while (name_to_find != "0") {
        HeaderOutput();
        BSearchAll2Name(telephones, sorted_2, N, name_to_find);
        cout << "\n\tEnter name to find (enter 0 to exit)\n\t";
        cin >> name_to_find;
    }

    return 0;
}

void FillInc(int* a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = i;
}

void FillDec(int* a, int n)
{
    int i, j;
    for (i = n - 1, j = 0; i >= 0; i--, j++)
        a[j] = i;
}

void FillRand(int* a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

int CheckSum(int* a, int n)
{
    int i, sum = 0;
    for (i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

int RunNumber(int* a, int n)
{
    int i, serial = 1;
    for (i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])
            serial++;
    }
    return serial;
}

void PrintMas(int* a, int n)
{
    int i;
    cout << "\tArray:" << endl;
    printf("\t");
    for (i = 0; i < n; i++) {
        printf("%3d ", a[i]);
    }
    cout << endl;
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

float MiddleSerial(int* a, int n, int length)
{
    int i;
    int sum = 0;
    int serial = 1;
    for (i = 0; i < n - 1; i++) {
        if (a[i] < a[i + 1])
            serial++;
        if (a[i] >= a[i + 1]) {
            sum += serial;
            serial = 1;
        }
    }
    return (sum * 1.0) / (length * 1.0);
}

int SelectSort(int* a, int n)
{
    int i, min, j, c = 0, m = 0;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            c++;
            if (a[j] < a[min])
                min = j;
        }
        if (min != i) {
            swap(&a[min], &a[i]);
            m += 3;
        }
    }
    return (m + c);
}

int BubbleSort(int* a, int n)
{
    int i, j, m = 0, c = 0;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++) {
            c++;
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                m += 3;
            }
        }
    return (m + c);
}

int ShakerSort(int* a, int n)
{
    int L = 0, R = n - 1, k = n - 1, c = 0, m = 0;
    int i;

    do {
        for (i = R; i >= L + 1; i--) {
            c++;
            if (a[i] < a[i - 1]) {
                swap(&a[i], &a[i - 1]);
                k = i;
                m += 3;
            }
        }

        L = k;

        for (i = L; i <= R - 1; i++) {
            c++;
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                k = i;
                m += 3;
            }
        }

        R = k;

    } while (L < R);
    return (m + c);
}

int InsertSort(int* a, int n)
{
    int i, j, c = 0, m = 0;
    int tmp;
    for (i = 1; i < n; i++) {
        tmp = a[i];
        m++;
        j = i - 1;
        while ((j >= 0) && (tmp < a[j])) {
            c++;
            a[j + 1] = a[j];
            m++;
            j--;
        }
        a[j + 1] = tmp;
        m++;
    }
    return (m + c);
}

int ShellSort(int* a, int n)
{
    int i, k, j, tmp, c = 0, m = 0;

    int m_size = (int)(floor(log2(n)) - 1);
    int* h = new int[m_size];
    h[0] = 1;
    for (i = 1; i < m_size; i++)
        h[i] = 2 * h[i - 1] + 1;

    for (k = m_size - 1; k >= 0; k--) {
        for (i = h[k]; i < n; i++) {
            tmp = a[i];
            m++;
            j = i - h[k];
            while ((j >= 0) && (tmp < a[j])) {
                c++;
                a[j + h[k]] = a[j];
                m++;
                j -= h[k];
            }
            a[j + h[k]] = tmp;
            m++;
        }
    }

    delete[] h;

    return (m + c);
}

int BSearch1(int* a, int n, int x)
{
    int L = 0, R = n - 1, m, c = 0;
    while (L <= R) {
        m = (int)(floor((L + R) / 2));
        c++;
        if (a[m] == x) {
            break;
        }
        c++;
        if (a[m] < x)
            L = m + 1;
        else
            R = m - 1;
    }
    return c;
}

int BSearch2(int* a, int n, int x)
{
    int L = 0, R = n - 1, m, c = 0;
    while (L < R) {
        m = (int)(floor((L + R) / 2));
        c++;
        if (a[m] < x)
            L = m + 1;
        else
            R = m;
    }
    c++; // if (a[R] == x)
    return c;
}

int BSearchAll1(int* a, int n, int x)
{
    int L = 0, R = n - 1, m, c = 0, i;
    bool found = false;
    while (L <= R) {
        m = (int)(floor((L + R) / 2));
        c++;
        if (a[m] == x) {
            found = true;
            break;
        }
        c++;
        if (a[m] < x)
            L = m + 1;
        else
            R = m - 1;
    }

    if (found) {
        i = m + 1;
        while (a[m] == a[i]) {
            c++;
            i++;
        }
        c++; // while end
        i = m - 1;
        while (a[m] == a[i]) {
            c++;
            i--;
        }
        c++; // while end
    }
    return c;
}

int BSearchAll2(int* a, int n, int x)
{
    int L = 0, R = n - 1, m, c = 0;
    while (L < R) {
        m = (int)(floor((L + R) / 2));
        c++;
        if (a[m] < x)
            L = m + 1;
        else
            R = m;
    }

    c++; // if (a[R] == x)
    if (a[R] == x) {
        int i = m + 1;
        c++;
        while (a[m] == a[i]) {
            c++;
            i++;
        }
    }
    return c;
}

void BSearch1Pos(int* a, int n, int x)
{
    int L = 0, R = n - 1, m;
    bool found = false;
    cout << "\n\tKey of search = " << x << endl;
    while (L <= R) {
        m = (int)(floor((L + R) / 2));
        if (a[m] == x) {
            found = true;
            break;
        }
        if (a[m] < x)
            L = m + 1;
        else
            R = m - 1;
    }
    if (found)
        cout << "\tPosition = " << m;
    else
        cout << "\tCant find element " << x << endl;
}

void BSearch2Pos(int* a, int n, int x)
{
    int L = 0, R = n - 1, m;
    cout << "\n\tKey of search = " << x << endl;
    while (L < R) {
        m = (int)(floor((L + R) / 2));
        if (a[m] < x)
            L = m + 1;
        else
            R = m;
    }
    if (a[R] == x) {
        cout << "\tPosition = " << R;
    } else {
        cout << "\tCant find element " << x << endl;
    }
}

void BSearchAll1Pos(int* a, int n, int x)
{
    int L = 0, R = n - 1, m, i;
    bool found = false;
    cout << "\n\tKey of search = " << x << endl;
    while (L <= R) {
        m = (int)(floor((L + R) / 2));
        if (a[m] == x) {
            found = true;
            break;
        }
        if (a[m] < x)
            L = m + 1;
        else
            R = m - 1;
    }

    if (found) {
        cout << "\tPosition = " << m;
        i = m + 1;
        while (a[m] == a[i]) {
            cout << "\tPosition = " << i;
            i++;
        }
        i = m - 1;
        while (a[m] == a[i]) {
            cout << "\tPosition = " << i;
            i--;
        }
    } else {
        cout << "\tCant find element " << x << endl;
    }
}

void BSearchAll2Pos(int* a, int n, int x)
{
    int L = 0, R = n - 1, m, i;
    cout << "\n\tKey of search = " << x << endl;
    while (L < R) {
        m = (int)(floor((L + R) / 2));
        if (a[m] < x)
            L = m + 1;
        else
            R = m;
    }

    if (a[R] == x) {
        cout << "\tPosition = " << R;
        i = R + 1;
        while (a[R] == a[i]) {
            cout << "\tPosition = " << i;
            i++;
        }
    } else {
        cout << "\tCant find element " << x << endl;
    }
}

bool less_tel1(telephone x, telephone y) // Сортировка по номеру (убывание)
{
    int key;
    if (x.number < y.number)
        key = true;
    else {
        if (x.number > y.number)
            key = false;
    }
    return key;
}

bool less_tel2(telephone x, telephone y)
{
    int key; // Сортировка по алфавиту (имена), а имена по номеру по убыванию
    if (x.name < y.name)
        key = true;
    else {
        if (x.name > y.name)
            key = false;
        else {
            if (x.number > y.number)
                key = true;
            else
                key = false;
        }
    }
    return key;
}

void StructLineOutput(telephone x)
{
    cout << "\t| " << setw(3) << x.id << " | " << setw(10) << x.number << " | "
         << setw(14) << x.name << " | " << setw(14) << x.surname << endl;
}

void HeaderOutput()
{
    cout << "\t| " << setw(3) << "id"
         << " | " << setw(10) << "number"
         << " | " << setw(14) << "name"
         << " | " << setw(14) << "surname" << endl;
}

void BSearchAll2Number(telephone* a, int* index_sorted, int n, long long x)
{
    int L = 0, R = n - 1, m;
    while (L < R) {
        m = (int)(floor((L + R) / 2));
        if (a[index_sorted[m]].number < x) {
            L = m + 1;
        } else
            R = m;
    }

    if (a[index_sorted[R]].number == x) {
        int i = R;
        do {
            StructLineOutput(a[index_sorted[i]]);
            i++;
            if (R == n - 1)
                break;
        } while (a[index_sorted[R]].number == a[index_sorted[i]].number);
    } else
        cout << "\tCant find this number :(" << endl;
    cout << "\t";
}

void BSearchAll2Name(telephone* a, int* index_sorted, int n, string x)
{
    int L = 0, R = n - 1, m;
    while (L < R) {
        m = (int)(floor((L + R) / 2));
        if (a[index_sorted[m]].name < x) {
            L = m + 1;
        } else
            R = m;
    }

    if (a[index_sorted[R]].name == x) {
        int i = R;
        do {
            StructLineOutput(a[index_sorted[i]]);
            i++;
            if (R == n - 1)
                break;
        } while (a[index_sorted[i]].name == x);
    } else
        cout << "\tCant find this name :(" << endl;
    cout << "\t";
}
