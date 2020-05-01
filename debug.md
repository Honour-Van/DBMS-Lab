## Interface::Input()
```json
create database name1;
create database 
name1;
create      database
name1;
create database
 name1;


;
```

## sql_itp::Create()
- `smatch` is a sectionalized 'string' (its size() return 1+n, n is the number of expression in small parenthesis), when debugging with string, remember to assert its size!
- if we want to create a filefolder, we need to use the DOS cmd. and like that of other file-functions, invocation of `system(char * command)` receive `char *` param 


## in_out
be careful about the param of `ostream::write(const char *s, streamsize n)`.

create database test1;
use test1;
create table table1(id int, name varchar(20));
insert into table1 value(1, xiaoming);
insert into table1 value(2, xiaohua);
insert into table1 value(3, xiaoli);
select name from table1;
update table1 set name = xiaozhao
where id = 3;
delete from test1 where id < 2;
select * from table1;