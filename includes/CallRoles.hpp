#ifndef CALL_ROLES_HPP
#define CALL_ROLES_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include "Utils.hpp"
#include "Player.hpp"
#include "Village.hpp"
#include "RoleData.hpp"

class Village;
class Player;

class CallRoles
{

public:
	CallRoles(Village &v);
	~CallRoles();

	// METHODS
	void call(int role);
	void callVillage();

	// GETTERS

	// SETTERS

private:
	CallRoles();

	// ATTRIBUTES

	const int _night_count;
	Village &_village;
	int _werewolves_target;

	static std::vector<Role> _roles_list;

	// METHODS

	void callWerewolf(Player &);
	void callDrunk(Player &);
	void callSeer(Player &);
	void callBodyguard(Player &);
	void callSpellCaster(Player &);
	void callCursed(Player &);

	Player &targetPlayer(Player &);
	bool tryTargetPlayer(int, Player&);

	int targetPlayer();
	bool tryTargetPlayer(int);

	bool deadRolesManager(int role, Player &p);
};

#endif
