#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Date
{
public:
	Date();
	Date(int day, int month, int year);

	int get_day() const;
	int get_month() const;
	int get_year() const;

	void set_day(int day);
	void set_month(int month);
	void set_year(int year);

	int count_leap_years() const;
	friend ostream& operator<<(ostream& os, const Date& date);
	friend istream& operator>>(istream& is, Date& date);
	Date input_date();
private:
	int day;
	int month;
	int year;
	bool leap_year() const;
};
int days_diff(Date& date1, Date& date2);

