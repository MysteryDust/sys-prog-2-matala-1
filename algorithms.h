#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

namespace graph {

    // Graph algorithm functions
    Graph BFS(Graph& g, int start);
    void DFSVisit(Graph& g, int u, char color[], Graph& tree);
    Graph DFS(Graph& g, int start);
    Graph Prim(Graph& g);
    Graph Kruskal(Graph& g);
    Graph Dijkstra(Graph& g, int start);

} // namespace graph

#endif // ALGORITHMS_H
