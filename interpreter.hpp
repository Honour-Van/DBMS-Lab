/**
 * @file: interpreter.hpp
 * @author: fhn
 * @date: 4/20
 * @version: 1.0 to be improved : a function which formats a string into pieces of strings without spaces in them 
 * @description: receiving params from the ui::Input(), 
 *                  containing the main parts of interpreters
 *                  in different functions.
*/

//--------------------------------------------------------------------------------------------

#ifndef INTERPRETER_GUARD
#define INTERPRETER_GUARD

#include <string>
#include "in_out.hpp"

//--------------------------------------------------------------------------------------------


void Interpret(const std::string&);
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

/**
 * @author: fhn
 * @date: 4/21
 * @description: a namespace targeted for Interpret();
 * @version: 
*/
namespace sql_itp{
using std::string;

void trim(string&);
//free of where

/**
 * @author: fhn
 * @date: 4/22
 * @description: call in_out::Create(database_name) to create a database(as a filefolder) or table(file)
*/
void Create(char mode, const string& src);

/**
 * @author: fhn
 * @date: 4/22
 * @description: call in_out::Use(database_name), impl by changing cur_db.
*/
void Use(const string& src);

/**
* @author: fhn
* @date: 4/22
* @description: call in_out::Insert(table_name, )
*/
void Insert(const string& src);


//fucking blessed with where clause

/**
* @author: fhn
* @date: 4/25
* @description: return a Clause obj including info of Where.
*/
Clause Where(const string& src);

void Select(const string& src);
void Update(const string& src);
void Delete(const string& src);

} // namespace sql_itp


#endif