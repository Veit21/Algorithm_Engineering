#include "MathUtil.h"
#include "IO.h"
#include <omp.h>
#include <cmath>

// MathUtil member functions
float MathUtil::get_mean(const float *__restrict a_vector, int number_elements) {
    float sum_elements = 0;
#pragma omp simd reduction(+ : sum_elements) aligned(a_vector: 64)
    for (int i = 0; i < number_elements; i++) {
        sum_elements += a_vector[i];
    }
    float mean = sum_elements / (float)number_elements;
    return mean;
}

float MathUtil::get_std(const float *__restrict a_vector, float mean, int number_elements) {
    float variance = 0;
#pragma omp simd reduction(+ : variance) aligned(a_vector: 64)
    for (int i = 0; i < number_elements; i++) {
        variance += (a_vector[i] - mean) * (a_vector[i] - mean);
    }
    variance /= (float)number_elements;
    return sqrt(variance);
}

float MathUtil::get_pearson_correlation(const float *__restrict vector_x, float mean_x, float std_x,
                                        const float *__restrict vector_y, float mean_y, float std_y,
                                        int number_elements) {
    float sum = 0.0;
#pragma omp simd reduction(+ : sum) aligned(vector_x, vector_y: 64)
    for (int i = 0; i < number_elements; i++){
        sum += (vector_x[i] - mean_x) * (vector_y[i] - mean_y);
    }
    float covariance = sum / (float)number_elements;
    return covariance / (std_x * std_y);
}

float MathUtil::statistical_error(float first_value, float second_value, int decimals) {
    float first_value_floor = floor(first_value * pow(10.0, decimals));
    float second_value_floor = floor(second_value * pow(10.0, decimals));
    return fabs(first_value_floor - second_value_floor);
}

statistics MathUtil::get_statistics(dataframe& a_df) {
    float x_mean = get_mean(a_df.x_coordinates.data(), a_df.size);
    float y_mean = get_mean(a_df.y_coordinates.data(), a_df.size);
    float x_std = get_std(a_df.x_coordinates.data(), x_mean, a_df.size);
    float y_std = get_std(a_df.y_coordinates.data(), y_mean, a_df.size);
    float pearson_correlation = get_pearson_correlation(a_df.x_coordinates.data(), x_mean, x_std,
                                                        a_df.y_coordinates.data(), y_mean, y_std,
                                                        a_df.size);

    // Declare and initialize a struct which holds all the statistical data
    statistics stats = {
            .x_mean = x_mean,
            .y_mean = y_mean,
            .x_std = x_std,
            .y_std = y_std,
            .pearson_correlation = pearson_correlation,
    };
    return stats;
}

float MathUtil::get_line_magnitude(float &x1, float &y1, float &x2, float &y2) {
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    auto magnitude = (float)sqrt(delta_x * delta_x + delta_y * delta_y);
    return magnitude;
}

float MathUtil::get_minimal_distance_point_line(float &point_x, float &point_y, float x1, float y1, float x2, float y2) {
    float length_squared = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)); // magnitude of the line segment
    if (length_squared == 0)
        return get_line_magnitude(x1, y1, point_x, point_y); // doesn't matter if we return distance to (x1, y1) or (x2, y2) because they are the same

    // extend the line segment and project the point P(x, y) on it
    float dot_product = (((point_x - x1) * (x2 - x1)) + ((point_y - y1) * (y2 - y1))) / length_squared;
    float upper_border = (1.0 < dot_product) ? 1.0 : dot_product;
    float t = (0.0 > upper_border) ? 0.0 : upper_border;
    float projected_x = x1 + t * (x2 - x1);
    float projected_y = y1 + t * (y2 - y1);
    return get_line_magnitude(projected_x, projected_y, point_x, point_y);
}

float MathUtil::smooth_curve(float &a_value) {
    if (a_value < 0.5f) {
        return 2 * a_value * a_value;
    }
    else {
        float value = a_value * 2 - 1;
        return -0.5f * (value * (value - 2) - 1);
    }
}

uint64_t MathUtil::rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k)); // rotate
}

uint64_t MathUtil::xoroshiro128plus(uint64_t &s0, uint64_t &s1) {
    s1 ^= s0;                            // modify s1
    s0 = rotl(s0, 24) ^ s1 ^ (s1 << 16); // modify s0
    s1 = rotl(s1, 37);                   // modify s1
    return s0 + s1;
}

double MathUtil::get_double_uniform_distribution(uint64_t &s0, uint64_t &s1) {
    uint64_t random_int = xoroshiro128plus(s0, s1);
    const union {
        uint64_t i;
        double d;
    } u =  {.i = UINT64_C(0x3FF) << 52 | random_int >> 12};
    return u.d - 1.0;
}

int MathUtil::get_int_uniform_distribution(uint64_t &s0, uint64_t &s1, int n) {
    return (int) round(get_double_uniform_distribution(s0, s1) * n);
}

double MathUtil::get_double_normal_distribution(uint64_t &s0, uint64_t &s1) {
    double random_unif1 = get_double_uniform_distribution(s0, s1);
    double random_unif2 = get_double_uniform_distribution(s0, s1);
    double some_constant = sqrt(-2 * log(random_unif1));
    double random_normal1 = some_constant * cos(2 * pi * random_unif2);
    double random_normal2 = some_constant * sin(2 * pi * random_unif2);
    return random_normal1;
}