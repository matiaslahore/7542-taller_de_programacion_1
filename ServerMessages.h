//
// Created by mati on 27/9/19.
//

#ifndef CMAKE_DEMO_SERVERMESSAGES_H
#define CMAKE_DEMO_SERVERMESSAGES_H

#include <string>
#include <unordered_map>

#define LIST_DIR_START_CODE "150 "
#define QUIT_SUCCESS_CODE "221 "
#define LIST_DIR_END_CODE "226 "
#define SUCCESS_CODE "257 "
#define SUCCESS_RMD_CODE "250 "
#define UNKNOWN_COMMAND_CODE "500 "
#define FAIL_CODE "550 "

#define LIST_DIR_START_MESSAGE "LIST_START"
#define LIST_DIR_END_MESSAGE "LIST_END"
#define MKD_SUCCESS_MESSAGE "MKDSUCCESS"
#define MKD_FAIL_MESSAGE "MKDFAIL"
#define PWD_SUCCESS_MESSAGE "PWDSUCCESS"
#define UNKNOWN_COMMAND_MESSAGE "UNKNOWN_COMMAND"
#define RMD_SUCCESS_MESSAGE "RMD_SUCCESS"
#define RMD_FAIL_MESSAGE "RMD_FAIL"
#define QUIT_SUCCESS_MESSAGE "QUIT_SUCCESS"

class ServerMessages {
private:
    std::unordered_map<std::string, std::string> messages;

    std::string createMessage(const std::string& key, std::string pre, const std::string& post);

public:
    ServerMessages();

    std::string getMkdSuccess(const std::string& name);

    ~ServerMessages();

    std::string getMkdFail();

    std::string getUnknownCommand();

    std::string getPwdSuccess();

    std::string getListFolders(const std::string& folders);

    std::string getRemoveSuccess();

    std::string getRemoveFail();

    std::string getQuit();
};


#endif //CMAKE_DEMO_SERVERMESSAGES_H
