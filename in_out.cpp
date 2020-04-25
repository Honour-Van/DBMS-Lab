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
using std::cin, std::cout, std::endl, std::string, std::vector;
string cur_db; //used for indicating the current database, called in use sentence.
// vector<std::map<int, string>> cache; // used to store the data temporarily.

void Table::print() const
{
    cout << col_num << endl;
    for (auto it : info_)
        cout << it.first << ' ' << it.second << endl;
}

void CreateDatabase(const string& name)
{
    string mkdir = "mkdir " + name;
    system(mkdir.c_str());
}

void CreateTable(const string& name, const in_out::Table& table_info)
{
    std::ofstream fout(name.c_str(), std::ios::out | std::ios::app);
    table_info.print();// if we want to remain the const of table_info, we should define the print() as const.
    
}

void Use(string src);
void Insert(string, std::vector<string>);

void Select(string, std::vector<string>, sql_itp::Clause);
void Update(string table_name, string col_name, sql_itp::Clause);
void Delete(string table_name, sql_itp::Clause);

}