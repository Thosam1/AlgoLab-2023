#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;


int get_idx(int x, int y, int w) {
    return x * w + y;
}

pair<int, int> get_coordinates(int idx, int w, int h) {
    int x = idx % w;
    int y = floor((double) idx / (double) w);
    return make_pair(x, y);
}

void problem() {

    // === Getting the inputs ===
    // nb coloumns and rows (lines),
    int w, h;
    cin >> w >> h;

    int total_size = w * h;
    vector<char> fields(total_size);
    // Storing total number of empty tiles
    int nb_empty = 0;
    for(int i = 0; i < total_size; i++) {
        cin >> fields[i];
        if(fields[i] == '.') {
            nb_empty++;
        }
    }

//    cout << "nb empty : " << nb_empty << endl;
    // Pre-check with modulus 2, to see if we have an even number of empty
    // This avoid doing all the later computations
    if(nb_empty & 1) { // bit slower way: nb_empty % 2 == 1
        cout << "no" << "\n";
        return;
    }

    // % w -> column
    // / w -> row
    // x: left to right
    // y: top to bottom
    // example:
    // x . . x
    // . . . .
    // . . . .
    // x . . x

    // (x=0, y=0) -> top left corner

    // Creating graph
    graph g(total_size);

    // connecting all empty tiles that are adjacent to themselves
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {

            // get the idx in the vector
            int idx = get_idx(i, j, w);

            if(fields[idx] == '.') {

                // since goes from top to bottom, left to right
                // only need to look up and look left (backward to the direction we iterate)
                int left_idx = get_idx(i-1, j, w);
                int top_idx = get_idx(i, j-1, w);
                if (i && fields[left_idx] == '.') {
                    boost::add_edge(idx, left_idx, g);
                }
                if (j && fields[top_idx] == '.') {
                    boost::add_edge(idx, top_idx, g);
                }
            }
        }
    }

    // Now that the graph is connected, we can run a maximum cardinality matching algorithm
    vector<vertex_desc> domino(total_size);
    edmonds_maximum_cardinality_matching(g, &domino[0]);
    int nb_pairs = boost::matching_size(g, &domino[0]);

    if(nb_pairs == nb_empty / 2) {
        // not a multiple of 2
        cout << "yes\n";
    } else {
        cout << "no\n";
    }
//    cout << "nb pairs : " << nb_pairs << endl;

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

