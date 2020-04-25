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
#include "interpreter.hpp"

//--------------------------------------------------------------------------------------------

namespace in_out{
using std::string;

struct Table
{
    Table() : col_num(0) { }
    int col_num;
    std::map<string, int> info_;//first is the length of col_name, indicating the type of col_name; 
                                //second is the name is the col_name
    void add(string s, int i) { info_.insert(make_pair(s, i)); col_num++;}
    void print() const;
};


void CreateDatabase(const string& name);
void CreateTable(const string& name, const in_out::Table&);
void Use(string src);
void Insert(string, std::vector<string>);

void Select(string, std::vector<string>, sql_itp::Clause);
void Update(string table_name, string col_name, sql_itp::Clause);
void Delete(string table_name, sql_itp::Clause);

}

#endif
