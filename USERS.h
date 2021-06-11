#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class USERS
{
public:
	USERS();
	USERS(const string email, const string password, const string username);
	virtual ~USERS();
	virtual const string get_email() const;
	virtual const string get_password() const;
	virtual const string get_username() const;

	void set_email(const string email);
	void set_password(const string password);
	void set_username(const string username);
private:
	string email;
	string password;
	string username;
};

