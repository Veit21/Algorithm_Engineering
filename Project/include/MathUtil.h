#ifndef ALGOENGI_MATHUTIL_H
#define ALGOENGI_MATHUTIL_H

#include "aligned_allocator.h"
#include "IO.h"
#include <vector>
#include <cmath>

template <class T>
using aligned_vector = std::vector<T, aligned_allocator<T, 64>>;

typedef struct {
    float x_mean, y_mean, x_std, y_std, pearson_correlation;
} statistics;

const double pi = M_PI;

// TODO: Make a test class in the end to show the rng holds with the statistics
class MathUtil {
private:

    /**
     * Source: Lecture Algorithm Engineering
     * Helper function for the scalar xoroshiro128+
     *
     * @param x Input value which will be modified
     * @param k Parameter which defines how the input will be shifted and rotated bitwise
     * @return Modified input value
     */
    static inline uint64_t rotl(const uint64_t x, int k);

public:

    /**
     * Calculate the mean of a list of values
     *
     * @param a_vector Pointer to the a_vector containing all values
     * @param number_elements Length of the input a_vector
     * @return The mean of the values
     */
    static float get_mean(const float *__restrict__ a_vector, int number_elements);

    /**
     * Calculate the standard deviation of a list of values
     *
     * @param a_vector Pointer to the a_vector containing all values
     * @param mean Mean of the values
     * @param number_elements Length of the input a_vector
     * @return The standard deviation of the values
     */
    static float get_std(const float *__restrict__ a_vector, float mean, int number_elements);

    /**
     * Calculate the pearson correlation of a set of (x, y) coordinates
     *
     * @param vector_x Pointer to the vector containing all x-coordinates
     * @param mean_x Mean of the x values
     * @param std_x Standard deviation of the x values
     * @param vector_y Pointer to the vector containing all x-coordinates
     * @param mean_y Mean of the y values
     * @param std_y Standard deviation of the y values
     * @param number_elements Length of the input vectors
     * @return The pearson correlation of the (x, y) coordinates
     */
    static float get_pearson_correlation(const float *__restrict__ vector_x, float mean_x, float std_x,
                                         const float *__restrict__ vector_y, float mean_y, float std_y, int number_elements);

    /**
     * Compares two values and gives back the difference with a defined precision
     *
     * @param first_value First value to be compared
     * @param second_value Second value to be compared
     * @param decimals Defines the precision with which the two values should be compared
     * @return The difference of both values with a set precision
     */
    static float statistical_error(float first_value, float second_value, int decimals);

    /**
     * Calculates mean, standard deviation and pearson correlation of the x- and y-coordinates
     *
     * @param a_df Dataframe for which the statistical properties shall be calculated
     * @return A struct which contains all the statistics
     */
    static statistics get_statistics(dataframe& a_df);

    /**
     * Calculates the magnitude of a LineShape segment defined by two points (x1, y1) and (x2, y2)
     *
     * @param x1 X coordinate of the first point.
     * @param y1 Y coordinate of the first point.
     * @param x2 X coordinate of the second point.
     * @param y2 Y coordinate of the second point.
     * @return The magnitude of a LineShape segment.
     */
    static float get_line_magnitude(float& x1, float& y1, float& x2, float& y2);

    /**
     * Source: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment/1501725#1501725
     * Calculates the minimal get_minimal_distance between a point P0(x0,y0) and a LineShape which is defined by two points P1(x1, y1) and
     * P2(x2, y2)
     *
     * @param point_x X coordinate of the point P0
     * @param point_y Y coordinate of the point P0
     * @param x1 X coordinate of the point P1
     * @param y1 Y coordinate of the point P1
     * @param x2 X coordinate of the point P2
     * @param y2 Y coordinate of the point P2
     * @return The minimal get_minimal_distance between the point P0 and the LineShape segment
     */
    static float get_minimal_distance_point_line(float &point_x, float &point_y, float x1, float y1, float x2, float y2);

    /**
     * Quadratically smooths a input value (?)
     *
     * @param a_value Value between 0 and 1 which will be smoothed
     * @return The smoothed value
     */
    static float smooth_curve(float& a_value);

    /**
     * Source: Lecture Algorithm Engineering
     * Scalar xoroshiro128+ random number generator
     *
     * @param s0 First seed
     * @param s1 Second seed
     * @return A random 64 bit integer
     */
    static inline uint64_t xoroshiro128plus(uint64_t &s0, uint64_t &s1);

    /**
     * Source: https://prng.di.unimi.it/
     * Generates a random double in the interval [0, 1)
     *
     * @param s0 First seed
     * @param s1 Second seed
     * @return Random double from the interval [0, 1)
     */
    static double get_double_uniform_distribution(uint64_t& s0, uint64_t& s1);

    /**
     * Generates a random integer value from the interval [1, n)
     *
     * @param s0 First seed
     * @param s1 Second seed
     * @param n Largest integer to be drawn from the distribution
     * @return Random integer from the interval [0, n)
     */
    static int get_int_uniform_distribution(uint64_t& s0, uint64_t& s1, int n);

    /**
     * Source: https://www.baeldung.com/cs/uniform-to-normal-distribution
     * Generates two random doubles from the standard normal distribution N(0, 1).
     * Samples of uniformly distributed values are transformed using the Box-Muller Transform.
     *
     * @param s0 First seed
     * @param s1 Second seed
     * @param random_normal1 Template for the first normally distributed random variable. Will be overwritten by this method
     * @param random_normal2 Template for the second normally distributed random variable. Will be overwritten by this method
     */
    static double get_double_normal_distribution(uint64_t& s0, uint64_t& s1);

};

#endif //ALGOENGI_MATHUTIL_H
