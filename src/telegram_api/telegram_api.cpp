#include "../include/project/telegram_api.h"

#include <iostream>
#include <fstream>

#include "../include/project/Utils.h"


TelegramBot::TelegramBot(std::string bot_token) {

    Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_SYSTEM, 
                    "Starting the bot with the provided token");

    // TODO: Check if bot_token is correct
    bot_url = "https://api.telegram.org/bot" + bot_token;
}


TelegramBot::TelegramBot() {

    Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_SYSTEM, 
                    "Starting the bot with the stored token");

    std::ifstream inputFile("../resources/telegram_bot_token.txt"); 
    
    if (!inputFile.is_open()) {

        Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_ERROR, 
                        "Token file not found!");
    }
    else {

        std::string bot_token;
        getline(inputFile, bot_token); 
        
        inputFile.close();
        
        Utils::Log::log(Utils::Log::LogLevel::LOG_LEVEL_DEBUG, 
                        "Token file contains: " + bot_token);

        // TODO: Check if bot_token is correct
        bot_url = "https://api.telegram.org/bot" + bot_token;
    }
}


/**
 * Send a text message to a specified chat.
 */
TelegramBotResult TelegramBot::sendTextMessage(const std::string& chat_id,
                                               const std::string& message) {

    // Suppose everything is executing fine
    TelegramBotResult execution_result = TelegramBotResult::RESULT_NO_ERROR;

    // Api url to send the text_message
    const std::string url = bot_url + "/sendMessage";

    
    Utils::HttpRequests::RequestExecutor request_executor(url);

    request_executor.addTextContent("chat_id", chat_id);
    request_executor.addTextContent("text", message);

    request_executor.executeRequest();
    
    return execution_result;
 }

