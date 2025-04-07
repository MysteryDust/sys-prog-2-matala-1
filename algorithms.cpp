#include "algorithms.h"

namespace graph {

    Graph BFS(Graph& g, int start) {
        char color[N];
        for (int i = 0; i < g.size; ++i) {
            color[i] = 'w'; //intialize to white means not visited
        }
        Queue q;
        Graph bfsTree(g.size);

        color[start] = 'g';
        q.push(start);

        while (!q.empty()) {
            int u = q.pop();

            Node* cur = g.adj[u].head;
            while (cur) {
                int v = cur->val;
                if (color[v] == 'w') {
                    color[v] = 'g'; //turn to gray means visited but not finished checking adj list
                    q.push(v);
                    bfsTree.addEdge(u, v, g.getWeight(u, v));
                }
                cur = cur->next;
            }

            color[u] = 'b'; //finished u adj list so turn into black meaning finished
        }

        return bfsTree;
    }

    void DFSVisit(Graph& g, int u, char color[], Graph& tree) {
        color[u] = 'g'; // same as explanation from bfs
    
        Node* cur = g.adj[u].head;
        while (cur) {
            int v = cur->val;
            if (color[v] == 'w') {
                tree.addEdge(u, v, g.getWeight(u, v));
                DFSVisit(g, v, color, tree);
            }
            cur = cur->next;
        }
    
        color[u] = 'b';
    }
    
    Graph DFS(Graph& g, int start) {
        char color[N];
        for (int i = 0; i < g.size; ++i) {
            color[i] = 'w';
        }
        Graph tree(g.size);
        DFSVisit(g, start, color, tree);
        return tree;
    }
    
    Graph Prim(Graph& g) {
        bool inMST[N]; //signifies which of the edges from g will be inside the returned mst
        for(int i = 0; i < N; i++) {
            inMST[i] = false; 
        }

        int key[N];
        for (int i = 0; i < g.size; ++i) {
            key[i] = INF; // represents the distance from the hope of each student in third year
        }
    
        Graph mst(g.size); //returned mst
        MinPQ pq;
        key[0] = 0;
        pq.push({-1, 0, 0}, 0); //start from 0 because why not
    
        while (!pq.empty()) {
            Edge e = pq.pop();
            int u = e.to;
            if (inMST[u]) continue; //if picked already, go on
            inMST[u] = true;
            if (e.from != -1)
                mst.addEdge(e.from, u, e.wt); //add to mst if not a non existing starting node parent
    
            Node* cur = g.adj[u].head;
            while (cur) {
                int v = cur->val;
                int weigh =g.getWeight(u, v);
                if (!inMST[v] && weigh < key[v]) {
                    key[v] = weigh;
                    pq.push({u,v, weigh}, weigh);
                }
                cur = cur->next;
            }
        }
        return mst;
    }

    Graph Kruskal(Graph& g) {
        Edge sorted[N * N];
        for (int i = 0; i < g.edgeCount; ++i){sorted[i] = g.edges[i];}//copy entire thing to paste into sorting
        int count = g.edgeCount;
    
        // Bubble sort because efficiency == bad returns true
        for (int i = 0; i < count - 1; ++i){
            for (int j = 0; j < count - i - 1; ++j){
                if (sorted[j].wt > sorted[j + 1].wt) {
                    Edge temp = sorted[j];
                    sorted[j] = sorted[j + 1];
                    sorted[j + 1] = temp;
                }
            }
        }
        UnionFind uf(g.size);
        Graph mst(g.size);
        int added = 0;
        for (int i = 0; i < count && added < g.size - 1; ++i) {
            int u = sorted[i].from;
            int v = sorted[i].to;
            if (uf.find(u) != uf.find(v)) { //checks if under same tree
                uf.unite(u, v); //connects them into 1 if they aren't
                mst.addEdge(u, v, sorted[i].wt);
                added++;
            }
        }
        return mst;
    }
    
    Graph Dijkstra(Graph& g, int start) {
        int dist[N];
        bool visited[N] = {false}; //we don't like meeting the same people twice *just cs stuff*
        for (int i = 0; i < g.size; ++i){
            dist[i] = INF; //infinitely far away like me actually getting my diploma :(
        }
        dist[start] = 0; //defualt dsitance for starting node
    
        MinPQ pq;
        pq.push({-1, start, 0}, 0);
        Graph tree(g.size); //not actually a tree yet, but it'll grow dont' worry
    
        while (!pq.empty()) {
            Edge e = pq.pop();
            int u = e.to;
            if (visited[u]) continue; //no backtracking!
            visited[u] = true;
            if (e.from!=-1) //make sure we're not adding a non existent parent woops
                tree.addEdge(e.from, u, dist[u]); 
    
            Node* cur = g.adj[u].head;
            while (cur) {
                int v = cur->val;
                int wt = g.getWeight(u, v);
                if (!visited[v] && dist[u] + wt < dist[v]) { // if we find shorter path update it
                    dist[v] = dist[u] +wt;
                    pq.push({u, v, wt}, dist[v]); //definetly optimal don't check please
                }
                cur= cur->next;
            }
        }
        return tree;
    }
}
