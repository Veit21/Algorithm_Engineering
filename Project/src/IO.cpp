#include "IO.h"
#include <iostream>

dataframe read_csv(std::string& import_path, std::string& file_type) {

    // open file with coordinates
    std::fstream file;
    file.open(import_path);
    std::string line;

    // create map for coordinates
    aligned_vector<float> x_coords;
    aligned_vector<float> y_coords;
    int df_size = 0;

    // open the file and save data
    if (file.is_open()){

        // check the file extension
        if (file_type == "tsv") {

            // iterate file line by line and divide by a given delimiter (here tab-spaces)
            while (getline(file, line)){
                std::string delimiter = "\t";
                size_t pos_of_delimiter = line.find(delimiter);
                std::string line_title = line.substr(0, pos_of_delimiter); // first entry of example is the title

                // only read values of dino for testing
                if (line_title == "dino"){
                    line.erase(0, pos_of_delimiter + delimiter.length());
                    std::string entry;

                    while ((pos_of_delimiter = line.find(delimiter)) != std::string::npos) {
                        df_size += 1;
                        x_coords.push_back(stof(line.substr(0, pos_of_delimiter)));
                        line.erase(0, pos_of_delimiter + delimiter.length());
                        pos_of_delimiter = line.find(delimiter);
                        y_coords.push_back(stof(line.substr(0, pos_of_delimiter)));
                        line.erase(0, pos_of_delimiter + delimiter.length());
                    }
                }
            }
        }
        else if (file_type == "csv") {

            // read the data line by line
            while(getline(file, line)) {
                std::string delimiter = ",";
                size_t pos_of_delimiter = line.find(delimiter);

                while ((pos_of_delimiter = line.find(delimiter)) != std::string::npos) {
                    df_size += 1;
                    x_coords.push_back(stof(line.substr(0, pos_of_delimiter)));
                    line.erase(0, pos_of_delimiter + delimiter.length());
                    pos_of_delimiter = line.find(delimiter);
                    y_coords.push_back(stof(line.substr(0, pos_of_delimiter)));
                    line.erase(0, pos_of_delimiter + delimiter.length());
                }
            }
        }
        else {
            std::cout << "File is not from type .csv, nor from .tsv.\nGiving back empty data frame." << std::endl;
        }
        file.close();
    }

    dataframe df {
            .x_coordinates = x_coords,
            .y_coordinates = y_coords,
            .size = df_size,
    };

    return df;
}

void write_csv(std::string& an_output_path, dataframe& a_df, int& frame) {
    std::ofstream file;
    file.open(an_output_path, std::ios::app);
    if (file.is_open()) {
        std::string buffer;
        buffer.reserve(a_df.size * 4);
        for (int i = 0; i < a_df.size; ++i) {
            buffer += std::to_string(a_df.x_coordinates[i]) + "," + std::to_string(a_df.y_coordinates[i])
                    + "," + std::to_string(frame) + "\n";
        }
        file << buffer;
        buffer.clear();
        file.close();
    }
    else {
        std::cout << "Could not open the file!" << std::endl;
    }
}

bool does_cmd_option_exist(char** begin, char** end, const std::string& option) {
    return std::find(begin, end, option) != end; // if no elements match, returns 'end'
}

char* get_cmd_option(char** begin, char** end, const std::string& option) {
    char** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}