#include "Release.h"
void Release::run() {
	
	data.read_all_rooms();
	cin >> room_number;
	int index = data.find_room_index(room_number);
	data[index].set_is_available(1);
	data[index].set_arrival(Date(0, 0, 0));
	data[index].set_leave(Date(0, 0, 0));
	data[index].set_name("-");
	data[index].set_additional_info("-");
	data.save_to_file();
}
