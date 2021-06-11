#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Player
{
public:
	Player();
	Player(const string username, const unsigned int score);
	virtual ~Player();
	virtual const string get_username() const;
	virtual const unsigned int get_score() const;

	void set_username(const string username);
	void set_score(const unsigned int score);
	
private:
	string username;
	unsigned int score;
};

