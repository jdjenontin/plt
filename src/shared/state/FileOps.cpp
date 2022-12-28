#include "FileOps.h"
#include <fstream>
#include <unistd.h>
#include <iostream>

namespace state{

/**
 * @brief Parse a json file to a Json::Value object
*/
Json::Value FileOps::jsonParser(std::string a_path)
{
    std::ifstream file(a_path);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        char buffer[FILENAME_MAX];
        if (getcwd(buffer, FILENAME_MAX) != NULL) {
            std::cout << "Current working directory: " << buffer << std::endl;
        } 
        exit(1);
    }

    // Parse the JSON file
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errors;
    if (!Json::parseFromStream(builder, file, &root, &errors)) {
        std::cerr << "Error parsing JSON: " << errors << std::endl;
        exit(1);
    }

    return root;
}

/**
 * @brief Parse a csv file to a boolean array
*/
std::vector<std::vector<bool>> FileOps::csvParser(std::string a_path){
    std::ifstream file(a_path);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        char buffer[FILENAME_MAX];
        if (getcwd(buffer, FILENAME_MAX) != NULL) {
            std::cout << "Current working directory: " << buffer << std::endl;
        } 
        exit(1);
    }

    // Read the file line by line
    std::string line;
    std::vector<std::vector<bool>> array;
    while (std::getline(file, line))
    {
        // Split the line by commas
        std::stringstream ss(line);
        std::string cell;
        std::vector<bool> row;
        while (std::getline(ss, cell, ','))
        {
            // Convert the cell to an integer and add it to the row
            row.push_back((bool) std::stoi(cell));
        }
        // Add the row to the array
        array.push_back(row);
    }

    return array;
}

}