#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Finite_faces_iterator Face_iterator;

int main() {
    // read number of points
    std::size_t n;
    std::cin >> n;
    // read points
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        pts.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    // output all edges
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
        std::cout << t.segment(e) << "\n";
    // output all triangles
    for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
        std::cout << t.triangle(f) << "\n";
}
