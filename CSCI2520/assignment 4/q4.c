#include <stdio.h>
#include <stdlib.h>

long factorial(int n) {
	if (n == 0)return 1;
	else
		return n * factorial(n - 1);
}

int sumArray(int* strengtharray, int* result, int k) {
	int sum = 0;
	for (int i = 0; i < k; i++)
		sum = sum + strengtharray[result[i]];
	return sum;
}

int minArray(int* weaknessarray, int* result, int k) {
	int min = 10000;
	for (int i = 0; i < k; i++)
		if (weaknessarray[result[i]] < min)
			min = weaknessarray[result[i]];
	return min;
}

int power(int* strengtharray, int* weaknessarray, int* result, int k) {
	return sumArray(strengtharray, result, k) * minArray(weaknessarray, result, k);
}

void insert(int* heaparray, int* heapsize, int p) {
	int i;
	for (i = ++heapsize[0]; heaparray[i / 2] < p; i /= 2)
		heaparray[i] = heaparray[i / 2];
	heaparray[i] = p;
	heapsize[0]++;
}

//Note that nCk is equalvalent to pick 1 first, then (n-1)C(k-1). So we can call a recursive function
void combination_insert_heap(int* strengtharray, int* weaknessarray, int* combinationarray, int* combinationresult, int start, int index, int end, int k, int kflag, int* heaparray, int* heapsize) {//nCk
	if (kflag == 0) {//stop the combination_nCk
		//printf("combination: %d %d %d \n", combinationresult[0], combinationresult[1], combinationresult[2]); //for checking
		insert(heaparray, heapsize, power(strengtharray, weaknessarray, combinationresult, k));
		return;
	}
	for (int i = index; i < index + k && i <= end; i++) {//i denote the first element we pick
		combinationresult[start] = combinationarray[i];
		combination_insert_heap(strengtharray, weaknessarray, combinationarray, combinationresult, start+1, i+1, end, k, kflag-1, heaparray, heapsize);//comb{remaining elements}
	}
	//Example: 5C3
	//comb{1,2,3,4,5}
	//{1,comb{2,3,4,5}},                                    {2,comb{3,4,5}},              {3,comb{4,5}}
	//{1,2,comb{3,4,5}},      {1,3,comb{4,5}},{1,4,comb{5}},{2,3,comb{4,5}},{2,4,comb{5}},{3,4,comb{5}}
	//{1,2,3},{1,2,4},{1,2,5},{1,3,4},{1,3,5},{1,4,5},      {2,3,4},{2,3,5},{2,4,5}       {3,4,5}
	//combination_nCk(array,reult,0,4,5,3)
	//                   i   =   0                                    i = 1                  i=2
	//combination_nCk(array,result,1,4,5,3)
	//        i   =   1            i = 2        i=3             i  =   2      i=3            i=3
	//combination_nCk(array,result,2,4,5,3)
	// i = 2    i = 3   i = 4   i = 3   i = 4   i = 4         i = 3   i = 4   i = 4         i = 4

}

int main() {
	int n, k;
	scanf_s("%d", &n); scanf_s("%d", &k);
	int* strengtharray = (int*)malloc(n * sizeof(int));
	int* weaknessarray = (int*)malloc(n * sizeof(int));
	int* combinationarray = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		combinationarray[i] = i;
	for (int i = 0; i < n; i++)
		scanf_s("%d", &strengtharray[i]);
	for (int i = 0; i < n; i++)
		scanf_s("%d", &weaknessarray[i]);
	int* combinationresult = (int*)malloc(k * sizeof(int));
	int* heaparray = (int*)malloc(((factorial(n)/(factorial(n-k)*factorial(k)))+1) * sizeof(int));
	int* heapsize = (int*)malloc(sizeof(int)); heapsize[0] = 0;
	heaparray[0] = 10000;
	combination_insert_heap(strengtharray, weaknessarray, combinationarray, combinationresult, 0, 0, 4, k, k, heaparray, heapsize);
	printf("%d\n", heaparray[1]);
	//for (int i = 1; i <= ((factorial(n) / (factorial(n - k) * factorial(k))) + 1); i++) //for checking
	//printf("%d ", heaparray[i]);
	return 0;
}