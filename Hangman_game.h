#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
class Hangman_game
{
public:
	void save_game(string file_name, unsigned int misses, string letters, string blank, string word, unsigned int personal_score);
	string take_word(string name_of_file);
	string blank_word(string word);
	void add_word(string name_of_file);
	int guess(const string word, string answer_word, unsigned int personal_score, const string username, int& misses);
	void draw_hangman(unsigned int misses);
	string upper_letters(string& word);
private:
	string word;
	string answer_word;
	string input;
	vector<string> words;
};

