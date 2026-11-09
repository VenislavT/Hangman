#include "Menu.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

const std::string BACK_COMMAND = "/back";
const std::string SAVE_COMMAND = "/save";

Menu::Menu(const std::string& users_file, const std::string& words_file) 
	: registration(users_file), words_file(words_file)
{
}

void Menu::run() {
	registration.load();

	if(login_menu()) {
		main_menu();
	}
}

bool Menu::login_menu() {
	while (current_username.empty()) {
		clear_screen();
		std::cout << "=====HANGMAN=====" << std::endl;
		std::cout << "1. Register" << std::endl;
		std::cout << "2. Login" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "=================" << std::endl;

		std::string choice;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		if (choice == "1") {
			register_user();
		} 
		else if (choice == "2") {
			login();
		} 
		else if (choice == "0") {
			return false;
		}
		else {
			std::cout << "Invalid choice! Please try again." << std::endl;
			wait_for_enter();
		}
	}
	return true;
}

void Menu::register_user() {
	clear_screen();
	
	std::string username, password, email;

	std::cout << "=====REGISTER=====" << std::endl;
	std::cout << "(type " << BACK_COMMAND << " to go back)" << std::endl;
	
	if(!ask("Enter username: ", username)) {
		return;
	}

	while (registration.username_is_taken(username)) {
		if(!ask("Username is taken! Enter new username: ", username)) {
			return;
		}
	}

	if(!ask("Enter email: ", email)) {
		return;
	}

	while (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
		if(!ask("Invalid email! Enter a valid email: ", email)) {
			return;
		}
	}

	if (!ask("Enter password: ", password)) {
		return;
	}

	registration.add_user(USERS(email, password, username));
	current_username = username;
	std::cout << "Registration successful! You are logged in as " << current_username << "!" << std::endl;
	
	wait_for_enter();
}

void Menu::login() {
	clear_screen();
	std::string username, password, email;

	std::cout << "=====LOGIN=====" << std::endl;
	std::cout << "(type " << BACK_COMMAND << " to go back)" << std::endl;

	if(!ask("Enter username: ", username)) {
		return;
	}
	while (!registration.username_is_taken(username)) {
		if (!ask("Not such username! Enter username: ", username)) {
			return;
		}
	}
	
	if(!ask("Enter password: ", password)) {
		return;
	}

	while (!registration.check_login(username, password)) {
		std::cout << "Wrong password! Please try again." << std::endl;

		std::string answer;
		if(!ask("Forgot password? (y/n): ", answer)) {
			return;
		}
		while (answer != "y" && answer != "Y" && answer != "n" && answer != "N") {
			if (!ask("Invalid input! Forgot password? (y/n): ", answer)) {
				return;
			}
		}

		if (answer == "y" || answer == "Y") {
			if(!ask("Enter your email: ", email)) {
				return;
			}
			while (!registration.check_email(username, email)) {
				if (!ask("Wrong email! Enter your email: ", email)) {
					return;
				}
			}

			std::string new_password;
			if(!ask("Enter new password: ", new_password)) {
				return;
			}

			if (registration.reset_password(username, email, new_password)) {
				std::cout << "Password reset successful!" << std::endl;
				wait_for_enter();
				break;
			}
		
			std::cout << "Password reset failed! Please check your email." << std::endl;
		}

		if(!ask("Enter password: ", password)) {
			return;
		}
	}

	current_username = username;
}

void Menu::main_menu() {
	while (true) {
		clear_screen();
		std::cout << "=====MAIN MENU=====" << std::endl;
		std::cout << "1. New Game" << std::endl;
		std::cout << "2. Continue Game" << std::endl;
		std::cout << "3. Leaderboard" << std::endl;
		std::cout << "4. Add Word" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "===================" << std::endl;
		
		std::string choice;
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		
		if (choice == "1") {
			new_game();
		}
		else if (choice == "2") {
			continue_game();
		}
		else if (choice == "3") {
			show_leaderboard();
		}
		else if (choice == "4") {
			add_word();
		}
		else if (choice == "0") {
			return;
		}
		else {
			std::cout << "Invalid choice! Please try again." << std::endl;
			wait_for_enter();
		}
	}
}

void Menu::new_game() {
	hangman_game.start(hangman_game.take_word(words_file));
	play();
}

void Menu::continue_game() {
	if (!hangman_game.load(save_file_name())) {
		std::cout << "No saved game found!" << std::endl;
		wait_for_enter();
		return;
	}
	play();
}

void Menu::play() {
	std::string message;
	
	while (!hangman_game.is_over()) {
		clear_screen();
		
		std::cout << hangman_game.get_drawing() << std::endl;
		std::cout << "Word: ";
		for (char c : hangman_game.get_answer_word()) {
			std::cout << c << " ";
		}
		std::cout << std::endl;

		std::cout << "Tried: ";
		for (char c : hangman_game.get_guessed_letters()) {
			std::cout << c << " ";
		}
		std::cout << std::endl;

		std::cout << "Lives: " << hangman_game.get_lives() << std::endl;
		std::cout << std::endl << message << std::endl;

		std::string input;
		std::cout<<"Guess a letter or the whole word (" << SAVE_COMMAND << " to save and exit): ";
		std::cin >> input;

		if (input == SAVE_COMMAND) {
			hangman_game.save(save_file_name());
			std::cout<<"Game saved successfully!" << std::endl;
			wait_for_enter();
			return;
		}

		Guess_result result = hangman_game.guess(input);

		if (result == Guess_result::CORRECT) {
			message = "Correct!";
		}
		else if (result == Guess_result::WRONG) {
			message = "Wrong!";
		}
		else if (result == Guess_result::ALREADY_GUESSED) {
			message = "You've already guessed " + input + "!";
		}
		else {
			message = "Invalid input! Please enter a letter or the whole word.";
		}
	}

	clear_screen();
	std::cout << hangman_game.get_drawing() << std::endl;
	std::cout << "Word: " << hangman_game.get_word() << std::endl << std::endl;

	if (hangman_game.is_won()) {
		std::cout << "You've won! +1 point" << std::endl;
		registration.set_score(current_username, registration.get_score(current_username) + 1);
	}
	else {
		std::cout << "Game over! You've lost!" << std::endl;
	}

	std::remove(save_file_name().c_str());
	wait_for_enter();
}

void Menu::show_leaderboard() const {
	clear_screen();

	std::cout << "=====LEADERBOARD=====" << std::endl;
	leaderboard.print(registration.get_users());
	std::cout << "=====================" << std::endl;
	
	wait_for_enter();
}

void Menu::add_word() {
	std::string word;

	if (!ask("Enter a new word (or '" + BACK_COMMAND + "' to go back): ", word)) {
		return;
	}

	if (!hangman_game.is_valid_word(word)) {
		std::cout << "Word must be at least 3 characters and only letters!" << std::endl;
	}
	else if (hangman_game.word_exists(words_file, word)) {
		std::cout << "Word already exists!" << std::endl;
	}
	else {
		hangman_game.add_word(words_file, word);
		std::cout << "Word added successfully!" << std::endl;
	}
	wait_for_enter();
}

void Menu::clear_screen() const {
	system("cls");
}

void Menu::wait_for_enter() const {
	std::cout << "Press Enter to continue...";
	std::cin.ignore();
	std::cin.get();
}

bool Menu::ask(const std::string& question, std::string& answer) const {
	std::cout << question;
	std::cin >> answer;
	return answer != BACK_COMMAND;
}

std::string Menu::save_file_name() const {
	return "data/save_" + current_username + ".txt";
}