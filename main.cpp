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
#include <climits>
#include "ui.hpp"
#include "exception.hpp"

//--------------------------------------------------------------------------------------------

extern bool broken;

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
        cout << "#ERROR " << e.what() << endl<< endl;
#ifdef _TEST5_
clog << std::cin.eof() << " " << std::cin.bad() << " " << std::cin.fail() << std::endl;
#endif
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');//we must put an end symbol here, else we would input another INT_MAX elems to restart.
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