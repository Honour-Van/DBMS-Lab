/**
 * @file: in_out.cpp
 * @author: fhn
 * @date: 4/21
 * @description: offer the main I/O interfaces for interpreters, in which we would interact with file
 *                  in other words, this is the executing module.
 * @version: 1.0: interact with txt files.
             v2.0: finished with vector structrue ordered map.
*/

//--------------------------------------------------------------------------------------------

#include "in_out.hpp"
#include <sstream>// in v1.0 used for piece together the cmd
//--------------------------------------------------------------------------------------------


namespace in_out{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::map;
    using std::string;
    using std::vector;
    using std::fstream; 
    using std::ios;

string cur_db; // used for indicating the current database, called in use sentence.
string cur_tb; // used for indicating the current table, if doesn't change, edit directly in cache.

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
std::clog << "ColInfo::PrintInfo() called. column info was put once" << endl;
#endif
    cout << col_num_ << ' ' << 0 << endl; // the second 0 indicates the num of elem (when table is created)
    for (auto it : col_info_)
        cout << it.first << ' ' << it.second << endl;
}

/**
* @author: fhn
* @date: 4/27
* @description: input a string, output the what's the rank of it in col_info. 
                not found: -1.
* @version: v1.0
*/
int ColInfo::FindCol(const string & name)
{
    vector<std::pair<string, int>>::iterator it = cache.col_info_.begin();
    for (auto it = col_info_.begin(); it < col_info_.end(); it++)
    {
        if ((*it).first == name)
            return it - col_info_.begin();
    }
    std::cerr << "col not found" << endl;
    return -1;
}

/**
 * @author: fhn
 * @date: 4/25
 * @description: print the table_info, mainly used in tagged the table store file.
 * @version: 1.0 : simply output the info of table's map.
*/
void Table::PrintInfo() const
{
#ifdef _LOC_
std::clog << "table print once" << endl;
#endif
    cout << col_num_ << ' ' << elem_num_ << endl;
    int cnt = 0;
    for (int i = 0; i < col_num_; i++)
    {
        cout << col_info_[i].first << ' ' << col_info_[i].second << ' ';
#ifdef _LOC_
std::clog << "elem num is " << elem_num_ << "  and before deleting: "<< elem_info_[0].size() << endl;
#endif
        for (int j = 0; j < elem_info_[0].size(); j++)
            if (!isDelete[j])
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
#ifdef _LOC_
std::clog << "a col was added" << endl;
#endif
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
#ifdef _LOC_
std::clog << "the table was initialized" << endl;
#endif
    cin >> col_num_ >> elem_num_;
    string tmp_name; int tmp_length; string tmp_elem;
    
    SetColNum(col_num_);
    isDelete.reserve(elem_num_ * 2);
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
#ifdef _LOC_
std::clog << "column num was set as "<< col_num << endl;
#endif
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
#ifdef _LOC_
std::clog << "vector[" << col_no << "] was added with elem. now  elem_num  is " <<  index_num + 1  << endl;
#endif
    isDelete.push_back(false);
    elem_info_[col_no].push_back(make_pair(elem, index_num));
}

void Table::EraseElem(const int& id)
{
#ifdef _LOC_
std::clog << "the "<< id << "th elem was erased" << endl;
#endif
    if (isDelete[id]) return;
    elem_num_--;
    isDelete[id] = true;
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
    if (cur_db.size() == 0) 
    { std::cerr << "no database in use" << endl; return; }
    string file_path = cur_db + "\\" + name;
    if (exist(file_path))
    { std::cerr << "file already exists" << endl; return;}
    freopen(file_path.c_str(), "w", stdout);
    column_info.PrintInfo();// if we want to remain the const of table_info, we should define the print() as const.
    freopen("CON", "w", stdout);
    cout << "Query OK, 0 rows affected" << endl << endl;
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
    // if (cur_db == name)
    // { std::cerr << "database already in use." << endl;}
    if (!system(tmp.c_str()))//if the folder doesn't exist, system will warns.
    {    
        cur_db = name;
        cur_tb = "";
        cout << "Database changed" << endl;
    }
}

//--------------------------------------------------------------------------------------------
//below are some I/O functions

/**
 * @author: fhn
 * @date: 4/26
 * @description: insert a row into a table.
 * @version: v1.0
 *           v2.0: using redirection technique; rewrite the Table::SetColNum()<else there'll be an segfault.>
 *              to be improved: this function and the ones following needs to deal with unexisted file.
*/
void Insert(string table_name, vector<string> col_name)
{
    if (!cur_db.size())
    { std::cerr << "no database used" << endl; return;}
    string file_path = cur_db + "\\" + table_name;//default
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
        freopen(file_path.c_str(), "r", stdin);
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
        cur_tb = table_name;// renew only when everything is right.
    }
    freopen("CON", "r", stdin);
    cache.SetElemNum(cache.elem_num()+1);
    
    freopen(file_path.c_str(), "w", stdout);
    cache.PrintInfo();
    freopen("CON", "w", stdout);
}

/**
 * @author: fhn
 * @date: 4/27
 * @description: execute Select sentence cmds. 
                in order to simplify the output of charts, we input all the tableinfo once a time.
 * @version: v1.0
 *           v1.1: about rereading: if this is the first time, the read and the unknown elem_num  is compatible
*/
void Select(string table_name, vector<string> item, Clause where)
{
    if (!cur_db.size())
    { std::cerr << "ERROR 1046 (3D000): No database selected" << endl; return; }
    string file_path = cur_db + "\\" + table_name;
    if (cur_tb != table_name)
    {
        freopen(file_path.c_str(), "r", stdin);
        cache.InitRead();
        freopen("CON", "r", stdin); //here we didn't get the stdin back, which caused a bad loops
        cur_tb = table_name;//evething has been put in, then renew;(somehow different from the Insert()): possibly because we need to output once a time
    }

    //select columns to be put
    vector<int> item_col(cache.col_num()); int tmp, sel_cnt = 0;

#ifdef _LOC_
std::clog << item[0] << endl;
#endif

    if (item[0] == "*") 
        for (int i = 0; i < cache.col_num(); i++) item_col[i] = i, sel_cnt++; 
    else for (int i = 0; i < item.size(); i++)
        {
            tmp = cache.FindCol(item[i]);
            if (tmp != -1)
                item_col[i] = tmp, sel_cnt++;
        }
#ifdef _LOC_
if (item[0] ==  "*")
    for (int i = 0; i < item_col.size(); i++)
        cout << "item_col[" << i  << "] = " << item_col[i]<< endl; 
std::clog << sel_cnt << " col(s) selected" << endl;
#endif
    vector<int> col_len(sel_cnt);
    for (int i = 0; i < sel_cnt; i++)
    {
        int tmp = cache.col_info_[item_col[i]].second;
        if (tmp) col_len[i] = tmp;
        else col_len[i] = 10;
    }

    //select rows to be put
    if (!where.op.size()) // no more rules
    {
        PrintHead(col_len, item_col);
        for (int i = 0; i < cache.elem_num(); i++)
            PrintLine(col_len, item_col, i);
        PrintTail(col_len);
    }
    else if (where.op.size())// where branch
    {    
        int col_base, hasnt = 1;
        col_base = cache.FindCol(where.name); 
        if (col_base == -1)  { std::cerr << "Invalid name in where clause." << endl; return; } //assignment and judge......
        for (auto it : where.value)
            if (!isalnum(it))
                { std::cerr << "Invalid value in where clause." << endl; return; }

        if (where.op == "=")
        {
            for (auto it : cache.elem_info_[col_base])
                if (it.first == where.value)
                {
                    if (hasnt)
                        PrintHead(col_len, item_col);
                    PrintLine(col_len, item_col, it.second);
                    hasnt = 0;
                }
            if (!hasnt) PrintTail(col_len);
        }
        else if (where.op == ">")
        {
            for (auto it : cache.elem_info_[col_base])
                if (it.first > where.value)
                {
                    if (hasnt)
                        PrintHead(col_len, item_col);
                    PrintLine(col_len, item_col, it.second);
                    hasnt = 0;
                }
            if (!hasnt) PrintTail(col_len);
        }
        else if (where.op == ">=")
        {
            for (auto it : cache.elem_info_[col_base])
                if (it.first >= where.value)
                {
                    if (hasnt)
                        PrintHead(col_len, item_col);
                    PrintLine(col_len, item_col, it.second);
                    hasnt = 0;
                }
            if (!hasnt) PrintTail(col_len);
        }
        else if (where.op == "<")
        {
            for (auto it : cache.elem_info_[col_base])
                if (it.first < where.value)
                {
                    if (hasnt)
                        PrintHead(col_len, item_col);
                    PrintLine(col_len, item_col, it.second);
                    hasnt = 0;
                }
            if (!hasnt) PrintTail(col_len);
        }
        else if (where.op == "<=")
        {
            for (auto it : cache.elem_info_[col_base])
                if (it.first <= where.value)
                {
                    if (hasnt)
                        PrintHead(col_len, item_col);
                    PrintLine(col_len, item_col, it.second);
                    hasnt = 0;
                }
            if (!hasnt) PrintTail(col_len);
        }
        else if (where.op == "!=")
        {
            for (auto it : cache.elem_info_[col_base])
                if (it.first != where.value)
                {
                    if (hasnt)
                        PrintHead(col_len, item_col);
                    PrintLine(col_len, item_col, it.second);
                    hasnt = 0;
                }
            if (!hasnt) PrintTail(col_len);
        }
        else
            std::cerr << "unknown where operator type when Select()" << endl;
    }
    else std::cerr << "select wrong in both modes" << endl;
}

/**
 * @author: fhn
 * @date: 5/4
 * @description:  print the upper chart line of a table and the gauge outfit.
 * @version: 
*/
void PrintHead(vector<int> col_len, vector<int> item_col)
{
    cout << " ┌";
    for (int i = 0; i < col_len.size(); i++)
    {
        for (int j = 0; j < col_len[i]; j++) cout << "─";
        if (i < col_len.size() - 1)
            cout << "┬";
        else cout << "┐";
    }
    cout << endl;

    cout << " │";
    for (int i = 0; i < col_len.size(); i++)
    {
        int tmp = col_len[i]-cache.col_info_[item_col[i]].first.size();
        for (int j = 0; j < tmp/2; j++) cout << ' ';
        if (tmp%2) cout << ' ';
        cout << cache.col_info_[item_col[i]].first;
        for (int j = 0; j < tmp/2; j++) cout << ' ';
        cout << "│";
    }
    cout << endl;
}

/**
 * @author: fhn
 * @date: 5/4
 * @description: in select(), print the body info of table. upper chart line and a row of info
 * @version:  v2.0 : 
*/
void PrintLine(vector<int> col_len, vector<int> item_col, int row_index)
{
    cout << " ├";
    for (int i = 0; i < col_len.size(); i++)
    {
        for (int j = 0; j < col_len[i]; j++) cout << "─";
        if (i < col_len.size() - 1)
             cout << "┼";
        else cout << "┤";
    }
    cout << endl;

    cout << " │";
    for (int i = 0; i < col_len.size(); i++)
    {
        int tmp = col_len[i]-(cache.GetElem(item_col[i], row_index)).first.size();
        for (int j = 0; j < tmp/2; j++) cout << ' ';
        if (tmp%2) cout << ' ';
        cout << cache.GetElem(item_col[i], row_index).first;
        for (int j = 0; j < tmp/2; j++) cout << ' ';
        cout << "│";
    }
    cout << endl;
}

void PrintTail(vector<int> col_len)
{
    cout << " └";
    for (int i = 0; i < col_len.size(); i++)
    {
        for (int j = 0; j < col_len[i]; j++) cout << "─";
        if (i < col_len.size() - 1)
            cout << "┴";
        else cout << "┘";
    }
    cout << endl;
}

//--------------------------------------------------------------------------------------------

void Update(string table_name, string col_name, string newvalue, Clause where)
{
    if (!cur_db.size())
    { std::cerr << "ERROR 1046 (3D000): No database selected" << endl; return; }
    string file_path = cur_db + "\\" + table_name;
    if (cur_tb != table_name)
    {
        freopen(file_path.c_str(), "r", stdin);
        cache.InitRead();
        freopen("CON", "r", stdin);
        cur_tb = table_name;
    }

    int nc = cache.FindCol(col_name);
    if (nc == -1)  
    { std::cerr << "col to update invalid" << endl; return;}
    
    int bc = cache.FindCol(where.name);
    if (bc == -1) { std::cerr << "col to judge (update) invalid " << endl; return; }

    if (where.op == "=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first == where.value)
                cache.SetElem(nc, it.second, newvalue);
    }
    else if (where.op == ">")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first > where.value)
                cache.SetElem(nc, it.second, newvalue);
    }
    else if (where.op == ">=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first >= where.value)
                cache.SetElem(nc, it.second, newvalue);
    }
    else if (where.op == "<")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first < where.value)
                cache.SetElem(nc, it.second, newvalue);
    }
    else if (where.op == "<=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first <= where.value)
                cache.SetElem(nc, it.second, newvalue);
    }
    else if (where.op == "!=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first != where.value)
                cache.SetElem(nc, it.second, newvalue);
    }
    else std::cerr << "unknown where type in Update()" << endl;

    freopen(file_path.c_str(), "w", stdout);
    cache.PrintInfo();
    freopen("CON", "w", stdout);
}
void Delete(string table_name, Clause where)
{
    if (!cur_db.size())
    { std::cerr << "ERROR 1046 (3D000): No database selected" << endl; return; }
    string file_path = cur_db + "\\" + table_name;
    if (cur_tb != table_name)
    {
        freopen(file_path.c_str(), "r", stdin);
        cache.InitRead();
        freopen("CON", "r", stdin);
        cur_tb = table_name;
    }

    int bc = cache.FindCol(where.name);
    if (bc == -1) { std::cerr << "col to judge (delete) invalid " << endl; return; }

    if (where.op == "=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first == where.value)
                cache.EraseElem(it.second);
    }
    else if (where.op == ">")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first > where.value)
                cache.EraseElem(it.second);
    }
    else if (where.op == ">=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first >= where.value)
                cache.EraseElem(it.second);
    }
    else if (where.op == "<")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first < where.value)
                cache.EraseElem(it.second);
    }
    else if (where.op == "<=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first <= where.value)
                cache.EraseElem(it.second);
    }
    else if (where.op == "!=")
    {
        for (auto it : cache.elem_info_[bc])
            if (it.first != where.value)
                cache.EraseElem(it.second);
    }
    freopen(file_path.c_str(), "w", stdout);
    cache.PrintInfo();
    freopen("CON", "w", stdout);
}

}