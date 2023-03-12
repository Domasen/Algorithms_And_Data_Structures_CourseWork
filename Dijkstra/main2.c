#include "graph.h"

//Driver program to test above functions
int main()
{
    int V = 8;
    int price[V];
    int prev[V];
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 5, "Rimas");
    addEdge(graph, 0, 4, 50, "Jurgis");
    addEdge(graph, 0, 3, 6, "Petras");
    addEdge(graph, 1, 2, 20, "Adomas");
    addEdge(graph, 2, 5, 20, "Adomas");
    addEdge(graph, 3, 6, 6, "Petras");
    addEdge(graph, 4, 5, 6, "Adomas");
    addEdge(graph, 4, 7, 6, "Jurgis");
    addEdge(graph, 6, 7, 6, "Jurgis");


 
    //printGraph(graph);

    dijkstra(graph, 0, price, prev, "Adas");

    printResults(0, 5, price, prev);
    


 
    return 0;
}