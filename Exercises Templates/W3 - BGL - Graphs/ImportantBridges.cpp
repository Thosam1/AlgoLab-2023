/**
 *  Biconnected components
 */

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

// STL includes
#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

using namespace std;
using namespace boost;

// BGL typedefs
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_name_t, int>> Graph; // using our custom struct
// typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_name_t, int>> Graph; // we can abuse edge_name_t

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator  EdgeIt;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::vertex_iterator VertexIt;

void problem() {
    // getting the inputs
    int n = 0; // nb vertices
    cin >> n;

    int m = 0; // nb edges
    cin >> m;

    // creating the graph
    Graph G(n);

    for(int i = 0; i < m; ++i) {
        int p1, p2;
        cin >> p1 >> p2;

        // adding the edge to the graph
        add_edge(p1, p2, G);
    }

    // =============================================


    // Getting biconnected components
    // this will map for example: given an EdgeIt, it will return the component
    // number it belongs to. eg: components_map[*eit] = 2 means belong to container no2
    property_map<Graph, edge_name_t>::type components_map = get(edge_name, G);
    size_t num_comps = biconnected_components(G, components_map);

    // contains the critical bridges
    vector<pair<int, int>> critical_bridges;

    // this variable contains the number of edges in the component at index i
    vector<int> component_size(num_comps);

    EdgeIt ei, ei_end;

    // Count edges per components
    for(tie(ei, ei_end) = edges(G); ei != ei_end; ++ei) {
        component_size[components_map[*ei]] += 1;
    }

    // Retrieve results if edge is a bridge
    for(tie(ei, ei_end) = edges(G); ei != ei_end; ei++) {

        // if the current edge belongs to a component of size 1 edge
        // (meaning doesn't belong to a cycle -> by itself !!!)
        if(component_size[components_map[*ei]] == 1) {
            int src = source(*ei, G);
            int tar = target(*ei, G);

            // important to push it in order to pass the tests
            if(src < tar) {
                critical_bridges.push_back((make_pair(src, tar)));
            } else {
                critical_bridges.push_back(make_pair(tar, src));
            }
        }
    }

    // Sort in lexicographical order -> to pass the tests
    sort(critical_bridges.begin(), critical_bridges.end());

    // printing out the total number of critical bridges
    cout << critical_bridges.size() << "\n";

    // printing out the critical bridges
    for(int i = 0; i < (int) critical_bridges.size(); i++) {
        cout << critical_bridges[i].first << " " << critical_bridges[i].second << "\n";
    }
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

