#include "Player.h"
Player::Player() : username("Unknown"), score(0){
	
}
Player::Player(const string username, const unsigned int score) {
	set_username(username);
	set_score(score);
}
Player::~Player() {

}
const string Player::get_username() const {
	return username;
}
const unsigned int Player::get_score() const {
	return score;
}

void Player::set_username(const string username) {
	this->username = username;
}
void Player::set_score(const unsigned int score) {
	this->score = score;
}
//Player* Player::clone() const {
//	Player* copy = new Player(*this);
//	return copy;
//}