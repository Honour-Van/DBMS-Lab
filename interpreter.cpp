/**
* @file: interpreter.cpp
* @author: fhn
* @date: 4/20
* @version: 1.0 to be improved: 
                better the strings' formattting(we need to carry out this rules in differeent because the sentence we're faced with truly has different models), when dealing with the strings containing commas and spaces
                where there is spaces and commas, there truly is something to improve. in 1.0, we just need to consider all the syntax is followed well.
            1.2 (4/25) better in formatting string (with commas and spaces in them with function trim())
                to be improved: improve the function trim, e.g. use ss as its param, with more encapsulation.
* @description: interpreters of different sentences.
*/

//--------------------------------------------------------------------------------------------

#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include "interpreter.hpp"

//--------------------------------------------------------------------------------------------

/**
 * @author: fhn
 * @date: 4/21
 * @description: act as the public interface and shunting entry
 * @version: v1.0
 *           v1.01: changed param string to 'const&'
*/
void Interpret(const std::string& raw)
{
    using std::string; using std::stringstream;
    string judge;
    stringstream ss(raw);
    ss >> judge;
    switch(judge[0])
    {
        case 'c': case 'C':
            ss >> judge;
            sql_itp::Create(judge[0], raw);
            break;
        case 'u': case 'U':
            if (judge[1] == 's')
                sql_itp::Use(raw);
            else sql_itp::Update(raw);
            break;
        case 's': case 'S':
            sql_itp::Select(raw);
            break;
        case 'd': case 'D':
            sql_itp::Delete(raw);
            break;
    }
}


namespace sql_itp
{
//using std::string;

/**
 * @author: fhn
 * @date: 4/25
 * @description: washing the strings out of spaces at the front and rear.
 * @version: 1.0: to be improved: maybe stringstream as param(if the other functions can adapt)
*/
void trim(string & src)
{
    src.erase(0, src.find_first_not_of(" "));
    src.erase(src.find_last_not_of(" ")+1);
}

//--------------------------------------------------------------------------------------------

/**
 * @author: fhn
 * @date: 1.1: 4/20; 2.0: 4/24
 * @version: 2.1: robustness with integrated spaces(in the rol param) is improved.
 * @description: get the dbname or tablename from the create sentence.
 * @outout: database mode: database name
 *          table mode: table name and a object containing the column info formatted like this: <size, name>
*/
void Create(char mode, const string& src)
{
    if (mode == 'd')
    {
        std::regex pattern{"^.*?create.*?database.*?(\\w+).*?;$", std::regex::icase};
        std::smatch mat;
        regex_match(src, mat, pattern);
        in_out::CreateDatabase(mat[1]);
    }
    else if (mode == 't')
    {
        std::regex pattern{"^.*?create.*?table.*?(\\w+)\\s*[(]\\s*(.*)[)].*?;.*?$", std::regex::icase};
                                //table name must be in the alphas, nums and '_'
        std::smatch mat;
        regex_match(src, mat, pattern);//mat[1] is tablename, mat[2] is the param of columns.
        in_out::ColInfo param;
        std::string name, type;
        std::stringstream ss(mat[2]);
        while (ss.peek() != EOF) // if using "while (ss)", the eof won't be trigered in time.
        {
            while (ss.peek() == ' ') ss.ignore(); 
            getline(ss, name, ' ');
            while (ss.peek() == ' ') ss.ignore();// ignore the heading spaces.
            getline(ss, type, ',');
            trim(name); trim(type);
            if (type[0] == 'i') 
                param.AddCol(name, 0);
            else if (type[0] == 'v') //this may be improved : in the form of 'varchar (20)' isn;t supported
                                    //2.1 : now supported.
            {
                int cnt = 0, ans = 0;
                while (!isdigit(type[8+cnt])) cnt++;
                while (std::isdigit(type[8+cnt]))
                    ans = ans * 10 + (type[8+cnt]-'0'), cnt++;
                param.AddCol(name, ans);
            }
        }
        in_out::CreateTable(mat[1], param);
    }
}

/**
 * @author: fhn
 * @date: 4/24
 * @description: get the dataname to be used;
*/
void Use(const string& src)
{
    std::regex pattern{"^.*?use.*?(\\w+).*?;", std::regex::icase};
    std::smatch mat;
    regex_match(src, mat, pattern);
    string tmp = mat[1].str();
    trim(tmp);
    in_out::Use(tmp);
}

/**
 * @author: fhn
 * @date: 4/24
 * @description: insert value vectors into table
 * @output: table name and a row vector of values(in v1.2, exluding spaces at the front and rear).
 * @version: 1.2
*/
void Insert(const string& src)
{
    std::regex pattern{"^.*?insert.*?into.*?(\\w+).*?value.*?[(]\\s*(.*)[)].*?;.*?$", std::regex::icase};
    std::smatch mat;
    regex_match(src, mat, pattern);
    std::string name(mat[1]);
    std::stringstream ss(mat[2]);
    std::vector<string> vec_param;
    std::string tmp;
    while (ss.peek() != EOF)
    {
        while (ss.peek() == ' ') ss.ignore();
        getline(ss, tmp, ',');
        trim(tmp);
        vec_param.push_back(tmp);
    }
    in_out::Insert(name, vec_param);
}

//--------------------------------------------------------------------------------------------

/**
 * @author: fhn
 * @date: 4/24
 * @description: dealing with select sentence. calling in_out::select.
 *          vec_param: col_names.
 * @version: 1.0
*/
void Select(const string& src)
{
    std::regex pattern{"^.*?select\\s*(.*)\\s*from\\s+(\\w+)\\s+(where.*?)\\s*;.*?$"};
    std::smatch mat;
    regex_match(src, mat, pattern);
    std::string name(mat[2]);
    std::stringstream ss(mat[1]);
    std::vector<string> vec_param;
    std::string tmp;
    while (ss.peek() != EOF)
    {
        getline(ss, tmp, ',');
        trim(tmp);
        vec_param.push_back(tmp);
    }
    in_out::Select(name, vec_param, Where(mat[3].str()));
}

/**
 * @author: fhn
 * @date: 4/25
 * @description: deals with friendly update sentence. output the table_name, col_to_change name, Where clause 
 * @version: 1.0
*/
void Update(const string& src)
{
    std::regex pattern{"^.*?update\\s+(\\w+)\\s+set\\s+(.+)\\s+=\\s+(.*?)\\s+(where.*?)\\s+;.*?$", std::regex::icase};
    std::smatch mat;
    regex_match(src, mat, pattern);
    in_out::Update(mat[1].str(), mat[2].str(), mat[3].str(), Where(mat[4].str()));
}

/**
 * @author: fhn
 * @date: 4/25
 * @description: deals with delete sentence
 * @version: 1.0
*/
void Delete(const string& src)
{
    std::regex pattern{"^.*?delete\\s+from\\s+(\\w+)\\s+(where.*?)\\s+;.*?$", std::regex::icase};
    std::smatch mat;
    regex_match(src, mat, pattern);
    in_out::Delete(mat[1].str(), Where(mat[2].str()));
}


/**
 * @author: fhn
 * @date: 4/25
 * @description: transform a string of 'where clause' into a Clause obj(which contains the info of it).
 * @input: a string without front and rear spaces; started with where. 
 *          if a void string in, directly return an obj (0, 0, 0)
 * @version: 1.0
*/
Clause Where(const string& src)
{
    std::regex pattern{"^.*?where\\s+(\\w+)\\s+(.*?)\\s+(.*?)\\s+;.*?$", std::regex::icase};
    std::smatch mat;
    if (regex_match(src, mat, pattern))
        return Clause{mat[1].str(), mat[2].str(), mat[3].str()};
    else return Clause();
}


} // namespace sql_itp