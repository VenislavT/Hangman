#include "Collection.h"

Collection::Collection() {
	
}
Collection::Collection(const Collection& other) {
	copy_from(other);
}
Collection& Collection::operator=(const Collection& other) {
	if (this != &other) {
		free();
		copy_from(other);
	}
	return *this;
}
Collection::~Collection() {
	free();
}
void Collection::free() {
	delete[] rooms;
}
void Collection::copy_from(const Collection& other) {
	for (int i = 0; i < rooms_count(); i++) {
		rooms[i] = other.rooms[i];
	}
}

void Collection::set_rooms(const Room& rooms) {
	delete this->rooms;
	this->rooms = new Room(rooms);
}
const Room& Collection::get_rooms() const {
	return *rooms;
}
Room& Collection::operator[] (int index) {
	if (index > rooms_count()) {
		throw "Invalid index";
	}
	return rooms[index];
}

const Room& Collection::operator[] (int index) const {
	/*if (index > rooms_count()) {
		throw "Invalid index";
	}*/
	return rooms[index];
}

int Collection::rooms_count() {

	ifstream file("hotel.txt");

	if (!file.is_open()) {
		return 0;
	}
	int count = 0;
	while (!file.eof()) {
		char buff[1024];
		file.getline(buff, 1024);
		count++;
	}
	file.close();
	return count;
}
void Collection::read_all_rooms() {
	ifstream file("hotel.txt");
	if (!file.is_open()) {
		cout << "Error opening database." << endl;
		
	}
	for (int i = 0; i < rooms_count(); i++)
	{
		char temp[1024];
		file.getline(temp, 1024);
		MyString buff(temp);
		rooms = new Room[rooms_count()];
		read_one_room(i,buff);
	}
	file.close();
}
bool Collection::existing_room(int room_number) {
	for (int i = 0; i < rooms_count(); i++) {
		if (room_number = rooms[i].get_room_number()) {
			return true;
		}
	}
	return false;
}
int Collection::find_room_index(int room_number) {
	for (int i = 0; i < rooms_count(); i++) {
		if (room_number = rooms[i].get_room_number()) {
			return room_number;
		}
	}
	return -1;
}
void Collection::save_to_file() {

	ofstream file("hotel.txt", ios::trunc);
	if (!file.is_open())
		return;
	for (int i = 0; i < rooms_count(); i++) {
		file << rooms[i].get_room_number() << "/" << rooms[i].get_beds_count() << "/" << rooms[i].get_is_available() << "/" << rooms[i].get_arrival()
			<< "/" << rooms[i].get_leave() << "/" << rooms[i].get_name() << "/" << rooms[i].get_additional_info();

	}
	file.close();
}
void Collection::change_room(int index,Date& arrival,Date& leave, MyString& name, MyString& additional_info) {

	rooms[index].set_arrival(arrival);
	rooms[index].set_leave(leave);
	rooms[index].set_is_available(0);
	rooms[index].set_name(name);
	rooms[index].set_additional_info(additional_info);
}
MyString Collection::split_field(MyString& source, int& index) {
	int counter = 0;
	int temp = index;
	while (source[index] != '/' && source[index] != '.' && source[index] != '\0') {
		counter++;
		index++;
	}
	char* str = new char[counter + 1];
	counter = 0;
	while (source[temp] != '/' && source[temp] != '.' && source[temp] != '\0') {
		str[counter] = source[temp];
		temp++;
		counter++;
	}
	str[counter] = '\0';
	index++;
	MyString t(str);
	delete[] str;
	return t;
}
void Collection::read_one_room(int index,MyString& line) {

	MyString text;
	Date arrive;
	Date leave;
	int i = 0;
	
	text = split_field(line, i);
	rooms[index].set_room_number(atoi(text.c_str()));

	text = split_field(line, i);
	rooms[index].set_beds_count(atoi(text.c_str()));
	
	text = split_field(line, i);
	rooms[index].set_is_available(atoi(text.c_str()));

	text = split_field(line, i);
	arrive.set_day(atoi(text.c_str()));
	text = split_field(line, i);
	arrive.set_month(atoi(text.c_str()));
	text = split_field(line, i);
	arrive.set_year(atoi(text.c_str()));

	rooms[index].set_arrival(arrive);

	split_field(line, i);
	leave.set_day(atoi(text.c_str()));
	split_field(line, i);
	leave.set_month(atoi(text.c_str()));
	split_field(line, i);
	leave.set_year(atoi(text.c_str()));
	rooms[index].set_leave(leave);

	split_field(line, i);
	rooms[index].set_name(text.c_str());

	split_field(line, i);
	rooms[index].set_additional_info(text.c_str());

}
