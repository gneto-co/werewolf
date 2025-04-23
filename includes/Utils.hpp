#ifndef UTILS_HPP
#define UTILS_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cstdlib> 

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

	static void clearScreen()
	{
		system("clear");
	}

	template <typename T>
	static void printVectorIndex(std::vector<T> &v)
	{
		for (size_t i = 0; i < v.size(); i++)
		{
			std::cout << i << " - " << v[i] << std::endl;
		}
	}

	template <typename T1, typename T2>
	static void printVectorSideToSide(std::vector<T1> &v1, std::vector<T2> &v2)
	{
		size_t size = (v1.size() < v2.size() ? v1.size() : v2.size());
		for (size_t i = 0; i < size; i++)
		{
			std::cout << i << " - " << v1[i] << " - " << v2[i] << std::endl;
		}
	}

private:
	Utils();
	~Utils();
};

#endif
