#include "USERS.h"

USERS::USERS(const string& email, const string& password, const string& username, int score)  
	: email(email), password(password), username(username), score(score)
{
}

const string& USERS::get_email() const {
	return email;
}
const string& USERS::get_password() const {
	return password;
}
const string& USERS::get_username() const {
	return username;
}
int USERS::get_score() const {
	return score;
}

void USERS::set_email(const string& email) {
	this->email = email;
}
void USERS::set_password(const string& password) {
	this->password = password;
}
void USERS::set_username(const string& username) {
	this->username = username;
}
void USERS::set_score(int score) {
	this->score = score;
}
