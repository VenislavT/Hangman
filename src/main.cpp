#include "Menu.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand((unsigned int)time(nullptr));

	Menu menu("data/users_collection.txt", "data/words.txt");
	menu.run();
	return 0;
}