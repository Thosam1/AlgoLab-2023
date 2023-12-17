#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

using namespace std;

// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct coord {
    int x, y;
};

void problem() {

    /** === Getting the inputs === **/
    //nb new posters
    int n;
    cin >> n;
    // nb old posters
    int m;
    cin >>  m;
    // height
    int h;
    cin >>  h;
    // width
    int w;
    cin >>  w;

    // new posters
    vector<coord> red_rects(n);
    // old posters
    vector<coord> blue_rects(m);

    for(int i = 0; i < n; i++) {
        cin >> red_rects[i].x >> red_rects[i].y;
    }
    for(int i = 0; i < m; i++) {
        cin >> blue_rects[i].x >> blue_rects[i].y;
    }

    /** ======== **/

    // create an LP with Ax <= b, lower bound 1 (a_i cannot be lower than 1) and no upper bounds
    Program lp (CGAL::SMALLER, true, 1, false, 0);

    // red/red constraints
    // iterate to get all possible pairs
    // total size / nb of rows of matrix A = n choose 2
    int row = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            // row represents the current row of matrix A

            ET dx = abs(red_rects[i].x - red_rects[j].x);
            ET dy = abs(red_rects[i].y - red_rects[j].y);

            lp.set_a(i, row, 1);
            lp.set_a( j, row, 1 );
            lp.set_b( row, 2 * max( dx/w, dy/h ) );
            row++;
        }
    }

    // red/blue constraints
    // iterate to get all possible pairs
    for(int i = 0; i < n; i++) {
        ET limit = 33554432; // safe because from Section 4 we know that a_i < 2^25
        for(int j = 0; j < m; j++) {
            ET dx = abs( red_rects[i].x - blue_rects[j].x );
            ET dy = abs( red_rects[i].y - blue_rects[j].y );
            ET current_limit = 2 * std::max( dx/w, dy/h ) - 1;

            // if the constraint we find here is above the instruction,
            // we overwrite the limit to be equal to the one given
            // in the instructions -> a_i < 2^25
            limit = std::min( limit, current_limit );
        }

        // setting an upper boud for each a_i coefficient !

        lp.set_u( i, true, limit );

    }

    // setting the objective function
    for(int i = 0; i < n; i++) {
        lp.set_c(i, -2 * (w + h));
    }

    /** Finding the solution **/
    Solution s = CGAL::solve_linear_program(lp, ET());
    cout << ceil(CGAL::to_double(-s.objective_value())) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    // !!! Very important !!!
    cout << fixed << std::setprecision( 0 );

    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        problem();
    }
}