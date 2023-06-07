#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

#define N 5

typedef struct tData
{
    int Data;
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

typedef struct Queue
{
    List *head;
    List *tail;
} Queue;

List *ListFillInc(int n);
List *ListFillDec(int n);
List *ListFillRand(int n);

Queue *InitQueue(int data);
Queue *ListFillIncQ(int n);
Queue *ListFillDecQ(int n);
Queue *ListFillRandQ(int n);

int isEmpty(List *head);
void ListCheck(List *head);
void ListFree(List *head);
void Push(List **head, int data);
int Pop(List **head); // pop(&head) = dequeue(&head);
void Enqueue(Queue *c, int data);
int ListCheckSum(List *head);
int ListCheckRunNumber(List *head);

int MergeSort(List **S);
int Split(List **S, List **a, List **b);
int Merge(List *&a_head, int &q, List *&b_head, int &r, Queue &c);

void TableHeaderOutput();

int main()
{
    srand(time(NULL));
    int n = 100;
    int mc = 0, i;
    List *head = new List;
    Queue *queue = new Queue;

    int *a;

    TableHeaderOutput();

    for (i = 0; i < N; i++)
    {
        a = new int[n];
        head = new List;

        cout << "\t| " << setw(5) << n;

        head = ListFillDec(n);
        mc = MergeSort(&head);
        cout << " | " << setw(9) << mc;

        head = ListFillRand(n);
        mc = MergeSort(&head);
        cout << " | " << setw(9) << mc;

        head = ListFillInc(n);
        mc = MergeSort(&head);
        cout << " | " << setw(9) << mc << " |\n";
        ListFree(head);

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

    delete[] a;
    return 0;
}

int isEmpty(List *head)
{
    return head == NULL;
}

void Push(List **head, int data)
{
    List *p;
    p = new List;
    p->Data.Data = data;
    p->next = *head;
    *head = p;
}

int Pop(List **head)
{
    List *p;
    p = *head;
    int value = p->Data.Data;
    *head = p->next;
    delete p;
    return value;
}

void Enqueue(Queue *c, int data)
{
    List *p;
    p = new List;
    p->Data.Data = data;
    p->next = NULL;
    if (c->tail == NULL)
        c->head = p;
    else
        ((c)->tail)->next = p;
    c->tail = p;
}

List *ListFillDec(int n)
{
    List *head = NULL;
    int i = 0;
    for (i = 0; i < n; i++)
        Push(&head, i);
    return head;
}

List *ListFillInc(int n)
{
    List *head = NULL;
    int i = n - 1;
    for (i = n - 1; i >= 0; i--)
        Push(&head, i);
    return head;
}

List *ListFillRand(int n)
{
    List *head = NULL;
    int i = 0;
    for (i = 0; i < n; i++)
        Push(&head, rand() % n);
    return head;
}

Queue *ListFillIncQ(int n)
{
    Queue *queue = new Queue;
    for (int i = 0; i < n; i++)
        Enqueue(queue, i);
    return queue;
}

Queue *ListFillDecQ(int n)
{
    Queue *queue = new Queue;
    int i = 0;
    for (i = n - 1; i >= 0; i--)
        Enqueue(queue, i);
    return queue;
}

Queue *ListFillRandQ(int n)
{
    Queue *queue = new Queue;
    int i = 0;
    for (i = n - 1; i >= 0; i--)
        Enqueue(queue, rand() % n);
    return queue;
}

void ListCheck(List *head)
{
    List *p;
    p = head;
    cout << "\n\tOur list " << endl
         << "\t";
    while (p != NULL)
    {
        cout << setw(5) << p->Data.Data;
        p = p->next;
    }
    cout << endl;
}

int ListCheckSum(List *head)
{
    List *p;
    int sum = 0;
    p = head;
    while (p != NULL)
    {
        sum += p->Data.Data;
        p = p->next;
    }
    return sum;
}

int ListCheckRunNumber(List *head)
{
    List *p;
    int serial = 1;
    p = head;
    while (p->next != NULL)
    {
        if ((p->Data.Data) < (p->next->Data.Data))
            serial++;
        p = p->next;
    }
    return serial;
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

int Split(List **S, List **a, List **b)
{
    List *k;
    List *p;
    *a = *S;
    *b = (*S)->next;
    k = *a;
    p = *b;
    int n = 1;

    while (p != NULL)
    {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    return n;
}

int MergeSort(List **S)
{
    List *a, *b;
    a = b = NULL;
    Queue c[2];
    int mc = 0;
    int n = Split(S, &a, &b);
    int p = 1;
    int q;
    int r;
    while (p < n)
    {
        c[0].tail = (List *)&c[0].head;
        c[1].tail = (List *)&c[1].head;
        int i = 0;
        int m = n;
        while (m > 0)
        {
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

int Merge(List *&a_head, int &q, List *&b_head, int &r, Queue &c)
{
    int mc = 0;
    while ((q != 0) && (r != 0))
    {
        mc++;
        if ((a_head->Data.Data) <= (b_head->Data.Data))
        {
            Enqueue(&c, Pop(&a_head));
            mc += 2;
            q--;
        }
        else
        {
            Enqueue(&c, Pop(&b_head));
            mc += 2;
            r--;
        }
    }
    while (q > 0)
    {
        Enqueue(&c, Pop(&a_head));
        mc += 2;
        q--;
    }
    while (r > 0)
    {
        Enqueue(&c, Pop(&b_head));
        mc += 2;
        r--;
    }
    return mc;
}

void TableHeaderOutput()
{
    cout << "\n\t+-------+-----------+-----------+-----------+\n";
    cout << "\t|       |      M(f) + C(f) Merge (RED)      |\n";
    cout << "\t|   n   +-----------+-----------+-----------+\n";
    cout << "\t|       |    Dec    |    Rand   |    Inc    |\n";
    cout << "\t+-------+-----------+-----------+-----------+\n";
}