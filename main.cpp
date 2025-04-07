#include "graph.h"
#include "algorithms.h"
#include <iostream>

int main() {
    using namespace graph;
    
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 5);

    Graph bfsTree = BFS(g, 0);
    std::cout << "BFS tree graph\n";
    bfsTree.printGraph();

    Graph dfsTree = DFS(g, 0);
    std::cout << "DFS tree\n";
    dfsTree.printGraph();

    Graph primTree = Prim(g);
    std::cout << "Prim MST graph\n";
    primTree.printGraph();

    Graph kruskalTree = Kruskal(g);
    std::cout << "Kruskal MST graph\n";
    kruskalTree.printGraph();

    Graph dijkstraTree = Dijkstra(g, 0);
    std::cout << "Dijkstra graph\n";
    dijkstraTree.printGraph();

    return 0;
}
