// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

using namespace std;

void problem() {

    /** === Getting the inputs === **/

    // nb rows (lines)
    int h = 0;
    cin >> h;

    // nb columns (letters per line)
    int w = 0;
    cin >> w;

    /** === Preparing data for the algorithm === **/

    /** === Setting up the algorithm === **/

    /** === Running the algorithm === **/

    /** === Printing the answer === **/

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


