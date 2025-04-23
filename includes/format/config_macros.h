#ifndef CONFIG_MACROS_H
#define CONFIG_MACROS_H

/******************************************
 *                                        *
 *                  ENUM                  *
 *                                        *
 ******************************************/

/*
 * STEPS TO INSERT A NEW CHARACTER
 * 1 - add it to the roles enum (config_macros.h)
 * 2 - if it wakes, adds it to the night() (Village.cpp)
 * 3 - add is information on getRoleInfo() (RoleData.cpp)
 * 4 - if it wakes create new functions on (CallRoles.cpp)
 * 5 - add new rules in the code if needed
 * 6 - add to reset night if is a role with one night target
 * 7 - add new wining option if needed
 */
enum roles
{
	UNKNOW = 100,
	// ROLES THAT WAKE DURING THE NIGHT
	CURSED,
	SEER,
	BODYGUARD,
	SPELL_CASTER,
	WEREWOLF,
	// ROLES THAT DONT WAKE DURING THE NIGHT
	VILLAGER,
	TANNER,
	LYCAN,
	PRINCE,
	// END
	END_ROLE
};

enum status
{
	ALIVE = 200,
	DEAD,
};

enum team
{
	VILLAGE_TEAM = 300,
	WEREWOLF_TEAM,
	TANNER_TEAM,
};

enum message_type
{
	DEBUG_MESSAGE = 400,
	VILLAGE_MESSAGE,
	ANNOUNCE_MESSAGE,
	DAY_MESSAGE,
	NIGHT_MESSAGE,
	ENTER,
	WAIT,
	TIME00,
	TIME0,
	TIME1,
	TIME2,
	TIME3,
	TARGET,
	VILLAGE_TEAM_VICTORY,
	WEREWOLF_TEAM_VICTORY,
	TANNER_TEAM_VICTORY,
};

/******************************************
 *                                        *
 *                INCLUDES                *
 *                                        *
 ******************************************/

#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <climits>
#include <cctype>
#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <csignal>
#include <stdexcept>
#include <poll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <utility>

#include <vector>
#include <map>
#include <unordered_set>

#endif
