// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

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

// function that returns the idx of an uppercase letter (ASCII)
int get_index_of_corresponding_letter(char letter) {
    return ((int) letter) - ((int) 'A');
}

void problem() {

    // === Getting the inputs ===

    // nb rows (lines)
    int h = 0;
    cin >> h;

    // nb columns (letters per line)
    int w = 0;
    cin >> w;

    // note
    string note;
    cin >> note;

    vector<string> front_lines(h);
    for(int i = 0; i < h; i++) {
        cin >> front_lines[i];
    }
    vector<string> back_lines(h);
    for(int i = 0; i < h; i++) {
        cin >> back_lines[i];
    }

    // === Preparing for the algorithm ===

    // total number of 2 letters combinations
    int nb_pairs = 26*26;

    // nb of letters in the note
    int n = note.size();

    // nb of occurrences of each letter in the note -> to calculate their corresponding capacity
    vector<int> letter_occurrences(26, 0);
    for(int i = 0; i < n; i++) {
        letter_occurrences[get_index_of_corresponding_letter(note[i])] += 1;
    }

    // nb of occurrences of each pair of letters (appearing in newspaper) -> to calculate their corresponding capacity
    vector<int> pair_occurrences(nb_pairs, 0);
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int front_letter = get_index_of_corresponding_letter(front_lines[i][j]);
            int back_letter = get_index_of_corresponding_letter(back_lines[i][w-j-1]);
            pair_occurrences[front_letter * 26 + back_letter] += 1; // since [A, A],...,[A,Z] and so on
        }
    }

    // === Setting up the algorithm ===

    // Creating the graph
    graph G(nb_pairs+26+2);
    // vertices are ordered as follows:
    // [0, nb_pairs[ -> pairs
    // [nb_pairs, nb_pairs + 26[ -> letters
    // nb_pairs + 26 = source
    // nb_pairs + 27 = sink
    int source = nb_pairs + 26;
    int sink = nb_pairs + 27;

    // Adding the edges
    edge_adder adder(G);
    // Linking up the source to the pairs
    for(int i = 0; i < nb_pairs; i++) {
        adder.add_edge(source, i, pair_occurrences[i]); // from, to, capacity
    }
    // Linking up the pairs to the letters
    for(int i = 0; i < nb_pairs; i++) {
        int first_letter = floor(i / 26);
        int second_letter = i % 26;

        // corresponding vertex index offset by nb_pairs
        adder.add_edge(i, nb_pairs + first_letter, n); // the maximum capacity it can have is equal to the length of the note !!!
        adder.add_edge(i, nb_pairs + second_letter, n);
    }
    // Linking the letters to the sink
    for(int i = 0; i < 26; i++) {
        adder.add_edge(nb_pairs + i, sink, letter_occurrences[i]);
    }


    // === Running the algorithm ===

    // Calculate flow from source to sink
    // The flow algorithm uses the interior properties (managed in the edge adder)
    // - edge_capacity, edge_reverse (read access),
    // - edge_residual_capacity (read and write access).
    long flow = boost::push_relabel_max_flow(G, source, sink);


//    // Retrieve capacity map and reverse capacity map
//    const auto c_map = boost::get(boost::edge_capacity, G);
//    const auto rc_map = boost::get(boost::edge_residual_capacity, G);
//    edge_desc edge = ...;
//    long flow_through_edge = c_map[edge] - rc_map[edge];

    // printing out the answer
    // flow == n means, all letters positions in the note are filled with newspaper pieces
    if(flow == n) {
        cout << "Yes" << "\n";
    } else {
        cout << "No" << "\n";
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

