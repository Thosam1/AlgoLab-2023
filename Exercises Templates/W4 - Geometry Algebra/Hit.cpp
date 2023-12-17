#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

// CGAL includes
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

void problem(size_t n_segments) {

    /** === Getting the inputs === **/
    // getting ray coordinates and constructing the ray
    // !!! OMG, USE LONG, WITH INT IT DOESN'T GIVE CORRECT ANSWER !!!
    long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    K::Ray_2 r(K::Point_2(x1, y1), K::Point_2(x2, y2));

    bool hit = false;
    // getting the segments and constructing them
    for (size_t i = 0; i < n_segments; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        /** === Solving the problem === **/
        if(hit == false) {
            // avoid constructing if we already know it hits !!!
            K::Segment_2 s(K::Point_2(x1, y1), K::Point_2(x2, y2));
            if(CGAL::do_intersect(r, s)) {
                hit = true;
            }
        }
    }

    if(hit) {
        cout << "yes\n";
    } else {
        cout << "no\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t n;
    std::cin >> n;

    while(n > 0) {
        problem(n);
        cin >> n;
    }
}

