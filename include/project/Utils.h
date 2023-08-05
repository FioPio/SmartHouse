#pragma once

#include <string>
#include <vector>

#include <curl/curl.h>

/**
 * Headers showed before the message loggings
 */
#define LOG_LEVEL_INFO_HEADER    "[INFO]"
#define LOG_LEVEL_SYSTEM_HEADER  "[SYST]"
#define LOG_LEVEL_WARNING_HEADER "[WRNG]"
#define LOG_LEVEL_ERROR_HEADER   "[ERRO]"
#define LOG_LEVEL_DEBUG_HEADER   "[DEBG]"

/**
 * Utility namespace containing other namespaces for auxiliary purposes.
 */
namespace Utils {

    /**
     * Utility namespace containing logging functionality.
     */
    namespace Log {

        /**
         * Enumeration of different log levels.
         */
        enum class LogLevel {
            LOG_LEVEL_INFO,     /**< Informational messages. */
            LOG_LEVEL_SYSTEM,   /**< System-related messages. */
            LOG_LEVEL_WARNING,  /**< Warning messages. */
            LOG_LEVEL_ERROR,    /**< Error messages. */
            LOG_LEVEL_DEBUG     /**< Debugging messages. */
        };


        /**
         * Convert a log level enum to its corresponding log level header text.
         *
         * This function maps a given log level enumeration value to the
         * corresponding log level header text.
         *
         * @param log_level The log level enumeration value.
         * @return The corresponding log level header text.
         */
        const char* logLevelToString(LogLevel log_level);


        /**
         * Log a message with the specified log level.
         *
         * @param log_level The log level of the message.
         * @param message The message to be logged.
         */
        void log(LogLevel log_level, const std::string& message);
    };

    /**
     * Utility namespace containing Http requests functionality.
     */
    namespace HttpRequests {

        /**
         * Enumeration of different types of content the request may contain.
         */
        enum class ContentType {
            CONTENT_TYPE_TEXT,   /**< Text type of data. */
            CONTENT_TYPE_IMAGE,  /**< Image type of data. */
            CONTENT_TYPE_AUDIO,  /**< Audio type of data. */
            CONTENT_TYPE_VIDEO   /**< Video type of data. */
        };

        /**
         * A struct holing all the relevant data for the post field.
         */
        struct ContentData {
            std::string key;           /**< Request field where to put the value. */
            std::string value;         /**< Content of the field. */
            ContentType content_type;  /**< Type of data for the value. */

            /**
             * Default constructor.
             */
            ContentData() {}

            /**
             * Constructor that already sets all the data.
             * 
             * @param key_to_set Request field where to put the value.
             * @param value_to_set Content of the field.
             * @param content_type_to_set  Type of data for the value. 
             */
            ContentData(std::string key_to_set, 
                        std::string value_to_set, 
                        ContentType content_type_to_set) : 
                            key(key_to_set), 
                            value(value_to_set), 
                            content_type(content_type_to_set) {}

        };

        /**
         * A class that manages the requests.
         */
        class RequestExecutor {
            
            std::string request_url;           /**< URL used for the request. */
            std::vector<ContentData> contents; /**< Content added to the request. */

            /**
             * Fill the content of the post with the provided data.
             *
             * @param post Pointer to pointer used by curl.
             * @param last Pointer to pointer used by curl.
             * @param content Content used to fill the post.
             */
            void setPostContents(curl_httppost** post, curl_httppost** last);

        public:

            /**
             * Default constructor.
             */
            RequestExecutor() {}

            /**
             * Constructor that already saves the request url.
             * 
             * @param request_url_to_set The request URL.
             */
            RequestExecutor(const std::string& request_url_to_set) : 
                                           request_url(request_url_to_set) {}
                                    
            /**
             * To set the request URL.
             * 
             * @param request_url_to_set The request URL.
             */
            void setRequestUrl(const std::string& request_url_to_set);

            /**
             * To get the request URL.
             * 
             * @return the request URL.
             */
            std::string getRequestUrl() const;

            /**
             * Adds text into the request.
             * 
             * @param key The field of the request that is set.
             * @param text The value of the field of the request that is set.
             */
            void addTextContent(const std::string& key, const std::string& text);

            /**
             * Adds an image into the request.
             * 
             * @param key The field of the request that is set.
             * @param image The content of the field of the request that is set.
             */
            void addImageContent(const std::string& key, const std::string& image);

            /**
             * Gets the content of the request.
             * 
             * @return A vector with all the post content.
             */
            std::vector<ContentData> getContents() const;

            /**
             * Executes the request.
             * 
             * @return A string with the content of the response in JSON format.
             */
            std::string executeRequest();
        };
    };


    /**
     * Utility namespace to interact with files.
     */
    namespace File {

        /**
         * Reads the content of a file.
         * 
         * @param file_path The path to the file that has to be read.
         * @return A vector that contains every line in the file.
         */
        std::vector<std::string> readFileContent(const std::string& file_path);
    };

    
    /**
     * Utility namespace to manipulate strings.
     */
    namespace String {

        /**
         * Splits a string into smaller strings using the provided delimiter.
         * 
         * @param input_string The string that will be split.
         * @param delimiter The string that will be used as delimiter.
         * @return A vector that contains all the sub strings.
         */
        std::vector<std::string> splitString(const std::string& input_string, 
                                             const std::string& delimiter);


        /**
         * Replaces the indicated substrings for others in a string.
         * 
         * @param input_string The string that contains all the text.
         * @param search_substring The string that will be replaced.
         * @param replace_substring The string that will be added.
         * @return A string with the modifications.
         */
        std::string replaceString(const std::string& input_string, 
                                  const std::string& search_substring, 
                                  const std::string& replace_substring);
    };
};