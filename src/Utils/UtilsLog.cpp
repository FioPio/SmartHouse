#include "../include/project/Utils.h"

#include <iostream>


// Convert a log level enum to its corresponding log level header text
const char* Utils::Log::logLevelToString(Utils::Log::LogLevel log_level) {

    switch (log_level) {

        case LogLevel::LOG_LEVEL_INFO: 
            return LOG_LEVEL_INFO_HEADER;

        case LogLevel::LOG_LEVEL_SYSTEM: 
            return LOG_LEVEL_SYSTEM_HEADER;

        case LogLevel::LOG_LEVEL_WARNING: 
            return LOG_LEVEL_WARNING_HEADER;

        case LogLevel::LOG_LEVEL_ERROR: 
            return LOG_LEVEL_ERROR_HEADER;

        case LogLevel::LOG_LEVEL_DEBUG: 
            return LOG_LEVEL_DEBUG_HEADER;

        default: 
            return "[????]"; // Default for unknown log level
    }
}


// Log a message with the specified log level
void Utils::Log::log(LogLevel log_level, const std::string& message) {

    if (log_level == LogLevel::LOG_LEVEL_DEBUG) {

        #ifdef NDEBUG
        // In release mode, skip printing DEBUG logs
        return;
        #endif
    }

    std::string log_level_text = logLevelToString(log_level);
    
    // Print the formatted log message
    std::cout << log_level_text << " " << message << std::endl;
}