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

```sql
create database test1;
use test1;

use test1;
create table table1(id int, name varchar(20));
insert into table1 value(1, xiaoming);
insert into table1 value(2, xiaohua);
insert into table1 value(3, xiaoli);
```

## test1
```sql
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
```

## test2(first full)
```sql
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
```

## test3 (excption)
```sql
use test1;
select*from table2;
update table1 set value = 1.1 where id = 1;
```

```sql
use test1;
insert into table1 value(1, "xiaoming");
delete from table1 where name = xiaoming;
insert into table1 value(1, 'xiaoming');
insert into table1 values(1, "xiaoming');
insert into table1 values(1, xiaoming);
```

```sql
use test1;
select*from table1;
update table1 set id  = 2 where name = xiaofang;
update table1 set name = 'xiaohua' where name = 'xiaofang';
```

```sql
create database test1;
use test1;
create table table1(id int, name varchar(20));
insert into table1 value(1, 'xiaohua');
insert into table1 value(2, "xiaoh');
insert into table1 value(2, "xiaoh");
select*from table1;
select name, id from table1;
select name id from table1;
update table1 set id = 2 where name = xiaohua;
update table1 set id = 2 where name = 'xiaohong';
update table1 set id = 3 where name = "xiaohua";
delete from table1 where name = 'xiaoh';
```

## test4 (time_cnt & exception more)
```sql

insert into table1 value(1, "h");
use test1;
insert into table1 value(1, 'h');
select *from table1;
insert into table1 value(2, 'hh');
select*from table1;
insert into table1 values(3, "hhh");
select * from table1;
insert into table1 value(4, "hhhh");
select * from table1;
insert into table1 value(5, "hhhhh");
select * from table1;
update table1 where id >= 4 set name = 'hhhhhh';
update table1 set name = 'hhhhhh' where id >= 4;
update table1 set id = 6 where name = 'hhhhhh';
update table1 set name = 'ha' where id != 2;
select * from table1;
delete from table1 where name <= "hh";
select* from table1;

```

### delete test:
i have a deep confusion with the initread in the select:

before start table1:
```
2 3
id 0 3 4 5 
name 20 hhh hhhh hhhhh
```

```sql
1. 
use test1;
select *from table1;
delete from table1 where name <= "hh";
delete from table1 where name <= "hh";
```
- bug: the `isDelete()` function has not enough space, thus, when judging: wrong
- sln: `reserve` to `resize`

```sql
2.
use test1;
select*from table1;
delete from table1 where name <= "hh";
select*from table1;
delete from table1 where name <= "hh";

3.
use test1;
delete from table1 where name <= "hh";
select*from table1;

```


## recreate
```sql
use test1;
create table table1(id int, name varchar(20));
select*from table1;
```
```
2 0
id 0
name 20
```

## test5
vector is a dangerous container: its push_back and size() during cases prevails
```sql
use test1;
select*from table1;
select*from table2;
```
### insert retest
```sql
insert into table2 value(2, 'wdnmd', 'xxxxxxx');
insert into table2 value(2, 'wdnmd', 'xx');
select*from table2;
```
### create table retest
```sql
use test1;
create table table3(id Int, name varchar(20));
create table table3(id int, name varchar);
create table table3(id int, name varchar(20));
```
