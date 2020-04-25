# sql features:
## create
create database database_name;
- Query OK, 1 row affected(... sec)
- (if no name) '\n\t->'
create table table_name ('name' int,'name' varchar(20));
- (if no name) '\n\t->'
- (if no vars) '\n\t->'
- (name1 type1, name2 type2); Query OK, 0 rows affected (0.11 sec)  
## use
use database_name;?
- Database changed
- if no name here, warn.
## insert
insert into table_name values("name",123,234);
- Query OK, 1 row affected (0.01 sec)
## select
select name(, name2...) or "*" from table_name;
- output a chart
- 1 row in set (0.00 sec)

select name from table_name where name op value;
## update
update table_name set name = newValue where name op value;
- Query OK, 1 row affected (0.01 sec)
- Rows matched: 1  Changed: 1  Warnings: 0
## delete
delete from table_name where name op value;
- Query OK, 1 row affected (0.00 sec)
## (other bits)
- if we use regular exp to match, there is another problem of getting the 
- when we impl. the interpreter should be in a whole namespace to guarantee the encapsulation