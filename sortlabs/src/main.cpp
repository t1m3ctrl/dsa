#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include "../include/graphic.h"

using namespace std;

void FillInc(int* a, int n);
void FillDec(int* a, int n);
void FillRand(int* a, int n);

int CheckSum(int* a, int n);
int RunNumber(int* a, int n);

void TableHeaderOutput();
void TableHeaderOutput_l5();
void TableHeaderOutput_l6();
void PrintMas(int* a, int n);

void swap(int* a, int* b);

float MiddleSerial(int* a, int n, int length);

int SelectSort(int* a, int n);
int BubbleSort(int* a, int n);
int ShakerSort(int* a, int n);
int InsertSort(int* a, int n);
int ShellSort(int* a, int n, int* h, int m_size);

int main()
{
    srand(time(NULL));
    int *a, n = 100, mc = 0, i;
    int m_size, *h, j;

    // int* c_select = new int[5];
    // int* c_bubble = new int[5];
    // int* c_shaker = new int[5];
    int* c_insert = new int[5];
    int* c_shell = new int[5];

    // TableHeaderOutput();
    // TableHeaderOutput_l5();
    TableHeaderOutput_l6();

    for (i = 0; i < 5; i++) {
        a = new int[n];
        printf("\t| %3d |", n);

        m_size = (int)(floor(log2(n))) - 1;
        h = new int[m_size];
        h[0] = 1;
        for (j = 1; j < m_size; j++)
            h[j] = 2 * h[j - 1] + 1;

        printf("  %6d       |", m_size);

        // FillRand(a, n);
        // mc = SelectSort(a, n);
        // c_select[i] = mc;
        // printf("  %11d  |", mc);

        // FillRand(a, n);
        // mc = BubbleSort(a, n);
        // c_bubble[i] = mc;
        // printf("  %13d  |", mc);

        // FillRand(a, n);
        // mc = ShakerSort(a, n);
        // c_shaker[i] = mc;
        // printf("  %12d  |", mc);

        FillRand(a, n);
        mc = InsertSort(a, n);
        c_insert[i] = mc;
        printf("  %13d  |", mc);

        FillRand(a, n);
        mc = ShellSort(a, n, h, m_size);
        c_shell[i] = mc;
        printf("  %12d  |", mc);

        // printf("\n\t+-----+---------------+-----------------+----------------+-"
        //        "--"
        //        "--------------+\n");

        printf("\n\t+-----+---------------+-----------------+----------------+"
               "\n");

        n += 100;
    }

    n = 150;

    // puts("");
    // a = new int[n];
    // FillRand(a, n);
    // PrintMas(a, n);
    // SelectSort(a, n);
    // puts("\n\tSorted rand (select)");
    // PrintMas(a, n);

    // puts("");
    // a = new int[n];
    // FillRand(a, n);
    // PrintMas(a, n);
    // BubbleSort(a, n);
    // puts("\n\tSorted rand (bubble)");
    // PrintMas(a, n);

    // puts("");
    // a = new int[n];
    // FillRand(a, n);
    // PrintMas(a, n);
    // ShakerSort(a, n);
    // puts("\n\tSorted rand (shaker)");
    // PrintMas(a, n);

    puts("");
    a = new int[n];
    FillRand(a, n);
    PrintMas(a, n);
    InsertSort(a, n);
    puts("\n\tSorted rand (insert)");
    PrintMas(a, n);

    puts("");
    a = new int[n];
    FillRand(a, n);
    PrintMas(a, n);

    m_size = (int)(floor(log2(n))) - 1;
    h = new int[m_size];
    puts("Steps array");
    h[0] = 1;
    printf("%d ", h[0]);
    for (i = 1; i < m_size; i++) {
        h[i] = 2 * h[i - 1] + 1;
        printf("%d ", h[i]);
    }

    ShellSort(a, n, h, m_size);
    puts("\n\tSorted rand (Shell)");
    PrintMas(a, n);

    // WindowOutput4(c_select, c_bubble, c_shaker, c_insert);

    WindowOutput2(c_insert, c_shell);

    delete[] a;
    // delete[] c_select;
    // delete[] c_bubble;
    // delete[] c_shaker;
    delete[] c_insert;
    delete[] c_shell;

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

void TableHeaderOutput()
{
    printf("\n\t+-----+-----------+-----------+-----------+-----------+--------"
           "---+-----------+\n");
    printf("\t|     |         M(f) + C(f) bubble (red)  |         M(f) + C(f) "
           "shaker (blue) |\n");
    printf("\t+  n  "
           "+-----------+-----------+-----------+-----------+-----------+------"
           "-----+\n");
    printf("\t|     |    Dec    |    Rand   |    Inc    |    Dec    |    Rand  "
           " |    Inc    |\n");
    printf("\t+-----+-----------+-----------+-----------+-----------+----------"
           "-+-----------+\n");
}

void TableHeaderOutput_l5()
{
    printf("\n"
           "\t+-----+---------------+-----------------+----------------+-------"
           "----------+\n");
    printf("\t|  n  |  Select(red)  |  Bubble(green)  |  Shaker(blue)  |  "
           "Insert(white)  |\n");
    printf("\t+-----+---------------+-----------------+----------------+-------"
           "----------+\n");
}

void TableHeaderOutput_l6()
{
    printf("\n"
           "\t+-----+---------------+-----------------+----------------+\n");
    printf("\t|  n  |       k       |   Insert(red)   |  Shell(blue)   |\n");
    printf("\t+-----+---------------+-----------------+----------------+\n");
}

void PrintMas(int* a, int n)
{
    int i;
    puts("\tArray:");
    printf("\t");
    for (i = 0; i < n; i++) {
        printf("%3d ", a[i]);
    }
    puts("");
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
        for (j = i - 1; j >= 0; j--) {
            c++;
            if (tmp > a[j])
                break;
            a[j + 1] = a[j];
            m++;
        }
        a[j + 1] = tmp;
        m++;
    }
    return (m + c);
}

int ShellSort(int* a, int n, int* h, int m_size)
{
    int i, k, j, tmp, c = 0, m = 0;

    for (k = m_size - 1; k >= 0; k--) {
        for (i = h[k]; i < n; i++) {
            m++;
            tmp = a[i];
            for (j = i - h[k]; j >= 0;) {
                c++;
                if (tmp > a[j])
                    break;
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