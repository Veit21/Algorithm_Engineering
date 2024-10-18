#include <omp.h>
#include <atomic>
#include <iostream>
#include <mutex>

using namespace std;

bool is_solution(int number) {  // test if number solves the problem
    for (volatile int i = 10000000; i--;) {}  // mock computation
    return number > 133 && number < 140;
}

int main() {
    mutex m;
    constexpr int biggest_possible_number = 10000;
    // To avoid undefined code, it is necessary to use std::atomic for variables
    // where race conditions may happen.
    // https://databasearchitects.blogspot.com/2020/10/c-concurrency-model-on-x86-for-dummies.html
    atomic<bool> solution_found(false);  // if true than we found the solution
    atomic<int> final_solution(INT32_MAX);
    const double start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic)  // start parallel region
    for (int i = 0; i < biggest_possible_number; ++i) {
        if (solution_found)  // we found the solution, just continue iterating
            continue;
        if (is_solution(i)) {     // find some solution, not necessary the smallest
            lock_guard<mutex> a_lock_guard(m);
            solution_found = true;
            final_solution = (final_solution.load() < i) ? final_solution.load() : i;
        }
    }  // end parallel region
    // check if we've found a solution at all is omitted, you can add the check
    cout << "The solution is: " << final_solution << endl;
    cout << omp_get_wtime() - start << " seconds" << endl;
}
