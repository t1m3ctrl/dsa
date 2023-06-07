#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <iomanip>
#include "../include/graphic.h"

using namespace std;

#define N 5 // 700 - max how can i fix this?

typedef struct StructList {
    struct StructList* next;
    int data;
} List;

typedef struct Queue {
    List* head;
    List* tail;
} Queue;

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
int ShellSort(int* a, int n);
int QuickSortV1(int* a, int L, int R);
int QuickSortV2(int* a, int L, int R);

int heapify(int* a, int L, int R);
int HeapSort(int* a, int n);

int BSearch1(int* a, int n, int x);
int BSearch2(int* a, int n, int x);
int BSearchAll1(int* a, int n, int x);
int BSearchAll2(int* a, int n, int x);

void BSearch1Pos(int* a, int n, int x);
void BSearch2Pos(int* a, int n, int x);
void BSearchAll1Pos(int* a, int n, int x);
void BSearchAll2Pos(int* a, int n, int x);

List* ListFillInc(int n);
List* ListFillDec(int n);
List* ListFillRand(int n);

Queue* InitQueue(int data);
Queue* ListFillIncQ(int n);
Queue* ListFillDecQ(int n);
Queue* ListFillRandQ(int n);

int isEmpty(List* head);
void ListCheck(List* head);
void ListFree(List* head);
void Push(List** head, int data);
int Pop(List** head); // pop(&head) = dequeue(&head);
void Enqueue(Queue* c, int data);
int ListCheckSum(List* head);
int ListCheckRunNumber(List* head);

int MergeSort(List** S);
int Split(List** S, List** a, List** b);
int Merge(List*& a_head, int& q, List*& b_head, int& r, Queue& c);

void TableHeaderOutput();

int main()
{
    srand(time(NULL));
    int n = 100;
    int mc = 0, i;
    List* head = new List;
    Queue* queue = new Queue;

    int* a;
    int alg_num = 4; // alg_num - количество алгоритмов, для которых
                     //  нужно нарисовать график

    int** c_array = new int*[alg_num];
    for (i = 0; i < alg_num; i++)
        c_array[i] = new int[N];

    // COLORS IN TABLE :
    // 1. RED
    // 2. AQUA
    // 3. FUCHSIA
    // 4. GREEN
    // 5. YELLOW
    // 6. BLUE
    // 7. OLIVE
    // 8. SILVER

    TableHeaderOutput();

    for (i = 0; i < N; i++) {
        a = new int[n];
        head = new List;

        cout << "\t| " << setw(5) << n;

        head = ListFillDec(n);
        mc = MergeSort(&head);
        cout << " | " << setw(9) << mc;

        head = ListFillRand(n);
        mc = MergeSort(&head);
        c_array[0][i] = mc;
        cout << " | " << setw(9) << mc;

        head = ListFillInc(n);
        mc = MergeSort(&head);
        cout << " | " << setw(9) << mc << " |\n";
        ListFree(head);

        FillRand(a, n);
        mc = ShellSort(a, n);
        c_array[1][i] = mc;

        FillRand(a, n);
        mc = HeapSort(a, n);
        c_array[2][i] = mc;

        FillRand(a, n);
        mc = QuickSortV1(a, 0, n);
        c_array[3][i] = mc;

        cout << "\t+-------+-----------+-----------+-----------+\n";
        n += 100;
    }

    n = 10;

    head = NULL;
    head = ListFillRand(n);
    ListCheck(head);
    cout << "\tCheckSum = " << ListCheckSum(head) << endl;
    cout << "\tRunNumber = " << ListCheckRunNumber(head) << endl;
    MergeSort(&head);
    ListCheck(head);
    cout << "\tCheckSum = " << ListCheckSum(head) << endl;
    cout << "\tRunNumber = " << ListCheckRunNumber(head) << endl;
    ListFree(head);

    queue->head = NULL;
    queue->tail = NULL;
    queue = ListFillRandQ(n);
    ListCheck(queue->head);
    cout << "\tCheckSum = " << ListCheckSum(queue->head) << endl;
    cout << "\tRunNumber = " << ListCheckRunNumber(queue->head) << endl;
    MergeSort(&queue->head);
    ListCheck(queue->head);
    cout << "\tCheckSum = " << ListCheckSum(queue->head) << endl;
    cout << "\tRunNumber = " << ListCheckRunNumber(queue->head) << endl;
    ListFree(queue->head);

    WindowOutput(c_array, alg_num, N);

    delete[] a;
    delete[] c_array;
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
    cout << "\tArray:" << endl << "\t";
    for (i = 0; i < n; i++)
        cout << setw(4) << a[i];
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
            c++;
            while ((j >= 0) && (tmp > a[j])) {
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

int heapify(int* a, int L, int R)
{
    int x = a[L]; // x - root (koren')
    int i = L;    // root index
    int j;        // 2i
    int mc = 1;
    while (true) {
        j = 2 * i + 1;
        if (j > R) {
            break;
        }
        mc++;
        if ((j < R) && (a[j + 1] <= a[j])) {
            j++;
        }
        mc++;
        if (x <= a[j]) {
            break;
        }
        a[i] = a[j];
        mc++;
        i = j;
    }
    a[i] = x;
    mc++;
    return (mc);
}

int HeapSort(int* a, int n)
{
    int mc = 0;
    int L = (int)(floor(n / 2));
    while (L >= 0) {
        mc += heapify(a, L, n - 1);
        L--;
    }
    int R = n - 1;
    while (R > 0) {
        swap(&a[0], &a[R]);
        mc += 3;
        mc += heapify(a, 0, R - 1);
        R--;
    }
    return mc;
}

int QuickSortV1(int* a, int L, int R)
{
    int x = a[(L + R) / 2];
    int i = L;
    int j = R;
    int mc = 1;
    while (i <= j) {
        mc++;
        while (a[i] < x)
            i++, mc++;
        mc++;
        while (a[j] > x)
            j--, mc++;
        if (i <= j) {
            swap(&a[i], &a[j]);
            mc += 3;
            i++;
            j--;
        }
    }

    if (L < j) {
        mc += QuickSortV1(a, L, j);
    }
    if (i < R) {
        mc += QuickSortV1(a, i, R);
    }
    return mc;
}

int QuickSortV2(int* a, int L, int R)
{
    int mc = 1;

    while (L < R) {
        int i = L, j = R;
        int x = a[L];
        while (i <= j) {
            mc++;
            while (a[i] < x)
                i++, mc++;
            mc++;
            while (a[j] > x)
                j--, mc++;
            if (i <= j) {
                swap(&a[i], &a[j]);
                mc += 3;
                i++;
                j--;
            }
        }
        if ((j - L) > (R - i)) {
            mc += QuickSortV2(a, i, R);
            R = j;
        } else {
            mc += QuickSortV2(a, L, j);
            L = i;
        }
    }
    return mc;
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

int isEmpty(List* head)
{
    return head == NULL;
}

void Push(List** head, int data)
{
    List* p;
    p = new List;
    p->data = data;
    p->next = *head;
    *head = p;
}

int Pop(List** head)
{
    List* p;
    p = *head;
    int value = p->data;
    *head = p->next;
    delete p;
    return value;
}

void Enqueue(Queue* c, int data)
{
    List* p;
    p = new List;
    p->data = data;
    p->next = NULL;
    if (c->tail == NULL)
        c->head = p;
    else
        ((c)->tail)->next = p;
    c->tail = p;
}

List* ListFillDec(int n)
{
    List* head = NULL;
    int i = 0;
    for (i = 0; i < n; i++)
        Push(&head, i);
    return head;
}

List* ListFillInc(int n)
{
    List* head = NULL;
    int i = n - 1;
    for (i = n - 1; i >= 0; i--)
        Push(&head, i);
    return head;
}

List* ListFillRand(int n)
{
    List* head = NULL;
    int i = 0;
    for (i = 0; i < n; i++)
        Push(&head, rand() % n);
    return head;
}

Queue* ListFillIncQ(int n)
{
    Queue* queue = new Queue;
    for (int i = 0; i < n; i++)
        Enqueue(queue, i);
    return queue;
}

Queue* ListFillDecQ(int n)
{
    Queue* queue = new Queue;
    int i = 0;
    for (i = n - 1; i >= 0; i--)
        Enqueue(queue, i);
    return queue;
}

Queue* ListFillRandQ(int n)
{
    Queue* queue = new Queue;
    int i = 0;
    for (i = n - 1; i >= 0; i--)
        Enqueue(queue, rand() % n);
    return queue;
}

void ListCheck(List* head)
{
    List* p;
    p = head;
    cout << "\n\tOur list " << endl << "\t";
    while (p != NULL) {
        cout << setw(4) << p->data;
        p = p->next;
    }
    cout << endl;
}

int ListCheckSum(List* head)
{
    List* p;
    int sum = 0;
    p = head;
    while (p != NULL) {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int ListCheckRunNumber(List* head)
{
    List* p;
    int serial = 1;
    p = head;
    while (p->next != NULL) {
        if ((p->data) < (p->next->data))
            serial++;
        p = p->next;
    }
    return serial;
}

void ListFree(List* head)
{
    List *p, *q;
    q = p = head;
    while (p != NULL) {
        p = q->next;
        delete q;
        q = p;
    }
    head = NULL;
}

int Split(List** S, List** a, List** b, int* n)
{
    int mc = 0;

    List* k;
    List* p;
    *a = *S;
    *b = (*S)->next;
    k = *a;
    p = *b;

    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
        mc += 2;
    }
    return mc;
}

int MergeSort(List** S)
{
    List *a, *b;
    a = b = NULL;
    Queue c[2];
    int n = 1;
    int mc = Split(S, &a, &b, &n);
    int p = 1;
    int q;
    int r;
    while (p < n) {
        c[0].tail = (List*)&c[0].head;
        c[1].tail = (List*)&c[1].head;
        int i = 0;
        int m = n;
        while (m > 0) {
            if (m >= p)
                q = p;
            else
                q = m;
            m -= q;
            if (m >= p)
                r = p;
            else
                r = m;
            m -= r;
            mc += Merge(a, q, b, r, c[i]);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p = 2 * p;
    }
    c[0].tail->next = NULL;
    *S = c[0].head;
    return mc;
}

int Merge(List*& a_head, int& q, List*& b_head, int& r, Queue& c)
{
    int mc = 0;
    while ((q != 0) && (r != 0)) {
        mc++;
        if ((a_head->data) <= (b_head->data)) {
            Enqueue(&c, Pop(&a_head));
            mc += 2;
            q--;
        } else {
            Enqueue(&c, Pop(&b_head));
            mc += 2;
            r--;
        }
    }
    while (q > 0) {
        Enqueue(&c, Pop(&a_head));
        mc += 2;
        q--;
    }
    while (r > 0) {
        Enqueue(&c, Pop(&b_head));
        mc += 2;
        r--;
    }
    return mc;
}

void TableHeaderOutput()
{
    cout << "\n\t+-------+-----------+-----------+-----------+\n";
    cout << "\t|       |      M(f) + C(f) Merge (RED) v1   |\n";
    cout << "\t|   n   +-----------+-----------+-----------+\n";
    cout << "\t|       |    Dec    |    Rand   |    Inc    |\n";
    cout << "\t+-------+-----------+-----------+-----------+\n";
}
