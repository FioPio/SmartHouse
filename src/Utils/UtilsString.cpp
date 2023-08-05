#include "../include/project/Utils.h"

#include <sstream>


/**
 * Splits a string into smaller strings using the provided delimiter.
 */
std::vector<std::string> Utils::String::splitString(
        const std::string& input_string, const std::string& delimiter) {
    
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = input_string.find(delimiter);

    while (end != std::string::npos) {

        tokens.push_back(input_string.substr(start, end - start));
        start = end + delimiter.length();
        end = input_string.find(delimiter, start);
    }

    tokens.push_back(input_string.substr(start));

    return tokens;
}


/**
 * Replaces the indicated substrings for others in a string.
 */
std::string Utils::String::replaceString(const std::string& input_string, 
                                         const std::string& search_substring, 
                                         const std::string& replace_substring) {

    std::string result = input_string;
    size_t pos = 0;

    while ((pos = result.find(search_substring, pos)) != std::string::npos) {
        result.replace(pos, search_substring.length(), replace_substring);
        pos += replace_substring.length();
    }

    return result;
}
