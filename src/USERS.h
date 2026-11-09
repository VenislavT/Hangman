#pragma once
#include <string>
using namespace std;

class USERS
{
public:
	USERS() = default;
	USERS(const string& email, const string& password, const string& username, int score = 0);
	//virtual ~USERS();
	
	const string& get_email() const;
	const string& get_password() const;
	const string& get_username() const;
	int get_score() const;

	void set_email(const string& email);
	void set_password(const string& password);
	void set_username(const string& username);
	void set_score(int score);

private:
	string email;
	string password;
	string username;
	int score = 0;
};

