/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
*  Copyright (C) 2020 by Dongmin Jang(�嵿��), All rights reserved.
*
*  Purpose of program: Addressbook, �ּҷ� ���α׷�
*
*  Programmer: Dongmin Jang  (�嵿��),
*                 Software Engineering Lab,
*                 Department of Electrical and Computer Engineering,
*                 Sungkyunkwan University
*
*  Program date: July 10, 2020
*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include "AddressBook.h"
#include <iostream>
using namespace std;

AddressBook::AddressBook(string name,
	string phoneNumber,
	string email,
	string address,
	int birthdayMonth,
	int birthdayDay)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->address = address;
	this->birthdayMonth = birthdayMonth;
	this->birthdayDay = birthdayDay;
}

AddressBook::~AddressBook()
{
}

string AddressBook::getName()const
{
	return name;
}
string AddressBook::getPhoneNumber()const
{
	return phoneNumber;
}
string AddressBook::getEmail()const
{
	return email;
}
string AddressBook::getAddress()const
{
	return address;
}
int AddressBook::getBirthdayMonth()const
{
	return birthdayMonth;
}
int AddressBook::getBirthdayDay()const
{
	return birthdayDay;
}


void AddressBook::setName(string name)
{
	this->name = name;
}
void AddressBook::setPhoneNumber(string phoneNumber)
{
	this->phoneNumber = phoneNumber;
}
void AddressBook::setEmail(string email)
{
	this->email = email;
}
void AddressBook::setAddress(string address)
{
	this->address = address;
}
void AddressBook::setBirthdayMonth(int birthdayMonth)
{
	this->birthdayMonth = birthdayMonth;
}
void AddressBook::setBirthdayDay(int birthdayDay)
{
	this->birthdayDay = birthdayDay;
}

void AddressBook::Print()
{
	cout << "�̸�: " << this->name << ", "
		<< "����ó: " << this->phoneNumber << ", "
		<< "�̸���: " << this->email << ", "
		<< "�ּ�: " << this->address << ", "
		<< "����: " << this->birthdayMonth << "/" << this->birthdayDay
		<< endl;
}
