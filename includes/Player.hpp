#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include "Utils.hpp"
#include "CallRoles.hpp"
#include "RoleData.hpp"

class CallRoles;

class Player
{
public:
	Player(int card, int id, std::string name);
	Player();
	~Player();

	// METHODS

	// GETTERS

	int getRole() const;
	int getRoleCard() const;
	int getStatus() const;
	int getKilledBy() const;
	int getTargetId() const;
	int getId() const;
	std::string getRealName() const;

	// SETTERS

	void setRole(int);
	void setTargetId(int);
	void setStatus(int);
	void setKilledBy(int);

private:
	// ATTRIBUTES
	int _card;
	int _id;
	int _role;
	int _status;
	int _killed_by;
	std::string _real_name;
	int _target_id;

	// METHODS
};

#endif
