#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Registration.h"
#include "USERS.h"
#include "Hangman_game.h"
#include "Leaderboard.h"
using namespace std;
int main() {
	string input_username;
	string input_email;
	string input_password;
	string name_of_file = "users_collection.txt";
	string name_of_leaderboard = "leaderboard.txt";
	string name_of_words_file = "words.txt";

	Leaderboard collection;
	Hangman_game play;
	Registration helper;

	int count_of_users = helper.count_users(name_of_file);
	int max_count_users = count_of_users + 1;
	USERS* users = new USERS[max_count_users];

	int count_of_players = collection.count_players(name_of_leaderboard);
	int max_count_players = count_of_players + 1;
	Player* players = new Player[max_count_players];

	ifstream data_base_users(name_of_file, ios::app);
	if (!data_base_users.is_open()) {
		cout << "Error opening database."<<endl;
        return -1;
	}
	int i = 0;
    while (!data_base_users.eof()) {
        string buff;
        getline(data_base_users,buff);
		if (i >= count_of_users) {
			cout << "More lines than count." << endl;
			break;
		}
        helper.read_user(buff, users[i]);
        i++;
    }
	data_base_users.close();
	
	ifstream data_base_players(name_of_leaderboard, ios::app);
	if (!data_base_players.is_open()) {
		cout << "Error opening database." << endl;
		return -1;
	}
	int j = 0;
	while (!data_base_players.eof()) {
		string buff2;
		getline(data_base_players, buff2);
		if (j >= count_of_players) {
			cout << "More lines than count." << endl;
			break;
		}
		collection.read_leaderboard(buff2, players[j]);
		j++;
	}
	data_base_players.close();

	bool first_command = true;
	Player player;
	while (first_command) {
		/*system("cls");*/
		cout << "------COMMANDS------" << endl;
		cout << "    $ register      " << endl;
		cout << "     $ login        " << endl;
		cout << "--------------------" << endl;
		cout << endl;
		string command;
		cout << "Enter your command: ";
		getline(cin, command);
		cout << endl;
		if (command == "$ register") {
			first_command = false;
			cout << "Enter username: ";
			cin >> input_username;
			cout << endl;
			while (helper.username_is_taken(count_of_users, input_username, users)) {
				cout << "Username is taken! Enter new username: ";
				cin >> input_username;
				cout << endl;
			}

			cout << "Enter email: ";
			cin >> input_email;
			cout << endl;

			cout << "Enter password: ";
			cin >> input_password;
			cout << endl;
			cout << "--------------------" << endl;
			int first_score=0;
			USERS user(input_email, input_password, input_username);
			helper.add_user(name_of_file,user,users,count_of_users,max_count_users);

			Player new_player(input_username, first_score);
			player = new_player;
			collection.add_leaderboard(name_of_leaderboard, player,count_of_players,max_count_players, players);
		}
		else if (command == "$ login") {
			first_command = false;
			cout << "Enter username: ";
			cin >> input_username;
			cout << endl;

			cout << "Enter password: ";
			cin >> input_password;
			cout << endl;
			cout << "--------------------" << endl;
			while (helper.find_user_index(count_of_users, input_username, users) == -1) {
				cout << "Wrong username or password!" << endl;
				cout << "Enter username: ";
				cin >> input_username;
				cout << endl;

				cout << "Enter password: ";
				cin >> input_password;
				cout << endl;
				cout << "--------------------" << endl;
			}
			int user_index = helper.find_user_index(count_of_users, input_username, users);
			if (input_password != users[user_index].get_password()) {
				helper.new_password(count_of_users, input_username, users);
			}
			int index = collection.get_stats(input_username, players, count_of_players);
			Player new_player(input_username, players[index].get_score());
			player = new_player;
		}
		else {
			cout << "Wrong command! Try again." << endl;
			cout << endl;
		}
	}
	

	system("cls");
	while (true) {
		
		cout << "------COMMANDS------" << endl;
		cout << "    $ new game      " << endl;
		cout << "    $ continue      " << endl;
		cout << "   $ leaderboard    " << endl;
		cout << "    $ add word      " << endl;
		cout << "      $ exit        " << endl;
		cout << "--------------------" << endl;
		cout << "User:"<< input_username <<"  "<< endl;
		cout << "Personal score:  " << player.get_score() << endl;
		cout << endl;
		string game_command;
		cout << "Enter your command: ";
		getline(cin>>ws, game_command);
		int miss = 0;
		if (game_command == "$ new game") {
			string word_to_guess=play.take_word(name_of_words_file);
			int score = player.get_score();
			play.guess(word_to_guess,play.blank_word(word_to_guess),score, input_username,miss);
			player.set_score(score);
			cout << endl;
			cout << endl;
		}
		else if(game_command == "$ continue"){
			cout << "Enter name of file: ";
			string saved_file_name;
			getline(cin >> ws, saved_file_name);
			ifstream saved_file(saved_file_name + ".txt");
			if (!saved_file.is_open()) {
				std::cout << "Error opening file" << endl;
				return 0;
			}
			int misses;
			string letters;
			string blank;
			string word;
			int personal_score;
			while (saved_file >> misses >> letters >> blank >> word >> personal_score) {
				play.guess(word, blank, personal_score, input_username,misses);
			}
			saved_file.close();
			cout << endl;
			cout << endl;
		}
		else if (game_command == "$ leaderboard") {
			cout << endl;
			cout << endl;
			cout << "     LEADERBOARD    " << endl;
			cout << "--------------------" << endl;
			collection.print_leaderboard(name_of_leaderboard);
			cout << "--------------------" << endl;
			cout << endl;
			cout << endl;
		}
		else if (game_command == "$ add word") {
			play.add_word(name_of_words_file);
		}
		else if (game_command == "$ exit") {
			break;
		}
		else {
			cout << endl;
			cout << "Wrong command! Try again." << endl;
			cout << endl;
			cout << endl;
		}
	}
}

