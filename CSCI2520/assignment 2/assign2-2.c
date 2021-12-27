#include <stdio.h>
#include <stdlib.h>

void Read(int* num, int N)
{
	printf("Input all strings: ");
	for (int i = 0; i < N; i++) {
		scanf_s("%d", &num[i]);
	}
}

void PrintNum(int* num, int N, int cnt)
{
	printf("Final result: ");
	for (int i = 0; i < N; i++) {
		printf("%d ", num[i]);
	}
	printf("\nCalled times: %d\n", cnt);
}

int quickSort(int* num, int start, int end);

int main()
{
	int N;
	printf("Enter how many strings: ");
	scanf_s("%d", &N);
	int* num = (int*)malloc(sizeof(int) * N);

	Read(num, N);
	int call_cnt = quickSort(num, 0, N - 1);
	PrintNum(num, N, call_cnt);

	return 0;
}

// Please finish this function implementation.
int quickSort(int* num, int start, int end)
{
	int count = 1;
	if (start == end)
		return count;
	int lh = start + 1, rh = end, pivot = start;
	do {
		while (lh < rh && num[rh] >= num[pivot])
			rh--;
		while (lh < rh && num[lh] < num[pivot])
			lh++;
		if (lh != rh) {
			int tmp = num[lh];
			num[lh] = num[rh];
			num[rh] = tmp;
		}
	} while (lh != rh);
	if (num[pivot] > num[lh]) {
		int tmp2 = num[pivot];
		num[pivot] = num[lh];
		num[lh] = tmp2;
		pivot = lh;
	}
	if (pivot == start)
		count = quickSort(num, start, pivot) + quickSort(num, pivot + 1, end);
	else
		if (pivot == end)
			count = quickSort(num, start, pivot - 1) + quickSort(num, pivot, end);
		else
			count = quickSort(num, start, pivot - 1) + quickSort(num, pivot + 1, end);
	return count + 1;
}