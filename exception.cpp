/**
* @file: exception.cpp
* @author: fhn
* @date: 5/1
* @version: v1.0
* @description:  after dealing with exception, turn the file stream to console , and possibly delete the table file
*/

//--------------------------------------------------------------------------------------------

#include "exception.hpp"

//--------------------------------------------------------------------------------------------

bool exist(const std::string& s)
{
    FILE *fp = fopen(s.c_str(), "r");
    if (fp == NULL) return false;
    return true;
}