#pragma once

#include <string>

/**
 * Enumeration representing the results of Telegram Bot actions.
 */
enum class TelegramBotResult {
    RESULT_NO_ERROR,       /**< The action was successful with no errors. */
    RESULT_SENDING_ERROR   /**< An error occurred while sending the message. */
};

/**
 * A class representing a Telegram Bot for sending messages.
 */
class TelegramBot {

    std::string bot_url; /**< The URL for interacting with the Telegram Bot API. */

public:

    /**
     * Constructs a TelegramBot object with the provided bot token.
     * 
     * @param bot_token The token of the Telegram Bot.
     */
    TelegramBot(std::string bot_token);

    /**
     * Constructs a TelegramBot object with the default bot token.
     * 
     * This constructor initializes the TelegramBot with a bot token read from 
     * a default file. The default file contains the bot token for convenience.
     */
    TelegramBot();

    /**
     * Send a text message to a specified chat.
     * 
     * @param chat_id The ID of the chat where the message will be sent.
     * @param message The text message to be sent.
     * @return The result of the sending action (success or error).
     */
    TelegramBotResult sendTextMessage(const std::string& chat_id,
                                      const std::string& message);


};