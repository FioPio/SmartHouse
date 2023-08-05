#include "project/telegram_api.h"
#include "project/Utils.h"

#include <iostream>


int main() {

    TelegramBot bot;

     // Reads the content of the file
    std::vector<std::string> chat_id_file_content = 
            Utils::File::readFileContent("../resources/main_chat_id.txt");
    
    // If it has some content
    if (chat_id_file_content.size() > 0) {

        // The first line contains the token
        std::string chat_id = chat_id_file_content[0];

        bot.sendTextMessage(chat_id, "Test with some extra functionality");

        std::vector<ChatMessage> chats_updates = bot.getChatsUpdates();

        for (const ChatMessage& chat_update:chats_updates) {

            std::cout << "Update id: " << chat_update.update_id
                  << "  Chat id: " << chat_update.chat_id 
                  << "  Timestamp: " << chat_update.timestamp
                  << "  Message content: " << chat_update.message << std::endl;
        }
    }

    return 0;
}