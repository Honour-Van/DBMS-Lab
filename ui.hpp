/**
 * @file: ui.h
 * @author: fhn
 * @date: 4/20
 * @version: 1.0
 * @description: textual interface
 */

//--------------------------------------------------------------------------------------------

#ifndef UI_GUARD
#define UI_GUARD

//--------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include "interpreter.hpp"
#include "time_cnt.hpp"


//--------------------------------------------------------------------------------------------

class Interface
{
public:
    void Hello();
    std::string Input();
    void Goodbye();
    bool exit() const { return exit_; }
private:
    bool exit_;
};

#endif // UI_GUARD