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

use test1;
create table table1(id int, name varchar(20));
insert into table1 value(1, xiaoming);
insert into table1 value(2, xiaohua);
insert into table1 value(3, xiaoli);

## test1
use test1;
select name from table1;

use test1;
select * from table1;

use test1;
update table1 set name = xiaozhao
where id = 3;

use test1;
select* from table1;
delete from table1 where id > 2;
select*from table1;

## test2(first full)
create database test1;
use test1;
create table table1(id int, name varchar(20));
insert into table1 value(1, xiaoming);
insert into table1 value(2, xiaohua);
insert into table1 value(3, xiaoli);
select*from table1;
select name from table1 where id > 2;
update table1 set name = xiaozhao
where id = 3;
select*from table1;
delete from table1 where name = xiaoming;
select*from table1;

## test3 (excption)
use test1;
select*from table2;
update table1 set value = 1.1 where id = 1;

use test1;
insert into table1 value(1, "xiaoming");
delete from table1 where name = xiaoming;
insert into table1 value(1, 'xiaoming');
insert into table1 values(1, "xiaoming');
insert into table1 values(1, xiaoming);

use test1;
select*from table1;
update table1 set name = 'xiaohua' where name = 'xiaofang';

