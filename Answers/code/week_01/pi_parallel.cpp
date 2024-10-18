#include <iomanip>
#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int num_steps = 100000000; // number of rectangles
    double width = 1.0 / double(num_steps); // width of a rectangle
    double sum = 0.0; // sum of all heights of rectangles

    double start_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < num_steps; i++) { // integration over all rectangles
        double x = (i + 0.5) * width;
        sum += (1.0 / (1.0 + x * x));
    }
    double pi = 4 * sum * width;
    double run_time = omp_get_wtime() - start_time;

    cout << "Pi with " << num_steps << " steps is " << setprecision(17) << pi << " in " << setprecision(8) <<
    run_time << " seconds" << endl;
}