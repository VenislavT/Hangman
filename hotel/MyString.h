#pragma once
#pragma warning(disable : 4996)
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
class MyString
{
public:

	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other);
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);
	~MyString();

	int get_size() const;
	const char* c_str() const;

	MyString& operator+=(const MyString& other);
	char& operator[] (int index);
	const char& operator[] (int index) const;
	friend istream& operator>>(istream& is, MyString& obj);
	friend ostream& operator<<(ostream& os, const MyString& obj);
private:
	char* str;
	int size;
	void copy_from(const MyString& other);
	void free();
};

MyString operator+(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);


