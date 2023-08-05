#include "project/telegram_api.h"

int main() {

    TelegramBot bot;

    bot.sendTextMessage(/*add your chat id here*/"", "Test");

    return 0;
}