#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b, cost;
} Muchie;



void sort(Muchie muchii[100], int n){
    for(int i=0;i<n*(n-1)/2-1;i++)
        for(int j=i+1;j<n*(n-1)/2;j++)
            if(muchii[i].cost>muchii[j].cost){
                Muchie aux=muchii[i];
                muchii[i]=muchii[j];
                muchii[j]=aux;
            }
}
void printArbore(Muchie arbore[100], int n){
    for(int i=0;i<n*(n-1)/2;i++)
        printf("%d %d cost: %d\n", arbore[i].a, arbore[i].b, arbore[i].cost);
}

int muchieAlreadyExists(Muchie muchie[100], int a, int b, int n){
    for(int i=0;i<n*(n-1)/2;i++)
        if(muchie[i].a==a && muchie[i].b==b || muchie[i].a==b && muchie[i].b==a)
            return 1;
    return 0;
}


void generateFullGraph(Muchie muchii[100], int n){
    int k=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            muchii[k].a=i;
            muchii[k].b=j;
            muchii[k].cost=(rand() % n) * (rand() % 3+1)+1;
            k++;
        }
}

void generateMunchiiRandom(Muchie muchii[100], int n){
    for(int i=0;i<n;i++){
        int a, b, cost;
        do{
        a = rand() % n+1;
        b = rand() % n+1;
        cost = (rand() % n) * (rand() % 3+1)+1;
        } while(a==b || muchieAlreadyExists(muchii, a, b, n));
        printf("muchia %d: ", i+1);
        muchii[i].a = a;
        muchii[i].b = b;
        muchii[i].cost = cost;
    }
}

int isInViz(int viz[100], int node, int n){
    for(int i=0;i<n;i++)
        if(viz[i]==node)
            return 1;
    return 0;
}

Muchie getCheapestNode(Muchie muchii[100], int a, int viz[100], int n){
    Muchie minMuchie = {0, 0, 999999};
    for(int i=0;i<(n*(n-1)/2);i++)
        if(muchii[i].a==a && !isInViz(viz, muchii[i].b, n)){
            minMuchie=muchii[i];
            break;
        } else if(muchii[i].b==a && !isInViz(viz, muchii[i].a, n)){
            minMuchie=muchii[i];
            break;
        }
    if(minMuchie.cost==999999)
        printf("Nu exista muchie\n");
    return minMuchie;
}



void findTheLeastExpensiveCycleGreedy(Muchie muchii[100], int n, int start, int viz[100]){
    viz[0]=start;
    int iVis=0;
    for(int i=1;i<=n;i++){
        // we search for the first node in muchii that has viz[iVis] as a node
        Muchie minMuchie=getCheapestNode(muchii, viz[iVis], viz, n);
        // we add the node to viz
        iVis++;
        if(minMuchie.a==viz[iVis-1])
            viz[iVis]=minMuchie.b;
        else
            viz[iVis]=minMuchie.a;


        // and we add the other node to viz
        // we also check if the other node is already in viz

    }
}

int main() {
    Muchie muchii[100];
    // ={{1, 2, 5}, {1, 3, 10}, {2, 3, 4}, {2, 4, 11}, {3, 4, 5}, {3, 2, 2}};
    int n=10;
    generateFullGraph(muchii, n);
    sort(muchii, n);

    printArbore(muchii, n);
    int viz[100];
    findTheLeastExpensiveCycleGreedy(muchii, n, 1, viz);
    for(int i=0;i<n;i++)
        printf("%d ", viz[i]);
    return 0;
}

