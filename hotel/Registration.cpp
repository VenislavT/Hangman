#include "Registration.h"


void Registration::run() {

	int room_number; 
	Date arrive;
	Date leave;
	MyString name;
	MyString additional_info;
	data.read_all_rooms();
	cout << "Enter room number: ";
	cin >> room_number;
	cout << room_number << endl;
	cout << endl;
	while (!data.existing_room(room_number)) {
		cout << "Room does not exist." << endl;
		cout << "Enter room number";
		cin >> room_number;
	}
	int index = data.find_room_index(room_number);

	system("cls");
	cout << "----Arrival----";
	cout << endl;
	arrive.input_date();
	cout << "----Depart---- ";
	cout << endl;
	leave.input_date();
	
	if (days_diff(arrive, leave) < 0) {
		cout << "Can not be possible. Swap dates." <<endl;
	}

	cout << "Name of guest: ";
	cin >> name;

	cout << "Additional info: ";
	cin >> additional_info;

	data.change_room(index, arrive, leave, name, additional_info);
	data.save_to_file();
}

