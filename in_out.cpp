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
    error("col not found");
    return -1;
}

/**
 * @author: fhn
 * @date: 4/25
 * @description: print the table_info, mainly used in tagged the table store file.
 * @version: 1.0 : simply output the info of table's map.
 *           v2.0: deal with much trouble with the output range(DON'T TRUST VECTOR SIZE AS THE RANGE!!!) and the tmp watch is very significant
*/
void Table::PrintInfo() const
{
#ifdef _LOC_
std::clog << "table print once" << endl;
#endif
    cout << col_num_ << ' ' << elem_num_ << endl;
    for (int i = 0; i < col_num_; i++)
    {
        cout << col_info_[i].first << ' ' << col_info_[i].second << ' ';
#ifdef _LOC_
std::clog << "elem num is " << elem_num_ << "  and before deleting: "<< elem_info_[0].size() << endl;
#endif
        // int tmp = elem_num() < elem_info_[0].size() ? elem_num() : elem_info_[0].size();
        // after deleting, use the elem_info[0], if insert is haulting, use elem_num; vector size is quite dangerous, use elem_num is somehow 
        int tmp = elem_num();
#ifdef _TEST4_//the rang is very strange, so we spent lots of time on it.
std::clog << "print info: " << tmp << endl;
int dcnt = 0;
for (int i = 0; i < isDelete.size(); i++)
    if (isDelete[i])
        std::clog << "isDelete[" << i << "] is true; " << endl;
#endif
#ifdef _TEST5_//the rang is very strange, so we spent lots of time on it.
std::clog << "print info: " << tmp << endl;
#endif

        for (int j = 0; j < tmp; j++)
            if (!isDelete[j])
            {
                cout << elem_info_[i][j].first << ' ';
#ifdef _TEST5_
std::clog << "print info: " << tmp << endl;
#endif
            }
            // else if (j == 0) tmp++;
            else tmp++;
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
    // for (auto it: elem_info_)
    //     while (!it.empty())
    //         it.pop_back();
#ifdef _LOC_
std::clog << "the table was initialized" << endl;
#endif
    cin >> col_num_ >> elem_num_;
    Break();
    string tmp_name; int tmp_length; string tmp_elem;
    
    SetColNum(col_num_);
    isDelete.resize(elem_num_ * 2);
    for (int i = 0; i < col_num_; i++)
    {
        cin >> tmp_name >> tmp_length;
#ifdef _TEST5_
std::clog << cin.eof() << " " << cin.bad() << " " << cin.fail() << std::endl;
#endif
        Break();
        col_info_[i].first = tmp_name;
        col_info_[i].second = tmp_length;
        elem_info_[i].resize(elem_num());
        for (int j = 0; j < elem_num_; j++)
        {
            cin >> tmp_elem;
            Break();
            elem_info_[i][j].first = tmp_elem;
            elem_info_[i][j].second = j;
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

void Table::SetElemNum(const int elem_num)
{ 
    elem_num_ = elem_num; 
    for (auto it: elem_info_)
        it.reserve(elem_num*2), it.resize(elem_num); 
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
#ifdef _TEST5_
std::clog << "vector[" << col_no << "] was added with " << elem << ". now  elem_num  is " <<  index_num + 1  << endl;
#endif
}

void Table::EraseElem(const int& id)
{
#ifdef _TEST5_
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
    if (!system(mkdir.c_str()))
    { 
        cout << "Query OK, 1 row affected ";
        time_cnt::end();
        cout << endl;
    }
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
    { error("No database selected"); return; }
    string file_path = cur_db + "\\" + name;
    if (exist(file_path))
    { error("file already exists"); return;}
    freopen(file_path.c_str(), "w", stdout);
    column_info.PrintInfo();// if we want to remain the const of table_info, we should define the print() as const.
    freopen("CON", "w", stdout);
    cout << "Query OK, 0 rows affected ";
    time_cnt::end();
    cout << endl;
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
    if (!system(tmp.c_str()))//if the folder doesn't exist, system will warns.
    {    
        cur_db = name;
        cur_tb = "";
        cout << "Database changed" << endl;
    }
}

//--------------------------------------------------------------------------------------------
//below are some I/O functions

bool trim(string & str)
{
    int pos1 = str.find_first_of("\""), pos2 = str.find_first_of("\'");
    if (pos1 == string::npos && pos2 == string::npos)
        return false;
    else if (pos1 != string::npos && pos2 != string::npos)
        return false;
    else if (pos1 != string::npos && pos1 == 0)
    {
        //erase the first and last "
        str.erase(pos1, 1);
        pos1 = str.find_first_of("\"");
        if (pos1 != string::npos && pos1 == str.size()-1)
            str.erase(pos1, 1);
        else return false;
        
        //to see if there other non-alnum chars
        for (auto it : str)
            if (!isalnum(it))
                return false;
    }
    else if (pos2 != string ::npos && pos2 == 0)
    {
        //erase the first and last "
        str.erase(pos2, 1);
        pos2 = str.find_last_of("\'");
        if (pos2 != string::npos && pos2 == str.size()-1)
            str.erase(pos2, 1);
        else return false;

        //to see if there other non-alnum chars
        for (auto it : str)
            if (!isalnum(it))
                return false;
    }
    return true;
}

/**
 * @author: fhn
 * @date: 5/7
 * @description: if there is something wrong in the in_out::Insert(), if the quotation mark is wrong
 * @version: v1.0
*/
void Table::ClearError(int row_num, int err_col)
{
    for (int i = 0; i < err_col; i++)
        elem_info_[i].erase(elem_info_[i].begin()+row_num);
}

#ifdef _TEST5_
void WATCH()
{
    for (int i = 0; i < cache.elem_info_.size(); i++)
    {
        for(int j = 0; j < cache.elem_info_[i].size(); j++)
            std::clog << cache.elem_info_[i][j].first << ' ';
        cout << std::endl;
    }
}
#endif

/**
 * @author: fhn
 * @date: 4/26
 * @description: insert a row into a table.
 * @version: v1.0
 *           v2.0: using redirection technique; rewrite the Table::SetColNum()<else there'll be an segfault.>
 *              to be improved: this function and the ones following needs to deal with unexisted file.
 *           v3.0: improve the file-exist problem；
 *                  high robustness with string and its quotaion mark.
 *                  need to remember: DO NOT TRY TO SPAN 'freopen()' SCOPE TOO LONG.
*/
void Insert(string table_name, vector<string> col_name)
{
    if (!cur_db.size())
    { error("no database used"); return;}
    string file_path = cur_db + "\\" + table_name;//default
    if (!exist(file_path))
    { error("table ", table_name, " doesn't exists"); return; }

    if (cur_tb == table_name) // to use cache to just insert into cache
    {
        cache.SetColNum(cache.col_num());
        if (cache.col_num() != col_name.size())
        { error("in insert: param num not fit"); cur_tb = ""; return;}
        for (int n_col = 0; n_col < cache.col_num(); n_col++)
        {
            if (cache.col_len(n_col) && !trim(col_name[n_col]))
            { 
                error("insert syntax wrong: varchar to be inserted illegal"); 
                cur_tb = ""; cache.ClearError(cache.elem_num()+1, n_col);
                return;
            }//if returns in these two interfaces, we must clear the polluted data.
            if (cache.col_len(n_col) && col_name[n_col].size() > cache.col_len(n_col))
            { 
                error("Elem to be inserted illegal: too long"); 
                cur_tb = ""; cache.ClearError(cache.elem_num()+1, n_col);
                return;
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
            
            cache.col_info_[n_col].first = tmp_name;//don't try to use add col: just here, for the cache needs to be cleared.
            cache.col_info_[n_col].second = tmp_length;
            for (int j = 0; j < cache.elem_num(); j++)
            {
                cin >> tmp_elem;
                cache.SetElem(n_col, j, tmp_elem);
            }
            string c = col_name[n_col];
            if (cache.col_len(n_col))// if this colomn's type is varchar
                if (!trim(c))
                { 
                    error("insert syntax wrong: varchar to be inserted illegal");
                    freopen("CON", "r", stdin); 
                    cache.ClearError(cache.elem_num()+1, n_col);
                    return;
                }
            if (tmp_length && col_name[n_col].size() > tmp_length)
            { 
                error("Elem to be inserted illegal: too long"); 
                freopen("CON", "r", stdin); cur_tb = ""; 
                cache.ClearError(cache.elem_num()+1, n_col);
                return; 
            }//if returns here, the data which has been inserted was deprecated. for the elem_num_ remain unchanged.
            cache.elem_info_[n_col].resize(cache.elem_num()+1);
            cache.elem_info_[n_col][cache.elem_num()].first = c;
        }
        cur_tb = table_name;// renew only when everything is right.
    }
    freopen("CON", "r", stdin);
    cache.SetElemNum(cache.elem_num()+1);
    
    freopen(file_path.c_str(), "w", stdout);
    cache.PrintInfo();
    freopen("CON", "w", stdout);
    cout << "Query OK, 1 row affected ";
    time_cnt::end(); cout << endl;
#ifdef _TEST5_
    WATCH();
#endif
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
    { error("1046 (3D000): No database selected"); return; }
    string file_path = cur_db + "\\" + table_name;
    if (!exist(file_path))
    { error("table ", table_name, " doesn't exists"); return; }
#ifdef _TEST4_
std::clog << "current table name is " << cur_tb << endl;
#endif
    if (cur_tb != table_name)
    {
        freopen(file_path.c_str(), "r", stdin);
        cache.InitRead();
        freopen("CON", "r", stdin); //here we didn't get the stdin back, which caused a bad loops
        cur_tb = table_name;//evething has been put in, then renew;(somehow different from the Insert()): possibly because we need to output once a time
    }
#ifdef _LOC_
std::clog << "current table name is " << cur_tb << endl;
#endif
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
    if (sel_cnt == 0)
    {
        cout << "empty set" << endl;
        return;
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
        if (!cache.col_info_[item_col[i]].second) 
            col_len[i] = 10;
        else col_len[i] = (cache.col_info_[item_col[i]].first.size() > cache.col_info_[item_col[i]].second
                        ?  cache.col_info_[item_col[i]].first.size() : cache.col_info_[item_col[i]].second) + 1;
    }

    //select rows to be put
    if (!where.op.size()) // no more rules
    {
        PrintHead(col_len, item_col);
        for (int i = 0; i < cache.elem_num(); i++)
            PrintLine(col_len, item_col, i);
        PrintTail(col_len);
        if (cache.elem_num()) 
            cout << cache.elem_num() << " rows in set ";
        else cout << "empty set "; 
        time_cnt::end();
        cout << endl;
    }
    else if (where.op.size())// where branch
    {    
        int col_base, hasnt = 1;
        col_base = cache.FindCol(where.name); 
        if (col_base == -1)  { error("Invalid name in where clause."); return; } //assignment and judge......
        if (cache.col_len(col_base) && !trim(where.value))
        { error("in Select(): where varchar value wrong"); return; }

        for (auto it : where.value)
            if (!isalnum(it))
                { error("Invalid value in where clause."); return; }

        bool (*p)(const string&, const string&);//choose the right mode to act as the cmp function
        
        if (where.op == "=")
            p = equal_to;
        else if (where.op == ">")
            p = greater;
        else if (where.op == ">=")
            p = greater_equal;
        else if (where.op == "<")
            p = less;
        else if (where.op == "<=")
            p = less_equal;
        else if (where.op == "!=")
            p = not_equal_to;
        else
            error("unknown where operator type when Select()");

        int row_cnt = 0;
        for (auto it : cache.elem_info_[col_base])
            if (p(it.first, where.value))
            {
                if (hasnt)
                    PrintHead(col_len, item_col);
                PrintLine(col_len, item_col, it.second);
                row_cnt++;
                hasnt = 0;
            }
        if (hasnt) 
            cout << "Empty set ";
        else 
        {
            PrintTail(col_len);
            cout << row_cnt << "row(s) in set ";
        }
        time_cnt::end(); cout << endl;
    }
    else error("select wrong in both modes");
#ifdef _TEST5_
    WATCH();
#endif
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
 *            v2.1: add the quotation mark of varchar
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
        if (cache.col_len(item_col[i]))// if it's varchar
            tmp -= 2;
        for (int j = 0; j < tmp/2; j++) cout << ' ';
        if (tmp%2) cout << ' ';
        if (cache.col_len(item_col[i]))// if it's varchar
            cout << '\"' << cache.GetElem(item_col[i], row_index).first << '\"';
        else cout << cache.GetElem(item_col[i], row_index).first;
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
    { error("1046 (3D000): No database selected"); return; }
    string file_path = cur_db + "\\" + table_name;
    if (!exist(file_path))
    { error("in Update(): Table ", table_name, " doesn't exists"); return; }

    if (cur_tb != table_name)
    {
        freopen(file_path.c_str(), "r", stdin);
        cache.InitRead();
        freopen("CON", "r", stdin);
        cur_tb = table_name;
    }
#ifdef _TEST4_
cout << "in update: " << "table_name: " << table_name << "cur_tb: " << cur_tb << endl;
#endif
    int nc = cache.FindCol(col_name);
    if (nc == -1)  
    { error("in Update(): col to update invalid"); return;}
    if (cache.col_len(nc) && !trim(newvalue))
    { error("#ERROR in Update(): varchar newvalue wrong"); return; }
    
    int bc = cache.FindCol(where.name);
    if (bc == -1) { error("#ERROR: col to judge (update) invalid "); return; }
    if (cache.col_len(bc) && !trim(where.value))
    { error("in Update()'s where clause: varchar value wrong"); return; }

    bool (*p)(const string&, const string&);
        
    if (where.op == "=")
        p = equal_to;
    else if (where.op == ">")
        p = greater;
    else if (where.op == ">=")
        p = greater_equal;
    else if (where.op == "<")
        p = less;
    else if (where.op == "<=")
        p = less_equal;
    else if (where.op == "!=")
        p = not_equal_to;
    else
        error("unknown where operator type when Select()");

    int row_cnt = 0;
    for (auto it : cache.elem_info_[bc])
            if (p(it.first, where.value))
                if (cache.GetElem(nc, it.second).first != newvalue)
                    cache.SetElem(nc, it.second, newvalue), row_cnt++;


    freopen(file_path.c_str(), "w", stdout);
    cache.PrintInfo();
    freopen("CON", "w", stdout);
    
    cout << "Query OK, " << row_cnt << " rows affected ";
    time_cnt::end();
    //TimeCount();
    cout << endl;
    cout << "Rows matched: " << row_cnt << "  Changed: 0  Warnings: 0 ";
    cout << endl << endl;
}

/**
 * @author: fhn
 * @date: 5/6
 * @description: executing the deleting action
 * @version: v3.0
*/
void Delete(string table_name, Clause where)
{
    if (!cur_db.size())
    { error("1046 (3D000): No database selected"); return; }
    string file_path = cur_db + "\\" + table_name;
    if (!exist(file_path))
    { error("table ", table_name, " doesn't exists"); return; }
#ifdef _TEST4_
cout << "in delete: " << "table_name: " << table_name << " cur_tb: " << cur_tb << endl;
#endif

    if (cur_tb != table_name)
    {
        freopen(file_path.c_str(), "r", stdin);
        cache.InitRead();
        freopen("CON", "r", stdin);
        // cur_tb = table_name;//unnecessary daylight
    }

    int bc = cache.FindCol(where.name);
    if (bc == -1) { error("in Delete(): col to judge (delete) invalid "); return; }
    if (cache.col_len(bc) && !trim(where.value))
    { error("in Delete()'s where: varchar value wrong"); return; }


    bool (*p)(const string&, const string&);
    if (where.op == "=")
        p = equal_to;
    else if (where.op == ">")
        p = greater;
    else if (where.op == ">=")
        p = greater_equal;
    else if (where.op == "<")
        p = less;
    else if (where.op == "<=")
        p = less_equal;
    else if (where.op == "!=")
        p = not_equal_to;
    else
        error("unknown where operator type when Select()");
    
    int row_cnt = 0;
    for (auto it : cache.elem_info_[bc])
            if (p(it.first,where.value))
                cache.EraseElem(it.second), row_cnt++;

    freopen(file_path.c_str(), "w", stdout);
    cache.PrintInfo();
    freopen("CON", "w", stdout);

    cur_tb = "";//because the elem in cache is quite different from that in the file, we'd better do this.
    for (auto it : cache.isDelete)
        it = false;

    cout << "Query OK, " << row_cnt << " rows affected ";
    time_cnt::end(); cout << endl;
}

}