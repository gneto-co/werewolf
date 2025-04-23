#include "../includes/PrintMessage.hpp"

PrintMessage OutMessage;

PrintMessage::PrintMessage() {}
PrintMessage::~PrintMessage() {}

bool PrintMessage::getSkipTime() { return skipTime(); }
void PrintMessage::setSkipTime(bool v) { skipTime() = v; }

void PrintMessage::out(int role_id, std::string msg)
{
    std::ostringstream oss;

    // messages
    if (role_id == DEBUG_MESSAGE)
    {
        oss << LOW_BRIGHT ITALICS << msg;
    }
    else if (role_id == VILLAGE_MESSAGE)
    {
        oss << BOLT GREEN << "(Village) ";
        oss << LOW_BRIGHT WHITE << msg;
    }
    else if (role_id == ANNOUNCE_MESSAGE)
    {
        oss << BOLT CYAN << "ANNOUNCE - " << msg;
    }
    // roles
    else if (RoleData::getInfo(role_id).team == WEREWOLF_TEAM)
    {
        oss << BOLT RED << RoleData::getInfo(role_id).name << ", ";
        oss << LOW_BRIGHT WHITE << msg;
    }
    else if (RoleData::getInfo(role_id).team == VILLAGE_TEAM)
    {
        oss << BOLT BRIGHT_BLUE << RoleData::getInfo(role_id).name << ", ";
        oss << LOW_BRIGHT WHITE << msg;
    }
    oss << RESEND;

    printMethod(oss.str());
    out(TIME0);
}

void PrintMessage::out(int type)
{
    std::ostringstream oss;

    if (type == WAIT)
    {
        Utils::pressAnyKey();
        return;
    }
    if (type == ENTER)
    {
        oss << RESEND;
    }
    if (type == TIME00)
    {
        if (getSkipTime() == false)
            Utils::wait(300);
        else
            Utils::wait(0050);
    }
    if (type == TIME0)
    {
        if (getSkipTime() == false)
            Utils::wait(1000);
        else
            Utils::wait(0050);
    }
    if (type == TIME1)
    {
        if (getSkipTime() == false)
            Utils::wait(1500);
        else
            Utils::wait(0050);
    }
    if (type == TIME2)
    {
        if (getSkipTime() == false)
            Utils::wait(2000);
        else
            Utils::wait(0050);
    }
    if (type == TIME3)
    {
        if (getSkipTime() == false)
            Utils::wait(2500);
        else
            Utils::wait(0050);
    }
    if (type == VILLAGE_TEAM_VICTORY)
    {
        oss << GREEN << std::endl;
        oss << " ▗▖  ▗▖▗▄▄▄▖▗▖   ▗▖    ▗▄▖  ▗▄▄▖▗▄▄▄▖    ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖▗▖  ▗▖" << std::endl;
        oss << " ▐▌  ▐▌  █  ▐▌   ▐▌   ▐▌ ▐▌▐▌   ▐▌       ▐▌  ▐▌  █  ▐▌     █ ▐▌ ▐▌▐▌ ▐▌▝▚▞▘ " << std::endl;
        oss << " ▐▌  ▐▌  █  ▐▌   ▐▌   ▐▛▀▜▌▐▌▝▜▌▐▛▀▀▘    ▐▌  ▐▌  █  ▐▌     █ ▐▌ ▐▌▐▛▀▚▖ ▐▌  " << std::endl;
        oss << "  ▝▚▞▘ ▗▄█▄▖▐▙▄▄▖▐▙▄▄▖▐▌ ▐▌▝▚▄▞▘▐▙▄▄▖     ▝▚▞▘ ▗▄█▄▖▝▚▄▄▖  █ ▝▚▄▞▘▐▌ ▐▌ ▐▌  " << std::endl;
        oss << RESEND;
    }
    if (type == WEREWOLF_TEAM_VICTORY)
    {
        oss << RED << std::endl;
        oss << " ▗▖ ▗▖▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖▗▖ ▗▖ ▗▄▖ ▗▖  ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖    ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖▗▖  ▗▖" << std::endl;
        oss << " ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌  ▐▌  ▐▌▐▌   ▐▌       ▐▌  ▐▌  █  ▐▌     █ ▐▌ ▐▌▐▌ ▐▌▝▚▞▘ " << std::endl;
        oss << " ▐▌ ▐▌▐▛▀▀▘▐▛▀▚▖▐▛▀▀▘▐▌ ▐▌▐▌ ▐▌▐▌  ▐▌  ▐▌▐▛▀▀▘ ▝▀▚▖    ▐▌  ▐▌  █  ▐▌     █ ▐▌ ▐▌▐▛▀▚▖ ▐▌  " << std::endl;
        oss << " ▐▙█▟▌▐▙▄▄▖▐▌ ▐▌▐▙▄▄▖▐▙█▟▌▝▚▄▞▘▐▙▄▄▖▝▚▞▘ ▐▙▄▄▖▗▄▄▞▘     ▝▚▞▘ ▗▄█▄▖▝▚▄▄▖  █ ▝▚▄▞▘▐▌ ▐▌ ▐▌  " << std::endl;
        oss << RESEND;
    }
    if (type == TANNER_TEAM_VICTORY)
    {
        oss << ORANGE << std::endl;
        oss << " ▗▄▄▄▖▗▄▖ ▗▖  ▗▖▗▖  ▗▖▗▄▄▄▖▗▄▄▖     ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖▗▖  ▗▖" << std::endl;
        oss << "   █ ▐▌ ▐▌▐▛▚▖▐▌▐▛▚▖▐▌▐▌   ▐▌ ▐▌    ▐▌  ▐▌  █  ▐▌     █ ▐▌ ▐▌▐▌ ▐▌▝▚▞▘ " << std::endl;
        oss << "   █ ▐▛▀▜▌▐▌ ▝▜▌▐▌ ▝▜▌▐▛▀▀▘▐▛▀▚▖    ▐▌  ▐▌  █  ▐▌     █ ▐▌ ▐▌▐▛▀▚▖ ▐▌  " << std::endl;
        oss << "   █ ▐▌ ▐▌▐▌  ▐▌▐▌  ▐▌▐▙▄▄▖▐▌ ▐▌     ▝▚▞▘ ▗▄█▄▖▝▚▄▄▖  █ ▝▚▄▞▘▐▌ ▐▌ ▐▌  " << std::endl;
        oss << RESEND;
    }

    printMethod(oss.str());
}

void PrintMessage::out(int type, int day_count)
{
    std::ostringstream oss;

    if (type == DAY_MESSAGE)
    {
        OutMessage << LOW_BRIGHT ITALICS << "Start the day";
        Utils::pressAnyKey();
        Utils::clearScreen();
        oss << BLUE << std::endl;
        oss << "  ▗▄▄▄  ▗▄▖▗▖  ▗▖" << std::endl;
        oss << "  ▐▌  █▐▌ ▐▌▝▚▞▘ " << std::endl;
        oss << "  ▐▌  █▐▛▀▜▌ ▐▌  " << std::endl;
        oss << "  ▐▙▄▄▀▐▌ ▐▌ ▐▌  " << day_count << std::endl;
        oss << RESEND;
    }
    else if (type == NIGHT_MESSAGE)
    {
        OutMessage << LOW_BRIGHT ITALICS << "Start the night";
        Utils::pressAnyKey();
        Utils::clearScreen();
        oss << RED << std::endl;
        oss << "  ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖" << std::endl;
        oss << "  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌  █  " << std::endl;
        oss << "  ▐▌ ▝▜▌  █  ▐▌▝▜▌▐▛▀▜▌  █  " << std::endl;
        oss << "  ▐▌  ▐▌▗▄█▄▖▝▚▄▞▘▐▌ ▐▌  █  " << day_count << std::endl;
        oss << RESEND;
    }

    printMethod(oss.str());
    out(TIME1);
}

void PrintMessage::out(std::string msg)
{
    printMethod(msg);
}

void PrintMessage::out(std::ostringstream oss)
{
    printMethod(oss.str());
}

void PrintMessage::out(Village &v)
{
    std::map<int, Player> players = v.getPlayersList();

    for (const auto &kv : players)
    {
        std::ostringstream oss;
        out(TIME00);
        Player p = kv.second;
        Role role = RoleData::getInfo(p.getRole());

        // (player_id) player_name  <space>     alive or dead message  <space>     (role)
        //        temp1_oss                          temp2_oss
        if (p.getStatus() == ALIVE)
        {

            std::ostringstream temp1_oss;
            temp1_oss << "(player " << p.getId() << ")   " << p.getRealName();
            std::ostringstream temp2_oss;
            temp2_oss << " is alive and healthy... for now";

            oss << PINK BOLT << L_ALIGN(25) << temp1_oss.str() << RESET << L_ALIGN(35) << temp2_oss.str();

            if (v.getShowingRolesOnChat() == true)
            {
                if (role.team == VILLAGE_TEAM)
                    oss << BRIGHT_BLUE;
                if (role.team == WEREWOLF_TEAM)
                    oss << RED;
                if (role.team == TANNER_TEAM)
                    oss << ORANGE;
                oss << " (" << role.name << ")";
            }
            oss << RESEND;
        }
        else if (p.getStatus() == DEAD)
        {
            std::ostringstream temp1_oss;
            temp1_oss << "(player " << p.getId() << ")   " << p.getRealName();

            std::ostringstream temp2_oss;
            if (role.team == VILLAGE_TEAM || role.team == TANNER_TEAM)
                temp2_oss << " was a good villager";
            if (role.team == WEREWOLF_TEAM)
                temp2_oss << " will not bother us anymore";

            oss << LOW_BRIGHT ITALICS << L_ALIGN(25) << temp1_oss.str() << L_ALIGN(35) << temp2_oss.str();

            if (v.getShowingRolesOnChat() == true)
                oss << " (" << role.name << ")";

            oss << RESEND;
        }
        printMethod(oss.str());
    }
}

void PrintMessage::printMethod(std::string str)
{
    std::cout << str;
}