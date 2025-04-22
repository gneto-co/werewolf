#ifndef PRINT_MESSAGE_HPP
#define PRINT_MESSAGE_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include "Utils.hpp"
#include "RoleData.hpp"
#include "Player.hpp"
#include "Village.hpp"

class Player;
class Village;

class PrintMessage
{

public:
    PrintMessage();
    ~PrintMessage();

    // METHODS

    template <typename T>
    PrintMessage &operator<<(const T &val)
    {
        std::ostringstream oss;
        oss << val;
        printMethod(oss.str());
        return *this;
    }

    PrintMessage &operator<<(std::ostream &(*manipulator)(std::ostream &))
    {
        std::ostringstream oss;
        oss << manipulator;
        printMethod(oss.str());
        return *this;
    }

    static void out(int role_id, std::string msg);
    static void out(int type);
    static void out(int type, int day_count);
    static void out(std::string msg);
    static void out(std::ostringstream oss);
    static void out(Village &v);

private:
    // METHODS

    static void printMethod(std::string str);
};

extern PrintMessage OutMessage;

#endif
