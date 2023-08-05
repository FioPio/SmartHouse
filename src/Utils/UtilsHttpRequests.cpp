#include "../include/project/Utils.h"



/**
 * Fill the content of the post with the provided data.
 */
void Utils::HttpRequests::RequestExecutor::setPostContents(curl_httppost** post, 
                                         curl_httppost** last) {
    
    for (const ContentData& content : contents) {

        const std::string& key_field = content.key;
        const std::string& content_value = content.value;

        switch (content.content_type) {

            case Utils::HttpRequests::ContentType::CONTENT_TYPE_TEXT:

                curl_formadd(post, last, CURLFORM_COPYNAME, key_field.c_str(), 
                            CURLFORM_COPYCONTENTS, content_value.c_str(), 
                            CURLFORM_END);

                break;

            case Utils::HttpRequests::ContentType::CONTENT_TYPE_IMAGE:

                curl_formadd(post, last, CURLFORM_COPYNAME, key_field.c_str(), 
                            CURLFORM_COPYCONTENTS, content_value.c_str(),
                            CURLFORM_CONTENTTYPE, "image/jpeg", CURLFORM_END);
                
                break;

        }
    }
}


/**
 * To set the request URL.
 */
void Utils::HttpRequests::RequestExecutor::setRequestUrl(
    const std::string& request_url_to_set) {

    request_url = request_url_to_set;
}
           

/**
 * To get the request URL.
 */      
std::string Utils::HttpRequests::RequestExecutor::getRequestUrl() const {

    return request_url;
}


/**
 * Adds text into the request.
 */
void Utils::HttpRequests::RequestExecutor::addTextContent(const std::string& key, 
                                                      const std::string& text) {

    ContentData this_text(key, text, 
                          Utils::HttpRequests::ContentType::CONTENT_TYPE_TEXT);
    
    contents.push_back(this_text);
}


/**
 * Adds an image into the request.
 */
void Utils::HttpRequests::RequestExecutor::addImageContent(const std::string& key, 
                                                       const std::string& image) {

    ContentData this_image(key, image, 
                          Utils::HttpRequests::ContentType::CONTENT_TYPE_IMAGE);
    
    contents.push_back(this_image);
}


/**
 * Gets the content of the request.
 */
std::vector<Utils::HttpRequests::ContentData> 
        Utils::HttpRequests::RequestExecutor::getContents() const {

    return contents;
}


/**
 * Stores the response into the provided string variable user_data.
 */
size_t dummyWriteCallback(void *contents, size_t size, size_t nmemb, void *user_data) {

    ((std::string*)user_data)->append((char*)contents, size * nmemb);

    // This is a dummy callback that discards the received data
    return size * nmemb;
}


/**
 * Executes the request.
 */
void Utils::HttpRequests::RequestExecutor::executeRequest() {

    // Creates a CURL object to execute the request
    CURL* curl = curl_easy_init();

    // If created correctly
    if (curl) {

        struct curl_httppost* post = nullptr;
        struct curl_httppost* last = nullptr;

        setPostContents(&post, &last);

        curl_easy_setopt(curl, CURLOPT_URL, 
                         request_url.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);

        // Set the dummy callback to save the response into the variable
        // instead of printing it
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dummyWriteCallback);

        // Get a string with the result of the request
        std::string response_data;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {

            Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_ERROR,
            curl_easy_strerror(res));
        }

        curl_formfree(post);
        curl_easy_cleanup(curl);
    }
}

