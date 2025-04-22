#include "../includes/Village.hpp"

Village::Village(int players, std::vector<int> roles_list) : _players_amount(players), _roles(roles_list) { gameReset(); }

Village::~Village() {}

/* METHODS */

void Village::startGame()
{
    PrintMessage::out(DEBUG_MESSAGE, "Checking village data...");
    PrintMessage::out(TIME3);
    if (_players.size() != _players_amount)
        throw std::runtime_error("Players are not all ready");
    if (_showing_cards_by_dead == -1)
        throw std::runtime_error("How need to chose to show or dont show the cards by dead");
    if (_showing_roles_on_chat == -1)
        throw std::runtime_error("How need to chose to show or dont show the roles on moderator chat");
    PrintMessage::out(DEBUG_MESSAGE, "Everything ready");
    gameLoop();
}

void Village::gameLoop()
{
    PrintMessage::out(DEBUG_MESSAGE, "Starting game");
    PrintMessage::out(TIME0);
    while (true)
    {
        _day_count++;

        night();
        if (checkTeamVictory())
            break;
        day();
        if (checkTeamVictory())
            break;
    }
    PrintMessage::out(*this);
    PrintMessage::out(WAIT);
    PrintMessage::out(ENTER);
    PrintMessage::out(DEBUG_MESSAGE, "Ending game");
}

void Village::night()
{
    CallRoles r(*this);

    // messages
    PrintMessage::out(NIGHT_MESSAGE, _day_count);
    PrintMessage::out(VILLAGE_MESSAGE, "Everyone in the village falls asleep");
    PrintMessage::out(VILLAGE_MESSAGE, "Everyone close their eyes");
    PrintMessage::out(ENTER);
    PrintMessage::out(*this);
    PrintMessage::out(WAIT);
    PrintMessage::out(ENTER);

    // night calls in priority order
    r.call(DRUNK);
    r.call(CURSED);
    r.call(SEER);
    r.call(BODYGUARD);
    r.call(SPELL_CASTER);
    r.call(WEREWOLF);

    // reset one night informations
    resetOneNightData();

    PrintMessage::out(TIME2);
}

void Village::day()
{
    CallRoles r(*this);

    // announce werewolves victim or not
    Player *w_target = getWerewolvesVictim();

    if (_day_count != 1)
    {
        if (w_target != NULL)
        {
            PrintMessage::out(ANNOUNCE_MESSAGE, w_target->getRealName() + " was killed by werewolves");

            // if is a showing card game
            if (_showing_cards_by_dead == true)
                OutMessage << PINK BOLT << w_target->getRealName() << " show your card" << RESEND;
        }
        else
            PrintMessage::out(ANNOUNCE_MESSAGE, "no one was killed by werewolves... yet");
        _werewolves_victim_id = 0;
    }
    // announce spell caster target
    if (usingRole(SPELL_CASTER))
        PrintMessage::out(ANNOUNCE_MESSAGE, getPlayerById(getPlayerByRoleCard(SPELL_CASTER)->getTargetId())->getRealName() + " was silenced by the spell caster");

    // messages
    PrintMessage::out(DAY_MESSAGE, _day_count);
    PrintMessage::out(TIME2);
    PrintMessage::out(VILLAGE_MESSAGE, "The village wakes up");
    PrintMessage::out(VILLAGE_MESSAGE, "Everyone open their eyes");
    if (_day_count == 1)
    {
        PrintMessage::out(VILLAGE_MESSAGE, "Last night the news arrived that werewolves live among us");
        PrintMessage::out(VILLAGE_MESSAGE, "It is up to you to find and eliminate those werewolves");
    }
    // voting
    r.callVillage();

    PrintMessage::out(TIME2);
}

// return the victorious team
// or return 0 if the game isn't over yet
int Village::checkTeamVictory()
{
    // if TANNER is playing
    if (usingRole(TANNER))
    {
        // find TANNER
        for (const auto &kv : _players)
        {
            // if he was killed by VILLAGE_TEAM he won
            const auto p = kv.second;
            if (p.getRole() == TANNER && p.getStatus() == DEAD && p.getKilledBy() == VILLAGE_TEAM)
            {
                PrintMessage::out(TANNER_TEAM_VICTORY);
                return _victorious_team = TANNER_TEAM;
            }
        }
    }
    // if WEREWOLVES are playing
    if (usingRole(WEREWOLF))
    {
        if ((double)getAlivePlayersAmount() / 2.0 <= getRoleAmount(WEREWOLF))
        {
            PrintMessage::out(WEREWOLF_TEAM_VICTORY);
            return _victorious_team = WEREWOLF_TEAM;
        }
    }
    // VILLAGE_TEAM
    if (getRoleAmount(WEREWOLF) == 0)
    {
        PrintMessage::out(VILLAGE_TEAM_VICTORY);
        return _victorious_team = VILLAGE_TEAM;
    }

    return 0;
}

// if role is being used, return TRUE
bool Village::usingRole(int role_id)
{
    for (const auto &role : _roles)
    {
        if (role == role_id)
            return true;
    }
    return false;
}

void Village::resetOneNightData()
{
    for (auto &kv : _players)
    {
        if (kv.second.getStatus() == DEAD)
            kv.second.setTargetId(0);
    }
}

/* SETTERS */

void Village::setNewPlayer(int player_id, int role_id, std::string name)
{
    Player p(role_id, player_id, name);

    if (role_id == DRUNK)
        p.setRole(_drunk_role);

    _players[player_id] = p;
}

void Village::setDrunkRole(int role) { _drunk_role = role; }

void Village::setShowingCardsByDeath(bool value) { _showing_cards_by_dead = value; }

void Village::setShowingRolesOnChat(bool value) { _showing_roles_on_chat = value; }

void Village::setWerewolvesVictimId(int id) { _werewolves_victim_id = id; }

void Village::gameReset()
{
    _day_count = 0;
    _showing_cards_by_dead = -1;
    _showing_roles_on_chat = -1;
    _drunk_role = UNKNOW;
    _werewolves_victim_id = 0;
}

/* GETTERS */

int Village::getDayCount() { return _day_count; }

Player *Village::getWerewolvesVictim() { return getPlayerById(_werewolves_victim_id); }

std::map<int, Player> &Village::getPlayersList() { return _players; }

int Village::getPlayersCount() { return _players_amount; }

int Village::getShowingCardsByDead() { return _showing_cards_by_dead; }

int Village::getShowingRolesOnChat() { return _showing_roles_on_chat; }

// return the number of (role) alive players in the game
int Village::getRoleAmount(int role)
{
    int amount = 0;
    for (const auto &kv : _players)
    {
        if (kv.second.getRole() == role && kv.second.getStatus() == ALIVE)
            amount++;
    }
    return amount;
}

// return a &(reference) for tha player that plays that role
Player *Village::getPlayerByRoleCard(int role)
{
    for (auto &kv : _players)
    {
        if (kv.second.getRoleCard() == role)
            return &kv.second;
    }
    return NULL;
}

// return a &(reference) for tha player that plays that role
Player *Village::getPlayerById(int id)
{
    for (auto &kv : _players)
    {
        if (kv.first == id)
            return &kv.second;
    }
    return NULL;
}

// return the number of (team) alive players in the game
int Village::getTeamAmount(int team)
{
    int amount = 0;
    for (const auto &kv : _players)
    {
        Player p = kv.second;
        if (RoleData::getInfo(p.getRole()).team == team && p.getStatus() == ALIVE)
            amount++;
    }
    return amount;
}

// return the number of alive players in the game
int Village::getAlivePlayersAmount()
{
    int amount = 0;
    for (const auto &kv : _players)
    {
        Player p = kv.second;
        if (p.getStatus() == ALIVE)
            amount++;
    }
    return amount;
}