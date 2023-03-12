// A C Program to demonstrate adjacency list
// representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// A structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    int price;
    char owner[100];
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};
 
// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices
// in graph)
struct Graph {
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int price, char owner[])
{
    struct AdjListNode* newNode
        = (struct AdjListNode*)malloc(
            sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->price = price;
    newNode->next = NULL;
    strcpy(newNode->owner, owner);
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph
        = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array = (struct AdjList*)malloc(
        V * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int price, char owner[])
{
    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the beginning
    struct AdjListNode* check = NULL;
    struct AdjListNode* newNode = newAdjListNode(dest, price, owner);
 
    if (graph->array[src].head == NULL) {
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    }
    else {
 
        check = graph->array[src].head;
        while (check->next != NULL) {
            check = check->next;
        }
        // graph->array[src].head = newNode;
        check->next = newNode;
    }
 
    // Since graph is undirected, add an edge from
    // dest to src also
    newNode = newAdjListNode(src, price, owner);
    if (graph->array[dest].head == NULL) {
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
    else {
        check = graph->array[dest].head;
        while (check->next != NULL) {
            check = check->next;
        }
        check->next = newNode;
    }
 
    // newNode = newAdjListNode(src);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}
 
// A utility function to print the adjacency list
// representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> (%d - %d price) ", pCrawl->dest, pCrawl->price);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int findMin(int* visited, int* price, int V){
    int index;
    int min = INT_MAX;

    for(int i = 1; i < V; ++i){
        if(price[i] < min && visited[i] == 1){
            index = i;
            min = price[i];
        }
    }

    return index;
}
 

void dijkstra(struct Graph* graph, int src, int* price, int* prev, char driver[]){
    
    int V = graph->V;
    int visited[V];

    for(int i = 0; i < V; ++i){
        visited[i] = 1;
        price[i] = INT_MAX;
        prev[i] = -1;
    }

    price[src] = 0;

    struct AdjListNode* pCrawl = graph->array[src].head;

    while(pCrawl){
        if(strcmp(driver, pCrawl->owner) == 0){
            price[pCrawl->dest] = pCrawl->price / 2;
        }else{
            price[pCrawl->dest] = pCrawl->price;
        }

        prev[pCrawl->dest] = src; 
        pCrawl = pCrawl->next;
    }
    visited[src] = 0;
    
    for(int i = 1; i < V; ++i){

        int next = findMin(visited, price, V);
        pCrawl = graph->array[next].head;

        int currentDist = price[next];

        while(pCrawl){
            if(strcmp(driver, pCrawl->owner) == 0){
               if(price[next] + (pCrawl->price / 2) < price[pCrawl->dest]){
                price[pCrawl->dest] = price[next] + (pCrawl->price / 2);
                prev[pCrawl->dest] = next; 
            } 
            }else if(price[next] + pCrawl->price < price[pCrawl->dest]){
                price[pCrawl->dest] = price[next] + pCrawl->price;
                prev[pCrawl->dest] = next; 
            }
            pCrawl = pCrawl->next;
        }

        visited[next] = 0;

    }
    
}

void printResults(int src,int dest, int* price, int* prev){

    int index = dest;

    if(price[dest] == INT_MAX){
        printf("No route available :')");
        return;
    }

    printf("\nPrice from City %d to City %d - %d\n", src, dest, price[dest]);
    printf("Route: %d <- ", dest);
    while(prev[index] != src){
        printf("%d <- ", prev[index]);
        index = prev[index];
    }
    printf("%d ", prev[index]);
}