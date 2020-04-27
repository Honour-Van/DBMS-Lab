/**
 * @file: in_out.cpp
 * @author: fhn
 * @date: 4/21
 * @description: offer the main I/O interfaces for interpreters, in which we would interact with file
 *                  in other words, this is the executing module.
 * @version: 1.0: interact with txt files.
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
using std::cin, std::cout, std::endl;
using std::map, std::string, std::vector;
using std::fstream, std::ios;

string cur_db; // used for indicating the current database, called in use sentence.
string cur_tb; // used for indicating the current table, if doesn't change, edit in cache.

Table cache;

/**
 * @author: fhn
 * @date: 4/27
 * @description: (virtual) output function
 * @version: 
*/
void ColInfo::PrintInfo() const
{
#ifdef _LOC_
clog << "ColInfo::PrintIno() called." << endl;
#endif
    cout << col_num_ << ' ' << 0 << endl; // the second 0 indicates the num of elem (when table is created)
    for (auto it : col_info_)
        cout << it.first << ' ' << it.second << endl;
}

/**
 * @author: fhn
 * @date: 4/25
 * @description: print the table_info, mainly used in tagged the table store file.
 * @version: 1.0 : simply output the info of table's map.
*/
void Table::PrintInfo() const
{
    cout << col_num_ << ' ' << elem_num_ << endl;
    int cnt = 0;
    for (int i = 0; i < col_num_; i++)
    {
        cout << col_info_[i].first << ' ' << col_info_[i].second << ' ';
        for (int j = 0; j < elem_num_; j++)
            cout << elem_info_[i][j].first << ' ';
        cout << endl;
    }
}

/**
 * @author: fhn
 * @date: 4/26
 * @description: push a pair of elem into the vector of col_info_; 
 *              mode for InitRead(); mode 1 default: col_num plus; mode 0 alter: num unchanged.
 * @version: v1.0
*/
void ColInfo::AddCol(string s, int i, bool mode)
{ 
    col_info_.push_back(make_pair(s, i));
    if (mode) 
        col_num_++;
}

/**
 * @author: fhn
 * @date: 4/26
 * @description: read information about a table from a file
 * @version: v1.0; without judgeing if an elem is illegal(because the inserted data is legal)
*/
void Table::InitRead()
{
    cin >> col_num_ >> elem_num_;
    string tmp_name; int tmp_length; string tmp_elem;
    
    for (int i = 0; i < col_num_; i++)
    {
        cin >> tmp_name >> tmp_length;
        AddCol(tmp_name, tmp_length, 0);
        for (int j = 0; j < elem_num_; j++)
        {
            cin >> tmp_elem;
            elem_info_[i].push_back(make_pair(tmp_elem, j));
        }
    }
}

/**
 * @author: fhn
 * @date: 4/27
 * @description: set table's colnum, override ColInfo::SetColNum(); more : dealing the elem_info_
 * @version: v2.0
*/
void Table::SetColNum(const int col_num)
{
    ColInfo::SetColNum(col_num); 
    elem_info_.resize(col_num);
}

/**
 * @author: fhn
 * @date: 4/27
 * @description: push a pair with its index_num to 
 * @version: v2.0: add pair into the 2D vector
*/
void Table::AddElem(int col_no, int index_num, string elem)
{
    elem_info_[col_no].push_back(make_pair(elem, index_num));
}

/**
 * @author: fhn
 * @date: 4/26
 * @description: create database using the name received.
 *               if failed, error by DOS cmd.
 * @version: 1.0
*/
void CreateDatabase(const string& name)
{
    string mkdir = "mkdir " + name;
    system(mkdir.c_str());
}

/**
 * @author: fhn
 * @date: 4/27
 * @description: create a table, and input basic info of it.
 * @version: v2.0: using redirection technique.
*/
void CreateTable(const string& name, const ColInfo& column_info)
{
    freopen(name.c_str(), "w", stdout);
    column_info.PrintInfo();// if we want to remain the const of table_info, we should define the print() as const.
    freopen("CON", "w", stdout);
}

/**
 * @author: fhn
 * @date: 4/26
 * @description: change the cur_db, 
 * @version: 1.0
*/
void Use(string name)
{
    string tmp = "cd " + name;
    if (!system(tmp.c_str()))
        cur_db = name;
}

//--------------------------------------------------------------------------------------------
//below are some I/O functions

/**
 * @author: fhn
 * @date: 4/26
 * @description: insert a row into a table.
 * @version: v1.0
 *           v2.0: using redirection technique; rewrite the Table::SetColNum()<else there'll be an segfault.>
*/
void Insert(string table_name, vector<string> col_name)
{
    string tmp = cur_db + "\\" + table_name;//default
    if (cur_tb == table_name) // to use cache to just insert into cache
    {
        cache.SetColNum(cache.col_num());
        for (int n_col = 0; n_col < cache.col_num(); n_col++)
        {
            if (cache.col_len(n_col) && col_name[n_col].size() > cache.col_len(n_col))
            {
                std::cerr  << "Elem to be inserted illegal." << endl; 
                freopen("CON", "r", stdin); return; 
            }//if returns here, the data which has been inserted was deprecated. for the elem_num_ remain unchanged.
            cache.AddElem(n_col, cache.elem_num(), col_name[n_col]);
        }
    }
    else {
        freopen(tmp.c_str(), "r", stdin);

        int tmp_num;
        cin >> tmp_num; cache.SetColNum (tmp_num);
        cin >> tmp_num; cache.SetElemNum(tmp_num);
        
        string tmp_name; int tmp_length; string tmp_elem;
        for (int n_col = 0; n_col < cache.col_num(); n_col++)
        {
            cin >> tmp_name >> tmp_length;
            if (tmp_length && col_name[n_col].size() > tmp_length)
            { 
                std::cerr  << "Elem to be inserted illegal." << endl; 
                freopen("CON", "r", stdin); return; 
            }//if returns here, the data which has been inserted was deprecated. for the elem_num_ remain unchanged.
            
            cache.AddCol(tmp_name, tmp_length, false);
            for (int j = 0; j < cache.elem_num(); j++)
            {
                cin >> tmp_elem;
                cache.AddElem(n_col, j, tmp_elem);
            }
            string c = col_name[n_col];
            cache.AddElem(n_col, cache.elem_num(), c);
        }
    }
    freopen("CON", "r", stdin);
    cache.SetElemNum(cache.elem_num()+1);
    freopen("dbms\\dbms1", "w", stdout);
    cache.PrintInfo();
}

void Select(string, vector<string>, sql_itp::Clause);
void Update(string table_name, string col_name, sql_itp::Clause);
void Delete(string table_name, sql_itp::Clause);

}