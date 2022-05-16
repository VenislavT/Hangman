#include "MyString.h"
MyString::MyString() {
	str = new char[1];
	str[0] = '\0';
	size = 0;
}
MyString::MyString(const char* str) {
	if (str == nullptr) {
		this->str = new char[1];
		this->str[0] = '\0';
		this->size = 0;
	}
	else {
		this->str = new char[strlen(str) + 1];
		strcpy(this->str, str);
		this->size = strlen(str);
	}
}
MyString::MyString(const MyString& other) {
	copy_from(other);
}
MyString::MyString(MyString&& other) {
	size = other.size;
	str = new char[strlen(other.str)+1];
	strcpy(str, other.str);
	delete[] other.str;
	other.str = nullptr;
	other.size = 0;
}
MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		free();
		copy_from(other);
	}
	return *this;
}
MyString& MyString::operator=(MyString&& other) {
	if (this != &other) {
		free();
		size = other.size;
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
		delete[] other.str;
		other.str = nullptr;
		other.size = 0;
	}
	return *this;
}
MyString::~MyString() {
	free();
}

int MyString::get_size() const {
	return size;
}
const char* MyString::c_str() const {
	return str;
}

char& MyString::operator[] (int index) {
	if (index > strlen(str)) {
		throw "Invalid index";
	}
	return str[index];
}

const char& MyString::operator[] (int index) const {
	if (index > strlen(str)) {
		throw "Invalid index";
	}
	return str[index];
}
MyString& MyString::operator+=(const MyString& other) {
	char* concat = new char[strlen(str) + strlen(other.str) + 1];
	strcpy(concat, str);
	strcat(concat, other.str);
	delete[] str;
	str = concat;
	size = strlen(concat);
	return *this;
}
istream& operator>>(istream& is, MyString& obj) {
	obj = MyString();
	char buff[1024];
	is >> buff;
	obj.str = new char[strlen(buff) + 1];
	strcpy(obj.str, buff);
	obj.size = strlen(buff);
	return is;
}
ostream& operator<<(ostream& os,const MyString& obj) {
	os << obj.str;
	return os;
}
void MyString::copy_from(const MyString& other) {
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	size = other.size;
}
void MyString::free() {
	delete[] str;
}
MyString operator+(const MyString& lhs, const MyString& rhs) {
	MyString copy(lhs);
	copy += lhs;
	return copy;
}
bool operator==(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}
bool operator>(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator<(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator<=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
