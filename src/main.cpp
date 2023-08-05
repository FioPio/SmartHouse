#include "project/telegram_api.h"
#include "project/Utils.h"



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
    }

    return 0;
}