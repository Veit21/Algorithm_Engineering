#ifndef ALGOENGI_SIMULATEDANNEALING_H
#define ALGOENGI_SIMULATEDANNEALING_H

#include "MathUtil.h"
#include "aligned_allocator.h"
#include "IO.h"
#include "Shape.h"
#include <vector>
#include <cmath>
#include <string>

typedef struct {
    float additional_shake, allowed_distance, max_temperature, min_temperature;
    int iterations;
} parameter_set;

/**
 * Compares the old and new statistics.
 *
 * @param old_stats Original statistics (includes mean, sta. deviation and pearson correlation)
 * @param new_stats New statistics (includes mean, sta. deviation and pearson correlation)
 * @return true if all values are the same, false if one value deviates
 */
bool is_error_okay(statistics& old_stats, statistics& new_stats);

/**
 * Perturbs one random x,y coordinate of the input data once towards the given target shape.
 *
 * @param orig_df Original DataFrame
 * @param Shape Target shape object.
 * @param shake Maximum amount of movement allowed in each iteration
 * @param allowed_distance Minimal distance below which we always accept the new state of the system (new (x,y) coordinates)
 * @param temperature Virtual temperature for the simulated annealing part
 * @param s0 First seed to initialize the rng
 * @param s1 Second seed to initialize the rng
 * @return The manipulated dataframe
 *
 */
dataframe perturb_once(dataframe& orig_df, Shape& target_shape, float& shake, float& allowed_distance,
                       float& temperature, uint64_t& s0, uint64_t& s1);

/**
 * Start multiple perturbations to let the points move towards a desired shape
 *
 * @param a_df Dataframe with the initial coordinates of all points
 * @param parameters Struct that holds all necessary parameters for the simulated annealing algorithm
 * @param target_shape Shape to perturb towards
 * @return The perturbed dataframe after the last iteration
 */
dataframe run_perturbations(dataframe& a_df, parameter_set& parameters, Shape& target_shape, std::string& an_output_path);

#endif //ALGOENGI_SIMULATEDANNEALING_H