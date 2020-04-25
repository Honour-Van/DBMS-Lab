/**
* @file: in_out.hpp
* @author: fhn
* @date: 4/20
* @version: 1.0
* @description: act as the main I/O module.
                responsible for inputting commands, 
                calling corresponding interpreter to get the targeted db/table name
*/

//--------------------------------------------------------------------------------------------

#ifndef INOUT_GUARD
#define INOUT_GUARD

//--------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <map>

//--------------------------------------------------------------------------------------------

namespace in_out{
using std::string;

string cur_db; //used for indicating the current database, called in use sentence.
std::vector<std::map<int, string>> cache; // used to store the data temporarily.
struct Table
{
    Table() : col_num(0) { }
    int col_num;
    std::map<int, string> info_;
    void add(int i, string s) { info_.insert(make_pair(i, s)); col_num++;}
};


void CreateDatabase(const string& name);
void CreateTable(const string& name, in_out::Table);
void Use(string src);
void Insert(string, std::vector<string>);

void Select(string, std::vector<string>, sql_itp::Clause);
void Update(string table_name, string col_name, sql_itp::Clause);
void Delete(string table_name, sql_itp::Clause);

}

#endif
