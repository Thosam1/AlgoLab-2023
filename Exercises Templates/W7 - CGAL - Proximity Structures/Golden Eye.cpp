#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef boost::disjoint_sets_with_storage<> UnionFind;
typedef pair<K::Point_2, int> Point_id;

struct Edge {
    Edge(int v1, int v2, K::FT sql): v1(v1), v2(v2), squared_length(sql) {}
    // 2 endpoints
    int v1, v2;
    // squared length
    K::FT squared_length;
};

inline bool operator<(const Edge& e, const Edge& f) {
    return e.squared_length < f.squared_length;
}

void problem() {

    /** === Getting the inputs === **/
    // nb jammers
    int n;
    cin >> n;
    // nb missions
    int m;
    cin >> m;
    // power consumption
    double p;
    cin >> p;
    // getting and storing jammers positions with their respective id
    vector<Point_id> jammers(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        jammers[i] = Point_id(K::Point_2(x, y), i);
    }

    // creating the triangulation with the given vertices (jammers)
    Triangulation t;
    t.insert(jammers.begin(), jammers.end());

    // going over the edges and store their length in the info field
    vector<Edge> edges;
    for (auto ei = t.finite_edges_begin(); ei != t.finite_edges_end(); ++ei) {
        int v1 = ei->first->vertex((ei->second+1)%3)->info();
        int v2 = ei->first->vertex((ei->second+2)%3)->info();
        K::FT sql = t.segment(ei).squared_length();
        edges.push_back(Edge(v1, v2, sql));
    }

    // sorting all the edges by length, in the triangulation
    // shortest to longest edge
    sort(edges.begin(), edges.end());

    /** Part i: Finding the components using p **/
    UnionFind part_i(n);
    // if the squared length is smaller or equal to p, it means,
    // we can draw an edge between the 2 vertices !
    // since it has been sorted previously,
    // we can stop as soon as the squared length > p
    // after this for loop, we have all the disjoint sets stored in part_i for the given p
    for(auto ei = edges.begin(); ei != edges.end(); ++ei) {
        if(ei->squared_length > p) {
            break;
        }
        // there is an intersection between the 2 jammers circle
        part_i.union_set(ei->v1, ei->v2);
    }

    /** ======== **/

    // the rest can be done efficiently
    UnionFind part_ii(n);
    auto ai = edges.begin(); // that way we go iterate only once
    K::FT smallest_p_for_all = 0;

    UnionFind part_iii(n);
    auto bi = edges.begin(); // that way we go iterate only once
    K::FT smallest_p_for_i = 0;

    // iterating over the missions
    for (int i = 0; i < m; i++) {
        // getting the inputs
        K::Point_2 source;
        cin >> source;
        K::Point_2 target;
        cin >> target;

        // finding the respective nearest vertex of each of the endpoints
        Triangulation::Vertex_handle s_nearest = t.nearest_vertex(source);
        Triangulation::Vertex_handle t_nearest = t.nearest_vertex(target);

        // computing the respective distance to the nearest point
        K::FT d1 = CGAL::squared_distance(source, s_nearest->point());
        K::FT d2 = CGAL::squared_distance(target, t_nearest->point());

        // since both points must be within the radius, we can only store the larger of the 2
        // d represents the squared distance between the nearest jammer to the point * 4 to fullfull the requirement
        // if d <= w, then it means that the current point is within the radius of its nearest jammer !
        // ||q - j_i|| <= sqrt(w / 4)
        // <=> (||q - j_i||) ^2 <= w / 4
        // <=> 4 * (||q - j_i||) ^2 <= w
        K::FT d = 4 * std::max(d1, d2);

        /** For each mission, answering if with current p, we can reach both endpoints **/
        // both points must be within the radius and both nearest vertices must be in the same set
        if (d <= p && part_i.find_set(s_nearest->info()) == part_i.find_set(t_nearest->info())) {
            cout << 'y';

            // Solving for part iii
            if (d > smallest_p_for_i) {
                // since d must be at most equal to w
                // w must be equal to the largest d out of all missions
                // that succeed under the predicate p
                smallest_p_for_i = d;
            }

            // Solving for part iii
            for (; bi != edges.end(); ++bi) {
                if(part_iii.find_set(s_nearest->info()) == part_iii.find_set(t_nearest->info())) {
                    break;
                }
                // building the sets as we go, so at the end we end up with a similar structure as in part i
                part_iii.union_set(bi->v1, bi->v2);
            }
        } else {
            cout << 'n';
        }

        /** Finding the smallest p to succeed in all missions **/
        if (d > smallest_p_for_all) {
            // since d must be at most equal to w
            // w must be equal to the largest d out of all missions
            // that succeed under the predicate p
            // therefore, here the smallest p gets updated everytime, the required p
            // to make the current mission succeed is bigger than the previous one
            smallest_p_for_all = d;
        }
        for (; ai != edges.end(); ++ai) {
            if(part_ii.find_set(s_nearest->info()) == part_ii.find_set(t_nearest->info())) {
                break;
            }
            // building the set as we go
            part_ii.union_set(ai->v1, ai->v2);
        }

    }

    if (ai != edges.begin() && (ai-1)->squared_length > smallest_p_for_all) {
        smallest_p_for_all = (ai - 1)->squared_length;
    }
    if (bi != edges.begin() && (bi-1)->squared_length > smallest_p_for_i) {
        smallest_p_for_i = (bi - 1)->squared_length;
    }

    std::cout << endl << smallest_p_for_all << endl << smallest_p_for_i << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        problem();
    }
}