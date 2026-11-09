#include "Registration.h"
#include <fstream>
#include <sstream>
Registration::Registration(const std::string& file_name) : file_name(file_name)
{
}

int Registration::find_user_index(const std::string& username) const {
	for (int i = 0; i < (int)users.size(); i++) {
		if (users[i].get_username() == username) {
			return i;
		}
	}
	return -1;
}

void Registration::load() {
	users.clear();

	std::ifstream file(file_name);
	std::string line;

	while(std::getline(file, line)) {
		std::istringstream fields(line);
		std::string username, email, password;

		if (fields >> username >> password >> email) {
			int score = 0;
			fields >> score;
			users.push_back(USERS(email, password, username, score));
		}
	}
}
void Registration::save() const {
	std::ofstream file(file_name);

	for (const USERS& user : users) {
		file << user.get_username() << " " << user.get_password() << " " << user.get_email() << " " << user.get_score() << "\n";
	}
}

bool Registration::username_is_taken(const std::string& username) const{
	return find_user_index(username) != -1;
}

bool Registration::add_user(const USERS& user) {
	if (username_is_taken(user.get_username())) {
		return false;
	}

	users.push_back(user);
	save();
	return true;
}

bool Registration::check_login(const std::string& username, const std::string& password) const{
	int i = find_user_index(username);

	if (i != -1) {
		return users[i].get_password() == password;
	}
	return false;
}

bool Registration::check_email(const std::string& username, const std::string& email) const {
	int i = find_user_index(username);
	if (i != -1) {
		return users[i].get_email() == email;
	}
	return false;
}

bool Registration::reset_password(const std::string& username, const std::string& email, const std::string& new_password) {
	int i = find_user_index(username);
	if (i != -1 && users[i].get_email() == email) {
		users[i].set_password(new_password);
		save();
		return true;
	}
	return false;
}

int Registration::get_score(const std::string& username) const {
	int i = find_user_index(username);
	
	if (i != -1) {
		return users[i].get_score();
	}
	return 0;
}

const std::vector<USERS>& Registration::get_users() const {
	return users;
}

bool Registration::set_score(const std::string& username, int score) {
	int i = find_user_index(username);
	
	if (i != -1) {
		users[i].set_score(score);
		save();
		return true;
	}
	return false;
}
