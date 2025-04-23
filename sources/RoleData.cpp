#include "../includes/RoleData.hpp"

static Role getRoleInfo(int);

RoleData::RoleData()
{
    for (int i = UNKNOW + 1; i < END_ROLE; i++)
    {
        _roles[i] = getRoleInfo(i);
    }
    for (auto &kv : _roles)
    {
        _roles_names_list.push_back(kv.second.name);
    }
}

const Role &RoleData::getInfo(int id)
{
    return getInstance()._roles[id];
}

int RoleData::getRolesAmount()
{
    return getInstance()._roles.size();
}

RoleData &RoleData::getInstance()
{
    static RoleData instance;
    return instance;
}

std::vector<std::string> &RoleData::getRolesNamesList() { return getInstance()._roles_names_list; }

static Role getRoleInfo(int id)
{
    Role role;

    switch (id)
    {

        // VILLAGE TEAM

    case VILLAGER:
        role.name = "Villager";
        role.role_card = VILLAGER;
        role.role = VILLAGER;
        role.village_impact = +1;
        role.team = VILLAGE_TEAM;
        break;

    case SEER:
        role.name = "Seer";
        role.role_card = SEER;
        role.role = SEER;
        role.village_impact = +7;
        role.team = VILLAGE_TEAM;
        role.can_target_it_self = false;
        role.wake_at_night = true;
        break;

    case CURSED:
        role.name = "Cursed";
        role.role_card = CURSED;
        role.role = CURSED;
        role.village_impact = -3;
        role.team = VILLAGE_TEAM;
        role.wake_at_night = true;
        break;

    case BODYGUARD:
        role.name = "Bodyguard";
        role.role_card = BODYGUARD;
        role.role = BODYGUARD;
        role.village_impact = +3;
        role.team = VILLAGE_TEAM;
        role.can_target_twice_in_row = false;
        role.can_target_it_self = false;
        role.wake_at_night = true;
        break;

    case PRINCE:
        role.name = "Prince";
        role.role_card = PRINCE;
        role.role = PRINCE;
        role.village_impact = +3;
        role.team = VILLAGE_TEAM;
        break;

    case LYCAN:
        role.name = "Lycan";
        role.role_card = LYCAN;
        role.role = LYCAN;
        role.village_impact = -1;
        role.team = VILLAGE_TEAM;
        break;

    case SPELL_CASTER:
        role.name = "Spell Caster";
        role.role_card = SPELL_CASTER;
        role.role = SPELL_CASTER;
        role.village_impact = +4;
        role.team = VILLAGE_TEAM;
        role.can_target_twice_in_row = false;
        role.wake_at_night = true;
        break;

        // WEREWOLF TEAM

    case WEREWOLF:
        role.name = "Werewolf";
        role.role_card = WEREWOLF;
        role.role = WEREWOLF;
        role.village_impact = -6;
        role.team = WEREWOLF_TEAM;
        role.can_target_it_self = false;
        role.can_target_same_team_players = false;
        role.wake_at_night = true;
        break;

        // OTHER TEAMS

    case TANNER:
        role.name = "Tanner";
        role.role_card = TANNER;
        role.role = TANNER;
        role.village_impact = -6;
        role.team = TANNER_TEAM;
        break;

    default:
        break;
    }

    return role;
}
