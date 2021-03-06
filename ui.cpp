/**
 * @file: ui.h
 * @author: fhn
 * @date: 4/20
 * @description: textual interface
 * @version: 1.0 has fulfilled
 */

//--------------------------------------------------------------------------------------------

#include "ui.hpp"

const std::string kMysql = "mysql> ";

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

/**
* @file: ui.cpp
* @author: fhn
* @date: 4/21
* @description: three main parts of textual ui.  Hello() is the welcome cover.
* @version: 1.0
*/

void Intro();
void Blingbling();
void FakeUser(const std::string&);

/**
* @author: fhn
* @date: 4/21
* @description: 1.0: simulate the interface of mysql 
                    hoping to do : to make the inputting more real;
* @version: 1.0 
*/
void Interface::Hello()
{
    Intro();
    Blingbling();
    using std::cin;
    using std::cout;
    using std::endl;
    cout << "Windows PowerShell" << endl
         << "版权所有 (C) Microsoft Corporation。保留所有权利。" << endl
         << "尝试新的跨平台 PowerShell https://aka.ms/pscore6" << endl
         << "PS C:\\Users\\abc44> ";
    FakeUser("net start mysql");
    cout << "请求的服务已经启动。\n\n"
         << "请键入 NET HELPMSG 2182 以获得更多的帮助。\n\n";
    cout << "PS C:\\Users\\abc44> ";
    FakeUser("cd D:\\Mysql\\mysql-8.0.19-winx64\\bin");
    cout << "PS D:\\Mysql\\mysql-8.0.19-winx64\\bin> ";
    FakeUser("mysql -u root -p");
    cout << "Enter password: ";
    FakeUser("********");
    cout << "Welcome to the MySQL monitor.  Commands end with ; or \\g.\n";
    cout << "Your MySQL connection id is 9\n";
    cout << "Server version: 8.0.19 MySQL Community Server - GPL\n\n";
    cout << "Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.\n\n";
    cout << "Oracle is a registered trademark of Oracle Corporation and/or its\n";
    cout << "affiliates. Other names may be trademarks of their respective\n";
    cout << "owners.\n\n";
    cout << "Type 'help;' or '\\h' for help. Type '\\c' to clear the current input statement.\n\n";
}

//--------------------------------------------------------------------------------------------

/**
 * @author: fhn
 * @date: 4/21
 * @description: to input a string, one line or more. 
 * @output: string ending with char ';'
 * @version: 
*/
std::string Interface::Input()
{
    using namespace std;
    cout << kMysql;
    string line, sentence;
    stringstream ss;
    bool already_in = false, danger = true;// to indicate whether we have input or not
    cin.clear();
    while (getline(cin, line))
    {
        danger = false;
        if (already_in && line.size() > 1) 
            ss << ' ';
        if (line.size()){
            ss << line;
            already_in = true;
        }
        if (line[line.size()-1] == ';'){
            sentence = ss.str(); // using `ss>>` we'll only get the first word of ss.
                                //(which is defined by the rules of stream inserting)
            break;
        }
        else
            cout << "    -> ";
    }
    extern bool broken;

    // if (danger)
    //     if (broken)
    //         error("Data Broken");
    //     else
    //         error("No input at all");
    time_cnt::start();
#ifdef _LOC_
cout << "src sentence was : " << sentence << endl;
#endif
    if (sentence == "exit;")
        exit_ = true;
    return sentence;
}

//--------------------------------------------------------------------------------------------

/**
 * @author: fhn
 * @date: 4/21
 * @description: 3 of the three main ui interface.
 * @version: 
*/
void Interface::Goodbye()
{
    using namespace std;
    cout << endl << "Bye!" << endl;
}

//--------------------------------------------------------------------------------------------

/**
* @author: fhn
* @date: 4/20
* @description: the basic information of myself.
* @version: 1.0
*/
void Intro()
{
    system("cls");
    system("mode con cols=80 lines=14");
    using std::cout; using std::endl;
    cout << endl << endl;
    cout << R"(                                                             )" << endl;
    cout << R"(                     DBMS LAB: A Scale Modeling of Mysql     )" << endl;  
    cout << R"(                                                             )" << endl;
    cout << R"(                          Fan Haonian, Depart. of EE         )" << endl;
    cout << R"(                                                             )" << endl;
    cout << R"(                                 Date: 4/21                  )" << endl;
    cout << R"(                                                             )" << endl;
    cout << R"(                        * Press any key to continue...       )" << endl;
    std::cin.get();
}

/**
* @author: fhn
* @date: 4/20
* @description: a dynamic blingbling~ opening of this program.
* @version: 1.0
*/
void Blingbling()
{
    system("cls");
    system("mode con cols=120 lines=20");
    using std::cout; using std::endl;
    cout << endl
         << endl
         << endl
         << endl;
    cout << R"(     *************        *******************           *****            **************        ****            ****      )" << endl;
    cout << R"(     *****     *****      *******************          *******           ****************        ****         ****       )" << endl;
    cout << R"(     *****      *****     ******                      **** ****          *****       *****        ****       ****        )" << endl;
    cout << R"(     *****     *****      *****************          ****   ****         *****        ****          ****   ****          )" << endl;
    cout << R"(     *************        *****************         *************        *****        ****             *****             )" << endl;
    cout << R"(     *****   ****         ******                   ****************      *****       *****             *****             )" << endl;
    cout << R"(     *****     ****       *******************     ****          ****     ***************               *****             )" << endl;
    cout << R"(     *****       ******   *******************    ****            ****    **************                *****             )" << endl;
    system("color 48");
    time_cnt::Sleep3();
    system("color 0F");
    time_cnt::Sleep2();
    system("color 68");
    time_cnt::Sleep3();
    system("color 0F");
    time_cnt::Sleep2();
    system("color F8");
    time_cnt::Sleep3();
    system("color 0F");
    time_cnt::Sleep1();
    system("mode con cols=110 lines=25");
};

void FakeUser(const std::string& info)
{
    time_cnt::Sleep1();
    for (int i = 0; i < info.size(); i++)
    {
        std::cout << info[i];
        time_cnt::Sleep4();
        if (i % 5 == 0)
            time_cnt::Sleep5();
    }
    std::cout << std::endl;
}