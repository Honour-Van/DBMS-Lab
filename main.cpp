/**
 * @file: main.cpp
 * @author: fhn
 * @date: 4/20
 * @description: main part of integrating the interfaces, 
 *              calling ui to input the cmd;
 *                      interpreter has a main integrated entry: then to different kinds of dealing parts
 *                       in_out: main I/O interfaces, the most difficult parts of cache and so on.
 *                      time_cnt: including the sleep functions and the time count function.
 * 
 * @version:
 *          v1.0 frist attmpt to structurize
 *          v2.0: add the exception parts
 *          release : more of the inputing exception 
*/

//--------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "ui.hpp"
#include "exception.hpp"

//--------------------------------------------------------------------------------------------

extern bool broken;

int main()
{
    Interface main;
    // main.Hello();
    while (true){
        Interpret(main.Input());
        if (main.exit())
            break;
    }
    main.Goodbye();
}