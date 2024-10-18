#include <iostream>
#include <omp.h>
#include <iomanip>
#include <mutex>

using namespace std;

int main() {

    mutex m;
    int num_steps = 100000000;
    double width = 1.0 / num_steps;
    double pi = 0.0;

    double start_time = omp_get_wtime();
#pragma omp parallel num_threads(4)
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        double sum_local = 0.0; // for summing up heights locally
        for (int i = thread_id; i < num_steps; i += num_threads) {
            double x = (i + 0.5) * width; // midpoint
            sum_local = sum_local + (1.0 / (1.0 + x * x)); // add new height
        }
        lock_guard<mutex> a_lock_guard(m);
        pi += sum_local * 4 * width;
    }
    double run_time = omp_get_wtime() - start_time;

    cout << "Pi with " << num_steps << " steps is " << setprecision(8) << pi << " in " << setprecision(8) <<
         run_time << " seconds" << endl;
}
