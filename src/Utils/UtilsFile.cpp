#include "../include/project/Utils.h"

#include <fstream>


/**
 * Reads the content of a file.
 */
std::vector<std::string> Utils::File::readFileContent(
                         const std::string& file_path) {
    
    // Opens the file from the provided path
    std::ifstream file(file_path);

    std::vector<std::string> file_content;
    
    // If the file could be open
    if (file.is_open()) {
        
        // Reads all the lines and adds each one to the vector
        std::string line;
        while (std::getline(file, line)) {

            file_content.push_back(line);
        }

        // Closes the file
        file.close();
    }
    else {
        
        // Print an error message
        Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_ERROR, 
                        "File could not be opened");
    }

    return file_content;
}