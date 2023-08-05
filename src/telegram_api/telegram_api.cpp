#include "../include/project/telegram_api.h"

#include <iostream>
#include <fstream>

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
    const std::string url = bot_url + "/sendMessage";

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

