#pragma once
#include "Registration.h"
#include "Leaderboard.h"
#include "Hangman_game.h"
#include <string>

class Menu 
{
public:
	Menu(const std::string& users_file, const std::string& words_file);
	void run();

private:
	bool login_menu();
	void register_user();
	void login();

	void main_menu();
	void new_game();
	void continue_game();
	void play();
	void show_leaderboard() const;
	void add_word();

	void clear_screen() const;
	void wait_for_enter() const;
	bool ask(const std::string& question, std::string& answer) const;
	std::string save_file_name() const;

	Registration registration;
	Leaderboard leaderboard;
	Hangman_game hangman_game;
	std::string words_file;
	std::string current_username;
};