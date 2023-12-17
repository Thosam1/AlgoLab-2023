/**
 *  Kruskal, Dijkstra
 */

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> G;
typedef graph_traits<G>::edge_descriptor Edge;
typedef graph_traits<G>::vertex_descriptor Vertex;
typedef property_map<G, edge_weight_t>::type WeightMap;

// Kruskal algorithm that returns the sum of weights in the MST
int kruskal(G &g) {
    vector<Edge> mst;    // vector to store MST edges (not a property map!)

    // getting the weightmap of the graph
    WeightMap weights = get(edge_weight, g);

    // running kruskal on G and putting the edges of mst into "mst"
    kruskal_minimum_spanning_tree(g, back_inserter(mst));

    // total sum of weights of MST
    int sumMST = 0;

    for (vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it) {
        sumMST += weights[*it];
    }
    return sumMST;
}

// Dijkstra algorithm that returns the distance of the node furthest from the source node 0
int dijkstra(G &g, int source) {
    int n = num_vertices(g);

    // will contain the distances from source node
    vector<int> dist_map(n);
    auto it_prop = make_iterator_property_map(dist_map.begin(), get(vertex_index, g));
    dijkstra_shortest_paths(g, source, distance_map(it_prop));

    // finding the distance furthest away from source node
    int max_dist = -1;
    for(int i = 0; i < n; i++) {
        max_dist = max(max_dist, dist_map[i]);
    }
    return max_dist;
}

void problem() {
    // getting the inputs
    int n = 0; // nb vertices
    cin >> n;

    int m = 0; // nb edges
    cin >> m;

    // creating the graph
    G G(n);
    WeightMap weights = get(edge_weight, G);

    Edge edge;
    for(int i = 0; i < m; ++i) {
        int p1, p2, w; // 2 end-points and the weight
        cin >> p1 >> p2 >> w;

        // adding the endge to the graph
        edge = add_edge(p1, p2, G).first; weights[edge]=w;
    }

    // printing out the answer
    cout << kruskal(G) << " " << dijkstra(G, 0) << "\n";
}



void tests() {
    int n_tests = 0;

    // reads number of tests
    cin >> n_tests;

    // for each test case we repeat the following
    for(int i = 0; i < n_tests; ++i) {
        // cout << " =============\n ";
        problem();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false); // Always!
    tests();
}

