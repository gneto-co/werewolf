#include "../includes/Village.hpp"
#include "../includes/CallRoles.hpp"
#include "../includes/PrintMessage.hpp"

static int getNumber(int min, int max)
{
	int input;

	while (true)
	{
		std::cout << "> ";

		// Read number
		std::cin >> input;

		// is valid
		if (std::cin.fail())
		{
			// not a number
			std::cin.clear();													// clear error
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore line
		}
		// is on range
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (input >= min && input <= max)
				return input;
		}
		OutMessage << CURSOR_UP(1) << CURSOR_ALL_LEFT << CLEAR_SCREEN_FORWARD_CURSOR;
	}
}
static std::string getString()
{
	std::string input;
	do
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		OutMessage << CURSOR_UP(1) << CURSOR_ALL_LEFT << CLEAR_SCREEN_FORWARD_CURSOR;
	} while (input.empty());
	return input;
}

static void printPlayersRoles(std::vector<std::string> &v1, std::vector<int> &v2)
{
	size_t size = (v1.size() < v2.size() ? v1.size() : v2.size());
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i << " - " << v1[i] << " - " << RoleData::getInfo(v2[i]).name << std::endl;
	}
}

static void printRoleData(int id)
{
	Role r = RoleData::getInfo(id);
	std::string team;
	if (r.team == WEREWOLF_TEAM)
		team = "werewolves";
	if (r.team == VILLAGE_TEAM)
		team = "village";
	if (r.team == TANNER_TEAM)
		team = "tanner";

	std::cout << "name:    " << r.name << std::endl;
	std::cout << "impact:  " << r.village_impact << std::endl;
	std::cout << "team:    " << team << std::endl;
	if (r.can_target_twice_in_row == false)
		std::cout << "can't target the same player twice in a row" << std::endl;
	if (r.can_target_it_self == false)
		std::cout << "can't target it self" << std::endl;
	if (r.can_target_same_team_players == false)
		std::cout << "can't target other players from that team" << std::endl;
	if (r.wake_at_night == true)
		std::cout << "wake at night to preform an action" << std::endl;
	else
		std::cout << "do not wake at night" << std::endl;
}

std::vector<std::string> g_names;
int g_showing_cards_by_dead = true;
int g_showing_roles_on_chat = true;

static void players_menu()
{
	while (true)
	{
		Utils::clearScreen();

		Utils::printVectorIndex(g_names);
		std::cout << std::endl;
		std::cout << ITALICS LOW_BRIGHT << "choose an option" << RESEND;
		std::cout << GREEN;
		std::cout << "(0) back" << std::endl;
		std::cout << "(1) add player" << std::endl;
		std::cout << "(2) remove player" << std::endl;
		std::cout << RESET;

		int id;
		switch (getNumber(0, 2))
		{
		case 0:
			return;
			break;
		case 1:
			std::cout << GREEN << "New player name" << RESEND;
			g_names.push_back(getString());
			break;
		case 2:
			std::cout << GREEN << "Removed player nick (-1 to cancel)" << RESEND;
			if ((id = getNumber(-1, g_names.size() - 1)) == -1)
				break;
			g_names.erase(g_names.begin() + id);
			break;
		default:
			break;
		}
		Utils::clearScreen();
	}
}

static void roles_menu()
{
	while (true)
	{
		Utils::clearScreen();

		Utils::printVectorIndex(RoleData::getRolesNamesList());
		std::cout << std::endl;
		std::cout << ITALICS LOW_BRIGHT << "choose an option" << RESEND;
		std::cout << GREEN;
		std::cout << "(0) back" << std::endl;
		std::cout << "(1) lear about a role" << std::endl;
		std::cout << RESET;
		switch (getNumber(0, 1))
		{
		case 0:
			return;
			break;
		case 1:
			std::cout << GREEN << "Role number" << RESEND;
			printRoleData(getNumber(0, RoleData::getRolesAmount()) + 101);
			Utils::pressAnyKey();
			break;
		default:
			break;
		}
		Utils::clearScreen();
	}
}

static void game_menu()
{
	while (true)
	{
		Utils::clearScreen();
		std::cout << ITALICS LOW_BRIGHT << "choose an option" << RESEND;
		std::cout << GREEN;
		std::cout << "(0) back" << std::endl;
		std::cout << "(1) showing cards by dead [" << (g_showing_cards_by_dead ? "ON" : "OFF") << "]" << std::endl;
		std::cout << "(2) showing roles on chat [" << (g_showing_roles_on_chat ? "ON" : "OFF") << "]" << std::endl;
		std::cout << "(3) skip wait time on messages [" << (PrintMessage::getSkipTime() ? "ON" : "OFF") << "]" << std::endl;

		std::cout << RESET;
		switch (getNumber(0, 3))
		{
		case 0:
			return;
			break;
		case 1:
			g_showing_cards_by_dead = g_showing_cards_by_dead ? false : true;
			break;
		case 2:
			g_showing_roles_on_chat = g_showing_roles_on_chat ? false : true;
			break;
		case 3:
			PrintMessage::setSkipTime(PrintMessage::getSkipTime() ? false : true);
			break;
		default:
			break;
		}
		Utils::clearScreen();
	}
}

static void start_menu()
{
	std::vector<int> roles_list;
	std::cout << "Handle all the cards" << std::endl;
	Utils::pressAnyKey();
	for (size_t i = 0; i < g_names.size(); i++)
	{
		Utils::clearScreen();
		Utils::printVectorIndex(RoleData::getRolesNamesList());
		std::cout << GREEN;
		std::cout << "Set the " << g_names[i] << " role" << std::endl;
		std::cout << RESET;

		roles_list.push_back(getNumber(0, RoleData::getRolesAmount()) + 101);
	}
	bool confirm = false;
	while (confirm == false)
	{
		Utils::clearScreen();
		printPlayersRoles(g_names, roles_list);
		std::cout << ITALICS LOW_BRIGHT << "choose an option" << RESEND;
		std::cout << GREEN;
		std::cout << "(0) back" << std::endl;
		std::cout << "(1) change a player's role" << std::endl;
		std::cout << "(2) START" << std::endl;
		std::cout << RESET;
		int id;
		switch (getNumber(0, 2))
		{
		case 0:
			return;
			break;
		case 1:
			std::cout << GREEN << "Player id" << RESEND;
			id = getNumber(0, g_names.size());
			Utils::printVectorIndex(RoleData::getRolesNamesList());
			std::cout << GREEN << "New role id" << RESEND;
			roles_list[id] = getNumber(0, RoleData::getRolesAmount()) + 101;
			break;
		case 2:
			confirm = true;
			break;
		default:
			break;
		}
	}

	Village village(g_names.size(), roles_list);
	village.setShowingCardsByDead(g_showing_cards_by_dead);
	village.setShowingRolesOnChat(g_showing_roles_on_chat);
	for (size_t i = 0; i < g_names.size(); i++)
		village.setNewPlayer(i + 1, roles_list[i], g_names[i]);
	try
	{
		village.startGame();
	}
	catch (const std::exception &e)
	{
		std::cerr << BRIGHT_RED << e.what() << RESEND;
		Utils::pressAnyKey();
	}
}

int main()
{
	while (true)
	{
		Utils::clearScreen();

		std::cout << ITALICS LOW_BRIGHT << "choose an option" << RESEND;
		std::cout << GREEN;
		std::cout << "(0) exit" << std::endl;
		std::cout << "(1) players" << std::endl;
		std::cout << "(2) roles" << std::endl;
		std::cout << "(3) game" << std::endl;
		std::cout << "(4) START" << std::endl;
		std::cout << RESET;
		switch (getNumber(0, 4))
		{
		case 0:
			return 0;
			break;
		case 1:
			players_menu();
			break;
		case 2:
			roles_menu();
			break;
		case 3:
			game_menu();
			break;
		case 4:
			start_menu();
			break;
		default:
			break;
		}
	}
}
