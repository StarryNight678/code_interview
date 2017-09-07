# shell 命令

## uniq


文字
uniq 是LINUX命令
用途
报告或删除文件中重复的行。
语法

uniq [ -c | -d | -u ] [ -f Fields ] [ -s Characters ] [ -Fields ] [ +Characters ] [ InFile [ OutFile ] ]

描述
uniq 命令删除文件中的重复行。
uniq 命令读取由 InFile 参数指定的标准输入或文件。该命令首先比较相邻的行，然后除去第二行和该行的后续副本。重复的行一定相邻。（在发出 uniq 命令之前，请使用 sort 命令使所有重复行相邻。）最后，uniq 命令将最终单独的行写入标准输出或由 OutFile 参数指定的文件。InFile 和 OutFile 参数必须指定不同的文件。如果输入文件用“- ”表示，则从标准输入读取；输入文件必须是文本文件。文本文件是包含组织在一行或多行中的字符的文件。这些行的长度不能超出 2048 个字节（包含所有换行字符），并且其中不能包含空字符。
缺省情况下，uniq 命令比较所有行。如果指定了-f Fields 或 -Fields 标志, uniq 命令忽略由 Fields 变量指定的字段数目。 field 是一个字符串，用一个或多个 <空格 > 字符将它与其它字符串分隔开。
如果指定了 -s Characters 或 -Characters 标志, uniq 命令忽略由 Characters 变量指定的字段数目。为 Fields 和 Characters 变量指定的值必须是正的十进制整数。
当前本地语言环境决定了 -f 标志使用的 <空白> 字符以及 -s 标志如何将字节解释成字符。
如果执行成功，uniq 命令退出，返回值 0。否则，命令退出返回值大于 0。
标志
-c 在输出行前面加上每行在输入文件中出现的次数。
-d 仅显示重复行。
-u 仅显示不重复的行。
-f Fields 忽略由 Fields 变量指定的字段数目。如果 Fields 变量的值超过输入行中的字段数目, uniq 命令用空字符串进行比较。这个标志和 -Fields 标志是等价的。
-s Characters 忽略由 Characters 变量指定的字符的数目。如果 Characters 变量的值超过输入行中的字符的数目, uniq 用空字符串进行比较。如果同时指定 -f 和 -s 标志, uniq 命令忽略由 -s Characters 标志指定的字符的数目，而从由 -f Fields 标志指定的字段后开始。 这个标志和 +Characters 标志是等价的。
-Fields 忽略由 Fields 变量指定的字段数目。这个标志和 -f Fields 标志是等价的。
+Characters 忽略由 Characters 变量指定的字符的数目。如果同时指定 - Fields 和 +Characters 标志, uniq 命令忽略由 +Characters 标志指定的字符数目，并从由 -Fields 标志指定的字段后开始。 这个标志和 -s Characters 标志是等价的。
- c 显示输出中，在每行行首加上本行在文件中出现的次数。它可取代- u和- d选项。
- d 只显示重复行 。
- u 只显示文件中不重复的各行 。
- n 前n个字段与每个字段前的空白一起被忽略。一个字段是一个非空格、非制表符的字符串，彼此由制表符和空格隔开（字段从0开始编号）。
+ n 前n个字符被忽略，之前的字符被跳过（字符从0开始编号）。
- f n 与- n相同，这里n是字段数。
- s n 与＋n相同，这里n是字符数。
退出状态
该命令返回以下退出值：
0 命令运行成功。
>0 发生错误。
补充
文件经过处理后在它的输出文件中可能会出现重复的行。例如，使用cat命令将两个文件合并后，再使用sort命令进行排序，就可能出现重复行。这时可以使用uniq命令将这些重复行从输出文件中删除，只留下每条记录的唯一样

## sort

用法：sort [选项]... [文件]...
串联排序所有指定文件并将结果写到标准输出。

排序选项：

-b, --ignore-leading-blanks	忽略前导的空白区域
-d, --dictionary-order	只考虑空白区域和字母字符
-f, --ignore-case	忽略字母大小写
-g, --general-numeric-sort	按照常规数值排序
-i, --ignore-nonprinting	只排序可打印字符
-n, --numeric-sort	根据字符串数值比较
-r, --reverse	逆序输出排序结果

## 例題

给一个超过100G大小的log file, log中存着IP地址, 设计算法找到出现次数最多的IP地址？
与上题条件相同，如何找到top K的IP？如何直接用Linux系统命令实现？
参考答案

Hash分桶法： 
• 将100G文件分成1000份，将每个IP地址映射到相应文件中：file_id = hash(ip) % 1000 
• 在每个文件中分别求出最高频的IP，再合并 Hash分桶法： 
• 使用Hash分桶法把数据分发到不同文件 
• 各个文件分别统计top K 
• 最后Top K汇总 
Linux命令，假设top 10：sort log_file | uniq -c | sort -nr k1,1 | head -10