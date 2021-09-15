#pragma once
#include <string>
using namespace std;

class AddressBook
{
	string name;
	string phoneNumber;
	string email;
	string address;
	int birthdayMonth;
	int birthdayDay;

public:
	AddressBook(string name, 
		string phoneNumber, 
		string email,
		string address,
		int birthdayMonth,
		int birthdayDay);

	~AddressBook();

	string getName()const;
	string getPhoneNumber()const;
	string getEmail()const;
	string getAddress()const;
	int getBirthdayMonth()const;
	int getBirthdayDay()const;
	

	void setName(string name);
	void setPhoneNumber(string phoneNumber);
	void setEmail(string email);
	void setAddress(string address);
	void setBirthdayMonth(int birthdayMonth);
	void setBirthdayDay(int birthdayDay);

	void Print();
};