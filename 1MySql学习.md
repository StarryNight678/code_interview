# MySql 学习

<<MYSQL高效编程>>

## 重要设置

- 关闭  safe update mode

SET SQL_SAFE_UPDATES = 0;

## 存储引擎选择

![](http://i.imgur.com/eqdAEKl.png)

查看数据库支持的存储引擎

```sql
show engines;
``` 
更改存储引擎

```sql
Alter table tableName engine =engineName
``` 

存储引擎

1. InnoDB
1. MRG_MYISAM
1. MEMORY
1. BLACKHOLE
1. MyISAM
1. CSV
1. ARCHIVE
1. PERFORMANCE_SCHEMA
1. FEDERATED

[MySQL存储引擎介绍](http://www.jellythink.com/archives/640)

## InnoDB

**事务**
InnoDB是一个健壮的事务型存储引擎

InnoDB还引入了行级锁定和外键约束，在以下场合下，使用InnoDB是最理想的选择：

1. 更新密集的表。InnoDB存储引擎特别适合处理多重并发的更新请求。
1. 事务。InnoDB存储引擎是支持事务的标准MySQL存储引擎。
1. 自动灾难恢复。与其它存储引擎不同，InnoDB表能够自动从灾难中恢复。
1. 外键约束。MySQL支持外键的存储引擎只有InnoDB。
1. 支持自动增加列AUTO_INCREMENT属性。

一般来说，如果需要事务支持，并且有较高的并发读取频率，InnoDB是不错的选择。

## MyISAM

MyISAM表无法处理事务，这就意味着有事务处理需求的表，不能使用MyISAM存储引擎。MyISAM存储引擎特别适合在以下几种情况下使用：

1. 选择密集型的表。MyISAM存储引擎在筛选大量数据时非常迅速，这是它最突出的优点。
1. 插入密集型的表。MyISAM的并发插入特性允许同时选择和插入数据。例如：MyISAM存储引擎很适合管理邮件1.或Web服务器日志数据。


## MEMORY

速度快,逻辑存储介质是系统内存

虽然在内存中存储表数据确实会提供很高的性能，但当mysqld守护进程崩溃时，所有的Memory数据都会丢失。获得速度的同时也带来了一些缺陷。它要求存储在Memory数据表里的数据使用的是长度不变的格式，这意味着不能使用BLOB和TEXT这样的长度可变的数据类型，VARCHAR是一种长度可变的类型，但因为它在MySQL内部当做长度固定不变的CHAR类型，所以可以使用。

一般在以下几种情况下使用Memory存储引擎：

1. 目标数据较小，而且被非常频繁地访问。在内存中存放数据，所以会造成内存的使用，可以通过参数max_heap_table_size控制Memory表的大小，设置此参数，就可以限制Memory表的最大大小。
1. 如果数据是临时的，而且要求必须立即可用，那么就可以存放在内存表中。
1. 存储在Memory表中的数据如果突然丢失，不会对应用服务产生实质的负面影响。

Memory同时支持散列索引和B树索引。

1. B树索引的优于散列索引的是，可以使用部分查询和通配查询，也可以使用<、>和>=等操作符方便数据挖掘。
1. 散列索引进行“相等比较”非常快，但是对“范围比较”的速度就慢多了，因此散列索引值适合使用在=和<>的操作符中，不适合在<或>操作符中，也同样不适合用在order by子句中。

- HASH散列索引

```sql
create table users
(
    id smallint unsigned not null auto_increment,
    username varchar(15) not null,
    pwd varchar(15) not null,
    index using hash (username),
    primary key (id)
)engine=memory;
```
- 使用BTREE索引

```sql
create table users
(
    id smallint unsigned not null auto_increment,
    username varchar(15) not null,
    pwd varchar(15) not null,
    index using btree (username),
    primary key (id)
)engine=memory;
```

## MERGE

说白了，Merge表就是几个相同MyISAM表的聚合器

MERGE存储引擎是一组MyISAM表的组合，这些MyISAM表结构必须完全相同，尽管其使用不如其它引擎突出，但是在某些情况下非常有用。

下面就通过一个简单的例子来说说如何建立引擎为merge类型的表。

- 先创建两个引擎为myisam（必须为myisam引擎）的表。

插入上述数据，然后创建merge表，进行merge操作。


```sql
create table tb_log1(
    id int unsigned not null auto_increment, 
    log varchar(45),
    primary key(id)) engine=myisam;

insert into tb_log1(log) values('tb_log1_1');
insert into tb_log1(log) values('tb_log1_2');
insert into tb_log1(log) values('tb_log1_3');
insert into tb_log1(log) values('tb_log1_4');
insert into tb_log1(log) values('tb_log1_5');

create table tb_log2(
    id int unsigned not null auto_increment,
    log varchar(45),
    primary key(id)) engine=myisam;

insert into tb_log2(log) values('tb_log2_1');
insert into tb_log2(log) values('tb_log2_2');
insert into tb_log2(log) values('tb_log2_3');
insert into tb_log2(log) values('tb_log2_4');
```

- 创建merge表

这样就得到了一个引擎为merge的表，并且合并了tb_log1和tb_log2两个表。查询tb_merge表，可以得到以下数据：

```sql
create table tb_merge(
    id int unsigned not null auto_increment, 
    log varchar(45), 
    primary key(id)
    )engine=merge 

union(tb_log1,tb_log2) insert_method=last;
```

1. ENGINE=MERGE
指明使用MERGE引擎，有些同学可能见到过ENGINE=MRG_MyISAM的例子，也是对的，它们是一回事

1. UNION=(t1, t2)
指明了MERGE表中挂接了些哪表，可以通过alter table的方式修改UNION的值，以实现增删MERGE表子表的功能。比如：

```sql
 alter table tb_merge engine=merge union(tb_log1) insert_method=last;
```

1. INSERT_METHOD=LAST
INSERT_METHOD指明插入方式，取值可以是：0 不允许插入；FIRST 插入到UNION中的第一个表； LAST 插入到UNION中的最后一个表。

1. MERGE表及构成MERGE数据表结构的各成员数据表必须具有完全一样的结构。每一个成员数据表的数据列必须按照同样的顺序定义同样的名字和类型，索引也必须按照同样的顺序和同样的方式定义。

## ARCHIVE

**归档**

Archive是归档的意思，在归档之后很多的高级功能就不再支持了，仅仅支持最基本的插入和查询两种功能。在MySQL 5.5版以前，Archive是不支持索引，但是在MySQL 5.5以后的版本中就开始支持索引了。Archive拥有很好的压缩机制，它使用zlib压缩库，在记录被请求时会实时压缩，所以它经常被用来当做仓库使用。

## [MySQL存储引擎](http://noalgo.info/1053.html)

## 如何选择最适合你的存储引擎呢

选择标准可以分为：是否需要支持事务；是否需要使用热备；崩溃恢复：能否接受崩溃；是否需要外键支持；
然后按照标准，选择对应的存储引擎即可:

1. MyISAM：默认的MySQL插件式存储引擎，它是在Web、数据仓储和其他应用环境下最常使用的MySQL存储引擎之一。注意，通过更改STORAGE_ENGINE配置变量，能够方便地更改MySQL服务器的默认存储引擎。
1. InnoDB：用于事务处理应用程序，具有众多特性，包括ACID事务支持。
1. BDB：可替代InnoDB的事务引擎，支持COMMIT、ROLLBACK和其他事务特性。
1. Memory：将所有数据保存在RAM中，在需要快速查找引用和其他类似数据的环境下，可提供极快的访问。
1. Merge：允许MySQL DBA或开发人员将一系列等同的MyISAM表以逻辑方式组合在一起，并作为1个对象引用它们。对于诸如数据仓储等VLDB环境十分适合。
1. Archive：为大量很少引用的历史、归档、或安全审计信息的存储和检索提供了完美的解决方案。
1. Federated：能够将多个分离的MySQL服务器链接起来，从多个物理服务器创建一个逻辑数据库。十分适合于分布式环境或数据集市环境。
1. Cluster/NDB：MySQL的簇式数据库引擎，尤其适合于具有高性能查找要求的应用程序，这类查找需求还要求具有最高的正常工作时间和可用性。
1. Other：其他存储引擎包括CSV（引用由逗号隔开的用作数据库表的文件），Blackhole（用于临时禁止对数据库的应用程序输入），以及Example引擎（可为快速创建定制的插件式存储引擎提供帮助）。

请记住，对于整个服务器或方案，你并不一定要使用相同的存储引擎，你可以为方案中的每个表使用不同的MySQL存储引擎，这点很重要。

## 各存储引擎之间的区别

- 字段和数据类型

虽然所有这些引擎都支持通用的数据类型，例如整型、实型和字符型等，但是，并不是所有的引擎都支持其它的字段类型，特别是BLOG(二进制大对象)或者TEXT文本类型。其它引擎也许仅支持有限的字符宽度和数据大小。

这些局限性可能直接影响到你可以存储的数据，同时也可能会对你实施的搜索的类型或者你对那些信息创建的索引产生间接的影响。这些区别能够影响你的应用程序的性能和功能，因为你必须要根据你要存储的数据类型选择对需要的存储引擎的功能做出决策。

- 锁定

数据库引擎中的锁定功能决定了如何管理信息的访问和更新。当数据库中的一个对象为信息更新锁定了，在更新完成之前，其它处理不能修改这个数据(在某些情况下还不允许读这种数据)。

锁定不仅影响许多不同的应用程序如何更新数据库中的信息，而且还影响对那个数据的查询。这是因为查询可能要访问正在被修改或者更新的数据。总的来说，这种延迟是很小的。大多数锁定机制主要是为了防止多个处理更新同一个数据。由于向数据中插入信息和更新信息这两种情况都需要锁定，你可以想象，多个应用程序使用同一个数据库可能会有很大的影响。

不同的存储引擎在不同的对象级别支持锁定，而且这些级别将影响可以同时访问的信息。得到支持的级别有三种:表锁定、块锁定和行锁定。支持最多的是表锁定，这种锁定是在MyISAM中提供的。在数据更新时，它锁定了整个表。这就防止了许多应用程序同时更新一个具体的表。这对应用很多的多用户数据库有很大的影响，因为它延迟了更新的过程。

页级锁定使用Berkeley DB引擎，并且根据上载的信息页(8KB)锁定数据。当在数据库的很多地方进行更新的时候，这种锁定不会出现什么问题。但是，由于增加几行信息就要锁定数据结构的最后8KB，当需要增加大量的行，也别是大量的小型数据，就会带来问题。

行级锁定提供了最佳的并行访问功能，一个表中只有一行数据被锁定。这就意味着很多应用程序能够更新同一个表中的不同行的数据，而不会引起锁定的问题。只有InnoDB存储引擎支持行级锁定。

-  建立索引

建立索引在搜索和恢复数据库中的数据的时候能够显著提高性能。不同的存储引擎提供不同的制作索引的技术。有些技术也许会更适合你存储的数据类型。
有些存储引擎根本就不支持索引，其原因可能是它们使用基本表索引(如MERGE引擎)或者是因为数据存储的方式不允许索引(例如FEDERATED或者BLACKHOLE引擎)。

- 事务处理

事务处理功能通过提供在向表中更新和插入信息期间的可靠性。这种可靠性是通过如下方法实现的，它允许你更新表中的数据，但仅当应用的应用程序的所有相关操作完全完成后才接受你对表的更改。例如，在会计处理中每一笔会计分录处理将包括对借方科目和贷方科目数据的更改，你需要要使用事务处理功能保证对借方科目和贷方科目的数据更改都顺利完成，才接受所做的修改。如果任一项操作失败了，你都可以取消这个事务处理，这些修改就不存在了。如果这个事务处理过程完成了，我们可以通过允许这个修改来确认这个操作。

## MyISAM与InnoDB的区别

虽然MySQL里的存储引擎不只是MyISAM与InnoDB这两个，但常用的就是它俩了,下面我们分别来看两种存储引擎的区别:

事务 外键 行锁

1. InnoDB支持事务，MyISAM不支持，这一点是非常之重要。事务是一种高级的处理方式，如在一些列增删改中只要哪个出错还可以回滚还原，而MyISAM就不可以了。
1. MyISAM适合查询以及插入为主的应用，InnoDB适合频繁修改以及设计到安全性就高的应用
1. InnoDB支持外键，MyISAM不支持
1. MyISAM是默认引擎，InnoDB需要指定
1. InnoDB不支持FULLTEXT类型的索引
1. InnoDB中不保存表的行数，如select count(*) from table时，InnoDB需要扫描一遍整个表来计算有多少行，但是MyISAM只要简单的读出保存好的行数即可。注意的是，当count(*)语句包含where条件时MyISAM也需要扫描整个表
1. 对于自增长的字段，InnoDB中必须包含只有该字段的索引，但是在MyISAM表中可以和其他字段一起建立联合索引
1. 清空整个表时，InnoDB是一行一行的删除，效率非常慢。MyISAM则会重建表
1. InnoDB支持行锁（某些情况下还是锁整表，如 update table set a=1 where user like ‘%lee%’


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

**在使用REPLACE时，表中必须有唯一索引，**而且这个索引所在的字段不能允许空值，否则REPLACE就和INSERT完全一样的。 

在执行REPLACE后，系统返回了所影响的行数，如果返回1，说明在表中并没有重复的记录，如果返回2，说明有一条重复记录，系统自动先调用了DELETE删除这条记录，然后再记录用INSERT来插入这条记录。如果返回的值大于2，那说明有多个唯一索引，有多条记录被删除和插入。 

REPLACE的语法和INSERT非常的相似，如下面的REPLACE语句是插入或更新一条记录。 

```sql
REPLACE INTO users (id,name,age) VALUES(123, '赵本山', 50); 
```

- 插入多条记录： 

```sql
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

## **having**使用

HAVING子句可以让我们筛选成组后的各组数据．WHERE子句在聚合前先筛选记录．也就是说作用在GROUP BY 子句和HAVING子句前．

而 HAVING子句在聚合后对组记录进行筛选。

- 显示每个地区的总人口数和总面积．

```sql
SELECT region, SUM(population), SUM(area)
FROM bbc
GROUP BY region
```

- 显示每个地区的总人口数和总面积．仅显示那些面积超过1000000的地区。

**HAVING**使用

```sql
SELECT region, SUM(population), SUM(area)
FROM bbc
GROUP BY region
HAVING SUM(area)>1000000
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




# sql 语句练习

[经典数据库SQL语句编写练习](http://tianbin.leanote.com/post/%E7%BB%8F%E5%85%B8%E6%95%B0%E6%8D%AE%E5%BA%93SQL%E8%AF%AD%E5%8F%A5%E7%BC%96%E5%86%99%E7%BB%83%E4%B9%A0%E9%A2%98%E2%80%94%E2%80%94SQL%E8%AF%AD%E5%8F%A5%E6%89%AB%E7%9B%B2)


![](http://7xr7ju.com1.z0.glb.clouddn.com/image/2cde884b-1.png)


## 建表语句

```sql
 use test;  
    create table student  
    (  
        SNO varchar(20) primary key,  
        SNAME varchar(20) character set gbk,  
        AGE int,  
        SEX  char(2) character set gbk CHECK(SEX IN('男','女'))   
    );  
    insert into student values('1','李强',23,'男');  
    insert into student values('2','刘丽',22,'女');  
    insert into student values('5','张友',22,'男');  
    create table course  
    (  
        CNO varchar(20) primary key,  
        CNAME varchar(20) character set gbk,  
        TEACHER varchar(20) character set gbk  
    );  
    insert into course values('K1','C语言','王华');  
    insert into course values('K5','数据库原理','程军');  
    insert into course values('K8','编译原理','程军');  
    create table sc  
    (  
        SNO varchar(20) NOT NULL,  
        CNO varchar(20) NOT NULL,  
        SCORE int NOT NULL,  
        primary key (SNO,CNO),  
        foreign key (SNO) references student(SNO),  
        foreign key (CNO) references course(CNO)  
    );  
    insert into sc values('1','K1',83);  
    insert into sc values('2','K1',85);  
    insert into sc values('5','K1',92);  
    insert into sc values('2','K5',90);  
    insert into sc values('5','K5',84);  
    insert into sc values('5','K8',80);  
```

- 查询“李强”同学所有课程的成绩；

```sql
  SELECT score FROM sc
    WHERE SNO = 
    ( SELECT SNO FROM student WHERE SNAME="李强"
    )
    //优化：
    SELECT s.SNAME,sc.SCORE FROM student s, sc 
    WHERE s.SNO=sc.SNO AND s.SNAME="李强"
```

- 查询课程名为“C语言”的平均成绩；

```sql
 SELECT AVG(score) FROM sc,course c WHERE sc.CNO=c.CNO AND c.CNAME="C语言"
```

- 检索至少选修王老师所授课程中一门课程的女学生姓名。

```sql
SELECT SNAME FROM student
    WHERE SEX="女" AND SNO in
    ( SELECT DISTINCT SNO FROM sc,course c WHERE sc.CNO=c.CNO AND c.teacher LIKE "王%"
    )
```

- 检索选修课程包含王老师所授课的学生学号。

```sql
 SELECT s.SNO FROM student s
    WHERE s.SNO IN
    ( SELECT sc.SNO FROM sc,course c
        WHERE sc.CNO=c.CNO AND c.TEACHER LIKE "王%"
    )
    //优化
    SELECT DISTINCT sno FROM sc  
    WHERE cno IN  
    (  
        SELECT cno FROM course  
        WHERE teacher LIKE '王%'  
    );  
```
- 统计所有学生选修的课程门数。

```sql
SELECT count(c.CNO) FROM course c
    WHERE c.CNO IN
    ( SELECT DISTINCT sc.CNO FROM sc
    )
    //优化
    SELECT count(*)  NumberOfCourse  
    FROM   
    (  
          SELECT DISTINCT cno FROM sc  
          GROUP BY cno  
    ) AS testTab;  
```

- 检索姓名为两个字，且姓张的学生的姓名和年龄。

```sql
 SELECT s.SNAME,s.AGE FROM student s WHERE s.SNAME LIKE "张_"
```

- 在SC中检索成绩为空值的学生学号和课程号。

```sql
SELECT sno,cno FROM sc WHERE score IS NULL;  
```

## HAVING

- 检索至少选修程老师所授课程中两门课程的女学生姓名。

```sql
  SELECT s.SNAME FROM student s
    WHERE s.SEX="女" AND s.SNO IN
    ( SELECT sc.SNO FROM sc,course c WHERE sc.CNO=c.CNO AND c.TEACHER LIKE "程%"
    GROUP BY sc.CNO
    HAVING COUNT(sc.CNO)>1
    )
```

- 检索选修不少于3门课程的学生学号(SNO)；

```sql
SELECT SNO FROM sc
    GROUP BY SNO
    HAVING COUNT(CNO)>=3
```

- 检索至少选修两门课程的学生学号。

```sql
    SELECT sc.SNO FROM sc 
    GROUP BY sc.sNO
    HAVING COUNT(sc.CNO)>=2
```

- 检索全部学生都选修的课程的课程号与课程名。**

```sql
SELECT c.CNO,c.CNAME FROM course c
    WHERE c.CNO =
    ( SELECT sc.CNO FROM sc
        GROUP BY sc.CNO
        HAVING COUNT(sc.SNO)=(SELECT COUNT(s.SNO) FROM student s)
    )
```

## IN

- 求选修K1课程的学生的平均年龄。

```sql
SELECT avg(s.AGE) FROM student s,sc
    WHERE s.SNO=sc.SNO AND sc.CNO="K1"
    //优化
    SELECT AVG(age) AverageOfAge  
    FROM student   
    WHERE sno IN  
    (  
        SELECT sno FROM sc  
        WHERE cno='K1'  
    );  
```
- 检索李同学不学的课程的课程号。

```sql
SELECT c.CNO FROM course c
    WHERE c.CNO NOT IN
    ( SELECT sc.CNO FROM sc,student s WHERE sc.SNO=s.SNO AND s.SNAME LIKE "李%"
    )
```
- 检索＂李强＂同学不学课程的课程号(CNO)；

```sql
    select course.cno from course  
    where course.cno not in  
    (  
    select sc.cno from sc,student  
    where student.sname='李强' and student.sno=sc.sno  
    );  
    //优化：
    SELECT CNO FROM course
    WHERE EXISTS
    ( SELECT * FROM student WHERE SNAME="李强" AND NOT EXISTS
        ( SELECT * FROM sc WHERE sc.CNO=course.CNO  AND sc.SNO=student.SNO
        )
    )
```
- 程老师所授课程的每门课程的学生平均成绩。

```sql
  SELECT sc.cno,AVG(sc.score)  
    FROM sc  
    WHERE sc.cno IN  
    (  
    SELECT course.cno FROM course  
    WHERE course.teacher LIKE '程%'  
    )  
    GROUP BY sc.cno  
    //优化
    SELECT c.CNAME,avg(sc.SCORE) FROM sc,course c
    WHERE sc.CNO=c.CNO AND c.TEACHER LIKE "程%"
    GROUP BY sc.CNO
```

## [关于 EXISTS和NOT EXISTS](http://blog.csdn.net/qsyzb/article/details/12523051)

EXISTS代表存在量词∃。带有EXISTS谓词的子查询不返回任何数据，只产生逻辑真值“true”或者逻辑假值“false”。

使用存在量词EXISTS后，若内层查询结果为非空，则外层的WHERE子句返回值为真，否则返回值为假。

- 要求：查询选修了课程”操作系统“的同学


```sql
SELECT Sname FROM student  
WHERE EXISTS  
(SELECT * FROM sc,course 
   WHERE Sno=student.Sno AND sc.Cno=course.Cno AND course.Cname="操作系统")  
```
本例中的子查询的查询条件依赖于外层父查询的某个属性值（本例中的是Student的Sno值），这个相关子查询的处理过程是：

1. 首先取外层查询中（student）表的第一个元组，根据它与内层查询相关的属性值（Sno值）处理内层查询，若外层的WHERE返回为真，则取外层查询中该元组的Sname放入结果表；
2. 然后再取（student）表的下一组，重复这一过程，直至外层（Student）表全部检查完毕。
查询结果表：

- NOT EXISTS

与EXISTS谓词相对的是NOT EXISTS谓词。使用存在量词NOT EXISTS后，若对应查询结果为空，则外层的WHERE子语句返回值为真值，否则返回假值。

- 要求：查询选修了全部课程的学生姓名。

```sql
SELECT Sname  
FROM Student   
WHERE NOT EXISTS  
(SELECT * FROM Course WHERE NOT EXISTS  
     (SELECT * FROM SC WHERE Sno=Student.Sno AND Cno=Course.Cno)  
);  
```

这个算是一个比较复杂的sql语句了，两个EXISTS和三个WHERE。

这个sql语句可以分为3层，最外层语句，最内层语句，中间层语句.

我们很关心最外层语句，因为结果表中的数据都是最外层的查询的表中的数据，我们更关心最内层的数据，因为最内层的数据包含了全部的判断语句，决定了student表中的那一条记录是我们查询的记录。
我们由内而外进行分析：

最外层的student表中的第一条记录是李勇同学对应的记录，然后中间层的course表的第一条记录是数据库对应的记录，然后对该数据进行判断（最内层的WHERE语句），结果返回真，则内层的NOT EXISTS为假，
然后继续对course表中的下一条记录进行判断，返现NOT EXISTS的值也为假，直到遍历完course表中的所有的数据，内层的NOT EXISTS的值一直都是假，所以中间层的WHERE语句的值也一直都是假。

对应student的李勇记录，course表中的所有的记录对应的中间层的返回值为假，所以最外层的NOT EXISTS对应的值为真，最外层的WHERE的值也为真，则李勇对应的记录符合查询条件，装入结果表中。

然后继续对student表中的下一条记录进行判断，直达student表中的所有数据都遍历完毕。
查询结果表：


- 检索至少选修＂程军＂老师所授全部课程的学生姓名（SNAME） 
（或：检索选修了“程军”老师所授全部课程的学生姓名）

```sql
   SELECT sname FROM student
    WHERE NOT EXISTS
    ( SELECT * FROM course WHERE TEACHER="程军" AND NOT EXISTS
        ( SELECT * FROM sc WHERE sc.CNO=course.CNO  AND sc.SNO=student.SNO
        )
    )
```

- 检索选修全部课程的学生姓名(SNAME)。

```sql
  SELECT SNAME FROM student
    WHERE NOT EXISTS
    ( SELECT * FROM course WHERE NOT EXISTS
        ( SELECT * FROM sc WHERE sc.SNO=student.SNO AND sc.CNO=course.CNO
        )
    )
```
- 检索不学”C语言”的学生信息

```sql
 SELECT * FROM student  
    WHERE EXISTS
    ( SELECT * FROM course WHERE cname="C语言" AND NOT EXISTS
        ( SELECT * FROM sc WHERE sc.CNO=course.CNO AND sc.SNO=student.SNO
        )
    )
```

## 嵌套查询

- 统计每门课程的学生选修人数（超过2人的课程才统计）。要求输出课程号和选修人数，查询结果按人数降序排列，若人数相同，按课程号升序排列。

```sql
SELECT cno,COUNT(SNO) AS num FROM sc 
GROUP BY cno
HAVING COUNT(sno)>=2
ORDER BY num DESC, cno ASC
//优化
SELECT cno,Num  
FROM   
(  
	SELECT cno,count(*) as Num  
	FROM sc  
	GROUP BY cno HAVING (count(*) >= 2)  
) tb_temp  
ORDER BY Num DESC,cno ASC  
```

- 检索学号比李同学大，而年龄比他小的学生姓名。

```sql
SELECT s.sname 
FROM student s,(SELECT MAX(sno) snoLi,MIN(age) ageLi FROM student WHERE sname LIKE "李%") AS stuLi
WHERE s.sno>stuLi.snoLi AND s.age<stuLi.ageLi
```

- 求年龄大于女同学平均年龄的男学生姓名和年龄。

```sql
SELECT s.SNAME,s.AGE FROM student s,(SELECT AVG(age) avgAge FROM student WHERE SEX="女") AS FeStu
WHERE s.AGE>FeStu.avgAge
    //优化
SELECT sname,age FROM student  
WHERE  
sex='男' AND age > (  
    SELECT AVG(age)  
    FROM student  
    WHERE sex='女'  
);  
```

- 检索学号比李同学大，而年龄比他小的学生姓名。

```sql
    SELECT s.sname 
    FROM student s,(SELECT MAX(sno) snoLi,MIN(age) ageLi FROM student WHERE sname LIKE "李%") AS stuLi
    WHERE s.sno>stuLi.snoLi AND s.age<stuLi.ageLi
```


