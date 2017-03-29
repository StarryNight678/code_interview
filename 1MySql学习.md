# MySql 学习

## 问题

存在记录则删除,没有记录则创建

- 启动

mysql -u 用户名 -p密码

注意**-p与密码间不能存在空格**


mysql -u 用户名 -p

则会提示输入密码


- 退出 

quit /exit

- 显示数据库

show databases;
drop database name;
create database name;

- 指定使用的数据库 

use db_name;

- 查看指定的数据库 

select database();

- 创建新表

数据类型

MySQL数据类型	| 含义（有符号）
---|  ----
tinyint(m)	|1个字节  范围(-128~127)
smallint(m)|	2个字节  范围(-32768~32767)
mediumint(m)|	3个字节  范围(-8388608~8388607)
int(m)	|4个字节  范围(-2147483648~2147483647)
bigint(m)|	8个字节  范围(+-9.22*10的18次方)

int(m)里的m是表示SELECT查询结果集中的显示宽度，并不影响实际的取值范围，没有影响到显示的宽度，不知道这个m有什么用


浮点型	| 含义
---|  ----
float(m,d)	|单精度浮点型     8位精度(4字节)     m总个数，d小数位
double(m,d)	| 双精度浮点型    16位精度(8字节)    m总个数，d小数位

取值范围如果加了unsigned，则最大值翻倍，如tinyint unsigned的取值范围为(0~256)。




字符串(char,varchar,_text)


MySQL数据类型	| 含义
---|  ----
char(n)	| 固定长度，最多255个字符
varchar(n)	| 固定长度，最多65535个字符
tinytext	| 可变长度，最多255个字符
text	| 可变长度，最多65535个字符
mediumtext	| 可变长度，最多2的24次方-1个字符
longtext| 	可变长度，最多2的32次方-1个字符

create tablse 表名 (



);


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


- 显示表的详细信息

show tables;

- 显示表结构

desc tablename;

- 删除表

drop table  表名;

- 数据产生如和显示

insert 表名 (列名) values();

mysql> insert S (sno,sname) values(4,'test');

select * from S;

- 创建表

- 更新

update 表名 set 列名=值1  where 表达式;

- 删除

delete from where 表达式;

- 检索

select  列名1 ,列名2 from 表名 [表达式];

```
like
is null
in
between 
```

- 多条件组合

select * from where 条件1 and 条件2;

select * from where 条件1 or 条件2;

理论运算符

运算符优先顺序.

NOT -> AND -> OR

- 结果排序

order by age DESC;

升序ASC,降序DESC

Mysql将NULL当成最小值.

指定数量,limt要与order by同时使用.

order by age DESC limt 2;

- 数据分组


select  sex  count() from group sex;


统计函数

```
avg
count
max
min
sum
```

mysql> select sdep,count(sno),max(sage)  from S group by sdep;

进行 group by,其他列选择只能是count等统计函数.

count只统计非NULL记录.


- Case函数

通过Case函数进行简单的条件判断

case 表达式
	when 比较值1 then 结果1
	when 比较值2 then 结果1
	esle 结果 N
end


- 多个表连接

内连接

inner join ... on

select 列名1  from 表1 
inner join 表2
on 表1.外键=表2.键值
where/order by


外链接

select 列名1  from 表1 
left outer join  表2
on 表1.外键=表2.键值
where/order by


















