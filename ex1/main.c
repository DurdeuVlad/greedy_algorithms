#include <stdio.h>

typedef struct {
    int a, b, cost;
} Muchie;



void sort(Muchie muchii[100], int n){
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(muchii[i].cost>muchii[j].cost){
                Muchie aux=muchii[i];
                muchii[i]=muchii[j];
                muchii[j]=aux;
            }
}



void primsAlgorithm(Muchie muchii[100],int i, int *n) {
    // check if by adding the least expensive edge we get a cycle
    if(i==0){
        primsAlgorithm(muchii, i+1, n);
    }
    else if(i==*n){
        return;
    }
    else{
        // check if by adding the least expensive edge we get a cycle
        int viz[100]={0};
        viz[muchii[i].a]=1;
        viz[muchii[i].b]=1;
        int ok=1;
        for(int j=0;j<i;j++){
            if(muchii[j].b==muchii[i].b && viz[muchii[j].a]==1 || muchii[j].a==muchii[i].b && viz[muchii[j].b]==1 || muchii[j].a==muchii[i].a && viz[muchii[j].b]==1 || muchii[j].b==muchii[i].a && viz[muchii[j].a]==1){
                ok=0;
                break;
            }
        }
        if(ok==0) {
            // if we get a cycle, we remove the edge
            for (int j = i; j < *n - 1; j++)
                muchii[j] = muchii[j + 1];
            *n = *n - 1;
            primsAlgorithm(muchii, i, n);
            }
        else
            primsAlgorithm(muchii, i+1, n);
    }


}

void printArbore(Muchie arbore[100], int n){
    for(int i=0;i<n;i++)
        printf("%d %d cost: %d\n", arbore[i].a, arbore[i].b, arbore[i].cost);
}

int main() {
    Muchie muchii[100]={{1, 2, 5}, {1, 3, 10}, {2, 3, 4}, {2, 4, 11}, {3, 4, 5}, {3, 2, 2}};
    int n=6;
    sort(muchii, n);
    primsAlgorithm(muchii, 0, &n);
    printArbore(muchii, n);
    return 0;
}
