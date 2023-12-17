#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Finite_faces_iterator Face_iterator;

using namespace std;

void problem(size_t n) {

    /** === Getting the inputs === **/
    // read existing points
    std::vector<K::Point_2> existing_pts;
    existing_pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        existing_pts.push_back(K::Point_2(x, y));
    }

    // read number of possible points
    std::size_t m;
    std::cin >> m;

    // read possible points
    std::vector<K::Point_2> possible_pts;
    possible_pts.reserve(m);
    for (std::size_t i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        possible_pts.push_back(K::Point_2(x, y));
    }

    /** === Setting up the algorithm === **/
    // construct triangulation
    Triangulation t;
    t.insert(existing_pts.begin(), existing_pts.end());

    /** === Running the algorithm === **/
    for (size_t i = 0; i < possible_pts.size(); i++) {
        Triangulation::Vertex_handle nearest_vertex = t.nearest_vertex(possible_pts[i]);
        // Calculate the Euclidean distance
        double squared_distance = CGAL::squared_distance(possible_pts[i], nearest_vertex->point());

        /** === Printing the answer **/
        cout << squared_distance << "\n";
    }

}


void tests() {
    while (true)
    {
        size_t n;
        cin >> n;
        if (n == 0)
            break;
        problem(n);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false); // Always!

    // !!!!!!!!!!!!!!!!!!!!!!! most important line !!!!!!!!!
    cout << setprecision(0) << fixed;
    tests();
}

