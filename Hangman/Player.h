#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Player
{
public:
	Player();
	Player(const string username, const int score);
	virtual ~Player();
	virtual const string get_username() const;
	virtual const int get_score() const;

	void set_username(const string username);
	void set_score(const int score);
	
private:
	string username;
	int score;
};

