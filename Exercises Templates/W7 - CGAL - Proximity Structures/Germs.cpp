#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_with_info_2<double, K> Fb;

//typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_vertex_base_with_info_2<K::FT,K> Vb;

typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Fh;
typedef K::Point_2 Point;
typedef Triangulation::Edge_iterator Edge_iterator;

using namespace std;

int distance_to_hour(double distance) {
    return ceil(sqrt(max(0., distance - 0.5)));
}


void problem(size_t n) {

    /** === Getting the inputs === **/
    int l, b, r, t;
    cin >> l >> b >> r >> t;

    // read bacteria positions
    vector<Point> germs;
    germs.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        germs.push_back(Point(x, y));
    }

    // construct triangulation
    Triangulation triangulation;
    triangulation.insert(germs.begin(), germs.end());

    // Finding the shortest distance to die with a collision against the border
    for(auto v = triangulation.finite_vertices_begin(); v != triangulation.finite_vertices_end(); v++) {
        Point v_point = v->point();

        // minimum distance to go horizontally before touching the border
        double min_horizontal = min(v_point.x() - l, r - v_point.x());
        double min_vertical = min(v_point.y() - b, t - v_point.y());

        // shortest distance between all 4 borders
        // radius the germ must have to hit the closest border
        double min_overall = min(min_horizontal, min_vertical);

        // store the answer
        v->info() = min_overall;
    }

    // Finding the shortest distance to die with a collision against one of the neighbors
    for(auto e = triangulation.finite_edges_begin(); e != triangulation.finite_edges_end(); ++e) {
        auto v_i = e->first->vertex(triangulation.cw(e->second));
        auto v_j = e->first->vertex(triangulation.ccw(e->second));
//        auto v_i = triangulation.segment(e).vertex(0);
//        auto v_j = triangulation.segment(e).vertex(1);

        double shortest_distance_to_die = sqrt(CGAL::squared_distance(v_i->point(), v_j->point())) / 2;
        v_i->info() = min(v_i->info(), shortest_distance_to_die);
        v_j->info() = min(v_j->info(), shortest_distance_to_die);
    }

    vector<double> distances_to_die;
    distances_to_die.reserve(n);
    for (auto v = triangulation.finite_vertices_begin(); v != triangulation.finite_vertices_end(); ++v) {
        distances_to_die.push_back(v->info());
    }
    std::sort(distances_to_die.begin(), distances_to_die.end());

//    Debugging like crazy wtf
//    cout << " ======= ";
//    for(int i = 0; i < n; i++){
//        cout << distances_to_die[i];
//    }
//    cout << " ======= ";


    // Printing the answers
    int first = distance_to_hour(distances_to_die[0]);
    int median = distance_to_hour(distances_to_die[n/2]);
    int last = distance_to_hour(distances_to_die[n-1]);

    cout << first << " " << median << " " << last << "\n";
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
    tests();
}

