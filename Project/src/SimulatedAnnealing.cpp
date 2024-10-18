#include "MathUtil.h"
#include "SimulatedAnnealing.h"
#include "IO.h"
#include <iostream>
#include <parallel/algorithm>
#include <cmath>
#include <random>
#include <vector>

bool is_error_okay(statistics& old_stats, statistics& new_stats) {
    if (MathUtil::statistical_error(old_stats.x_mean, new_stats.x_mean, 2) > std::numeric_limits<float>::epsilon()) return false;
    if (MathUtil::statistical_error(old_stats.y_mean, new_stats.y_mean, 2) > std::numeric_limits<float>::epsilon()) return false;
    if (MathUtil::statistical_error(old_stats.x_std, new_stats.x_std, 2) > std::numeric_limits<float>::epsilon()) return false;
    if (MathUtil::statistical_error(old_stats.y_std, new_stats.y_std, 2) > std::numeric_limits<float>::epsilon()) return false;
    if (MathUtil::statistical_error(old_stats.pearson_correlation, new_stats.pearson_correlation, 2) > std::numeric_limits<float>::epsilon()) return false;
    return true;
}

dataframe perturb_once(dataframe& a_df, Shape& target_shape, float& shake, float& allowed_distance,
                       float& temperature, uint64_t& s0, uint64_t& s1) {

    // define the borders within which the points are allowed to move
    float x_bounds[2] = {0.0, 100.0};
    float y_bounds[2] = {0.0, 100.0};

    // take one row at random that will be perturbed
    int random_position = MathUtil::get_int_uniform_distribution(s0, s1, a_df.size - 1);
    float x_original = a_df.x_coordinates[random_position];
    float y_original = a_df.y_coordinates[random_position];

    // for the simulated annealing part, draw a random 'temperature' (unif) which defines whether we accept a worse state of the system
    double random_temperature = MathUtil::get_double_uniform_distribution(s0, s1);
    bool accept_worse_state = random_temperature < temperature;

    // new x- and y-coordinates
    float x_new;
    float y_new;

    while (true) {

        // perturb the points a little
        float x_perturbed = x_original + MathUtil::get_double_normal_distribution(s0, s1) * shake;
        float y_perturbed = y_original + MathUtil::get_double_normal_distribution(s0, s1) * shake;

        // minimum distances of the original point and the slightly shifted point to the closest LineShape of the shape to perturb towards
        float min_old_distance;
        float min_new_distance;

        min_old_distance = target_shape.get_minimal_distance(x_original, y_original);
        min_new_distance = target_shape.get_minimal_distance(x_perturbed, y_perturbed);

        // check if new distance is shorter than old distance, or if distance is less than given allowed distance,
        // or if we accept the new state because of the temperature (annealing)
        if ((min_new_distance < min_old_distance or min_new_distance < allowed_distance or accept_worse_state)
            and x_perturbed > x_bounds[0] and x_perturbed < x_bounds[1] and y_perturbed > y_bounds[0] and y_perturbed < y_bounds[1]){
            x_new = x_perturbed;
            y_new = y_perturbed;
            break;
        }
    }

    // copy the original x- and y-coordinates and change the value at the given index
    dataframe new_df = a_df;
    new_df.x_coordinates[random_position] = x_new;
    new_df.y_coordinates[random_position] = y_new;

    return new_df;
}

dataframe run_perturbations(dataframe& a_df, parameter_set& parameters, Shape& target_shape, std::string& an_output_path) {

    // TODO: Find some way to make the seeds custom too?
    // set the seeds for the custom rng
    uint64_t seed0 = 1314482907319283471;
    uint64_t seed1 = 7870572464127067567;

    // define new dataframes
    dataframe current_df = a_df;
    dataframe new_df = a_df;

    // get the initial statistics
    statistics original_statistics = MathUtil::get_statistics(current_df);

    // perturb for n iterations
    int frame = 0;
    for (int i = 0; i < parameters.iterations; i++) {

        // get the temperature
        float smoothing_factor = (((float)parameters.iterations - (float)i) / (float)parameters.iterations);
        float temperature = (parameters.max_temperature - parameters.min_temperature) * MathUtil::smooth_curve(smoothing_factor) + parameters.min_temperature;

        // perturb once and get the new dataframe
        new_df = perturb_once(current_df, target_shape, parameters.additional_shake, parameters.allowed_distance,
                              temperature, seed0, seed1);

        // get new statistics
        statistics new_statistics = MathUtil::get_statistics(new_df);

        // check if the statistics are still the same
        if (is_error_okay(original_statistics, new_statistics)) {
            current_df = new_df;
            frame += 1;
            if (frame%1000 == 0) {
                int frame_num = int(frame/1000);
                write_csv(an_output_path, current_df, frame_num);
            }
        }
    }
    return new_df;
}