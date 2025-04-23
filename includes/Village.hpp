#ifndef VILLAGE_HPP
#define VILLAGE_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include "Utils.hpp"
#include "Player.hpp"
#include "CallRoles.hpp"
#include "RoleData.hpp"
#include "PrintMessage.hpp"

class Player;
class CallRoles;

class Village
{
public:
	Village(int, std::vector<int>);
	~Village();

	// METHODS

	void startGame();
	bool usingRole(int);

	// SETTERS

	void setNewPlayer(int id, int role, std::string name);
	void setShowingCardsByDead(bool);
	void setShowingRolesOnChat(bool);
	void setWerewolvesVictimId(int);

	// GETTERS

	int getDayCount();
	int getPlayersCount();
	Player *getPlayerByRoleCard(int role);
	Player *getPlayerById(int role);
	Player *getWerewolvesVictim();
	int getShowingCardsByDead();
	int getShowingRolesOnChat();
	std::vector<int> getRolesList();
	std::map<int, Player> &getPlayersList();

private:
	Village();

	// ATTRIBUTES

	// village basic information

	const size_t _players_amount;
	const std::vector<int> _roles;
	std::map<int, Player> _players;
	int _day_count;
	int _victorious_team;
	int _showing_cards_by_dead;
	int _showing_roles_on_chat;
	int _werewolves_victim_id;

	// METHODS

	void gameLoop();
	void day();
	void night();
	int checkTeamVictory();
	void resetOneNightData();
	int getRoleAmount(int role);
	int getTeamAmount(int role);
	int getAlivePlayersAmount();
	void printMethod(std::string str);
};

#endif
