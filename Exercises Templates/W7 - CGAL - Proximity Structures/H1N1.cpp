#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_with_info_2<double, K> Fb;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Fh;
typedef K::Point_2 Point;

using namespace std;

void problem(size_t n) {

    /** === Getting the inputs === **/
    // read existing points
    vector<Point> infected_people;
    for (size_t i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        infected_people.push_back(Point(x, y));
    }

    // construct triangulation
    Triangulation t;
    t.insert(infected_people.begin(), infected_people.end());

    // calculate for every face the max squared diameter of a disk that can escape and store it in the face info field
    // use a priority queue to always go from faces with biggest to faces with smallest escape values

    priority_queue<pair<double, Fh>> q;

    // initializing faces with escape value of infinite
    // so we start with them in the priority queue
    for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
        if(t.is_infinite(f)) {
            f->info() = INT64_MAX;
            q.emplace(INT64_MAX, f);
        } else {
            f->info() = 0;
        }
    }

    while(!q.empty()) {
        Fh curr_face = q.top().second;
        q.pop();

        // update the three neighbours
        for(int i = 0; i < 3; i++) {
            // returns the length of the segment divided by 2 associated with the ith edge of the current face (to get the radius)
            double curr_escape_radius = sqrt(t.segment(curr_face, i).squared_length()) / 2;

            // check if the current edge has the max_escape value
            double curr_max_escape_radius = min(curr_face->info(), curr_escape_radius);

            // returns the face that shares the ith edge with the current face
            Fh neighbor = curr_face->neighbor(i);

            // if the neighbor max escape value radius is smaller (likely to be equal to 0 at the beginning) than the current one,
            // we must update it, since we would want to escape through them
            // then we are done with the current face
            if (neighbor->info() < curr_max_escape_radius)
            {
                neighbor->info() = curr_max_escape_radius;
                q.emplace(neighbor->info(), neighbor);
            }
        }
    }


    // read number of possible points
    std::size_t m;
    std::cin >> m;

    // directly solve the algorithm here, avoiding 2 for loops and useless memory usage !
    for (std::size_t i = 0; i < m; ++i) {
        int x, y;
        double d;
        std::cin >> x >> y >> d;
        Point person = Point(x, y);

        /** PART 1 **/
        Triangulation::Vertex_handle nearest_vertex = t.nearest_vertex(person);
        // Calculate the Euclidean distance
        double squared_distance = CGAL::squared_distance(person, nearest_vertex->point());
        double distance = sqrt(squared_distance);

        // Looking if the current point is already too close to an infected point (within it's infecting radius)
        if(distance < sqrt(d)) {
            // means that the point lies within a "no safe zone"
            cout << "n";
        } else {

            /** PART 2 **/
            // Otherwise, we look which face the person is in, so that we can see if
            // the escape circles of it's 3 vertices overlap
            Fh f = t.locate(person);
            if(f->info() >= sqrt(d))
                cout << "y";
            else
                cout << "n";
        }
    }
    cout << "\n";
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

