# mysql-python
MySQL UDF library that provides access to the python interpreter. It is a highly experimental project inspired by the use of GraalVM on Oracle Database.

The aim of this project is try to use python as a query and data processing language inside a MySQL database.

For now, the only function available is `py_eval` that let's you evaluate python expression and returns the result as a MySQL string.

## How to Install

#### Ubuntu
Install dependencies

```bash
$ sudo apt update && sudo apt-get install -y build-essential make cmake g++
```

Clone and build
```bash
$ git clone --recursive https://github.com/mliezun/mysql-python.git
$ cd mysql-python
$ mkdir dist && cd dist
$ cmake .. && make
$ sudo mv libmysql-python.so.0.0.1 /usr/lib/mysql/plugin/py_eval.so
```

Add to MySQL
```sql
> create function py_eval returns string soname 'py_eval.so';
Query OK, 0 rows affected...

> select py_eval('[i**2 for i in range(10)]') test;
+--------------------------------------+
| test                                 |
+--------------------------------------+
| [0, 1, 4, 9, 16, 25, 36, 49, 64, 81] |
+--------------------------------------+
1 row in set (0.001 sec)

```
