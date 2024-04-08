#include <stdio.h>
#include <stdlib.h>



typedef struct Graph{
    int N;
    int **adjArr;
} Graph;


int vertexIndex(int vertex){
    return (vertex + 1);
}


void initGraph(Graph *graph, int N){
    printf("Creating graph!\n");
    int i,j;
    
    graph->N = N;
    graph->adjArr = (int **)malloc(N * sizeof(int *));

    if(graph->adjArr == NULL){
        printf("Failed to allocate memory!\n");
        return;
    }

    for(i = 0; i < N; i++){
        graph->adjArr[i] = (int *)malloc(N * sizeof(int));
     
        if(graph->adjArr[i] == NULL){
            printf("Failed to allocate memory!\n");
            return;
        }
    }

    for( i=0; i < N; i++){
        for( j=0; j < N; j++){
            graph->adjArr[i][j] = 0;
        }    
    }
    
    int numOfNeigh = 0;
    int count = 0;
    int v;
    
    for( i=0; i < N; i++){
        count = 0;
        numOfNeigh = 1 + rand() % (N - i - 1); // apo 0 - (N - 1)    
        printf("i = %d: numOfNeigh = %d\n", i, numOfNeigh);
        
        while(count < numOfNeigh){
            v = i + rand() % (N - i + 1);
            printf("count = %d - v = %d\n", count, v);
            
            if(v == i){
                printf("Same node!\n");
                continue;
            }
            
            if(graph->adjArr[i][v] == 1 && graph->adjArr[v][i] == 1){
                printf("Edge already exists!\n");
                continue;
            }
            else {
                printf("Found a match!\n");
                graph->adjArr[i][v] == 1;
                graph->adjArr[v][i] == 1;
                count++;
            }
        }
    }
    
    printf("Finished Initialization!\n");
    
}

void printGraph(Graph *graph){
    
    printf("\nPrinting adjArr\n");
    int i, j;
    int numOfHyphens = graph->N * 3 + 4;
    
    for(i=0; i<numOfHyphens; i++) printf("-");

    printf("\n");
    
    for(i=0; i < graph->N; i++){
        printf("%-3d", vertexIndex(i));    
    }
    
    printf("|\n");

    //printf("|");

    for(i=0; i<numOfHyphens; i++) printf("-");
    printf("\n");

    
    for(i=0; i < graph->N; i++){
        //printf("%d|%-2s", vertexIndex(i), "");
        for(j=0; j < graph->N; j++){
            printf("%-3d", graph->adjArr[i][j]);
        }    
        printf("|%2d", vertexIndex(i));
        printf("\n");
    }
    
    for(i=0; i<numOfHyphens; i++) printf("-");
}


int main()
{
    srand(4402);
    int N = 6  + rand() % (10 - 6 + 1);
    printf("Number of Vertices: %d", N);
    Graph graph;
    initGraph(&graph, N);
    printGraph(&graph);
    return 0;
}
