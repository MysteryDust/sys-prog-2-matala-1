#include "graph.h"
#include <iostream>

namespace graph {

    Node::Node(int v) : val(v), next(nullptr) {}

    LinkedList::LinkedList() : head(nullptr) {} //empty lke my motivation

    void LinkedList::insert(int x) {
        Node* n = new Node(x);
        n->next = head;
        head = n; //o(1) <3
    }

    void LinkedList::remove(int x) {
        Node *cur = head, *prev = nullptr;
        while (cur && cur->val != x) {
            prev = cur;
            cur = cur->next;
        }
        if (cur) { //if we actually found the node denoted as x
            if (prev) prev->next = cur->next;
            else head = cur->next;
            delete cur; 
        }
    }

    LinkedList::~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp; //image if c++ believed in garbage collector
        }
    }

    Graph::Graph(int n) : size(n), edgeCount(0) {
        adj = new LinkedList[n];
        edges = new Edge[N * N]; // extra making sure we don't reach end of list 
    }

    void Graph::addEdge(int from, int to, int wt) {
        adj[from].insert(to);
        adj[to].insert(from);
        edges[edgeCount++] = {from, to, wt}; //actual add action
    }

    void Graph::addEdge(int from, int to) { //default version, oop adapter flashbacks ;-;
        adj[from].insert(to);
        adj[to].insert(from);
        edges[edgeCount++] = {from, to, 1};
    }

    void Graph::removeEdge(int from, int to) { // Remove from adjacency list and then from edge list
        adj[from].remove(to);
        adj[to].remove(from); 
        bool exists = false;
        for (int i = 0; i < edgeCount; ++i) {
            if ((edges[i].from == from && edges[i].to == to) || (edges[i].from == to && edges[i].to == from)) {
                // Shift elements left to remove the edge
                for (int j = i; j < edgeCount - 1; ++j) {
                    edges[j] = edges[j + 1];
                }
                edgeCount--;
                exists = true;
                break;
            }
        }
        if(!exists) {
            throw std::runtime_error("Edge doesn't exist"); // my only use of standard library, don't fail me because of it please
        }
    }

    int Graph::getWeight(int u, int v) { //Traverse edges to get wanted edge weight, no you look great in that dress!
        for (int i = 0; i < edgeCount; ++i) {
            if ((edges[i].from == u && edges[i].to == v) ||
                (edges[i].from == v && edges[i].to == u))
                return edges[i].wt;
        }
        throw std::runtime_error("Edge doesn't exist"); // my only error message not explicily required in github :)
    }

    void Graph::printGraph() {  //print eAch edge by their first node, secod node and weight
        for (int i = 0; i < edgeCount; ++i) {
            std::cout << edges[i].from << " -> " << edges[i].to << " (weight: " << edges[i].wt << ")\n";
        }
        std::cout << "\n"; //dramatic pause 
    }

    Queue::Queue() : front(0), back(0) {} //starts from 0, like the sleep schedule of the one reading this :D

    void Queue::push(int x) { 
        back++;
        data[back-1] = x; // move x to back and incrmeent back, I love fifo
    }

    int Queue::pop() {
        front++;
        return data[front-1]; // nothing interseitng here, just simple fifo pop
    }

    bool Queue::empty() {
        return front == back;
    }

    MinPQ::MinPQ() : size(0) {}

    void MinPQ::push(Edge e, int priority) { // saddet insertion sort pretending to be heap
        int i = size;
        while (i > 0 && pri[i - 1] > priority) {
            data[i] = data[i-1];
            pri[i] = pri[i - 1];
            i=i-1; //bubbling slowly like my regret in choosing cs
        }
        data[i] = e;
        pri[i] = priority;
        size++;
    }

    Edge MinPQ::pop() {
        size--;
        return data[size]; //lowest priority at end because actual heaps are overrated
    }

    bool MinPQ::empty() {
        return size == 0;
    }

    // pretty simple UnionFind 
    UnionFind::UnionFind(int n) {
        for (int i=0; i < n;++i) {
            parent[i] = i;
            rank[i] = 0; // no hierachy... for now...
        }
    }

    int UnionFind::find(int x) { //find root /w path compression
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        return parent[x];
    }

    void UnionFind::unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return; //if same tree
        if (rank[rx] < rank[ry]) { // if rank of y is higher attach rootx tree to it
            parent[rx] = ry;
        }
        else { // other way around
            parent[ry] = rx;
            if (rank[rx] == rank[ry]) {
                rank[rx]++;
            }
        }
    }
}
