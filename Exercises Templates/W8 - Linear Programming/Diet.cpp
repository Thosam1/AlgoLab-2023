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
    // nb food
    int m;
    cin >>  m;

    vector<pair<int, int>> nutriments(n);
    vector<pair<int, vector<int>>> food(m);

    for(int i = 0; i < n; i++) {
        int min, max;
        cin >> min >> max;
        nutriments[i] = make_pair(min, max);
    }

    for(int j = 0; j < m; j++) {
        int price;
        cin >> price;

        vector<int> nuts(n);
        for(int i = 0; i < n; i++) {
            cin >> nuts[i];
        }
        food[j] = make_pair(price, nuts);
    }
    /** ======== **/

    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, true, 0, false, 0);

    // iterating over the nutriments
    for (int i = 0; i < n; ++i) {

        int min = nutriments[i].first;
        int max = nutriments[i].second;

        // iterating over the food
        for(int j = 0; j < m; j++) {
            // calories for nutrient_i, given by current food_j
            int calories = food[j].second[i];

            // 2 boundary for each nutrient
            lp.set_a(j, i, calories); lp.set_b(i, max);
            lp.set_a(j, n+i, -calories); lp.set_b(n+i, -min);
        }
    }

    // setting the objective function
    for(int j = 0; j < m; j++) {
        lp.set_c(j, food[j].first);
    }



    /** Finding the solution **/
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_optimal()) {
        cout << floor(CGAL::to_double(s.objective_value())) << endl;
    }else if (s.is_infeasible()) {
        std::cout << "No such diet." << endl;
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