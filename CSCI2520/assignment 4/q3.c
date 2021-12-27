#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Read(int** AdjacencyMatrix, int M, int N) {
    for (int i = 0; i < M; i++) {
        int x, y, w;
        scanf("%d", &x);// If scanf doesn't work, may try scanf_s
        scanf("%d", &y);
        scanf("%d", &w);
        AdjacencyMatrix[x - 1][y - 1] = w;
        AdjacencyMatrix[y - 1][x - 1] = w;
        //check
        //for (int i = 0; i < N; i++) {
        //   for (int j = 0; j < N; j++)
        //        printf("%10d ", AdjacencyMatrix[i][j]);
        //   printf("\n");
        //}
    }
}

int maxArray(int* array, int N) {
    int max = array[0];
    for (int i = 0; i < N; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

void DijkstraAlgorithmReturnMax(int** AdjacencyMatrix, int* DijkstraMax, int N) {
    int* temp = (int*)malloc(N * sizeof(int));
    int* vflag = (int*)malloc(N * sizeof(int));
    for (int v = 0; v < N; v++) {
        for (int i = 0; i < N; i++) {
            vflag[i] = 0;
            temp[i] = INT_MAX;
        }
        temp[v] = 0;
        for (int j = 0; j < N; j++) {
            if (AdjacencyMatrix[v][j] != INT_MAX && temp[j] != 0)  
                temp[j] = AdjacencyMatrix[v][j];      
        }
        //check
        //for (int i = 0; i < N; i++) {
        //    printf('%d ', temp[i]);
        //    printf(' Printing temp\n');
        //}
        while (1) {
            int p = INT_MAX;//p is the position of minimum value in temp except its flag is 1
            int min = INT_MAX;
            for (int i = 0; i < N; i++)
                if (temp[i] < min && vflag[i] == 0) {
                    min = temp[i];
                    p = i;
                }
            if (p == INT_MAX)break;
            for (int j = 0; j < N; j++)
                if ((AdjacencyMatrix[p][j] < INT_MAX) && (temp[p] + AdjacencyMatrix[p][j] < temp[j]))
                    temp[j] = temp[p] + AdjacencyMatrix[p][j];
            vflag[p] = 1;
            //check
            //for (int i = 0; i < N; i++) {
            //    printf('%d ', temp[i]);
            //    printf(' Printing temp\n');
            //}
        }
        DijkstraMax[v] = maxArray(temp, N);
        //check
        //for (int i = 0; i < N; i++) {
        //    printf('%d ', DijkstraMax[i]);
        //    printf(' Printing DijkstraMax\n');
        //}
    }
}

int main() {
    int N, M;
    scanf("%d", &N); scanf("%d", &M);// If scanf doesn't work, may try scanf_s
    //initializing AdjacencyMatrix
    int** AdjacencyMatrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        AdjacencyMatrix[i] = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            AdjacencyMatrix[i][j] = INT_MAX;
    //Read
    Read(AdjacencyMatrix, M, N);
    //initializing DijkstraMax
    int* DijkstraMax = (int*)malloc(N * sizeof(int));
    DijkstraAlgorithmReturnMax(AdjacencyMatrix, DijkstraMax, N);
    printf("%d", maxArray(DijkstraMax, N));
    return 0;
}