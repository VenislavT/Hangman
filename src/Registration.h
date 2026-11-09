#pragma once
#include "USERS.h"
#include <string>
#include <vector>

class Registration  
{
public:
	Registration(const std::string& file_name);

	void load();
	void save() const;

	bool username_is_taken(const std::string& username) const;
	bool add_user(const USERS& user);
	bool check_login(const std::string& username, const std::string& password) const;
	bool check_email(const std::string& username, const std::string& email) const;
	bool reset_password(const std::string& username, const std::string& email, const std::string& new_password);

	int get_score(const std::string& username) const;
	const std::vector<USERS>& get_users() const;

	bool set_score(const std::string& username, int score);

private:
	int find_user_index(const std::string& username) const;

	std::string file_name;
	std::vector<USERS> users;
};

