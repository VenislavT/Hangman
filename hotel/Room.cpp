#include "Room.h"

Room::Room() {
	room_number = 1;
	beds_count = 1;
	is_available = 1;
}
//Room::Room(int room_number, int beds_count, int is_available) {
//	set_room_number(room_number);
//	set_beds_count(beds_count);
//	set_is_available(is_available);
//}
Room::Room(int room_number, int beds_count, int is_available, Date arrival, Date leave, MyString name, MyString additional_info) {
	set_room_number(room_number);
	set_beds_count(beds_count);
	set_is_available(is_available);
	set_arrival(arrival);
	set_leave(leave);
	set_name(name);
	set_additional_info(additional_info);
}

int Room::get_room_number() const {
	return room_number;
}
int Room::get_beds_count() const {
	return beds_count;
}
bool Room::get_is_available() const {
	return is_available;
}
MyString Room::get_additional_info() const {
	return additional_info;
}
MyString Room::get_name() const {
	return name;
}
Date Room::get_arrival() const {
	return arrival;
}
Date Room::get_leave() const {
	return leave;
}

void Room::set_room_number(int room_number) {
	if (room_number <= 0) {
		throw "Wronng number";
	}
	this->room_number = room_number;
}
void Room::set_beds_count(int beds_count) {
	if (beds_count <= 0) {
		throw "Wrong beds count";
	}
	this->beds_count = beds_count;
}
void Room::set_is_available(bool is_available) {
	this->is_available = is_available;
}
void Room::set_additional_info(MyString additional_info) {
	this->additional_info = additional_info;
}
void Room::set_name(MyString name) {
	this->name = name;
}
void Room::set_arrival(Date arrival) {
	this->arrival = arrival;
}
void Room::set_leave(Date leave) {
	this->leave = leave;
}








