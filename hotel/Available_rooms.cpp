#include "Available_rooms.h"
void Available_rooms::run() {
	data.read_all_rooms();
	for (int i = 0; i < data.rooms_count(); i++) {
		if (data[i].get_is_available() == 1) {
			cout << data[i].get_room_number() << endl;
		}
	}
	cout << "----" << endl;
}
