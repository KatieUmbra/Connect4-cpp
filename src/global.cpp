#include "global.hpp"
#include <pch.hpp>
#include <cstdlib>

#ifdef _WIN32
#define CLEAR_CMD "cls"
#define PAUSE_CMD system("pause");
#else
#define CLEAR_CMD "clear"
#define PAUSE_CMD std::cout << "Press ENTER to continue..." << std::endl; system("read");
#endif

namespace c4
{
	void clear_console()
	{
		system(CLEAR_CMD);
	}

	void wait_for_input()
	{
		PAUSE_CMD
	}
}
