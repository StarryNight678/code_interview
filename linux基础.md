# Linux知识

[Linux 系统管理员面试常见的30个问题与答案](https://linuxstory.org/top-30-linux-system-administrator-interview-questions-and-answers/)

- 问: Linux系统中的/proc文件系统有什么用？
答: /proc文件系统是一个基于内存的文件系统，其维护着关于当前正在运行的内核状态信息，其中包括CPU、内存、分区划分、I/O地址、直接内存访问通道和正在运行的进程。这个文件系统所代表的并不是各种实际存储信息的文件，它们指向的是内存里的信息。/proc文件系统是由系统自动维护的。

- 如何在/usr目录下找出大小超过10MB的文件？

	find /usr -size +10M
如何在/home目录下找出120天之前被修改过的文件？
	find /home -mtime +120

- 为什么 LVM 是必需的？
LVM 的意思是逻辑卷管理器，它可以帮助我们根据文件系统的大小重新在线调整 Linux 中的 LVM 分区的大小。我们可以分别使用 lvextend 和 lvreduce 命令来增加或减小 LVM 分区的大小。

- 如何内存和 CPU 的统计数据？
我们可以分别使用 ‘free’ 和 ‘vmstat’ 命令来查看物理内存和虚拟内存的统计数据。使用 ‘sar’ 命令，我们可以看到 CPU 使用率以及其他资料。

- 如何从原始磁盘创建分区？
使用 fdisk，我们可以从原始磁盘创建分区。下面是具体步骤：
–fdisk  /dev/hd* (IDE) 或者 /dev/sd* (SCSI)
输入n来创建一个新分区
创建分区之后，输入w命令来保存磁盘分区信息。

- 什么是umask?
umask 意思是“用户文件创建掩码”，这决定了一个掩码控制哪些文件的权限在文件和目录被创建的时候。
读(4)+写(2)＋执行(1)  gid/uid,属主，组权，其它用户的权限

- 如何改变Linux中默认的运行级别？
为了改变运行级别，我们必须编辑“/etc/inittab”文件，并且改变默认的运行等级（id:5:initdefault:），使用‘init’命令，我们改变当前的运行级别。例如：‘init 3’，这个命令将会把系统的运行级别改为第三级。

- 如何检查并挂载 nfs 共享？
使用 ‘showmount’ 命令，我们可以看到有哪些目录通过 nfs 被共享了，例如：‘showmount -e <ip address of nfs server>’。使用 mount 命令，我们能够在 Linux 上挂载 nfs 共享。
mount -t auto /dev/cdrom /mnt/cdrom

- SMTP, DNS, FTP, DHCP, SSH 和 squid 使用的默认端口号是哪些？

服务               端口号

1. SMTP                25
1. DNS                 53
1. FTP                  20（数据传输），21（建立连接）
1. DHCP                67/UDP（dhcp 服务端），68/UDP（dhcp 客户端）
1. SSH                 22
1. Squid               3128


- 什么是网络绑定？
网络绑定是将多个 LAN 卡聚合在一起形成一个单一的绑定接口，来提供容错性和高性能。网络绑定也被叫做NIC Teaming。

- 如何检查哪些端口正在监听我的 Linux 服务器？
使用 ‘netstat -l’ 和 ‘lsof -i’ 命令

- 列出在一个特定的运行级别上，Linux 服务器所启动的服务。
使用chkconfig --list | grep 5:on命令，我们可以列出在运行级别5上启动的服务。查看其他运行级别是，只要将5换成对应的级别。
如何在一个特定的运行级别上启动服务？
我们可以使用类似 chkconfig <Service-Name> on –level 3 的命令。

- 什么是Puppet 服务器？
Puppet 是一个开源和企业软件，用来配置管理 UNIX 中的 toll 如操作系统。Puppet是一个自动化软件，使用代码推送配置到他的客户端（puppet 代理）。Puppet 代码可以完了各种任务，从安装新软件到检查文件权限，或者更新用户账户以及很多其他任务。
Puppet 中的 manifests 是什么？
Puppet 中的 mainfests 是指定客户端配置的文件。
在 Puppet 服务器中哪一个命令用于给请求的证书签名？
在2.x中使用 ‘puppetca  –sign hostname-of-agent’ 
在3.x中使用 ‘puppet ca  sign hostname-of-agent’

- 如何在目录中找到所有的常规文件？
使用命令 find /<directory -type f

- 在 Linux 中什么是平均负载？
平均负载被定义为在1分钟，5分钟和15分钟内等待在运行队列中的进程数目和当前正在执行的进程数目之和的平均值。使用 ‘top’ 和 ‘uptime’ 命令我们可以查询一个 Linux 服务器的平均负载。




[Linux运维工程师：30道面试题整理](https://zhangge.net/1986.html)


- 查看当前系统每个IP的连接数

	netstat -n | awk '/^tcp/ {print $5}'|

- ps aux 中的VSZ代表什么意思，RSS代表什么意思

VSZ:虚拟内存集,进程占用的虚拟内存空间
RSS:物理内存集,进程战用实际物理内存空间

- Linux系统的开机启动顺序

加载BIOS–>读取MBR–>Boot Loader–>加载内核–>用户层init一句inittab文件来设定系统运行的等级(一般3或者5，3是多用户命令行，5是界面)–>init进程执行rc.syninit–>启动内核模块–>执行不同级别运行的脚本程序–>执行/etc/rc.d/rc.local(本地运行服务)–>执行/bin/login,就可以登录了。


- 符号链接与硬链接的区别

我们可以把符号链接，也就是软连接 当做是 windows系统里的 快捷方式。
硬链接 就好像是 又复制了一份.
ln 3.txt 4.txt   这是硬链接，**相当于复制**，不可以跨分区，但**修改3,4会跟着变**，若删除3,4不受任何影响。
ln -s 3.txt 4.txt  这是软连接，相当于**快捷方式**。修改4,3也会跟着变，若删除3,4就坏掉了。不可以用了。

- 保存当前磁盘分区的分区表

dd 命令是以个强大的命令，在复制的同时进行转换

	 dd if=/dev/sda of=./mbr.txt bs=1 count=512

- 修改内核参数

	vi /etc/sysctl.conf  这里修改参数
	sysctl -p  刷新后可用

- FTP的主动模式和被动模式

FTP协议有两种工作方式：PORT方式和PASV方式，中文意思为主动式和被动式。
PORT（主动）方式的连接过程是：客户端向服务器的FTP端口（默认是21）发送连接请 求，服务器接受连接，建立一条命令链路。当需要传送数据时，客户端在命令链路上用PORT 命令告诉服务器：“我打开了XX端口，你过来连接我”。于是服务器从20端口向客户端的 XX端口发送连接请求，建立一条数据链路来传送数据。
PASV（被动）方式的连接过程是：客户端向服务器的FTP端口（默认是21）发送连接请 求，服务器接受连接，建立一条命令链路。当需要传送数据时，服务器在命令链路上用PASV 命令告诉客户端：“我打开了XX端口，你过来连接我”。于是客户端向服务器的XX端口 发送连接请求，建立一条数据链路来传送数据。
从上面可以看出，两种方式的命令链路连接方法是一样的，而数据链路的建立方法就完 全不同。

[Linux 面试基础问题 - 2](https://linux.cn/article-2370-1.html)

1. Linux 命令的正确语法是, Command [选项] [参数]。
1. 查看内核日志信息 	dmesg
1. 识别文件类型  	type
1. 找一条命令的二进制文件、源和手册的所在的路径 whereis
1. 默认用户配置,`.profile`和`.bashrc`
1. 配置环境变量 `export PATH=XX:$PATH`和`export LD_LIBRARY_PATH=XX:$LD_LIBRARY_PATH`
1. pci 设备的厂商和版本  `lspci`
全部磁盘块由四个部分组成，分别为引导块 、专用块 、 i节点表块 和数据存储块。
设定限制用户使用磁盘空间的命令是 quota 。

[搜狐linux工程师面试题](http://www.wuhanios.com/xueyuanjiuye/mianshishiti/17.html)

1. 查看Linux系统当前单个共享内存段的最大值（命令） 什么是共享内存？

采用共享内存通信的一个显而易见的好处是效率高，因为进程可以直接读写内存，而不需要任何数据的拷贝。对于像管道和消息队列等通信方式，则需要在内核和用户空间进行四次的数据拷贝，而共享内存则只拷贝两次数据[1]：一次从输入文件到共享内存区，另一次从共享内存区到输出文件。实际上，进程之间在共享内存时，并不总是读写少量数据后就解除映射，有新的通信时，再重新建立共享内存区域。而是保持共享区域，直到通信完毕为止，这样，数据内容一直保存在共享内存中，并没有写回文件。共享内存中的内容往往是在解除映射时才写回文件的。因此，采用共享内存的通信方式效率是非常高的。

Linux的2.2.x内核支持多种共享内存方式，如mmap()系统调用，Posix共享内存，以及系统V共享内存。linux发行版本如Redhat 8.0支持mmap()系统调用及系统V共享内存，但还没实现Posix共享内存，本文将主要介绍mmap()系统调用及系统V共享内存API的原理及应用。

```
jason@jason-HP:~/code$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00000000 655360     jason      600        524288     2          dest         
0x00000000 753665     jason      600        16777216   2                       
0x00000000 557058     jason      600        524288     2          dest

```

## 待续ing

2. 用什么命令查询指定IP地址的服务器端口

3. crontab中用什么命令定义某个程序执行的优先级别 
 
4. 如何让history命令显示具体时间

5. 查看Linux系统当前指定用户的邮件队列

6. 查看Linux系统当前加载的库文件

7. Ext3文件系统如何恢复RM命令删除文件 8.查看当前系统某一硬件的驱动版本.比如网卡 ehtool –i eth0

9. DNS服务器有哪三种类型 

10. apache目录访问身份验证的实施步骤（用htpasswd设置）

11. 使用tcpdump监听主机IP为192.168.1.1,tcp端口为80的数据,写出相应命令

12. 简述IDS作用和实现原理入侵检测

13. 用sed修改test.txt的23行test为tset；


[鸟哥的 Linux 私房菜 -- 基础学习篇目录](http://cn.linux.vbird.org/linux_basic/linux_basic.php)





## shell编程






## 命令整理

- netstat命令

```
常见参数
-a (all)显示所有选项，默认不显示LISTEN相关
-t (tcp)仅显示tcp相关选项
-u (udp)仅显示udp相关选项
-n 拒绝显示别名，能显示数字的全部转化成数字。
-l 仅列出有在 Listen (监听) 的服務状态

-p 显示建立相关链接的程序名
-r 显示路由信息，路由表
-e 显示扩展信息，例如uid等
-s 按各个协议进行统计
-c 每隔一个固定时间，执行该netstat命令。

提示：LISTEN和LISTENING的状态只有用-a或者-l才能看到
```

- ps 命令

```
-a 显示所有当前进程
-u 特定用户进程
c 显示进程的真实名称
f 显示程序间的关系
u 指定用户的所有进程
-au 显示较详细的资讯
-aux 显示所有包含其他使用者的行程
-C<命令> 列出指定命令的状况
–help 显示帮助信息
–version 显示版本显示
```

- wc

```
-c 统计字节数。
-l 统计行数。
-m 统计字符数。这个标志不能与 -c 标志一起使用。
-w 统计字数。一个字被定义为由空白、跳格或换行字符分隔的字符串。
-L 打印最长行的长度。
-help 显示帮助信息
--version 显示版本信息

```

- dd

```
if =输入文件（或设备名称）。 
of =输出文件（或设备名称）。 
例1：要把一张软盘的内容拷贝到另一张软盘上，利用/tmp作为临时存储区。把源盘插入驱动器中，输入下述命令： 

$ dd if =/dev/fd0 of = /tmp/tmpfile 
拷贝完成后，将源盘从驱动器中取出，把目标盘插入，输入命令： 

$ dd if = /tmp/tmpfile of =/dev/fd0 

```


- quota 限制用户磁盘空间

 quota 这支程式的限制内容主要分为底下几个部分：
soft：这是最低限制容量的意思，使用者在宽限期间之内，他的容量可以超过soft ，但必需要宽限时间之内将磁碟容量降低到soft的容量限制之下！
hard：这是『绝对不能超过』的容量！跟soft相比的意思为何呢？通常hard limit会比soft limit为高，例如网路磁碟空间为30 MB ，那么hard limit就设定为30MB ，但是为了让使用者有一定的警戒心，所以当使用空间超过25 MB时，例如使用者使用了27 MB的空间时，那么系统就会警告使用者，让使用者可以在『宽限时间内』将他的档案量降低至25 MB (亦即是soft limit )之内！也就是说， soft到hard之间的容量其实就是宽限的容量啦！可以达到针对使用者的『警示』作用！
宽限时间：那么宽限时间就可以很清楚的知道含意是什么了！也就是当您的使用者使用的空间超过了soft limit ，却还没有到达hard limit时，那么在这个『宽限时间』之内，就必需要请使用者将使用的磁碟容量降低到soft limit之下！而当使用者将磁碟容量使用情况超过soft limit时，『宽限时间』就会自动被启动，而在使用者将容量降低到soft limit之下，那么宽限时间就会自动的取消啰！

```
[asc16@su01 ~]$ quota -sv
Disk quotas for user asc16 (uid 657): 
     Filesystem  blocks   quota   limit   grace   files   quota   limit   grace
   io01:/export  81032M    512G   1024G            438k       0       0        
[asc16@su01 ~]$ 
```



















