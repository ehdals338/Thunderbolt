/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
*  Copyright (C) 2020 by Dongmin Jang(장동민), All rights reserved.
*
*  Purpose of program: Addressbook(주소록 프로그램)
*
*  Programmer: Dongmin Jang  (장동민),
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
		
		std::cout << "계속 하려면 Enter키를 누르세요." << std::endl;
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
	cout << "## 오늘의 생일 ##" << endl;

	PrintBirthday();
	
	cout << "" << '\n';
	cout << "-----------------" << endl;
	cout << " 1. 주소록 등록" << endl;
	cout << " 2. 주소록 목록" << endl;
	cout << " 3. 주소록 검색" << endl;
	cout << " 4. 주소록 삭제" << endl;
	cout << " 5. 종       료" << endl;
	cout << "-----------------" << endl;
	cout << "선택한 번호: " << this->index << endl;
	cout << "방향키를 활용하여 원하는 번호를 선택 후 Enter키를 누르세요." << endl;
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
	cout << "[주소록 등록]" << endl;

	string name;
	cout << "이름: ";
	cin >> name;
	cin.ignore();

	string phoneNumber;
	cout << "전화번호: ";
	cin >> phoneNumber;
	cin.ignore();

	string email;
	cout << "이메일: ";
	cin >> email;
	cin.ignore();

	string address;
	cout << "주소(도): ";
	cin >> address;
	cin.ignore();

	int birthdayMonth;
	cout << "생일(월): ";
	cin >> birthdayMonth;
	cin.ignore();

	int birthdayDay;
	cout << "생일(일): ";
	cin >> birthdayDay;
	cin.ignore();

	AddressBook* addressBook = new AddressBook(name,
		phoneNumber, email, address, birthdayMonth, birthdayDay);

	addressBookList.push_back(addressBook);
	cout << "추가 되었습니다." << endl;
}

void App::ListProc()
{
	cout << "[주소록 목록]" << endl;

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
	cout << "[주소록 검색]" << endl;

	string name;
	cout << "이름: ";
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
	cout << "[주소록 삭제]" << endl;

	int num;
	cout << "번호: ";
	cin >> num;
	cin.ignore();

	AddressBookIter seek = FindAddressBookPos(num - 1);
	AddressBookIter end = addressBookList.end();

	if (seek != end)
	{
		addressBookList.erase(seek);

		cout << "삭제 되었습니다. " << endl;
	}
	else
	{
		cout << "존재하지 않는 번호입니다." << endl;
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
		cout << "저장된 파일이 없습니다." << endl;
	}
}
/*
void App::InitProc()
{
	cout << "[파일 초기화]" << endl;

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
			cout << "<<오늘은 " << ab->getName() << "님의 생일입니다!>>" << endl;
		}
	}
}
