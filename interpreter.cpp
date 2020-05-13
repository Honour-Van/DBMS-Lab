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
        case 'i': case 'I':
            ss >> judge;
            sql_itp::Insert(raw);
            break;
        case 'u': case 'U':
            if (judge[1] == 's' || judge[1] == 'S')
                sql_itp::Use(raw);
            else sql_itp::Update(raw);
            break;
        case 's': case 'S':
            sql_itp::Select(raw);
            break;
        case 'd': case 'D':
            sql_itp::Delete(raw);
            break;
        std::cout << "#ERROR sentence syntax went wrong." << std::endl << std::endl; 
    }
#ifdef _LOC_
std::clog << "finished once" << std::endl;
#endif
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
 *          2.2： support for uppercase sentence
 *           2.3: able to deal with the exception of illegal vartable
 * @description: get the dbname or tablename from the create sentence.
 * @outout: database mode: database name
 *          table mode: table name and a object containing the column info formatted like this: <size, name>
*/
void Create(char mode, const string& src)
{
    if (mode == 'd' || mode == 'D')
    {
        std::regex pattern{"^.*?create.*?database.*?(\\w+).*?;$", std::regex::icase};
        std::smatch mat;
        if (!regex_match(src, mat, pattern))
        { std::cout << "#ERROR create database : syntax wrong" << std::endl << std::endl; return; }
        in_out::CreateDatabase(mat[1]);
    }
    else if (mode == 't' || mode == 'T')// 
    {
        std::regex pattern{"^.*?create.*?Table.*?(\\w+)\\s*[(]\\s*(.*)[)].*?;.*?$", std::regex::icase};
                                //table name must be in the alphas, nums and '_'
        std::smatch mat;
        if (!regex_match(src, mat, pattern))
        { std::cout << "#ERROR create table : syntax wrong" << std::endl << std::endl; return;}//mat[1] is tablename, mat[2] is the param of columns.
    #ifdef _LOC_
        else 
    std::clog << "create table matched" << std::endl;
    #endif
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
            if (type[0] == 'i' || type[0] == 'I') 
            {    
                if (!type.compare(0,3, "int", 0,3) && !type.compare(0,3, "INT", 0, 3))
                { std::cout << "#ERROR var table type illegal" << std::endl << std::endl; return;}
                else param.AddCol(name, 0);
            }
            else if (type[0] == 'v' || type[0] == 'V') //this may be improved : in the form of 'varchar (20)' isn;t supported
                                    //2.1 : now supported.
            {
                int cnt = 7, ans = 0;
                if (!(type.compare(0, 7, "varchar", 0, 7)||type.compare(0, 7, "VARCHAR", 0, 7)))
                { std::cout << "#ERROR var table type illegal" << std::endl << std::endl; return;}
                for (; cnt < type.size() && (!std::isdigit(type[cnt])); cnt++);
                if (cnt != type.size())
                    while (std::isdigit(type[cnt]))
                        ans = ans * 10 + (type[cnt]-'0'), cnt++;
                else { std::cout << "#ERROR var table type illegal" << std::endl << std::endl; return;}
                param.AddCol(name, ans);
            }
            else 
            { std::cout << "#ERROR var table type illegal" << std::endl << std::endl; return;}
        }
#ifdef _LOC_
std::clog << "create table prepared" << std::endl << std::endl;
#endif
        in_out::CreateTable(mat[1], param);
    }
    else std::cout << "#ERROR create table mode wrong." << std::endl << std::endl;
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
    if (!regex_match(src, mat, pattern))
    { using namespace std; cout << "#ERROR use sentence wrong" << endl << endl; return; };
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
    if (!regex_match(src, mat, pattern))
    { using namespace std; cout << "#ERROR insert syntax wrong: whole sentence" << endl << endl; return; }
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
 * @version: 1.2: regex has been modified from "^.*?select\\s*(.*)\\s*from\\s+(\\w+)\\s+(where.*?)\\s*;.*?$" to 
 *                                             "^.*?select\\s*(.*)\\s*from\\s+(\\w+)\\s*(where.*?)*\\s*;.*?$"
 *           v3.0: in test4, we found the regex is wrong with the where clause
*/
void Select(const string& src)
{
    std::regex pattern{"^.*?select\\s*(.*)\\s*from\\s+(\\w+)\\s*(where.*?)*\\s*;.*?$", std::regex::icase};
    std::smatch mat;
    if (!regex_match(src, mat, pattern))
    { using namespace std; cout << "#ERROR select syntax wrong: whole sentence" << endl << endl; return;};
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
 *              v1.1:  * and + make difference!!!
*/
void Update(const string& src)
{
    std::regex pattern{"^.*?update\\s+(\\w+)\\s+set\\s+(.*?)\\s*=\\s*(.+?)\\s+(where.*?)\\s*;.*?$", std::regex::icase};
    std::smatch mat;
    if (!regex_match(src, mat, pattern))
    { using namespace std; cout << "#ERROR: update syntax wrong: whole sentence" << endl << endl; return;};
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
    std::regex pattern{"^.*?delete\\s+from\\s+(\\w+)\\s+(where.*?)\\s*;.*?$", std::regex::icase};
    std::smatch mat;
    if (!regex_match(src, mat, pattern))
    { using namespace std; cout << "#ERROR delete sentence wrong" << endl << endl; return; };
    in_out::Delete(mat[1].str(), Where(mat[2].str()));
}


/**
 * @author: fhn
 * @date: 4/25
 * @description: transform a string of 'where clause' into a Clause obj(which contains the info of it).
 * @input: a string without front and rear spaces; started with where. 
 *          if a void string in, directly return an obj (0, 0, 0)
 * @version: 1.0
 *          v1.1: the * and + cause the regex to go wrong, improve the intercommunication of regex function cut the ';'
*/
Clause Where(const string& src)
{
    std::regex pattern{"^.*?where\\s+(\\w+)\\s*([><=!]{1,2})\\s*(.+?)\\s*$", std::regex::icase};
    std::smatch mat;
    if (regex_match(src, mat, pattern))
        return Clause{mat[1].str(), mat[2].str(), mat[3].str()};
    return Clause();
}


} // namespace sql_itp