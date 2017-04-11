# Mysql技术内幕InnoDB存储引擎

## 各存储引擎间比较
- 性能:

innodDb上存储超过1T数据,处理插入更新操作大约800次每秒.

## InnoDB存储引擎

1. 第一个完整支持ACID
1. 行锁设计
1. MVCC: Multi-Version Concurrency Control 多版本并发控制
1. 外键
1. 一致性非锁定读

数据库的应用类型分为

1. OLTP(OnLine Transaction Processing ，联机事务处理)
1. OLAP(OnLine Analysis Processing，联机分析处理)两种。

OLTP是传统关系型数据库的主要应用，其主要面向基本的、日常的事务处理，例如银行交易。

OLAP是数据仓库系统的主要应用，支持复杂的分析操作，侧重决策支持，并且提供直观易懂的查询结果。

![](http://image20.it168.com/201207_500x375/1111/4070a8d25582419d.jpg)

## 文件
## 表
## 索引与算法

- InnoDB索引类型

1. B+树索引
1. 全文索引
1. 哈希索引



## 锁
## 事务
## 备份与恢复
## 性能调优