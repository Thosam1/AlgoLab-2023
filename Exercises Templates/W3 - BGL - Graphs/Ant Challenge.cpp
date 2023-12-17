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

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

// Kruskal algorithm that returns the sum of weights in the MST
vector<std::tuple<Edge, int>> kruskal(Graph &g) {
    vector<Edge> mst;    // vector to store MST edges (not a property map!)

    // getting the weightmap of the graph
    WeightMap weights = get(edge_weight, g);

    // running kruskal on G and putting the edges of mst into "mst"
    kruskal_minimum_spanning_tree(g, back_inserter(mst));

    // total sum of weights of MST
    vector<std::tuple<Edge, int>> weightedEdges;
    for (const Edge& e : mst) {
        int weight = get(weights, e);
        weightedEdges.push_back(make_tuple(e, weight));
    }
    return weightedEdges;
}

// Dijkstra algorithm that returns the distance of the shortest path between source and destination
int dijkstra(Graph &g, int source, int destination) {
    int n = num_vertices(g);

    // will contain the distances from source node
    vector<int> dist_map(n);
    auto it_prop = make_iterator_property_map(dist_map.begin(), get(vertex_index, g));
    dijkstra_shortest_paths(g, source, distance_map(it_prop));

    return dist_map[destination];
}

void problem() {
    // getting the inputs
    int n = 0; // nb vertices (trees)
    cin >> n;

    int e = 0; // nb edges
    cin >> e;

    int s = 0; // nb species
    cin >> s;

    int a = 0; // source
    cin >> a;

    int b = 0; // destination
    cin >> b;

    // creating the graphs
    Graph graphs[s];
    for(int i = 0; i < s; i++) {
        graphs[i] = Graph(n);
    }

    Edge edge;
    for(int i = 0; i < e; ++i) {
        int p1, p2;
        cin >> p1 >> p2;

        int weightSpecies[s];
        for(int j = 0; j < s; j++) {
            cin >> weightSpecies[j];

            WeightMap weights = get(edge_weight, graphs[j]);
            // adding the edge to the graph
            edge = add_edge(p1, p2, graphs[j]).first; weights[edge]=weightSpecies[j];
        }
    }

    for(int i = 0; i < s; i++){
        int hive;
        cin >> hive;
    }

    Graph mainGraph(n);
    WeightMap weights = get(edge_weight, mainGraph);
    for(int i = 0; i < s; i++) {
        vector<std::tuple<Edge, int>> edgesWeight = kruskal(graphs[i]);
        for(auto & j : edgesWeight) {
            edge = add_edge(get<0>(j).m_source, get<0>(j).m_target, mainGraph).first; weights[edge]=get<1>(j);
        }
    }



    // printing out the answer
    cout << dijkstra(mainGraph, a, b) << "\n";
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

