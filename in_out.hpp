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
#include <utility>
#include <algorithm>
#include "interpreter.hpp"
#include "exception.hpp"
#include "time_cnt.hpp"

//--------------------------------------------------------------------------------------------

#ifndef CLAUSEGUARD
#define CLAUSEGUARD
struct Clause
{
    std::string name;
    std::string op;
    std::string value;
    Clause(std::string a, std::string b, std::string c) :name(a), op(b), value(c){ }; 
    Clause() : name(), op(), value(){ }
};
#endif
namespace in_out{
using std::string;
/**
 * @author: fhn
 * @date: 4/27
 * @description: a table of column's info; using a vector acting as ordered map;
 * @version: v2.0
*/
class ColInfo
{
protected:
    int col_num_;
public:
    //ordered pairs:    first is the length of col_name, indicating the type of col_name; second is the name is the col_name
    std::vector<std::pair<string, int>> col_info_;
    ColInfo() : col_num_(), col_info_() { }
    void AddCol(string, int, bool mode = 1);
    int col_num() const { return col_num_; }
    int col_len(int col) const { return col_info_[col].second; }
    int FindCol(const string&); //O(n)
    virtual void SetColNum(int col_num) { col_num_ = col_num; col_info_.resize(col_num);}
    virtual void PrintInfo() const;
};

/**
 * @author: fhn
 * @date: 4/27
 * @description: a table of all data; using a vector acting as ordered map;
 * @version: v2.0
*/
class Table : public ColInfo
{
private:
    int elem_num_;
    std::vector<bool> isDelete;
    std::vector<std::vector<std::pair<string,int>>> elem_info_; // used to store the data temporarily. the ordered 'map' guarantee the finding cost is O(n): a traversal cost. first dimension is column, second is id within vector, key is elem, value is index.
public:
    Table() : ColInfo(), elem_num_(0) { }
    int elem_num() const { return elem_num_; }
    
    inline void AddElem(int, int, string);
    std::pair<string, int> GetElem(int col, int row)const { return elem_info_[col][row]; }
    
    void SetElem(int col, int row, string newval) { elem_info_[col][row].first = newval; }
    void SetElemNum(const int elem_num);
    void SetColNum (const int col_num );
    void EraseElem(const int& id);
    void ClearError(int, int);

    void InitRead();
    void PrintInfo() const;
    
    friend void Insert(string, std::vector<string>);
    friend void Select(string, std::vector<string>, Clause);
    friend void Update(string table_name, string col_name, string newvalue, Clause);
    friend void Delete(string table_name, Clause);
#ifdef _TEST5_
    friend void WATCH();
#endif
};

bool trim(string &);

void CreateDatabase(const string& name);
void CreateTable(const string& name, const ColInfo&);
void Use(string);
void Insert(string, std::vector<string>);

void PrintHead(std::vector<int> col_len, std::vector<int> item_col);
void PrintLine(std::vector<int> col_len, std::vector<int> item_col, int row_index);
void PrintTail(std::vector<int> col_len);

void Select(string, std::vector<string>, Clause);
void Update(string table_name, string col_name, string newvalue, Clause);
void Delete(string table_name, Clause);

inline bool equal_to       (const string& a, const string& b) { return a == b; }
inline bool not_equal_to   (const string& a, const string& b) { return a != b; }
inline bool greater        (const string& a, const string& b) { return a > b; }
inline bool less           (const string& a, const string& b) { return a < b; }
inline bool greater_equal  (const string& a, const string& b) { return a >= b; }
inline bool less_equal     (const string& a, const string& b) { return a <= b; }

}

#endif