#include "Player.h"
Player::Player() : username(username), score(score){
	
}
Player::Player(const string username, const int score) {
	set_username(username);
	set_score(score);
}
Player::~Player() {

}
const string Player::get_username() const {
	return username;
}
const int Player::get_score() const {
	return score;
}

void Player::set_username(const string username) {
	this->username = username;
}
void Player::set_score(const int score) {
	this->score = score;
}
