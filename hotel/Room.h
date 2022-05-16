#pragma once
#include "MyString.h"
#include "Date.h"

class Room
{
public:

	Room();
	//Room(int room_number, int beds_count, int is_available);
	Room(int room_number, int beds_count, int is_available, Date arrival, Date leave, MyString name, MyString additional_info);

	int get_room_number() const;
	int get_beds_count() const;
	bool get_is_available() const;
	MyString get_additional_info() const;
	MyString get_name() const;
	Date get_arrival() const;
	Date get_leave() const;

	void set_room_number(int number);
	void set_beds_count(int beds_count);
	void set_is_available(bool is_available);
	void set_additional_info(MyString additional_info);
	void set_name(MyString name);
	void set_arrival(Date arrival);
	void set_leave(Date leave);

	

private:

	int room_number;
	int beds_count;
	bool is_available;
	Date arrival;
	Date leave;
	MyString name;
	MyString additional_info;

};

