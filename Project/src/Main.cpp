#include "IO.h"
#include "MathUtil.h"
#include "SimulatedAnnealing.h"
#include "Shape.h"
#include "json.hpp"
#include <fstream>
#include <omp.h>
#include <iostream>
#include <iomanip>

using json = nlohmann::json;

int main(int argc, char* argv[]){
    std::cout << std::setprecision(2) << std::fixed;

    // get user input -h
    if(does_cmd_option_exist(argv, argv+argc, "-h")) {
        std::cout << "\nOptions:" << std::endl;
        std::cout << "--preferences\tPath to the .json that contains the parameters" << std::endl;
    }

    // get user input for --preferences
    char *preferences = get_cmd_option(argv, argv + argc, "--preferences");

    // check for existence of preferences argument
    if(!preferences) {
        std::cout << "No argument for the preferences given!\nExit program." << std::endl;
        return 0;
    }

    // read the necessary data and parameters from the preferences.json
    std::ifstream preferences_path(preferences);

    // measure time
    double start_time = omp_get_wtime();

    // check if the file path is valid and set the parameters according to the .json - otherwise quit
    if (preferences_path) {
        json user_preferences = json::parse(preferences_path);
        preferences_path.close();

        // set parameters from file
        parameter_set parameters = {
                .additional_shake = user_preferences["parameters"]["additional_shake"],
                .allowed_distance = user_preferences["parameters"]["allowed_distance"],
                .max_temperature = user_preferences["parameters"]["max_temperature"],
                .min_temperature = user_preferences["parameters"]["min_temperature"],
                .iterations = user_preferences["parameters"]["iterations"],
        };

        std::string import_path = user_preferences["io"]["input_path"];
        std::string file_type = import_path.substr(import_path.find_last_of('.') + 1);
        std::ifstream import_path_test(import_path);

        // check if imported file (that should hold the data) exists and is of valid type
        if (!(import_path_test || file_type == "csv" || file_type == "tsv")){
            std::cout << "No valid import path!\nMake sure to give the path to a proper .csv/.tsv file!\nExit program."
            << std::endl;
            return 0;
        }
        // TODO: make a 'check_csv' method to assert the correctness of the data! Otherwise quit.
        dataframe df = read_csv(import_path, file_type);

        // calculate statistical properties of original dataset
        // region Original statistics
        statistics original_statistics = MathUtil::get_statistics(df);
        std::cout << "\nOriginal statistics:\n";
        std::cout << "x_mean: " << original_statistics.x_mean << "\ny_mean: " << original_statistics.y_mean << "\nx_std: " << original_statistics.x_std << "\ny_std: "<<
                  original_statistics.y_std << "\nPearson Correlation: " << original_statistics.pearson_correlation << std::endl;
        // endregion

        // TODO: remove fixes overwrite issue, but maybe not the most elegant solution
        // run multiple perturbations and save the data to a csv.file
        std::string output_path = user_preferences["io"]["output_path"];
        remove(output_path.c_str());
        std::string desired_shape = user_preferences["parameters"]["shape"];
        Shape& target_shape = get_shape(desired_shape);
        dataframe new_df = run_perturbations(df, parameters, target_shape, output_path);

        // calculate statistical properties of new dataset
        // region New statistics
        statistics  new_statistics = MathUtil::get_statistics(new_df);
        std::cout << "\nNew statistics:\n";
        std::cout << "x_mean: " << new_statistics.x_mean << "\ny_mean: " << new_statistics.y_mean << "\nx_std: " << new_statistics.x_std << "\ny_std: " <<
                  new_statistics.y_std << "\nPearson Correlation: " << new_statistics.pearson_correlation << std::endl;
        // endregion

    }
    else {
        std::cout << "\nPreferences file not found!\nPlease make sure to give the right path to the \'preferences.json\' file."
        << "with --preferences.\nExit program." << std::endl;
        return 0;
    }

    // measure time
    double run_time = omp_get_wtime() - start_time;
    std::cout <<"\nRuntime: " << run_time << "s" << std::endl;

    return 0;
}