#include "../include/project/telegram_api.h"

//#include <iostream>
//#include <fstream>

#include "../include/project/Utils.h"


/**
 * Constructs a TelegramBot object with the provided bot token.
 */
TelegramBot::TelegramBot(std::string bot_token) {

    Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_SYSTEM, 
                    "Starting the bot with the provided token");

    // TODO: Check if bot_token is correct
    bot_url = "https://api.telegram.org/bot" + bot_token;
}


/**
 * Constructs a TelegramBot object with the default bot token.
 */
TelegramBot::TelegramBot() {

    Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_SYSTEM, 
                    "Starting the bot with the stored token");

    // Reads the content of the file
    std::vector<std::string> bot_token_file_content = 
            Utils::File::readFileContent(TELEGRAM_BOT_TOKEN_FILEPATH);
    
    // If it has some content
    if (bot_token_file_content.size() > 0) {

        // The first line contains the token
        std::string bot_token = bot_token_file_content[0];

        // Debug print showing the token
        Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_DEBUG, 
                        "Token file contains: " + bot_token);

        // TODO: Check if bot_token is correct
        bot_url = "https://api.telegram.org/bot" + bot_token;
    }
}


/**
 * Sends a text message to a specified chat.
 */
TelegramBotResult TelegramBot::sendTextMessage(const std::string& chat_id,
                                               const std::string& message) {

    // Suppose everything is executing fine
    TelegramBotResult execution_result = TelegramBotResult::RESULT_NO_ERROR;

    // Api url to send the text_message
    const std::string url = bot_url + TELEGRAM_SEND_MESSAGE_METHOD;

    // Creates a request
    Utils::HttpRequests::RequestExecutor request_executor(url);

    // Adds the chat id where it has to be sent
    request_executor.addTextContent("chat_id", chat_id);

    // Adds the content of the message it has to send
    request_executor.addTextContent("text", message);

    // Executres the request
    request_executor.executeRequest();
    
    return execution_result;
 }


 /**
 * Reads updates in the chats.
 */
std::vector<ChatMessage> TelegramBot::getChatsUpdates() {

    // Suppose everything is executing fine
    TelegramBotResult execution_result = TelegramBotResult::RESULT_NO_ERROR;

    // Api url to send the text_message
    const std::string url = bot_url + TELEGRAM_GET_CHATS_UPDATES_METHOD;

    // Creates a request
    Utils::HttpRequests::RequestExecutor request_executor(url);

    // To avoid read messages it already read
    if (last_updated_id != "") {

        request_executor.addTextContent("offset", last_updated_id);
    }

    // Executres the request
    std::string request_response = request_executor.executeRequest();

    std::vector<ChatMessage> chats_updates;
    
    // TODO: Clean this part of code, by now it is a POC
    std::vector<std::string> messages = 
            Utils::String::splitString(request_response, "{\"update_id\":");
    

    for (int num_string = 1;  num_string < messages.size(); num_string++) {

        const std::string& message = messages[num_string];

        if (message.find(",\"is_bot\":true,") == std::string::npos) {

            ChatMessage chat_update;

            std::string update_id_str = 
                    Utils::String::splitString(message, ",") [0];

            // Reads it so it does not repeat the reading of this message
            last_updated_id = update_id_str;

            std::string chat_id_str = 
                    Utils::String::splitString(message, ",\"is_bot\":")[0];

            chat_id_str = 
                    Utils::String::splitString(chat_id_str, ",\"from\":{")[1];

            chat_id_str = Utils::String::replaceString(chat_id_str, "\"id\":", "");

            std::string timestamp_and_message_str = 
                    Utils::String::splitString(message, "},\"date\":")[1];

            std::vector<std::string> combined_data =
                    Utils::String::splitString(timestamp_and_message_str, 
                                            ",\"text\":\"");

            std::string timestamp_str = combined_data[0];

            std::string message_text = 
                    Utils::String::splitString(combined_data[1],"\"}}")[0];

            message_text = 
                    Utils::String::splitString(message_text,"\",\"entities\"")[0];

            chat_update.message = message_text;
            chat_update.timestamp = std::stol(timestamp_str);
            chat_update.chat_id = std::stol(chat_id_str);
            chat_update.update_id = std::stol(update_id_str);

            chats_updates.push_back(chat_update);

            update_id_str = message;
        }
    }

    return chats_updates;
 }

