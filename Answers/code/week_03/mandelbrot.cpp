#include <complex>
#include <fstream>
#include <iostream>
#include <omp.h>

using namespace std;

constexpr int width = 4000;
constexpr int height = width;

int compute_pixel(int x, int y) { // compute the gray value of a pixel
    complex<double> point(2.0 * x / width - 1.5, 2.0 * y / height - 1.0);
    complex<double> z(0, 0);
    constexpr int iterations = 100;
    int nb_iter = 0;
    // test if point in mandelbrot set
    while (abs(z) < 2 && nb_iter < iterations) {
        z = z * z + point;
        nb_iter++;
    }
    // white color (255) if point in mandelbrot set, else a shade of gray
    return (255 * nb_iter) / iterations;
}

int main() { // generate mandelbrot pgm (portable graymap)
    const string image_name = "mandelbrot.pgm";
    remove(image_name.c_str()); // remove file from disk
    const double start = omp_get_wtime();
    ofstream image(image_name); // file output stream
    if (image.is_open()) {
        image << "P2\n" << width << " " << height << " 255\n"; // pgm header
#pragma omp parallel
        {   // start parallel region
            string buffer;  // each thread has its own string buffer
            buffer.reserve(width * 4);  // reserve enough memory to avoid reallocation
#pragma omp for ordered schedule(dynamic)
            for (int i = 0; i < height; i++) {
                buffer.clear(); // every new row, clear the content of the buffer again!
                for (int j = 0; j < width; j++) {
                    buffer += to_string(compute_pixel(j, i)) + "\t"; // fill the buffer
                }
#pragma omp ordered
                image << buffer;
            }
        };  // end parallel region
        image.close(); // close file output stream
    } else {
        cout << "Could not open the file!";
    }
    cout << omp_get_wtime() - start << " seconds" << endl;
}
