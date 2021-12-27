#include <stdio.h>
#include <stdlib.h>

typedef enum { true, false, maybe } Keys;
typedef Keys ElementType;

void Read(ElementType A[], int N)
{
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
}

void MySort(ElementType A[], int N);

void PrintA(ElementType A[], int N)
{
    int i, k;

    k = i = 0;
    for (; i < N && A[i] == false; i++);
    if (i > k)
        printf("false in A[%d]-A[%d]\n", k, i - 1);
    k = i;
    for (; i < N && A[i] == maybe; i++);
    if (i > k)
        printf("maybe in A[%d]-A[%d]\n", k, i - 1);
    k = i;
    for (; i < N && A[i] == true; i++);
    if (i > k)
        printf("true in A[%d]-A[%d]\n", k, i - 1);
    if (i < N)
        printf("Wrong Answer\n");
}

int main()
{
    int N;
    ElementType* A;

    scanf("%d", &N);
    A = (ElementType*)malloc(N * sizeof(ElementType));
    Read(A, N);
    MySort(A, N);
    PrintA(A, N);
    return 0;
}

/* Please finish the implementtion of this function. */
void MySort(ElementType A[], int N)
{
    // To have O(N) time complexity, we use counting sort
    int truecount = 0, falsecount = 0, maybecount = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] == true) truecount++;
        if (A[i] == false) falsecount++;
        if (A[i] == maybe) maybecount++;
    }
    for (int i = 0; i < N; i++) {
        if (falsecount > 0) {
            A[i] = false;
            falsecount--;
        }
        else if (maybecount > 0) {
            A[i] = maybe;
            maybecount--;
        }
        else {
            A[i] = true;
            truecount--;
        }
    }
}