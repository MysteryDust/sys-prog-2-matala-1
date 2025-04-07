#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept> //I used standard library only for exception 

#define N 100
#define INF 1000000000

namespace graph {

    struct Edge { //There weren't any strict oopp requriements so I didn't have private data members
        int from, to, wt;
    };

    struct Node {
        int val;
        Node* next;
        Node(int v);
    };

    struct LinkedList {
        Node* head;
        LinkedList();
        void insert(int x);
        void remove(int x);
        ~LinkedList();
    };

    class Graph {
    public:
        int size;
        LinkedList* adj;
        Edge* edges;
        int edgeCount;

        Graph(int n);
        void addEdge(int from, int to, int wt);
        void addEdge(int from, int to);
        void removeEdge(int from, int to);
        int getWeight(int u, int v);
        void printGraph();
    };

    struct Queue {
        int data[N];
        int front, back;
        Queue();
        void push(int x);
        int pop();
        bool empty();
    };

    struct MinPQ {
        Edge data[N*N];
        int pri[N*N];
        int size;

        MinPQ();
        void push(Edge e, int priority);
        Edge pop();
        bool empty();
    };

    class UnionFind {
        int parent[N], rank[N];
    public:
        UnionFind(int n);
        int find(int x);
        void unite(int x, int y);
    };

}

#endif 
