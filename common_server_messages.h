//
// Created by mati on 27/9/19.
//

#ifndef CMAKE_DEMO_COMMON_SERVER_MESSAGES_H
#define CMAKE_DEMO_COMMON_SERVER_MESSAGES_H

#include <string>
#include <unordered_map>
#include <map>
#include <fstream>

#define LIST_DIR_START_CODE "150 "
#define QUIT_SUCCESS_CODE "221 "
#define LIST_DIR_END_CODE "226 "
#define LOGIN_SUCCESS_CODE "230 "
#define SUCCESS_RMD_CODE "250 "
#define SUCCESS_CODE "257 "
#define PSW_REQ_CODE "331 "
#define UNKNOWN_COMMAND_CODE "500 "
#define LOGIN_FAIL_CODE "530 "
#define FAIL_CODE "550 "

#define LIST_DIR_START_MESSAGE "listBegin"
#define LIST_DIR_END_MESSAGE "listEnd"
#define MKD_SUCCESS_MESSAGE "mkdSuccess"
#define MKD_FAIL_MESSAGE "mkdFailed"
#define PWD_SUCCESS_MESSAGE "currentDirectoryMsg"
#define UNKNOWN_COMMAND_MESSAGE "unknownCommand"
#define RMD_SUCCESS_MESSAGE "rmdSuccess"
#define RMD_FAIL_MESSAGE "rmdFailed"
#define QUIT_SUCCESS_MESSAGE "quitSuccess"
#define PSW_REQ_MESSAGE "passRequired"
#define LOGIN_SUCCESS_MESSAGE "loginSuccess"
#define LOGIN_FAIL_MESSAGE "loginFailed"
#define LOGIN_REQ_MESSAGE "clientNotLogged"
#define USERNAME "user"
#define PASS "password"

#define DEF_LIST_DIR_S_MESSAGE "Here comes the directory listing."
#define DEF_LIST_DIR_END_MESSAGE "Directory send OK."
#define DEF_MKD_SUCCESS_MESSAGE "created"
#define DEF_MKD_FAIL_MESSAGE "Create Directory operation failed"
#define DEF_PWD_SUCCESS_MESSAGE "\"/home/admin/ftp\" is the current directory."
#define DEF_UNKNOWN_COMMAND_MESSAGE "Unknown command."
#define DEF_RMD_SUCCESS_MESSAGE "Remove directory operation successful."
#define DEF_RMD_FAIL_MESSAGE  "Remove directory operation failed."
#define DEF_QUIT_SUCCESS_MESSAGE "Goodbye."
#define DEF_PSW_REQ_MESSAGE "Please specify the password."
#define DEF_LOGIN_SUCCESS_MESSAGE "Login successful."
#define DEF_LOGIN_FAIL_MESSAGE "Login incorrect."
#define DEF_LOGIN_REQ_MESSAGE "Please login with USER and PASS."
#define DEF_USERNAME "u"
#define DEF_PASS "p"


class common_server_messages {
private:
    std::unordered_map<std::string, std::string> messages;
    std::map<std::string, std::string> configValues;

    std::string createMessage(const std::string &key, std::string pre,
                              const std::string &post);

    std::string getConfigValue(const std::string &key);

public:
    explicit common_server_messages(char *config);

    std::string getMkdSuccess(const std::string &name);

    ~common_server_messages();

    std::string getMkdFail();

    std::string getUnknownCommand();

    std::string getPwdSuccess();

    std::string getListFolders(const std::string &folders);

    std::string getRemoveSuccess();

    std::string getRemoveFail();

    std::string getQuit();

    std::string getPswRequired();

    std::string getLoginSuccess();

    std::string getLoginFail();

    std::string getLoginRequired();

    void readConfig(char *filePath);

    std::string getUsername();

    std::string getPassword();
};


#endif //CMAKE_DEMO_COMMON_SERVER_MESSAGES_H
