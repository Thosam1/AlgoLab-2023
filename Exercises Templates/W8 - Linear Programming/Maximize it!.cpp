#include "stdc++.h" // don't forget to set it back to
// #include <bits/stdc++.h>

using namespace std;

// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void solve_1(int a, int b) {

    // create an LP with Ax <= b, lower bound 0 and no upper bounds (for the x, y variables !)
    Program lp (CGAL::SMALLER, true, 0, false, 0);

    // set the coefficients of A and b
    const int X = 0;
    const int Y = 1;
    lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);  //  x + y  <= 4
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b);  // 4x + 2y <= ab
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);  // -x + y <= 1

    // objective function
    lp.set_c(X, a);                                       // ax
    lp.set_c(Y, -b);                                        // -by
    lp.set_c0(0);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());

    // output solution
    if(s.is_infeasible()) {
        cout << "no\n";
    } else if(s.is_unbounded()) {
        cout << "unbounded\n";
    } else if(s.is_optimal()) {
        cout << -1 * ceil(CGAL::to_double(s.objective_value())) << endl;
    }
}

void solve_2(int a, int b) {
    // create an LP with Ax >= b, lower bound 0 and no upper bounds (for the x, y, z variables !)
    Program lp (CGAL::SMALLER, false, 0, true, 0);

    // set the coefficients of A and b
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    lp.set_a(X, 0,  -1); lp.set_a(Y, 0, -1); lp.set_a(Z, 0,  0); lp.set_b(0, 4);  //  -x - y  <= 4
    lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1,  -1); lp.set_b(1, a * b);  // -4x - 2y - z <= ab
    lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_a(Z, 2,  0); lp.set_b(2, 1);  // x - y <= 1

    // objective function
    lp.set_c(X, a);                                       // ax
    lp.set_c(Y, b);                                        // by
    lp.set_c(Z, 1);                                        // z

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());

    // output solution
    if(s.is_infeasible()) {
        cout << "no\n";
    } else if(s.is_unbounded()) {
        cout << "unbounded\n";
    } else if(s.is_optimal()) {
        cout << ceil(CGAL::to_double(s.objective_value())) << endl;
    }
}

void problem(int p) {

    /** === Getting the inputs === **/
    // nb missions
    int a, b;
    cin >> a >> b;

    /** ======== **/

    if(p==1) {
        solve_1(a, b);
    }
    if(p==2) {
        solve_2(a, b);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int p;
    cin >> p;
    while(p != 0) {
        problem(p);
        cin >> p;
    }
}