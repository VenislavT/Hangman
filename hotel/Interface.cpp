#include "Interface.h"
void Interface::run() {
	bool first_command = true;
	while (first_command) {
		//system("cls");
		cout << "--------Menu--------" << endl;
		cout << ">Registration" << endl;
		cout << endl;
		cout << ">Available" << endl;
		cout << endl;
		cout << ">Release" << endl;
		cout << endl;
		cout << ">Report" << endl;
		cout << endl;
		cout << ">Exit" << endl;
		cout << "---------------------" << endl;
		cout << endl;
		cout << "Command: ";
		cin >> command;
		if (command == "Registration") {
			first_command = false;
			Registration opr;
			opr.run();
		}
		else if (command == "Available") {
			first_command = false;
			Available_rooms opr2;
			opr2.run();
		}
		else if (command == "Release") {
			Available_rooms opr3;
			opr3.run();
		}
		else if (command == "Report") {
			Report opr4;
		}
		else if (command == "Exit") {
			break;
		}
		else {
			cout << endl;
			cout << "Wrong command! Try again." << endl;
		}
	}

}
