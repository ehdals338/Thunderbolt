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

void main()
{
    App* app = new App();
    app->Run();
    delete app;
}
