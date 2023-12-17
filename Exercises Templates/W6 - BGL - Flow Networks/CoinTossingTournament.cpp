#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;


// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_capacity_t, long,
                boost::property<boost::edge_residual_capacity_t, long,
                        boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
    graph &G;
public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity) {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    } };

void problem() {

    // === Getting the inputs ===
    // nb players, nb games
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> games(m);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        games[i] = make_tuple(a, b, c);
    }

    vector<int> final_scores(n);
    int total_scores = 0;
    for(int i = 0; i < n; i++) {
        int score;
        cin >> score;
        final_scores[i] = score;

        // to keep track
        total_scores += score;
    }

    /** === Setting up the algorithm === **/
    // Creating graph
    graph g(m + n + 2);
    // vertices are ordered as follows:
    // [0, m[ -> games
    // [m, m + n[ -> players
    // m + n = source
    // m + n + 1 = sink
    int source = m + n;
    int sink = m + n + 1;

    // Adding the edges
    edge_adder adder(g);
    // Linking up the source to the games
    for(int i = 0; i < m; i++) {
        adder.add_edge(source, i, 1); // from, to, capacity
    }
    // Linking up the games to the players
    for(int i = 0; i < m; i++) {

        int c = get<2>(games[i]);
        int winner_of_current_game;
        if(c == 1) {
            winner_of_current_game = get<0>(games[i]);
        }
        if(c == 2) {
            winner_of_current_game = get<1>(games[i]);
        }

        if(c == 0) {
            // add edge to both players
            adder.add_edge(i, m + get<0>(games[i]), 1);
            adder.add_edge(i, m + get<1>(games[i]), 1);
        } else {
            adder.add_edge(i, m + winner_of_current_game, 1);
        }
    }
    // Linking the players to the sink
    for(int i = 0; i < n; i++) {
        adder.add_edge(m + i, sink, final_scores[i]);
    }


    /** === Running the algorithm === **/
    // Calculate flow from source to sink
    // The flow algorithm uses the interior properties (managed in the edge adder)
    // - edge_capacity, edge_reverse (read access),
    // - edge_residual_capacity (read and write access).
    long flow = boost::push_relabel_max_flow(g, source, sink);

    // printing out the answer
    if(flow == total_scores && flow == m) {
        cout << "yes" << "\n";
    } else {
        cout << "no" << "\n";
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

