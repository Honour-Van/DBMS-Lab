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
#include "time_cnt.hpp"

//--------------------------------------------------------------------------------------------
#ifndef EXCEPTION_GUARD
#define EXCEPTION_GUARD

bool exist(const std::string&);
void Break();

inline void error(const std::string& errormessage)
{
    throw std::runtime_error(errormessage);
}

inline void error(std::string s1, std::string s2)
{
    error(s1+s2);
}

inline void error(std::string s1, std::string s2, std::string s3)
{
    error(s1+s2+s3);
}
#endif