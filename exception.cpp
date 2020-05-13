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

bool broken = false;
void Break()
{
    if (std::cin.eof() || std::cin.bad())
        if (!broken)
            {
                std::cerr << "Data is broken here as you can see." << std::endl;
                broken = true;
            }
}

bool exist(const std::string& s)
{
    FILE *fp = fopen(s.c_str(), "r");
    if (fp == NULL) return false;
    return true;
}