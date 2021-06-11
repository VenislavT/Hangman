#pragma once
#include "Player.h"
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;
class Leaderboard 
{
public:
	
	void resize_players(Player*& players, int& count);
	void add_leaderboard(string file_name, Player& player, int& all_players_count, int& max_players_count, Player*& players);
	
	void read_leaderboard(const string curr_line, Player& player);
	void print_leaderboard(string name_of_file) const;
	unsigned int get_stats(string username, const Player* players, const int count);
	int count_players(string name_of_file);
private:
	int all_players_count;

};

