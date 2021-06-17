#include "Leaderboard.h"
void Leaderboard::resize_players(Player*& players, int& count)
{
	Player* new_players = new Player[count * 2];
	for (int i = 0; i < count; i++) {
		new_players[i] = players[i];
	}
	delete[] players;
	players = new_players;
	count *= 2;
}
int Leaderboard::count_players(string name_of_file) {
	ifstream file(name_of_file, ios::app);
	if (!file.is_open()) {
		std::cout << "Error opening file" << endl;
		return -1;
	}
	string line;
	int count_of_players = 0;
	while (!file.eof()) {
		getline(file, line);
		count_of_players++;
	}
	file.close();
	this->all_players_count= count_of_players-1;
	return all_players_count;
}
void Leaderboard::add_leaderboard(string file_name, Player& player, int& all_players_count, int& max_players_count, Player*& players) {

	all_players_count++;
	if (all_players_count >= max_players_count) {
		resize_players(players, max_players_count);
	}
	players[all_players_count - 1] = player;
	ofstream file(file_name, ios::app);
	file << player.get_username() << " " << player.get_score() << endl;
	file.close();
	cout << "Registration complete." << endl;
}

void Leaderboard::print_leaderboard(string name_of_file) const {
	ifstream file(name_of_file);
	while (!file.eof()) {
		string line;
		getline(file, line);
		cout << line << endl;
	}
}
unsigned int Leaderboard::get_stats(string username, const Player* players, const int count) {
	for (int i = 0; i < count; i++) {
		if (username == players[i].get_username()) {
			return i;
		}
	}
	return -1;
}
void Leaderboard::read_leaderboard(const string curr_line, Player& player) {
	string username;
	string score_chars;
	string input;

	
	int interval_pos =  curr_line.find(" ");
	username = curr_line.substr(0, interval_pos);
	player.set_username(username);

	score_chars = curr_line.substr(interval_pos + 1, curr_line.size() - interval_pos - 1);
	int score = atoi(score_chars.c_str());
	player.set_score(score);
	

}