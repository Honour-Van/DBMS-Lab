/**
 * @file: in_out.cpp
 * @author: fhn
 * @date: 4/21
 * @version: 1.0
 * @description: offer the main I/O interfaces for interpreters, in which we would interact with file
 *                  in other words, this is the executing module.
*/

//--------------------------------------------------------------------------------------------

#include "in_out.hpp"
#include <vector>
#include <map>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>// used for piece together the cmd

//--------------------------------------------------------------------------------------------


namespace in_out{

void CreateDatabase(const string& name)
{
    std::string mkdir = "mkdir " + name;
    system(mkdir.c_str());
}


}