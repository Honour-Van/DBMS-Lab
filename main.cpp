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
#include <climits>
#include "ui.hpp"
#include "exception.hpp"

//--------------------------------------------------------------------------------------------

int main()
{
    Interface main;
    // main.Hello();
    while (true)
    {
    try{
        Interpret(main.Input());
    } catch (std::exception& e){
        using namespace std;
        cout << "#ERROR " << e.what() << endl;
#ifdef _TEST5_
clog << std::cin.eof() << " " << std::cin.bad() << " " << std::cin.fail() << std::endl;
#endif
        // cin.ignore(numeric_limits<std::streamsize>::max());  
        cin.clear();
        system("color 1F"); time_cnt::Sleep2(); system("color 0F");
    } catch(...){
        std::cout << "#WARNING: UNKNOWN EXCEPTION OCCURED" << std::endl;
    }
        if (main.exit())
            break;
    }
    main.Goodbye();
}