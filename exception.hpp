/**
* @file: exception.hpp
* @author: fhn
* @date: 5/1
* @version: v1.0
* @description: exception process
*/

//--------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>
#include <climits>
#include "time_cnt.hpp"

//--------------------------------------------------------------------------------------------
#ifndef EXCEPTION_GUARD
#define EXCEPTION_GUARD

bool exist(const std::string&);
void Break();

/**
 * @author: fhn
 * @date: 5/13
 * @description: at last we deprecate them, because unknown output hollow boxes.
 * @version: 0
*/
// inline void error(const std::string& errormessage)
// {
//     // static int times = 0;
//     using namespace std;
//     // throw std::runtime_error(errormessage);
//     // times++;
//     // if (times >= 2)
//     // {system("cls"); times = 0;}
//     fflush(stdin); fflush(stdout);
//     system("cls");
//     cerr << "#ERROR " << errormessage << endl << endl;
//     cin.ignore(INT_MAX, '\n');//we must put an end symbol here, else we would input another INT_MAX elems to restart.
//     cin.clear();
//     system("color 1F"); time_cnt::Sleep2(); system("color 0F");
// }

// inline void error(std::string s1, std::string s2)
// {
//     error(s1+s2);
// }

// inline void error(std::string s1, std::string s2, std::string s3)
// {
//     error(s1+s2+s3);
// }
#endif