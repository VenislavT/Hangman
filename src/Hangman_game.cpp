#include "Hangman_game.h"
#include <cstdlib>
#include <fstream>

const int MAX_MISSES = 6;

const std::string DRAWINGS[MAX_MISSES + 1] = {
	"\n"
	"\n"
	"\n"
	"\n"
	"\n"
	"\n"
	"=========\n",

	"\n"
	"      |\n"
	"      |\n"
	"      |\n"
	"      |\n"
	"      |\n"
	"=========\n",

	"  +---+\n"
	"  |   |\n"
	"      |\n"
	"      |\n"
	"      |\n"
	"      |\n"
	"=========\n",

	"  +---+\n"
	"  |   |\n"
	"  O   |\n"
	"      |\n"
	"      |\n"
	"      |\n"
	"=========\n",

	"  +---+\n"
	"  |   |\n"
	"  O   |\n"
	"  |   |\n"
	"      |\n"
	"      |\n"
	"=========\n",

	"  +---+\n"
	"  |   |\n"
	"  O   |\n"
	" /|\\  |\n"
	"      |\n"
	"      |\n"
	"=========\n",

	"  +---+\n"
	"  |   |\n"
	"  O   |\n"
	" /|\\  |\n"
	" / \\  |\n"
	"      |\n"
	"=========\n"
};

void Hangman_game::start(const std::string& new_word) {
	word = upper_letters(new_word);
	answer_word = blank_word(word);
	guessed_letters = "";
	misses = 0;
}

Guess_result Hangman_game::guess(const std::string& input) {
	std::string attempt = upper_letters(input);
	if (!is_letters_only(attempt)) {
		return Guess_result::INVALID;
	}

	if (attempt.size() > 1) {
		if (attempt == word) {
			answer_word = word;
			return Guess_result::CORRECT;
		}
		misses++;
		return Guess_result::WRONG;
	}

	char letter = attempt[0];
	if (guessed_letters.find(letter) != std::string::npos) {
		return Guess_result::ALREADY_GUESSED;
	}
	guessed_letters += letter;

	bool letter_is_found = false;
	for (int i = 0; i < (int)word.size(); i++) {
		if (word[i] == letter) {
			answer_word[i] = letter;
			letter_is_found = true;
		}
	}

	if (!letter_is_found) {
		misses++;
		return Guess_result::WRONG;
	}
	return Guess_result::CORRECT;
}

bool Hangman_game::is_won() const {
	return answer_word == word;
}

bool Hangman_game::is_lost() const {
	return misses >= MAX_MISSES;
}

bool Hangman_game::is_over() const {
	return is_won() || is_lost();
}

int Hangman_game::get_lives() const {
	return MAX_MISSES - misses;
}

const std::string& Hangman_game::get_word() const {
	return word;
}

const std::string& Hangman_game::get_answer_word() const {
	return answer_word;
}

const std::string& Hangman_game::get_guessed_letters() const {
	return guessed_letters;
}

std::string Hangman_game::get_drawing() const {
	return DRAWINGS[misses];
}

void Hangman_game::save(const std::string& file_name) const {
	std::ofstream file(file_name);
	file << word << "\n";
	file << answer_word << "\n";
	file << guessed_letters << "\n";
	file << misses << "\n";
}

bool Hangman_game::load(const std::string& file_name) {
	std::ifstream file(file_name);
	std::string saved_word, saved_answer, saved_letters;
	int saved_misses = 0;

	if (!std::getline(file, saved_word) || !std::getline(file, saved_answer) ||
		!std::getline(file, saved_letters) || !(file >> saved_misses)) {
		return false;
	}
	if (!is_letters_only(saved_word) || saved_answer.size() != saved_word.size() ||
		saved_misses < 0 || saved_misses >= MAX_MISSES) {
		return false;
	}

	word = saved_word;
	answer_word = saved_answer;
	guessed_letters = saved_letters;
	misses = saved_misses;
	return true;
}

std::string Hangman_game::take_word(const std::string& file_name) const {
	std::vector<std::string> words = read_words(file_name);
	if (words.empty()) {
		return "HANGMAN";
	}
	return words[rand() % words.size()];
}

bool Hangman_game::is_valid_word(const std::string& new_word) const {
	return new_word.size() >= 3 && is_letters_only(upper_letters(new_word));
}

bool Hangman_game::word_exists(const std::string& file_name, const std::string& new_word) const {
	std::string upper_word = upper_letters(new_word);
	for (const std::string& w : read_words(file_name)) {
		if (w == upper_word) {
			return true;
		}
	}
	return false;
}

bool Hangman_game::add_word(const std::string& file_name, const std::string& new_word) const {
	if (!is_valid_word(new_word) || word_exists(file_name, new_word)) {
		return false;
	}

	std::ofstream file(file_name, std::ios::app);
	file << "\n" << upper_letters(new_word);
	return true;
}

std::string Hangman_game::upper_letters(std::string text) const {
	for (int i = 0; i < (int)text.size(); i++) {
		if (text[i] >= 'a' && text[i] <= 'z') {
			text[i] = text[i] - ('a' - 'A');
		}
	}
	return text;
}

std::string Hangman_game::blank_word(const std::string& text) const {
	std::string result = text;
	for (int i = 0; i < (int)result.size(); i++) {
		result[i] = '_';
	}
	return result;
}

bool Hangman_game::is_letters_only(const std::string& text) const {
	if (text.empty()) {
		return false;
	}
	for (char c : text) {
		if (c < 'A' || c > 'Z') {
			return false;
		}
	}
	return true;
}

std::vector<std::string> Hangman_game::read_words(const std::string& file_name) const {
	std::vector<std::string> words;

	std::ifstream file(file_name);
	std::string line;
	while (file >> line) {
		line = upper_letters(line);
		if (line.size() >= 3 && is_letters_only(line)) {
			words.push_back(line);
		}
	}
	return words;
}