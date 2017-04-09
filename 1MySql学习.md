# MySql 学习

<<MYSQL高效编程>>

## 重要设置

关闭  safe update mode

SET SQL_SAFE_UPDATES = 0;

## 问题

存在记录则删除,没有记录则创建

[MySQL 当记录不存在时插入，当记录存在时更新](http://fenley.iteye.com/blog/626355)

MySQL 当记录不存在时插入，当记录存在时更新 
网上基本有三种解决方法


- 方法1:

插入多条记录

```
INSERT INTO clients 
(client_id, client_name, client_type) 
SELECT supplier_id, supplier_name, 'advertising' 
FROM suppliers 
WHERE not exists (select * from clients 
where clients.client_id = suppliers.supplier_id); 
```

插入一条记录

```
insert ss (name) 
select 'sb' from dual
where not exists (select * from ss where name='sb');
```

```
INSERT INTO clients 
(client_id, client_name, client_type) 
SELECT 10345, 'IBM', 'advertising' 
FROM dual 
WHERE not exists (select * from clients 
where clients.client_id = 10345); 
使用 dual 做表名可以让你在 select 语句后面直接跟上要插入字段的值，即使这些值还不存在当前表中。 

```

- 虚表

Mysql：语法：虚拟表DUAL

在mysql里也存在和oracle里类似的dual虚拟表：官方声明纯粹是为了满足select ... from...这一习惯问题，mysql会忽略对该表的引用。


- 方法2:


INSERT 中 ON DUPLICATE KEY UPDATE的使用 

```
insert ss (name)  values ('aa')
ON DUPLICATE KEY UPDATE name='aa';
```


INSERT INTO TABLE (a,c) VALUES (1,3) ON DUPLICATE KEY UPDATE c=c+1

出现重复则执行更新,否则插入新行.


- 方法3: REPLACE

在使用REPLACE时，表中必须有唯一索引，而且这个索引所在的字段不能允许空值，否则REPLACE就和INSERT完全一样的。 

在执行REPLACE后，系统返回了所影响的行数，如果返回1，说明在表中并没有重复的记录，如果返回2，说明有一条重复记录，系统自动先调用了DELETE删除这条记录，然后再记录用INSERT来插入这条记录。如果返回的值大于2，那说明有多个唯一索引，有多条记录被删除和插入。 

REPLACE的语法和INSERT非常的相似，如下面的REPLACE语句是插入或更新一条记录。 

REPLACE INTO users (id,name,age) VALUES(123, '赵本山', 50); 
　 
插入多条记录： 

```
REPLACE INTO users(id, name, age) 

VALUES(123, '赵本山', 50), (134,'Mary',15); 

REPLACE也可以使用SET语句 

REPLACE INTO users SET id = 123, name = '赵本山', age = 50; 
```

## 启动

mysql -u 用户名 -p密码

注意**-p与密码间不能存在空格**

mysql -u 用户名 -p

则会提示输入密码

退出  quit /exit

- 数据库

show databases;

drop database name;

create database name;

use 数据库名字;

- 查看指定的数据库 

select database();


## 数据类型

MySQL数据类型	| 含义（有符号）
---|  ----
tinyint(m)	|1个字节  范围(-128~127)
smallint(m)|	2个字节  范围(-32768~32767)
mediumint(m)|	3个字节  范围(-8388608~8388607)
int(m)	|4个字节  范围(-2147483648~2147483647)
bigint(m)|	8个字节  范围(+-9.22*10的18次方)

int(m)里的m是表示SELECT查询结果集中的显示宽度，并不影响实际的取值范围，没有影响到显示的宽度

取值范围如果加了unsigned，则最大值翻倍，如tinyint unsigned的取值范围为(0~256)。



浮点型	| 含义
---|  ----
float(m,d)	|单精度浮点型     8位精度(4字节)     m总个数，d小数位
double(m,d)	| 双精度浮点型    16位精度(8字节)    m总个数，d小数位


字符串(char,varchar,_text)

MySQL数据类型	| 含义
---|  ----
char(n)	| 固定长度，最多255个字符
varchar(n)	| 固定长度，最多65535个字符
tinytext	| 可变长度，最多255个字符
text	| 可变长度，最多65535个字符
mediumtext	| 可变长度，最多2的24次方-1个字符
longtext| 	可变长度，最多2的32次方-1个字符


1. Varchar往往用来保存可变长度的字符串。
1. CHAR数据类型与VARCHAR数据类型不同，其采用的是固定长度的存储方式。(当字符位数不足时，系统并不会采用空格来填充。相反，如果在保存CHAR值的时候，如果其后面有空值，系统还会自动过滤其空格。而在进行数据比较时，系统又会将空格填充到字符串的末尾。)

显然，VARCHAR与CHAR两种字符型数据类型相比，最大的差异就是前者是可变长度，而后者则是固定长度。在存储时，前者会根据实际存储的数据来分配最终的存储空间。而后者则不管实际存储数据的长度，都是根据CHAR规定的长度来分配存储空间。这是否意味着CHAR的数据类型劣于VARCHAR呢？其实不然。否则的话，就没有必要存在CHAR字符类型了。虽然VARCHAR数据类型可以节省存储空间，提高数据处理的效率。但是其可变长度带来的一些负面效应，有时候会抵消其带来的优势。为此在某些情况下，还是需要使用Char数据类型。

在实际项目中，如果某个字段的字符长度比较短此时一般是采用固定字符长度。

CHAR（1）与VARCHAR（1）两这个定义，会有什么区别呢？虽然这两个都只能够用来保存单个的字符，但是VARCHAR要比CHAR多占用一个存储位置。这主要是因为使用VARCHAR数据类型时，会多用1个字节用来存储长度信息。这个管理上的开销CHAR字符类型是没有的。

VARCHAR,有碎片问题,需要整理碎片.

- VARCHAR（100）与VARCHAR（200）真的相同吗？

于VARCHAR数据类型来说，硬盘上的存储空间虽然都是根据实际字符长度来分配存储空间的，但是对于内存来说，则不是。其时使用固定大小的内存块来保存值。简单的说，就是使用字符类型中定义的长度，即200个字符空间。显然，这对于排序或者临时表（这些内容都需要通过内存来实现）作业会产生比较大的不利影响。所以如果某些字段会涉及到文件排序或者基于磁盘的临时表时，分配VARCHAR数据类型时仍然不能够太过于慷慨。还是要评估实际需要的长度，然后选择一个最长的字段来设置字符长度。如果为了考虑冗余，可以留10%左右的字符长度。千万不能认为其为根据实际长度来分配存储空间，而随意的分配长度，或者说干脆使用最大的字符长度。



- 数据类型的属性

MySQL关键字	| 含义
--- |  ----
NULL	 | 数据列可包含NULL值
NOT NULL | 	数据列不允许包含NULL值
DEFAULT	 | 默认值
PRIMARY KEY	 | 主键
AUTO_INCREMENT	 | 自动递增，适用于整数类型
UNSIGNED	 | 无符号
CHARACTER SET name	 | 指定一个字符集
check | 自定义范围
unique |  定义唯一性


**主键被认为是NOT NULL和UNIQUE约束最好的结合。**

显示表: show tables;

显示表结构: desc tablename;

删除表:drop table  表名;

## 创建表

```sql
create table student (
	id  int(6) primary key auto_increment,
	name varchar(10) not null
	 );
```

```sql
insert s1 (name) valuse('s1');
```

## 插入数据

```sql
insert 表名 (列名) values();
mysql> insert S (sno,sname) values(4,'test');
```

如果插入数据覆盖了所有列的话,可以省略列名.

```
Topic: INSERT
 
Syntax:
INSERT [LOW_PRIORITY | DELAYED | HIGH_PRIORITY] [IGNORE]
    [INTO] tbl_name
    [PARTITION (partition_name,...)]
    [(col_name,...)]
    {VALUES | VALUE} ({expr | DEFAULT},...),(...),...
    [ ON  DUPLICATE  KEY  UPDATE
      col_name=expr
        [, col_name=expr] ... ]


Or:
INSERT [LOW_PRIORITY | DELAYED | HIGH_PRIORITY] [IGNORE]
    [INTO] tbl_name
    [PARTITION (partition_name,...)]
    SET col_name={expr | DEFAULT}, ...
    [ ON  DUPLICATE  KEY  UPDATE
      col_name=expr
        [, col_name=expr] ... ]


Or:
INSERT [LOW_PRIORITY | HIGH_PRIORITY] [IGNORE]
    [INTO] tbl_name
    [PARTITION (partition_name,...)]
    [(col_name,...)]
    SELECT ...
    [ ON  DUPLICATE  KEY  UPDATE
      col_name=expr
        [, col_name=expr] ... ]
```

## 查询

select * from S;

select 列1 ,列2 from 表名;

```sql
SELECT
    [ALL | DISTINCT | DISTINCTROW ]
      [HIGH_PRIORITY]
      [MAX_STATEMENT_TIME = N]
      [STRAIGHT_JOIN]
      [SQL_SMALL_RESULT] [SQL_BIG_RESULT] [SQL_BUFFER_RESULT]
      [SQL_CACHE | SQL_NO_CACHE] [SQL_CALC_FOUND_ROWS]
    select_expr [, select_expr ...]
    [FROM table_references
      [PARTITION partition_list]
    [WHERE where_condition]
    [GROUP  BY {col_name | expr | position}
      [ASC | DESC], ... [WITH  ROLLUP]]
    [HAVING where_condition]
    [ORDER  BY {col_name | expr | position}
      [ASC | DESC], ...]
    [LIMIT {[offset,] row_count | row_count OFFSET offset}]
    [PROCEDURE procedure_name(argument_list)]
    [INTO  OUTFILE 'file_name'
        [CHARACTER  SET charset_name]
        export_options
      | INTO  DUMPFILE 'file_name'
      | INTO var_name [, var_name]]
    [FOR  UPDATE | LOCK  IN  SHARE  MODE]]
```


## 注释 

--  注释内容 

或者

/* 注释内容 */

##  更新

```sql
update 表名 set 列名=值1  where 表达式;
update student set id=99 ,name='test' where id=3;
update student set name='test'   --省略where将更新所有记录
```

```
UPDATE [LOW_PRIORITY] [IGNORE] table_reference
    SET col_name1={expr1|DEFAULT} [, col_name2={expr2|DEFAULT}] ...
    [WHERE where_condition]
    [ORDER  BY ...]
    [LIMIT row_count]


Multiple-table syntax:
UPDATE [LOW_PRIORITY] [IGNORE] table_references
    SET col_name1={expr1|DEFAULT} [, col_name2={expr2|DEFAULT}] ...
    [WHERE where_condition]
```
## 删除

```sql
delete from tbl_name where 表达式;
```

省略 where将删除表的所有数据.

删除表所有数据,更快 更高效命令.

**truncate table  tbl_name**

破坏表的结构和数据,然后创建他.

```
DELETE [LOW_PRIORITY] [QUICK] [IGNORE] FROM tbl_name
    [PARTITION (partition_name,...)]
    [WHERE where_condition]
    [ORDER  BY ...]
    [LIMIT row_count]

DELETE [LOW_PRIORITY] [QUICK] [IGNORE]
    FROM tbl_name[.*] [, tbl_name[.*]] ...
    USING table_references
    [WHERE where_condition]
```
## 检索

select  列名1 ,列名2 from 表名 [表达式];


过滤重复行

SELECT distinct  name FROM  student;


```
SELECT
    [ALL | DISTINCT | DISTINCTROW ]
      [HIGH_PRIORITY]
      [MAX_STATEMENT_TIME = N]
      [STRAIGHT_JOIN]
      [SQL_SMALL_RESULT] [SQL_BIG_RESULT] [SQL_BUFFER_RESULT]
      [SQL_CACHE | SQL_NO_CACHE] [SQL_CALC_FOUND_ROWS]
    select_expr [, select_expr ...]
    [FROM table_references
      [PARTITION partition_list]
    [WHERE where_condition]
    [GROUP  BY {col_name | expr | position}
      [ASC | DESC], ... [WITH  ROLLUP]]
    [HAVING where_condition]
    [ORDER  BY {col_name | expr | position}
      [ASC | DESC], ...]
    [LIMIT {[offset,] row_count | row_count OFFSET offset}]
    [PROCEDURE procedure_name(argument_list)]
    [INTO  OUTFILE 'file_name'
        [CHARACTER  SET charset_name]
        export_options
      | INTO  DUMPFILE 'file_name'
      | INTO var_name [, var_name]]
    [FOR  UPDATE | LOCK  IN  SHARE  MODE]]
```

- 多条件组合

select * from where 条件1 and 条件2;

select * from where 条件1 or 条件2;

理论运算符

运算符优先顺序.

NOT -> AND -> OR

不等于  <>

```
like
not like 
is null
not null
in
between 
```

## 模糊检索

select * from student where name like 's%';

1. % 代表0个以上字符  
1. 下划线_ 代表一个字符

- null 条件

错误方法: select * from student where name == null;

正确: select * from student where name is null;


- 结果排序

order by age DESC;

select * from student order by  id desc ;

升序ASC,降序DESC

Mysql将NULL当成最小值;

指定数量,limt要与order by同时使用.

order by age DESC limt 2;



统计函数

```
avg
count
max
min
sum
```

select  count(id ) from student;

select  max(id ) from student;

select  id  from student order by id limit 2;

mysql> select sdep,count(sno),max(sage)  from S group by sdep;

select  *  from student  group by name;

- 数据分组


select  count(id),name  from student  group by name;
 

进行 group by,其他列选择只能是count等统计函数.

**count只统计非NULL记录.**

- 列的别名

as

select  count(id),name as hello from ss  group by name;

显示的时候也是使用别名.


## Case函数

通过Case函数进行简单的条件判断


```sql
case 表达式
	when 比较值1 then 结果1
	when 比较值2 then 结果1
	esle 结果 N
end

select 
	case id
	when id<20 then '小'
	else '大'
	end as id
,name
from student;
```


## 多个表连接

## 内连接

inner join ... on

```
select 列名1  from 表1 
inner join 表2
on 表1.外键=表2.键值
where/order by
```

## 外链接

```
select 列名1  from 表1 
left outer join  表2
on 表1.外键=表2.键值
where/order by
```

right outer join  ... on


## where 语句

select * from product where price > (select avg(price) from  product );

select * from usr where uid not in (select id from  name);

## exists 语句

select name from usr where exists (select * from name);


## alter 修改表结构

1. 修改列的定义: modify
1. 追加: add
1. 删除: drop
1. 修改列的名称: change

更改列的类型:

ALTER TABLE tbl_name  MODIFY [COLUMN] col_name column_definition;

追加新列

ALTER TABLE tbl_name  ADD  col_name column_definition;

修改列名与类型

ALTER TABLE tbl_name  CHANGE [COLUMN] old_col_name new_col_name column_definition

删除列

ALTER TABLE tbl_name  drop col_name;


```
ALTER [IGNORE] TABLE tbl_name
    [alter_specification [, alter_specification] ...]
    [partition_options]


alter_specification:
    table_options
  | ADD [COLUMN] col_name column_definition
        [FIRST | AFTER col_name ]
  | ADD [COLUMN] (col_name column_definition,...)
  | ADD {INDEX|KEY} [index_name]
        [index_type] (index_col_name,...) [index_option] ...
  | ADD [CONSTRAINT [symbol]] PRIMARY  KEY
        [index_type] (index_col_name,...) [index_option] ...
  | ADD [CONSTRAINT [symbol]]
        UNIQUE [INDEX|KEY] [index_name]
        [index_type] (index_col_name,...) [index_option] ...
  | ADD  FULLTEXT [INDEX|KEY] [index_name]
        (index_col_name,...) [index_option] ...
  | ADD  SPATIAL [INDEX|KEY] [index_name]
        (index_col_name,...) [index_option] ...
  | ADD [CONSTRAINT [symbol]]
        FOREIGN  KEY [index_name] (index_col_name,...)
        reference_definition
  | ALGORITHM [=] {DEFAULT|INPLACE|COPY}
  | ALTER [COLUMN] col_name {SET  DEFAULT literal | DROP  DEFAULT}
  | CHANGE [COLUMN] old_col_name new_col_name column_definition
        [FIRST|AFTER col_name]
  | LOCK [=] {DEFAULT|NONE|SHARED|EXCLUSIVE}
  | MODIFY [COLUMN] col_name column_definition
        [FIRST | AFTER col_name]
  | DROP [COLUMN] col_name
  | DROP  PRIMARY  KEY
  | DROP {INDEX|KEY} index_name
  | DROP  FOREIGN  KEY fk_symbol
  | DISABLE  KEYS
  | ENABLE  KEYS
  | RENAME [TO|AS] new_tbl_name
  | RENAME {INDEX|KEY} old_index_name TO new_index_name
  | ORDER  BY col_name [, col_name] ...
  | CONVERT  TO  CHARACTER  SET charset_name [COLLATE collation_name]
  | [DEFAULT] CHARACTER  SET [=] charset_name [COLLATE [=] collation_name]
  | DISCARD  TABLESPACE
  | IMPORT  TABLESPACE
  | FORCE
  | {WITHOUT|WITH} VALIDATION
  | ADD  PARTITION (partition_definition)
  | DROP  PARTITION partition_names
  | DISCARD  PARTITION {partition_names | ALL} TABLESPACE
  | IMPORT  PARTITION {partition_names | ALL} TABLESPACE
  | TRUNCATE  PARTITION {partition_names | ALL}
  | COALESCE  PARTITION number
  | REORGANIZE  PARTITION partition_names INTO (partition_definitions)
  | EXCHANGE  PARTITION partition_name WITH  TABLE tbl_name [{WITH|WITHOUT} VALIDATION]
  | ANALYZE  PARTITION {partition_names | ALL}
  | CHECK  PARTITION {partition_names | ALL}
  | OPTIMIZE  PARTITION {partition_names | ALL}
  | REBUILD  PARTITION {partition_names | ALL}
  | REPAIR  PARTITION {partition_names | ALL}
  | REMOVE  PARTITIONING
  | UPGRADE  PARTITIONING
```


## 表的复制与删除

复制表的构造和数据

create table 新表名 select * from 旧表名;

复制表的构造

create table 新表名 like 旧表名;

数据复制

insert 新表名 select * from 旧表名;



# 6 事务处理及锁定

- 显示使用的存储引擎 show create table student;

**ENGINE=InnoDB** 

'student', 'CREATE TABLE `student` (\n  `id` int(6) NOT NULL AUTO_INCREMENT,\n  `name` varchar(10) NOT NULL,\n  PRIMARY KEY (`id`)\n) ENGINE=InnoDB AUTO_INCREMENT=132 DEFAULT CHARSET=utf8'

- 替换存储引擎

alter table 表名 ENGINE=新存储引擎;

- 查看现在提交模式

select @@autocommit;


- 定义保存点

savepoint 保存点名;

回滚保存点

rollback to savepoint 保存点名;

- 事务处理的利用范围

以下命令执行后自动提交. 在事务处理范围外.

drop database;
drop table;
drop;
alter table;

- 锁定与事务处理分离

共享锁定(读取锁定): 只读

排他锁定: 其他不能读,独占


锁定粒度; 行 表 数据库


## 事务处理分离水平

1. 非提交读取: 脏读,读到未提交数据
1. 提交读取
1. 连续读取
1. 序列化读取

## 理解事务内部的动作

- undo 日志

回滚段.保存变更前的数据.

- redo日志

事务处理日志.

数据更新没有正确处理.

硬盘写入都是在检查点,到来时集中处理.减少硬盘次数.


# 7 数据库中使用索引

采用B树的方式来管理索引.

## 创建索引

```sql
create [unique] index 索引名 on 表名 (列名);
create index  id_index on student(id);
```

- 显示索引

```sql
show  index from student;
```

- 删除索引

drop index 索引名  on  表名;

- 创建多列构成的复合索引和唯一索引.

```sql
create [unique] index 索引名 on 表名 (列名1,列名2,列名3);
```

指定 unique 关键词将创建不可重复的索引.称为唯一索引.

- 确认索引使用状态.explain

```sql
explain select id from student;
```

'1', 'SIMPLE', 'student', NULL, 'index', NULL, 'id_index', '4', NULL, '64', '100.00', 'Using index'



##  索引使用哪个场合.

- like 只有前方一致性检索才能使用索引.

select * from table where name like 'w%';

下面的后方一致性和部分一致性无法使用索引.

select * from table where name like '%w';

select * from table where name like '%w%';

- 使用 is not null   <> 比较运算的场合无法使索引.

- 使用了运算符函数的场合

select * from table where year(birth)='1980';

-  复合索引的第一列没有包含在where语句中的情况 or也不行

create [unique] index 索引名 on 表名 (列名1,列名2,列名3);



# 8 视图使用

视图的本质就是将select 的数据以结果的形式保存出来.

##  视图作用

1. 公开特定行与列
1. 简化sql查询
1. 限制插入更新范围

## 创建视图

```sql
create view 视图名(列名)  as select 语句 [with check point];
create view myview (id)   as  select id from student;
```

## 删除视图

```sql
drop view  视图名;
```

显示列信息

show fields from myview;

视图的插入,删除,更新 和表方法相同.

- 以下情况不能插入 删除 更新

1. 视图列含有统计函数的情况
1. 视图使用group by /having 语句 distinct 
1. 使用子查询
1. 跨越多个表

- 过滤重复行 **distinct**

```sql
SELECT distinct  name FROM  student;
```

- with check point

不能插入,不符合视图检索条件数据


# 9 存储过程

- 好处

1. 提高执行性能: 存储过程事先完成解析,编译.
1. 减轻网络负担:复杂数据库操作可以在数据库服务器中完成.
1. 防止表直接访问:客户端只能通过存储过程来访问表.
1. 可将数据处理黑盒化


## 定义存储过程

三种类型参数
in
out
inout

```
create procedure 存储过程名(
参数种类1 参数1
参数种类2 参数2
)
begin
	处理内容
end
```

```
delimiter //
create procedure sp_name (
in p_name varchar(20)
)
begin
	if p_name is not null or p_name= '' then 
		select * from table_name;
	else
        select * from table_name where name like p_name;
	end if
end
//
delimiter ;
```

更换默认分隔符.

delimiter //

在执行完存储过程,后恢复默认的分隔符号.

```
if  XX
	XXX
elseif XX
	XXX
else 
	XXX
endif

case  表达式1
	when  值1 then 执行命令
    when  值2 then 执行命令
end case


repeat
	执行命令
until 表达式  end repeate

while 表达式  do
		执行命令
end while
```

- 显示存储过程

show procedure status;


- 调用存储过程

call sp_name(参数);

- 本地变量

declare 变量名  数据类型;

- 赋值

set 变量名=值;


# 10 函数与触发器

定义存储函数  

```
create function 函数名(
参数1 数据类型) 
returns 返回值类型
begin
	XX
	return 返回值;
end
```

## 存储过程和存储函数的区别

1. 存储函数,参数只有输入型
1. 存储函数必须在return后定义返回类型.

-  显示存储函数

show function status;

##  触发器

```
delimiter //
create trigger 触发器名 befor/after delete/update/insert on 表名 for each row
beging
	任意sql语句
end
delimiter ;
```

- 显示触发器

show triggers;


- 删除触发器

drop trigger 触发器名;

## **游标**

处理sql不擅长的对记录一件件单独处理.

先用select 语句检索出符合条件的记录保存到内存中.
然后游标对内存中集合依次处理.

游标通过移动指针进行逐行处理.

- 声明游标 

declare 游标名 cursor for select 语句;

- 打开游标 

取得具体记录的集合.

open 游标名

- 从指针中取得记录数据

fetch 游标名 into 变量名;

- 声明 取出所有记录时的处理

- 关闭游标

close 游标名;



# 11 数据库管理中文件的使用


- 导入数据文件

load data infile  文件名  into table 表名 选项;

- 导出数据

select * into outfile 文件名 选项 from  表名;

- 执行保存好的sql文件

source  文件名;


- 进行数据转存

mysqldumpp


- 利用转存文件进行恢复

mysqladmin 










