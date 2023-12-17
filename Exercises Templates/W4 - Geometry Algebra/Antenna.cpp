#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

// CGAL includes
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef  K::Point_2 Point;
typedef CGAL::Min_circle_2<Traits> Min_circle;


double ceil_to_double(const K::FT& x)
{
    double a = std::ceil((CGAL::to_double(x)));
    while (a-1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}


// https://doc.cgal.org/latest/Bounding_volumes/classCGAL_1_1Min__circle__2.html
void problem(size_t n) {

    /** === Getting the inputs === **/
    // getting ray coordinates and constructing the ray
    // !!! OMG, USE LONG, WITH INT IT DOESN'T GIVE CORRECT ANSWER !!!
    vector<Point> positions(n);
    for(size_t i = 0; i < n; i++) {
        long x, y;
        cin >> x >> y;
        positions[i] = Point(x, y);
    }

    Min_circle mc(positions.begin(), positions.end(), true);
    Traits::Circle c = mc.circle();

    auto radius_smallest_enclosing_circle = CGAL::sqrt(c.squared_radius());

    cout << long(ceil_to_double(radius_smallest_enclosing_circle)) << "\n";
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

