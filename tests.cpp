#include "graph.h"
#include "algorithms.h"
#include <cassert>
#include <iostream>

using namespace graph;

void testAddAndRemoveEdges() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 7);
    assert(g.getWeight(0, 1) == 5);
    assert(g.getWeight(1, 2) == 7);

    g.removeEdge(1, 2);
    assert(g.getWeight(1, 2) == -1);
}

void testPrimMST() {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);

    Graph mst = Prim(g);
    assert(mst.getWeight(0, 1) == 1);
    assert(mst.getWeight(1, 2) == 2);
    assert(mst.getWeight(2, 3) == 3);
    assert(mst.getWeight(3, 0) == -1); // this one should be excluded (heaviest)
}

void testKruskalMST() {
    Graph g(4);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 4);

    Graph mst = Kruskal(g);
    // Kruskal should pick 0-2 (1), 1-2 (2), 2-3 (4)
    assert(mst.getWeight(0, 2) == 1);
    assert(mst.getWeight(1, 2) == 2);
    assert(mst.getWeight(2, 3) == 4);
}

void testDijkstra() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(2, 1, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 9);
    g.addEdge(3, 4, 2);

    Graph tree = Dijkstra(g, 0);
    // Shortest paths:
    // 0 -> 2 (5), 2 -> 1 (3), 1 -> 3 (1), 3 -> 4 (2)
    assert(tree.getWeight(0, 2) == 5);
    assert(tree.getWeight(2, 1) == 3);
    assert(tree.getWeight(1, 3) == 1);
    assert(tree.getWeight(3, 4) == 2);
}

int main() {
    std::cout << "Running Unit Tests\n";

    testAddAndRemoveEdges();
    testPrimMST();
    testKruskalMST();
    testDijkstra();

    std::cout << "All tests passed\n";
    return 0;
}
