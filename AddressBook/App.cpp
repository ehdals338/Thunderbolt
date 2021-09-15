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


#include "App.h"
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <ctime>

#pragma warning(disable:4996)

App::App()
{
	index = 1;
}

App::~App()
{
	AddressBookIter seek = addressBookList.begin();
	AddressBookIter end = addressBookList.end();

	for (; seek != end; ++seek)
	{
		delete *seek;
	}
}


void App::Run()
{
	LoadProc();

	while (true)
	{
		int key = SelectMenu();

		switch (key)
		{
		case Add:
			AddProc();
			break;
		case List:
			ListProc();
			break;
		case Search:
			SearchProc();
			break;
		case Del:
			DelProc();
			break;
		case Exit:
		default:
			SaveProc();
			return;
		}
		
		std::cout << "��� �Ϸ��� EnterŰ�� ��������." << std::endl;
		getchar();
	}
}

int App::SelectMenu()
{
	int key;

	while (true)
	{
		PrintMenu();

		key = getch();

		if (key == Enter)
		{
			return this->index;
		}

		if (key == 0 || key == 224)
		{
			key = getch();

			switch (key)
			{
			case ArrowUp:
				this->index--;
				break;
			case ArrowDown:
				this->index++;
				break;
			default:
				break;
			}
		}

		if (this->index < Add)
		{
			this->index = Add;
		}
		else if (this->index > Exit)
		{
			this->index = Exit;
		}
	}
}

void App::PrintMenu()
{
	system("cls");
	cout << "*****************" << endl;
	cout << "*  We are the world!  *" << endl;
	cout << "*****************" << endl;
	cout << "" << '\n';
	cout << "## ������ ���� ##" << endl;

	PrintBirthday();
	
	cout << "" << '\n';
	cout << "-----------------" << endl;
	cout << " 1. �ּҷ� ���" << endl;
	cout << " 2. �ּҷ� ���" << endl;
	cout << " 3. �ּҷ� �˻�" << endl;
	cout << " 4. �ּҷ� ����" << endl;
	cout << " 5. ��       ��" << endl;
	cout << "-----------------" << endl;
	cout << "������ ��ȣ: " << this->index << endl;
	cout << "����Ű�� Ȱ���Ͽ� ���ϴ� ��ȣ�� ���� �� EnterŰ�� ��������." << endl;
}

AddressBook* App::FindAddressBook(int index)
{
	AddressBookIter seek = FindAddressBookPos(index);
	AddressBookIter end = addressBookList.end();

	if (seek == end)
	{
		return NULL;
	}
	else
	{
		return *seek;
	}
}

AddressBookIter App::FindAddressBookPos(int index)
{
	AddressBookIter seek = addressBookList.begin();
	AddressBookIter end = addressBookList.end();

	if (end - seek < index)
	{
		return end;
	}

	return seek + index;
}

void App::AddProc()
{
	cout << "[�ּҷ� ���]" << endl;

	string name;
	cout << "�̸�: ";
	cin >> name;
	cin.ignore();

	string phoneNumber;
	cout << "��ȭ��ȣ: ";
	cin >> phoneNumber;
	cin.ignore();

	string email;
	cout << "�̸���: ";
	cin >> email;
	cin.ignore();

	string address;
	cout << "�ּ�(��): ";
	cin >> address;
	cin.ignore();

	int birthdayMonth;
	cout << "����(��): ";
	cin >> birthdayMonth;
	cin.ignore();

	int birthdayDay;
	cout << "����(��): ";
	cin >> birthdayDay;
	cin.ignore();

	AddressBook* addressBook = new AddressBook(name,
		phoneNumber, email, address, birthdayMonth, birthdayDay);

	addressBookList.push_back(addressBook);
	cout << "�߰� �Ǿ����ϴ�." << endl;
}

void App::ListProc()
{
	cout << "[�ּҷ� ���]" << endl;

	AddressBookIter seek = addressBookList.begin();
	AddressBookIter end = addressBookList.end();
	int count = 0;
	for (; seek != end; ++seek)
	{
		cout << ++count << ". ";
		(*seek)->Print();
	}
}

void App::SearchProc()
{
	cout << "[�ּҷ� �˻�]" << endl;

	string name;
	cout << "�̸�: ";
	cin >> name;
	cin.ignore();

	AddressBookIter seek = addressBookList.begin();
	AddressBookIter end = addressBookList.end();

	for (; seek != end; ++seek)
	{
		AddressBook* ab = *seek;
		if (ab->getName() == name)
		{
			ab->Print();
		}
	}
}

void App::DelProc()
{
	cout << "[�ּҷ� ����]" << endl;

	int num;
	cout << "��ȣ: ";
	cin >> num;
	cin.ignore();

	AddressBookIter seek = FindAddressBookPos(num - 1);
	AddressBookIter end = addressBookList.end();

	if (seek != end)
	{
		addressBookList.erase(seek);

		cout << "���� �Ǿ����ϴ�. " << endl;
	}
	else
	{
		cout << "�������� �ʴ� ��ȣ�Դϴ�." << endl;
	}
}


void App::SaveProc()
{
	ofstream os;
	os.open(fileName);

	AddressBookIter seek = addressBookList.begin();
	AddressBookIter end = addressBookList.end();

	for (; seek != end; ++seek)
	{
		AddressBook* ab = *seek;

		os << ab->getName() << " "
			<< ab->getPhoneNumber() << " "
			<< ab->getEmail() << " "
			<< ab->getAddress() << " "
			<< ab->getBirthdayMonth() << " "
			<< ab->getBirthdayDay() << endl;
	}

	os.close();
}

void App::LoadProc() 
{
	ifstream is;
	is.open(fileName);

	if (is.is_open())
	{
		while (!is.eof())
		{
			string name;
			string phoneNumber;
			string email;
			string address;
			int birthdayMonth;
			int birthdayDay;

			is >> name >> phoneNumber >> email
				>> address >> birthdayMonth >> birthdayDay;

			if (name.empty() || phoneNumber.empty() || email.empty()
				|| address.empty())
			{
				return;
			}

			AddressBook* addressBook = new AddressBook(name,
				phoneNumber, email, address, birthdayMonth, birthdayDay);

			addressBookList.push_back(addressBook);
		}
	}
	else
	{
		cout << "����� ������ �����ϴ�." << endl;
	}
}
/*
void App::InitProc()
{
	cout << "[���� �ʱ�ȭ]" << endl;

	fstream fs;
	fs.open(fileName, ios::out);
	fs.close();
}
*/
void App::PrintBirthday()
{
	time_t t = time(0);
	tm* current = localtime(&t);

	AddressBookIter seek = addressBookList.begin();
	AddressBookIter end = addressBookList.end();

	for (; seek != end; ++seek)
	{
		AddressBook* ab = *seek;

		if (ab->getBirthdayMonth() == (current->tm_mon + 1)
			&& ab->getBirthdayDay() == current->tm_mday)
		{
			cout << "<<������ " << ab->getName() << "���� �����Դϴ�!>>" << endl;
		}
	}
}