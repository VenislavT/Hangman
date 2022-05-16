#include "Report.h"
void Report::run() {
	data.read_all_rooms();
	Date temp(0, 0, 0);
	d1.input_date();
	d2.input_date();
	int days_d1 = days_diff(temp, d1);
	int days_d2 = days_diff(temp, d2);
	ofstream file("dates.txt");
	for (int i = 0; i < data.rooms_count(); i++) {
		Date d3(data[i].get_arrival());
		Date d4(data[i].get_leave());
		int days_d3 = days_diff(temp, d3);
		int days_d4 = days_diff(temp, d4);
		int diff = min(days_d4, days_d2) - max(days_d3, days_d1);
		file << data[i].get_room_number() << " " << diff << endl;
	}
	file.close();
}
