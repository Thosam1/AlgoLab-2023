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

// mapping coordinates of a vertex to its index in G
int index(int x, int y, int m, int n, bool in) {
    return y + n*x + in*m*n;
}
void problem() {

    // === Getting the inputs ===
    // nb columns, nb rows, nb knights, nb vertex capacity
    int m, n, k, c;
    cin >> m >> n >> k >> c;

    vector<pair<int, int>> knights_pos(k);
    for(int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        knights_pos[i] = make_pair(x, y);
    }

    /** === Setting up the algorithm === **/
    // Creating graph
    graph g(2 * m * n + 2);
    // vertices are ordered as follows:
    // [0, mn[ -> vertices in
    // [mn, 2mn[ -> vertices out
    // 2mn = source
    // 2mn + 1 = sink
    int source = 2 * m * n;
    int sink = 2 * m * n + 1;

    // Adding the edges
    edge_adder adder(g);
    // Linking up the source to the games
    for(int i = 0; i < k; i++) {
        int curr_knight_x = knights_pos[i].first;
        int curr_knight_y = knights_pos[i].second;
        adder.add_edge(source, index(curr_knight_x, curr_knight_y, m, n, true), 1); // from, to, capacity
    }

    // basically together it gives: "up", "right", "down", "left"
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    for(int x = 0; x < m; x++) {
        for(int y = 0; y < n; y++) {

            // add edge between vertex "in" and vertex "out"
            adder.add_edge(index(x, y, m, n, true), index(x, y, m, n, false), c);

            // to look in all 4 directions and create connections
            for(int i = 0; i < 4; i++) {

                // coordinates of neighbor node
                int newx = x + dx[i];
                int newy = y + dy[i];

                // in order to create a connection from current
                // node to the neighbor, we must make sure that
                // the neighbor is indeed within the bounds
                if(newx>=0 && newx<m && newy>=0 && newy<n) {
                    // Configure the segments (excluding ending segments)
                    adder.add_edge(index(x,y,m,n,false), index(newx,newy,m,n,true), 1);
                }
            }

            // Linking the "out" vertices of the border nodes to the sink
            if(x==0 || x==m-1) {
                adder.add_edge(index(x,y,m,n,false), sink, 1);

            }
            if(y==0 || y==n-1) {
                adder.add_edge(index(x,y,m,n,false), sink, 1);
            }
        }
    }


    /** === Running the algorithm === **/
    // Calculate flow from source to sink
    long flow = boost::push_relabel_max_flow(g, source, sink);

    // printing out the answer
    cout << flow << "\n";
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

