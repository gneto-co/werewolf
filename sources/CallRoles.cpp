#include "../includes/CallRoles.hpp"

std::vector<Role> CallRoles::_roles_list;

CallRoles::CallRoles(Village &v) : _night_count(v.getDayCount()), _village(v)
{
}

CallRoles::~CallRoles() {}

/* METHODS */

// return true if that player role can be called
// return false should not
bool CallRoles::deadRolesManager(int role, Player &p)
{
    if (role == WEREWOLF)
        return true;
    if (p.getStatus() == DEAD && _village.getShowingCardsByDead() == true)
        return false;
    return true;
}

void CallRoles::call(int role)
{
    if (!_village.usingRole(role))
        return;

    Player *p = _village.getPlayerByRoleCard(role);
    if (p == NULL)
        return;

    if (deadRolesManager(role, *p) == false)
        return;

    switch (role)
    {
    case WEREWOLF:
        callWerewolf(*p);
        break;
        break;
    case SEER:
        callSeer(*p);
        break;
    case BODYGUARD:
        callBodyguard(*p);
        break;
    case SPELL_CASTER:
        callSpellCaster(*p);
        break;
    case CURSED:
        callCursed(*p);
        break;
    default:
        break;
    }
    PrintMessage::out(ENTER);
}

void CallRoles::callWerewolf(Player &p)
{
    int role = p.getRole();

    PrintMessage::out(role, "open your eyes");
    if (_night_count == 1)
    {
        // werewolves are called to see each other only
        PrintMessage::out(role, "learn how the other werewolves are");
        PrintMessage::out(WAIT);
    }
    else
    {
        // werewolves are called to chose a player to kill

        // get target
        PrintMessage::out(role, "choose your target");
        Player &target_player = targetPlayer(p);

        // if target is protected by BODYGUARD do nothing
        if (_village.usingRole(BODYGUARD) && _village.getPlayerByRoleCard(BODYGUARD)->getTargetId() == target_player.getId())
            ;
        // if target is the CURSED he joins werewolves team
        else if (target_player.getRole() == CURSED)
            target_player.setRole(WEREWOLF);
        else
        {
            target_player.setStatus(DEAD);
            _village.setWerewolvesVictimId(target_player.getId());
            target_player.setKilledBy(WEREWOLF_TEAM);
        }
    }
    PrintMessage::out(role, "close your eyes");
}

void CallRoles::callVillage()
{
    PrintMessage::out(VILLAGE_MESSAGE, "Choose someone to eliminate from village (0 to skip)");

    int input = targetPlayer();
    if (input == 0)
    {
        PrintMessage::out(ANNOUNCE_MESSAGE, "elimination skipped");
    }
    else
    {
        Player &target_player = *_village.getPlayerById(input);
        Role target = RoleData::getInfo(target_player.getRole());

        // PRINCE doesn't die at village vote
        if (target.role == PRINCE)
        {
            PrintMessage::out(ANNOUNCE_MESSAGE, "village tried to eliminate is PRINCE");
            OutMessage << PINK BOLT << target_player.getRealName() << " show your card" << RESEND;
            return;
        }

        // upgrade status
        target_player.setKilledBy(VILLAGE_TEAM);
        target_player.setStatus(DEAD);

        // reveal is team
        PrintMessage::out(ANNOUNCE_MESSAGE, target_player.getRealName() + " was eliminated by the village");
        if (target.team == WEREWOLF_TEAM)
            OutMessage << RED BOLT ITALICS << target_player.getRealName() << " was a werewolf" << RESEND;
        else if (target.team == TANNER_TEAM)
            OutMessage << ORANGE BOLT ITALICS << target_player.getRealName() << " was the tanner" << RESEND;
        else
            OutMessage << BRIGHT_BLUE BOLT << target_player.getRealName() << " was a villager" << RESEND;

        // if is a showing card game
        if (_village.getShowingCardsByDead() == true)
            OutMessage << PINK BOLT << target_player.getRealName() << " show your card" << RESEND;
    }

    PrintMessage::out(TIME0);
}

void CallRoles::callCursed(Player &p)
{
    int role_card = p.getRoleCard();
    int role = p.getRole();
    static bool already_revealed = false;

    if (_night_count != 1)
    {
        PrintMessage::out(role_card, "open your eyes");
        if (role == WEREWOLF)
        {
            // cursed find that he is now a werewolf
            if (p.getStatus() == ALIVE)
            {
                if (already_revealed == false)
                {
                    PrintMessage::out(role_card, RESET BOLT RED "a werewolf bit you and, suddenly, the moon looks more beautiful" RESET);
                    already_revealed = true;
                }
                PrintMessage::out(role_card, RESET BOLT RED "you are a werewolf" RESET);
            }
            else
                PrintMessage::out(DEBUG_MESSAGE, "just pretending to be alive");
        }
        else
        {
            if (p.getStatus() == ALIVE)
                PrintMessage::out(role_card, "you remain a normal villager, but why should it be any different?");
        }
        PrintMessage::out(WAIT);
        PrintMessage::out(role_card, "close your eyes");
    }
}

void CallRoles::callSeer(Player &p)
{
    // seer is called, chose a player and learn if that player is or is not on VILLAGE_TEAM
    int role = p.getRole();
    PrintMessage::out(role, "open your eyes");
    PrintMessage::out(role, "choose someone to learn if he is a villager");

    if (p.getStatus() == ALIVE)
    {
        // get target player from input
        Player &target_player = targetPlayer(p);
        Role target = RoleData::getInfo(target_player.getRole());

        // reveal is team
        if (target.team == WEREWOLF_TEAM || target.role == LYCAN)
            OutMessage << RED BOLT ITALICS << target_player.getRealName() << " is not a villager" << RESEND;
        else
            OutMessage << BLUE BOLT << target_player.getRealName() << " is a villager" << RESEND;
        PrintMessage::out(TIME0);
    }
    else
    {
        PrintMessage::out(DEBUG_MESSAGE, "just pretending to be alive");
        PrintMessage::out(TIME2);
    }

    PrintMessage::out(role, "close your eyes");
}

void CallRoles::callBodyguard(Player &p)
{
    // bodyguard wakes and chose a player to be protected from werewolf attacks
    if (_night_count != 1)
    {
        int role = p.getRole();
        PrintMessage::out(role, "open your eyes");
        PrintMessage::out(role, "choose someone to protect against werewolves attacks");
        if (p.getStatus() == ALIVE)
            targetPlayer(p);
        else
        {
            PrintMessage::out(DEBUG_MESSAGE, "just pretending to be alive");
            PrintMessage::out(TIME2);
        }
        PrintMessage::out(role, "close your eyes");
    }
}

void CallRoles::callSpellCaster(Player &p)
{
    // wakes every night and chose a player that will no be able to talk during the next day
    int role = p.getRole();
    PrintMessage::out(role, "open your eyes");
    if (p.getStatus() == ALIVE)
        targetPlayer(p);
    else
    {
        PrintMessage::out(DEBUG_MESSAGE, "just pretending to be alive");
        PrintMessage::out(TIME2);
    }
    PrintMessage::out(role, "close your eyes");
}

int CallRoles::targetPlayer()
{
    int input;

    while (true)
    {
        OutMessage << LOW_BRIGHT << "Player number ";

        // Read number
        std::cin >> input;

        // is invalid
        if (std::cin.fail())
        {
            // not a number
            std::cin.clear();                                                   // clear error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore line
        }
        // is on range
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (tryTargetPlayer(input))
            {

                PrintMessage::out(RESET);
                return input;
            }
        }
        OutMessage << CURSOR_UP(1) << CURSOR_ALL_LEFT << CLEAR_SCREEN_FORWARD_CURSOR;
    }
}

// return TRUE if (role) can target player
// return FALSE if (role) can't target player
bool CallRoles::tryTargetPlayer(int input)
{
    if (input == 0)
        return true;

    Player *pointer = _village.getPlayerById(input);

    // check if player exist
    if (pointer == NULL)
        return false;

    Player &target_player = *pointer;

    // player need to be alive
    if (target_player.getStatus() == DEAD)
        return false;

    return true;
}

Player &CallRoles::targetPlayer(Player &active_player)
{
    int input;

    while (true)
    {
        OutMessage << LOW_BRIGHT << "Player number ";

        // Read number
        std::cin >> input;

        // is valid
        if (std::cin.fail())
        {
            // not a number
            std::cin.clear();                                                   // clear error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore line
        }
        // is on range
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (tryTargetPlayer(input, active_player))
            {

                PrintMessage::out(RESET);
                return *_village.getPlayerById(input);
            }
        }
        OutMessage << CURSOR_UP(1) << CURSOR_ALL_LEFT << CLEAR_SCREEN_FORWARD_CURSOR;
    }
}

// return TRUE if (role) can target player
// return FALSE if (role) can't target player
bool CallRoles::tryTargetPlayer(int input, Player &active_player)
{
    Player *pointer = _village.getPlayerById(input);

    // check if player exist
    if (pointer == NULL)
        return false;

    Player &target_player = *pointer;

    Role active_player_role = RoleData::getInfo(active_player.getRole());
    Role target_player_role = RoleData::getInfo(target_player.getRole());

    // player need to be alive
    if (target_player.getStatus() == DEAD)
        return false;

    // some roles cant repeat their target twice in a row
    if (active_player_role.can_target_twice_in_row == false && target_player.getId() == active_player.getTargetId())
        return false;

    // some roles cant target them selfs
    if (active_player_role.can_target_it_self == false && target_player.getId() == active_player.getId())
        return false;

    // some roles cant target the same team players
    if (active_player_role.can_target_same_team_players == false && target_player_role.team == active_player_role.team)
        return false;

    active_player.setTargetId(target_player.getId());

    return true;
}