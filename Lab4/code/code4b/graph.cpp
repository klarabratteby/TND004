/*********************************************
 * file:	~\code4b\graph.h                  *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <format>
#include <cassert>     // assert
#include <limits>      // std::numeric_limits

#include "graph.h"
#include "dsets.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero
const int inf = std::numeric_limits<int>::max();
// -- CONSTRUCTORS

// Create a graph with n vertices and no vertices
Graph::Graph(int n) : table(size_t(n) + 1), size{n}, n_edges{0} {
    assert(n >= 1);
}

Graph::Graph(const std::vector<Edge> &V, int n) : Graph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge e
// update weight if edge e is present
void Graph::insertEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edge_insertion = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        if (auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                                   [e1](const Edge &ed) { return e1.links_same_nodes(ed); });
            it == end(T[e1.head])) {
            T[e1.head].push_back(e1);  // insert new edge e1
            ++n;                       // increment the counter of edges
        } else {
            it->weight = e1.weight;  // update the weight
        }
    };

    edge_insertion(e);
    edge_insertion(e.reverse());
}

// remove undirected edge e
void Graph::removeEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edgeRemoval = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                               [e1](const Edge &ed) { return e1.links_same_nodes(ed); });

        assert(it != end(T[e1.head]));
        T[e1.head].erase(it);  // remove edge e1
        --n;                   // decrement the counter of edges
    };

    edgeRemoval(e);
    edgeRemoval(e.reverse());
}

// Prim's minimum spanning tree algorithm
// inga cykler och träffa alla mål. Träd som spänner upp
void Graph::mstPrim() const {
    std::vector<int> dist(size_t(size) + 1, std::numeric_limits<int>::max());
    std::vector<int> path(size_t(size) + 1, 0);
    std::vector<bool> done(size_t(size) + 1, false);

    // *** TODO ***
    for (int i=1; i<= size; i++) {
        dist[i] = inf; // dist
        path[i] = 0; // path
        done[i] = false;
    }
    int v = 1;
    dist[v] = 0;
    done[v] = true;
    int totalWeight = 0;
    
    
    while (true) {
        for (auto it = table[v].begin(); it != table[v].end(); it++) {
            int u = it->tail;
            if (done[u]== false && dist[u] > it->weight) {
                dist[u] = it->weight;
                path[u] = v;
            }
        }
        int minDist = inf;
        for (int i = 1; i<=size; i++) {
        // Check if vertice is not visited and distance is smaller than previous smallest
            if (!done[i] && dist[i] < minDist ) {
                minDist = dist[i];
                v=i;
            }
        }
        if (minDist > inf - 1 ) // if no mor eedges can be added
        break; // if we cant find anything smaller than inf -> exit
           
        // Create new edge and print
        Edge e(path[v], v, dist[v]);
        std::cout << e << std::endl;
        totalWeight += dist[v];
        done[v] = true;
    }
    
    std::cout << "Total weight: " << totalWeight << std::endl;
}

// Kruskal's minimum spanning tree algorithm = faster
void Graph::mstKruskal() const {
    
    std::vector<Edge> V; // all edges
    int counter = 0;
    int totalWeight = 0;
    DSets D(size);
    
    // build V that stores all edges in the graph
    for (int i = 1; i <= size; ++i) {
        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if (i < it->tail) // avoiding duplicates
            V.push_back(*it); // adding edges to V
            }
        }
    // heap finds the minimum cost in the tree
    // greater = ensures that the smallest edge (based on weight) is at top of the heap
    std::make_heap(V.begin(),V.end(), std::greater<Edge>());
        
    // while V is not empty and tree has n-1 edges . size = number of vertices
    while (!V.empty() && counter < size - 1 ) {
        // reorganize the heap, ensures that the minelement is at top
        std::pop_heap(V.begin(),V.end(), std::greater<Edge>());
        
        //Minimum edge is stored in e
        Edge e = V.back();
        V.pop_back(); // deleteMin
        
        // checking for cycles
        if (D.find(e.head) != D.find(e.tail)) {
            D.join(D.find(e.head), D.find(e.tail));
            totalWeight += e.weight;
            std::cout << e << std::endl;
            counter++;
        }
    }
    std::cout << "Total weight: " << totalWeight << std::endl;
   
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "Vertex  adjacency lists\n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
                    std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight
                        << ") ";
                }
                std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}
