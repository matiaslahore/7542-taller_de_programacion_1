//
// Created by mati on 15/10/19.
//

#ifndef CMAKE_DEMO_EXCEPT_H
#define CMAKE_DEMO_EXCEPT_H

#include <exception>
#include <string>

class Except : virtual public std::exception {
private:
    int line_number;
    std::string file_name;
    std::string error_message;

public:
    explicit
    Except(std::string msg, std::string file, int err_num) :
            line_number(err_num),
            file_name(file),
            error_message(msg) {}

    virtual ~Except() throw () {}

    virtual const char* what() const throw () {
        std::string msg = "On file:" + this->file_name + " in line:";
        msg += std::to_string(this->line_number) + ":\n";
        msg += this->error_message;
        return msg.c_str();
    }
};

#endif //CMAKE_DEMO_EXCEPT_H
