#include "USERS.h"
USERS::USERS() : email(email), username(username), password(password){

}
USERS::USERS(const string email, const string password, const string username)  {
	set_email(email);
	set_password(password);
	set_username(username);
}
USERS::~USERS() {
	
}
void USERS::set_email(const string email) {
	this->email = email;
}
void USERS::set_password(const string password) {
	this->password = password;
}
void USERS::set_username(const string username) {
	this->username = username;
}
const string USERS::get_email() const {
	return email;
}
const string USERS::get_password() const {
	return password;
}
const string USERS::get_username() const {
	return username;
}
