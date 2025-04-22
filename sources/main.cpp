#include "../includes/Village.hpp"
#include "../includes/CallRoles.hpp"

int main()
{
	// define roles to be used
	std::vector<int> roles_list = {LYCAN, PRINCE, DRUNK, SEER, WEREWOLF, BODYGUARD, TANNER, CURSED, SPELL_CASTER, PRINCE};
	std::vector<std::string> names_list = {"BOB", "JOE", "MICK", "GABY", "LEO", "MARY", "MAT", "JACK", "KEVIN", "ELIZA"}; // name max length 14
	size_t players_nb = roles_list.size();
	
	Village village(players_nb, roles_list);

	for (size_t i = 0; i < players_nb; i++)
		village.setNewPlayer(i+1, roles_list[i], names_list[i]);

	// define if cards will be showed by dead
	village.setShowingCardsByDeath(false);
	village.setShowingRolesOnChat(true);

	try
	{
		village.startGame();
	}
	catch (const std::exception &e)
	{
		std::cerr << BRIGHT_RED << e.what() << RESEND;
	}

	return 0;
}
