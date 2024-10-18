#ifndef ALGOENGI_IO_H
#define ALGOENGI_IO_H

#include "aligned_allocator.h"
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <omp.h>

template<class T>
using aligned_vector = std::vector<T, aligned_allocator<T, 64>>;

typedef struct {
    aligned_vector<float> x_coordinates;
    aligned_vector<float> y_coordinates;
    int size;
} dataframe;

/**
 * Reads a csv file and saves the x- and y-coordinates in a dataframe
 *
 * @param import_path Path to the csv file
 * @param file_type File extension of the imported file. Can be .csv or .tsv. Depending on the extension the import differs.
 * @return The dataframe containing the coordinates read from the csv file
 */
dataframe read_csv(std::string& import_path, std::string& file_type);

/**
 * Writes the x- and y-coordinates from a dataframe to a csv file. Because there are multiple time points, the frame
 * is also added to the file as an additional column. This is important for the visualization of the point movement.
 *
 * @param an_output_path Path to the folder the file should be saved
 * @param a_df The dataframe from which the data should be saved
 * @param frame Indicator of the time point
 */
void write_csv(std::string& an_output_path, dataframe& a_df, int& frame);

/**
 * Source: https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
 * Reads a string 'option' in the range between two characters 'begin' and 'end'
 *
 * @param begin Pointer to the first character
 * @param end Pointer to the last character
 * @param option String to look after
 * @return The string to extract from the input if it exists, nullptr otherwise
 */
char* get_cmd_option(char** begin, char** end, const std::string& option);

/**
 * Source: https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
 * Checks whether the input string exists at all.
 *
 * @param begin Pointer to the first character of the input string
 * @param end Pointer to the last character of the input string
 * @param option String to search for in between the first and last character
 * @return true if the string exists, false if not
 */
bool does_cmd_option_exist(char** begin, char** end, const std::string& option);

/**
 * Opens a GUI for the user to draw the starting shape. The drawn shape is converted to x- and y-coordinates.
 *
 * @return A dataframe containing the coordinates of the drawn shape.
 */
dataframe get_user_shape();

#endif //ALGOENGI_IO_H