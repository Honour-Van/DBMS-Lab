#include "time_cnt.hpp"
namespace time_cnt
{

/**
* @author: fhn
* @date: 4/20
* @version: 1.0
* @description: three modes of sleeping of different time span, 
                this is the substitution for sleep() in "Windows.h", in order to guaratee the protability between windows, linux and mac.

                sleep1: INT_MAX/10
*/
void Sleep1()
{
    int i = 0, bound = INT_MAX/10;
    while (++i <= bound);
}

//sleep2: INT_MAX/15
void Sleep2()
{
    int i = 0, bound = INT_MAX/15;
    while (++i <= bound);
}

//sleep3: INT_MAX/27
void Sleep3()
{
    int i = 0, bound = INT_MAX/27;
    while (++i <= bound);
}

void Sleep4()
{
    int i = 0, bound = INT_MAX/80;
    while (++i <= bound);
}

void Sleep5()
{
    int i = 0, bound = INT_MAX/50;
    while(++i <= bound);
}

clock_t s, e;
void start()
{
    s = clock();
}
void end()
{
    e = clock();
    std::cout << "(" << (double)(e-s) / CLOCKS_PER_SEC << " sec)" << std::endl;
}

}//namespace time