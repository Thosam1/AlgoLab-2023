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


void problem(int n) {

    /** === Getting the inputs === **/
    // nb missions
    int d;
    cin >>  d;

    /** ======== **/

    // create an LP with Ax <= b, lower bound 0 and no upper bounds (for the x, y variables !)
    Program lp (CGAL::SMALLER, false, 0, false, 0);

    for (int i = 0; i < n; ++i) {
        int norm_2 = 0;

        // getting (a_i)j with j in [0, d-1]
        // j replaces x, y, z, ...
        for (int j = 0; j < d; ++j) {
            IT ai;
            std::cin >> ai;
            norm_2 += ai * ai;

            // j is the variable
            // i is the row in matrix
            // ai is the value
            // so for matrix A, we have n rows, d columns of ai + 1 column containing the norm2 of ai
            // x is composed of d values for coefficients (x, y, z, ...) + 1 value d which represents the radius to maximize
            lp.set_a(j, i, ai);
        }

        // check that the norm is indeed an integer
        int norm = std::floor(std::sqrt(norm_2));
        if (norm_2 != norm * norm)
            throw std::runtime_error("Error:␣norm_2!=␣norm*norm.\n");

        // also storing the norm as inequality
        lp.set_a(d, i, norm);

        // setting the bi values
        IT bi;
        std::cin >> bi;
        lp.set_b(i, bi);
    }

    // setting the objective function
    lp.set_c(d, -1); // inverting coefficient sign to maximize value of d instead

    // setting up lower bound on d
    lp.set_l(d, true, 0);

    /** Finding the solution **/
    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible()) {
        std::cout << "none\n";
    } else if (s.is_unbounded()) {
        std::cout << "inf\n";
    } else {
        std::cout << - (s.objective_value().numerator() / s.objective_value().denominator()) << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while(n != 0) {
        problem(n);
        cin >> n;
    }
}