/*********************************************
 * file:    ~\code4a\digraph.cpp              *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <algorithm>
#include <limits>  //std::numeric_limits
#include <vector>
#include <cassert>
#include <queue>
#include <iomanip>

#include "digraph.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

const int inf = std::numeric_limits<int>::max();

// -- CONSTRUCTORS

Digraph::Digraph(int n)
    : table(size_t(n) + 1)
    , size{n}
    , n_edges{0}
    , dist(size_t(n) + 1)
    , path(size_t(n) + 1)
    , done(size_t(n) + 1) {
    assert(n >= 1);

    // Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<Edge>& V, int n) : Digraph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge e = (u, v, w)
// update weight w if edge (u, v) is present
void Digraph::insertEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    // Check if edge e already exists
    if (auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                               [e](const Edge& ed) { return e.links_same_nodes(ed); });
        it == end(table[e.head])) {
        table[e.head].push_back(e);  // insert new edge e
        ++n_edges;
    } else {
        it->weight = e.weight;  // update the weight
    }
}

// remove directed edge e
void Digraph::removeEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                           [e](const Edge& ed) { return e.links_same_nodes(ed); });

    assert(it != end(table[e.head]));
    table[e.head].erase(it);
    --n_edges;
}

// construct unweighted single source shortest path-tree for start vertex s
void Digraph::uwsssp(int s) const {
    assert(s >= 1 && s <= size);

    // dist vector should be initialized with std::numeric_limits<int>::max()
    
    //std::sumeric_limits<int>::max();
    std::queue<int> Q;
    
    for (int i=1; i<= size; i++) {
        dist[i] = inf; // dist
        path[i] = 0; // path
    }
    
    dist[s] = 0; // start value
    Q.push(s); // instead of of enqueue
    
    
    while (!Q.empty()) {
        int v = Q.front(); // n�r v �r bes�kt plockas den bort
        Q.pop();
        
        for (auto it = table[v].begin(); it != table[v].end(); it++) {
            int u = it->tail; // tail = vertex adjacent
            
            if (dist[u] == inf) { // unvisited vertex u
                dist[u] = dist[v] + 1; // adding 1 because of unweighted graph
                path[u] = v;
                Q.push(u); // added to the queue
            }
        
        }
    }
    
}

// construct positive weighted single source shortest path-tree for start vertex s
// Dijktra�s algorithm
void Digraph::pwsssp(int s) const {
    assert(s >= 1 && s <= size);
    
    // dist vector should be initialized with std::numeric_limits<int>::max()
    for (int i = 1 ; i<= size; i++) {
        dist[i] = inf;
        path[i] = 0;
        done[i] = false;
    }
    
    dist[s] = 0;
    done[s] = true;
    int v = s;
    
    while (true) {
        for (auto it = table[v].begin(); it != table[v].end(); it++) {
            int u = it->tail;
            if (done[u] == false && dist[u] > dist[v] + it->weight) {
                dist[u] = dist[v] + it->weight;
                path[u] = v;
            }
            int minDist = inf;
            
            for (int i = 1; i<=size; i++) {
                // check if vertice is not visited and if distance is smaller than previous smallest distance
                if (!done[i] && dist[i] < minDist ) {
                    minDist = dist[i];
                    v=i;
                }
                
            }
            if (minDist == inf) break; // if we cant find anything smaller than inf -> exit
            done[v] = true;
            
        }
        
    }
}

// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "Vertex  adjacency lists\n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; ++v) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; ++v) {
            std::cout << std::setw(4) << v << " :" << std::setw(8)
                << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                << path[v] << "\n";
        }
        std::cout << "----------------------\n";
}

// print shortest path from s to t and the corresponding path length

// another function for total cost.
void Digraph::printPath(int t) const {
    assert(t >= 1 && t <= size);
    
    if(path[t] == 0) {
        std::cout << " " << t << " ";
        return;
    }
    // recursion
    printPath(path[t]);
       
    std::cout << "->" << t << " ";
    std::cout << "("<< dist[t] << ")";
    
}




