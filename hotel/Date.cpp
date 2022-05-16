#include "Date.h"

Date::Date() : Date(1,1,1) {

}
Date::Date(int day, int month, int year) {
	set_day(day);
	set_month(month);
	set_year(year);
}

int Date::get_day() const {
	return day;
}
int Date::get_month() const {
	return month;
}
int Date::get_year() const {
	return year;
}

void Date::set_day(int day) {
	if (day < 0) {
		this->day = 1;
	}
	if (month == 2) {
		if (leap_year()) {
			if (day <= 29) {
				this->day = day;
			}
		}
		else {
			if (day <= 28) {
				this->day = day;
			}
		}
	}
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (this->day <= 31) {
			this->day = day;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (this->day <= 30) {
			this->day = day;
		}
	}
}
void Date::set_month(int month) {
	if (month > 12 || month<=0) {
		month = 1;
	}
	this->month = month;
}
void Date::set_year(int year) {
	this->year = year;
}
bool Date::leap_year() const {
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
int Date::count_leap_years() const {
	int count = 0;
	for (int i = 0; i <= year; i++) {
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
			count++;
		}
	}
	if (month < 2 || (month == 2 && day < 29)) {
		count--;
	}
	return count;
}
int days_diff(Date& date1, Date& date2) {

	int months_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	long int date1_days = date1.get_year() * 365 + date1.get_day();
	for (int i = 0; i < date1.get_month(); i++) {
		date1_days += months_days[i];
	}
	date1_days += date1.count_leap_years();

	long int date2_days = date2.get_year() * 365 + date2.get_day();
	for (int j = 0; j < date2.get_month(); j++) {
		date2_days += months_days[j];
	}
	date2_days += date2.count_leap_years();

	return date2_days - date1_days;
}
ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day << "." << date.year << "." << date.year;
	return os;
}
istream& operator>>(istream& is, Date& date)
{
	is >> date.day;
	is.ignore(1);
	is >> date.month;
	is.ignore(1);
	is >> date.year;
	return is;
}
Date Date::input_date() {
	cout << "Enter day: ";
	cin >> day;
	cout << "Enter month: ";
	cin >> month;
	cout << "Enter year: ";
	cin >> year;
	return Date(day, month, year);
}
