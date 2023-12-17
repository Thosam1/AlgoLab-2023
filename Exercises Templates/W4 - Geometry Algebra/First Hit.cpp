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
typedef std::result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type IT;

// !!! Learn this snippet in hello-exact.cpp !!!
double floor_to_double(const K::FT& x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

// clip/set target of s to o
void shorten_segment(K::Segment_2& s, const IT& o) {
    if (const K::Point_2* p = boost::get<K::Point_2>(&*o))
        s = K::Segment_2(s.source(), *p);
    else if (const K::Segment_2* t = boost::get<K::Segment_2>(&*o))
        // select endpoint of *t closer to s.source()
        if (CGAL::collinear_are_ordered_along_line (s.source(), t->source(), t->target()))
            s = K::Segment_2(s.source(), t->source());
        else
            s = K::Segment_2(s.source(), t->target());
    else
        throw std::runtime_error("Strange␣segment␣intersection.");
}

void problem(size_t n_segments) {

    /** === Getting the inputs === **/
    // getting ray coordinates and constructing the ray
    // !!! OMG, USE LONG, WITH INT IT DOESN'T GIVE CORRECT ANSWER !!!
    long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    K::Ray_2 r(K::Point_2(x1, y1), K::Point_2(x2, y2));

    // getting the segments and constructing them
    vector<K::Segment_2> segs;
    segs.reserve(n_segments);
    for (size_t i = 0; i < n_segments; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        segs.push_back(K::Segment_2(K::Point_2(x1, y1), K::Point_2(x2, y2)));
    }

    // read input

    // shufflling order of segments to avoid worst case scenario
    std::random_shuffle(segs.begin(), segs.end());

    /** === Solving the problem === **/
    // create the ray_clip
    // clip the ray at each segment hit (cuts down on the number of intersection
    // points to be constructed: for a uniformly random order of segments, the
    // expected number of constructions is logarithmic in the number of segments
    // that intersect the initial ray.)
    // The initial value of rc.target() is irrelevant. But we have to set it to
    // something, so why not r.point(1)?
    K::Segment_2 ray_clip(r.source(), r.point(1));

    // First part is to find a first intersection, so that we can clip the ray
    size_t clip_idx = 0;
    for(size_t i = 0; i < n_segments; i++) {
        if(CGAL::do_intersect(segs[i], r)) {
            // then we store the ray clipped
            shorten_segment(ray_clip, CGAL::intersection(segs[i], r));
            clip_idx = i;
            break;
        }
        clip_idx++;
    }

    // if the clip idx is equal to n_segments, there are no intersections !
    if(clip_idx == n_segments) {
        cout << "no\n";
        return;
    }

    // we continue the for loop where we left off
    for(size_t i = clip_idx; i < n_segments; i++) {
        if(CGAL::do_intersect(segs[i], ray_clip)) {
            // then we store the ray clipped
            shorten_segment(ray_clip, CGAL::intersection(segs[i], r));
        }
    }

    cout << floor_to_double(ray_clip.target().x()) << " " << floor_to_double(ray_clip.target().y()) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    for (std::size_t n; std::cin >> n && n > 0;)
        problem(n);
}

/** No idea why it doesn't work **/
//void tests() {
//    int n_segments = 0;
//    // reads number of segments
//    cin >> n_segments;
//    // for each test case we repeat the following
//    while(n_segments > 0) {
//        problem(n_segments);
//    }
//}
//int main() {
//    std::ios_base::sync_with_stdio(false); // Always!
//    // !!! important !!!
//    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
//    tests();
//}

