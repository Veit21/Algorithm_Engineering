#include <iomanip>
#include <iostream>
#include <omp.h>
#include <thread>
#include <mutex>

using namespace std;

void integrate(double& global_sum, int thread_id, int num_steps, int num_threads, double width, mutex& m) {
    double local_sum = 0.0;
    for (int i = thread_id; i < num_steps; i += num_threads) { // integration over all rectangles
        double x = (i + 0.5) * width;
        local_sum += (1.0 / (1.0 + x * x));
    }
    lock_guard<mutex> a_lock_guard(m);
    global_sum += local_sum;
}

int main() {
    mutex m;
    int num_threads = 8;
    thread threads[num_threads];
    int num_steps = 100000000; // number of rectangles
    double width = 1.0 / double(num_steps); // width of a rectangle
    double sum = 0.0; // sum of all heights of rectangles

    double start_time = omp_get_wtime();

    // start all other threads
    for (int i = 1; i < num_threads; i++) {
        threads[i] = thread(integrate, ref(sum), i, num_steps, num_threads, width, ref(m));
    }

    // master thread
    integrate(sum, 0, num_steps, num_threads, width, m);

    // join threads again
    for (int i = 1; i < num_threads; i++) {
        threads[i].join();
    }

    double pi = 4 * sum * width;
    double run_time = omp_get_wtime() - start_time;

    cout << "Pi with " << num_steps << " steps is " << setprecision(17) << pi << " in " << setprecision(8) <<
         run_time << " seconds" << endl;
}