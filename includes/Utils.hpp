#ifndef UTILS_HPP
#define UTILS_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <thread>

class Utils
{
public:
	// methods
	static void pressAnyKey()
	{
		std::cout << LOW_BRIGHT << "...";

		struct termios old_terminal, newt;
		tcgetattr(STDIN_FILENO, &old_terminal);
		newt = old_terminal;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		getchar();
		std::cout << CURSOR_RIGHT(1) << CURSOR_ALL_LEFT << CLEAR_LINE_FORWARD_CURSOR << RESET;

		tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
	}
	// 1000 ms = 1 sec
	static void wait(int nb)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(nb));
	}

private:
	Utils();
	~Utils();
};

#endif
