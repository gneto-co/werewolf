#ifndef ROLE_DATA_HPP
#define ROLE_DATA_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include <string>
#include <unordered_map>

struct Role
{
	std::string name;
	int role_card;
	int role;
	int village_impact;
	int team;
	bool can_target_twice_in_row = true;
	bool can_target_it_self = true;
	bool can_target_same_team_players = true;
	bool wake_at_night = false;

	static Role getRole(int id);
};

class RoleData
{
public:
	static const Role &getInfo(int id);
	static std::vector<std::string> &getRolesNamesList();
	static int getRolesAmount();

private:
	RoleData();

	static RoleData &getInstance();

	std::map<int, Role> _roles;
	std::vector<std::string> _roles_names_list;
};

#endif