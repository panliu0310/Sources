#include <stdio.h>
#include <stdlib.h>

void Read(char A[][5], int N)
{
	printf("Input all strings: ");
	for (int i = 0; i < N; i++) {
		scanf("%s", A[i]);
		A[i][4] = '\0';
	}
}

void PrintA(char A[][5], int N)
{
	for (int i = 0; i < N; i++) {
		printf("%s ", A[i]);
	}
	printf("\n");
}

void PrintA_in_sort(char A[][5], int N, int round)
{
	printf("After Round-%d: ", round);
	for (int i = 0; i < N; i++) {
		printf("%s ", A[i]);
	}
	printf("\n");
}

void Selection_sort(char A[][5], int N);

int main()
{
	int N;
	printf("Enter how many strings: ");
	scanf("%d", &N);
	char A[300][5]; // A[i][4] stores '\0' to be the end of one string.

	Read(A, N);
	printf("Initial Array: ");
	PrintA(A, N);

	Selection_sort(A, N);
	return 0;
}

void Selection_sort(char A[][5], int N)
{
	int B[300][5];
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 5; j++)
			B[i][j] = A[i][j];

	int round = 0;
	for (int i = 0; i < N; i++) {
		for (int radix = 3; radix >= 0; radix--) {
			int min = i;
			for (int j = i + 1; j < N; j++)
				if (B[j][radix] < B[min][radix])
					min = j;
			for (int ti = 0; ti < 4; ti++) {
				int temp[5]; char temps[5];
				temp[ti] = B[i][ti]; temps[ti] = A[i][ti];
				B[i][ti] = B[min][ti]; A[i][ti] = A[min][ti];
				B[min][ti] = temp[ti]; A[min][ti] = temps[ti];
			}
		}
		PrintA_in_sort(A, N, round++);
	}
}