/**
 * @file: main.cpp
 * @author: fhn
 * @date: 4/20
 * @description: first attempt to structurize
 * @version: 1.0
*/

//--------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "ui.hpp"

//--------------------------------------------------------------------------------------------

int main()
{
    Interface main;
    // main.Hello();
    while (true)
    {
        Interpret(main.Input());
        if (main.exit())
            break;
    }
    main.Goodbye();
    return 0;
}