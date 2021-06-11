#include "Hangman_game.h"

void Hangman_game::save_game(string file_name, unsigned int misses, string letters, string blank, string word, unsigned int personal_score) {
	
	ofstream file(file_name);
	if (!file.is_open()) {
		return;
	}
	file << misses << " " << letters << " " << blank << " " << word << " " << personal_score << endl;
	file.close();
}
void Hangman_game::add_word(string name_of_file) {
	string word;
	cout << "Type the word to be added: ";
	cin >> word;
	upper_letters(word);
	ofstream file(name_of_file, ios::app);
	if (!file.is_open()) {
		return;
	}
	file << word << endl;
	file.close();
}
string Hangman_game::take_word(string name_of_file) {
	int misses = 0;
	string word;

	string answer_word;

	vector<string> words;
	ifstream file(name_of_file, ios::app);
	string line;
	while (getline(file, line)) {
		words.push_back(line);
	}
	file.close();
	word = words[rand() % words.size()];
	upper_letters(word);
	return word;
	/*guess(word, blank_word(word));*/
}
int Hangman_game::guess(const string word, string answer_word, unsigned int personal_score, const string username, int& misses) {
	/*int misses = 0;*/
	string guessed_letters;
	while (misses<=6) {
		system("cls");

		string guess;
		draw_hangman(misses);
		cout << "Number of lifes: " << (6 - misses) << endl;
		if (misses == 6) {
			cout <<"Word: "<< word << endl;
			cout << "Game over." << endl;
			return personal_score;
		}
		cout <<"Guessed word     "<< answer_word << endl;
		if (answer_word == word) {
			
			cout << "You win!" << endl;
			personal_score++;
			return personal_score;
		}
		cout << "Enter your guess: ";
		cout << guessed_letters;
		cout << " ";
		cin >> guess;
		upper_letters(guess);
		int x = 0;
		if (guess == "#") {
			for (int i = 0; i < answer_word.size(); i++) {
				x = x + word[i];
			}
			string file_to_save = username + to_string(x) + ".txt";
			save_game(file_to_save, misses, guessed_letters, answer_word, word, personal_score);
			break;
		}
		guessed_letters = guessed_letters +" "+ guess;

		bool letter_is_found = false;
		
		if (guess.size() > 1) {
			if (guess == word) {
				answer_word = guess;
				cout <<"The word is:  "<< answer_word << endl;
				cout << "You win." << endl;
				personal_score++;
				return personal_score;
			}
			else {
				misses++;
				/*system("cls");*/
				/*draw_hangman(misses);*/
			}
		}

		else if (guess.size() == 1) {
			for (int i = 0; i < word.size(); i++) {
				if (guess[0] == word[i]) {
					answer_word[i] = guess[0];
					letter_is_found = true;
				}
			}
			cout << answer_word << endl;
			if (!letter_is_found) {
				misses++;
				
				/*draw_hangman(misses);*/
			}
		}
		
	}
	
}
string Hangman_game::blank_word(string word) {
	/*string blank_word;
	while (blank_word.size() < word.size()) {
		blank_word.push_back('_');
	}
	cout << blank_word << endl;
	return word;*/
	for (int i = 0; i < word.size(); i++) {
		word[i] = '_';
	}
	cout << word << endl;
	return word;
}
void Hangman_game::draw_hangman(unsigned int misses) {
	if (misses >= 2) {
		cout << "+-------------" << endl;

	}
	if (misses >= 1) {
		if (misses == 3) {
			cout << "|" << "      |       " << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
		}
		else if(misses==4){
			cout << "|" << "      |       " << endl;
			cout << "|" << "      0       " << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
		}
		else if (misses == 5) {
			cout << "|" << "      |       " << endl;
			cout << "|" << "      0       " << endl;
			cout << "|" << "    \\ | /     " << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
		}
		else if (misses == 6) {
			cout << "|" << "      |       " << endl;
			cout << "|" << "      0       " << endl;
			cout << "|" << "    \\ | /     " << endl;
			cout << "|" << "      |       " << endl;
			cout << "|" << "     / \\      " << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
		}
		else if(misses >= 1){
			
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
		}
	}
	if (misses > 0) {
	
		cout << "+---------------------------" << endl;
	}
	if (misses == 0) {
		/*cout <<  endl;*/
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout <<  endl;
		cout << "+---------------------------" << endl;
	}
}

string Hangman_game::upper_letters(string& word) {
	for (int i = 0; i < word.size(); i++) {
		if (word[i] >= 'a' && word[i] <= 'z') {
			word[i] = word[i] - ('a'-'A');
		}
	}
	return word;
}