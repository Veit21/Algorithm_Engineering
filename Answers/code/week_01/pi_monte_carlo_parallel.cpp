#include <iostream>
#include <iomanip>
#include <random>
#include <omp.h>

using namespace std;

int main() {
    const int seed = 0;
    default_random_engine re{seed};
    uniform_real_distribution<double> zero_to_one{0.0, 1.0};

    int steps = 100000000;
    int counter = 0;
    double start_time = omp_get_wtime();

#pragma omp parallel for reduction(+ : counter)
    for (int i = 0; i < steps; i++) {
        double x = zero_to_one(re);
        double y = zero_to_one(re);
        if (x * x + y * y < 1.0)
            ++counter;
    }
    double pi = 4 * (double(counter) / steps);
    double run_time = omp_get_wtime() - start_time;

    cout << "pi " << pi << endl;
    cout << "steps " << steps << endl;
    cout << "time " << setprecision(6) << run_time << "s" << endl;
}