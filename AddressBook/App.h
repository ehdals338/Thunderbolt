#pragma once
#include <vector>
#include "AddressBook.h"

using namespace std;

typedef vector<AddressBook *> AddressBookList;
typedef vector<AddressBook *>::iterator AddressBookIter;

enum Menus
{
    Add = 1, List, Search, Del, Exit
};

enum Keys
{
    ArrowUp = 72,
    ArrowDown = 80,
    Enter = 13
};

static string fileName = "addressBook";

class App
{
    int index;
    AddressBookList addressBookList;
public:
    App();
    ~App();

    void Run();

private:
    int SelectMenu();
    void PrintMenu();

    void AddProc();
    void ListProc();
    void SearchProc();
    void DelProc();
    void SaveProc();
    void LoadProc();
    void InitProc();

    AddressBook* FindAddressBook(int index);
    AddressBookIter FindAddressBookPos(int index);

    void PrintBirthday();
};

