#pragma once
#include <string>
#include <vector>

enum class Guess_result
{
	CORRECT,
	WRONG,
	ALREADY_GUESSED,
	INVALID
};

class Hangman_game
{
public:
	void start(const std::string& new_word);

	Guess_result guess(const std::string& input);

	bool is_won() const;
	bool is_lost() const;
	bool is_over() const;

	int get_lives() const;
	const std::string& get_word() const;
	const std::string& get_answer_word() const;
	const std::string& get_guessed_letters() const;
	std::string get_drawing() const;

	void save(const std::string& file_name) const;
	bool load(const std::string& file_name);
	
	std::string take_word(const std::string& file_name) const;
	bool is_valid_word(const std::string& new_word) const;
	bool word_exists(const std::string& file_name, const std::string& new_word) const;
	bool add_word(const std::string& file_name, const std::string& new_word) const;
	
private:
	std::string upper_letters(std::string text) const;
	std::string blank_word(const std::string& text) const;
	bool is_letters_only(const std::string& text) const;
	std::vector<std::string> read_words(const std::string& file_name) const;

	std::string word;
	std::string answer_word;
	std::string guessed_letters;
	int misses = 0;
};

