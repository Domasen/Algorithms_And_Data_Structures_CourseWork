#include "graph.h"

//Driver program to test above functions
int main()
{
    int V = 8;
    int price[V];
    int prev[V];
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 10, "Rimas");
    addEdge(graph, 0, 4, 30, "Jurgis");
    addEdge(graph, 0, 3, 1, "Petras");
    addEdge(graph, 1, 2, 5, "Adomas");
    addEdge(graph, 2, 5, 20, "Adomas");
    addEdge(graph, 3, 6, 2, "Petras");
    addEdge(graph, 4, 5, 1, "Adomas");
    addEdge(graph, 4, 7, 2, "Jurgis");
    addEdge(graph, 6, 7, 3, "Jurgis");


 
    //printGraph(graph);

    dijkstra(graph, 0, price, prev, "Domas");

    printResults(0, 5, price, prev);
    


 
    return 0;
}