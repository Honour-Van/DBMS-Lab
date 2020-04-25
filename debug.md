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