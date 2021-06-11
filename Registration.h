#pragma once
#include "USERS.h"
#include <string>
#include <iostream>
#include <fstream>
class Registration  
{
public:
	void resize_users(USERS*& users, int& count);
	int count_users(string name_of_file);
	void add_user(string name_of_file, USERS& user, USERS*& users, int& all_users_count, int& max_users_count);
	void read_user(const string line, USERS& user);
	bool successful_login(const int users_count, const string username, const string password, const USERS* collection_users);
	int find_user_index(const int users_count, const string username, const USERS* collection_users);
	bool username_is_taken(const int users_count, const string username, const USERS* collection_users);
	void new_password(const int users_count, const string username, const string password, USERS* collection_users);
private:
	int all_users_count;
	USERS* all_users;
};

