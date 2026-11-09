#include "Leaderboard.h"
#include <algorithm>
#include <iostream>

bool compare_by_score(const USERS& a, const USERS& b) {
	if(a.get_score() != b.get_score()) {
		return a.get_score() > b.get_score();
	}
	return a.get_username() < b.get_username();
}

void Leaderboard::print(const std::vector<USERS>& users) const {
	std::vector<USERS> sorted_users = users;
	std::sort(sorted_users.begin(), sorted_users.end(), compare_by_score);

	for (int i = 0; i < (int)sorted_users.size(); i++) {
		std::cout << i + 1 << ". " << sorted_users[i].get_username() << " " << sorted_users[i].get_score() << std::endl;
	}
}
