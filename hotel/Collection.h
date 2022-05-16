#pragma once
#include "Room.h"
#include "Date.h"
#include "MyString.h"
class Collection
{
public:

	Collection();
	Collection(const Collection& other);
	Collection& operator=(const Collection& other);
	~Collection();

	const Room& get_rooms() const;
	void set_rooms(const Room& rooms);
	Room& operator[] (int index);
	const Room& operator[] (int index) const;

	int rooms_count();
	void read_all_rooms();
	bool existing_room(int room_number);
	int find_room_index(int room_number);
	void save_to_file();
	void change_room(int index, Date& arrival, Date& leave, MyString& name, MyString& additional_info);
	void read_one_room(int index,MyString& line);
	MyString split_field(MyString& source, int& index);
private:
	Room* rooms;
	void free();
	void copy_from(const Collection& other);
};

