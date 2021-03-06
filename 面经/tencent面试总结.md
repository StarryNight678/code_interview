# 面试需要知识准备

## 一致性哈希

致性hash算法提出了在动态变化的Cache环境中，判定哈希算法好坏的四个定义：

1. 平衡性(Balance)：平衡性是指哈希的结果能够尽可能分布到所有的缓冲中去，这样可以使得所有的缓冲空间都得到利用。很多哈希算法都能够满足这一条件。
2. 单调性(Monotonicity)：单调性是指如果已经有一些内容通过哈希分派到了相应的缓冲中，又有新的缓冲加入到系统中。哈希的结果应能够保证原有已分配的内容可以被映射到原有的或者新的缓冲中去，而不会被映射到旧的缓冲集合中的其他缓冲区。 
3. 分散性(Spread)：在分布式环境中，终端有可能看不到所有的缓冲，而是只能看到其中的一部分。当终端希望通过哈希过程将内容映射到缓冲上时，由于不同终端所见的缓冲范围有可能不同，从而导致哈希的结果不一致，最终的结果是相同的内容被不同的终端映射到不同的缓冲区中。这种情况显然是应该避免的，因为它导致相同内容被存储到不同缓冲中去，降低了系统存储的效率。分散性的定义就是上述情况发生的严重程度。好的哈希算法应能够尽量避免不一致的情况发生，也就是尽量降低分散性。 
4. 负载(Load)：负载问题实际上是从另一个角度看待分散性问题。既然不同的终端可能将相同的内容映射到不同的缓冲区中，那么对于一个特定的缓冲区而言，也可能被不同的用户映射为不同 的内容。与分散性一样，这种情况也是应当避免的，因此好的哈希算法应能够尽量降低缓冲的负荷。


环形Hash空间

![](http://img.blog.csdn.net/20140411000853609?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY3l3b3Nw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


普通hash求余算法最为不妥的地方就是在有机器的添加或者删除之后会照成大量的对象存储位置失效，这样就大大的不满足单调性了。下面来分析一下一致性哈希算法是如何处理的。


1. 节点（机器）的删除

    以上面的分布为例，如果NODE2出现故障被删除了，那么按照顺时针迁移的方法，object3将会被迁移到NODE3中，这样仅仅是object3的映射位置发生了变化，其它的对象没有任何的改动。如下图：

平衡性
根据上面的图解分析，一致性哈希算法满足了单调性和负载均衡的特性以及一般hash算法的分散性，但这还并不能当做其被广泛应用的原由，因为还缺少了平衡性。下面将分析一致性哈希算法是如何满足平衡性的。hash算法是不保证平衡的，如上面只部署了NODE1和NODE3的情况（NODE2被删除的图），object1存储到了NODE1中，而object2、object3、object4都存储到了NODE3中，这样就照成了非常不平衡的状态。在一致性哈希算法中，为了尽可能的满足平衡性，其引入了虚拟节点。
    ——“虚拟节点”（ virtual node ）是实际节点（机器）在 hash 空间的复制品（ replica ），一实际个节点（机器）对应了若干个“虚拟节点”，这个对应个数也成为“复制个数”，“虚拟节点”在 hash 空间中以hash值排列。
以上面只部署了NODE1和NODE3的情况（NODE2被删除的图）为例，之前的对象在机器上的分布很不均衡，现在我们以2个副本（复制个数）为例，这样整个hash环中就存在了4个虚拟节点，最后对象映射的关系图如下



![](http://img.blog.csdn.net/20140411001433375?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY3l3b3Nw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)



## Java中锁
synchronized 和 ReentrantLock等等 ) 。这些已经写好提供的锁为我们开发提供了便利，但是锁的具体性质以及类型却很少被提及。本系列文章将分析JAVA中常见的锁以及其特性，为大家答疑解惑。

Java中锁的种类

1. 自旋锁

2. 自旋锁的其他种类

3. 阻塞锁

4. 可重入锁

5. 读写锁

6. 互斥锁

7. 悲观锁

8. 乐观锁

9. 公平锁

10. 非公平锁

11. 偏向锁

12. 对象锁

13. 线程锁

14. 锁粗化

15. 轻量级锁

16. 锁消除

17. 锁膨胀

18. 信号量


## C++中锁

锁种类：自旋锁（Spinlock）. 互斥锁（Mutex）. 读写锁（Read-Write-Lock）等

##  IO通信

- select

```
int select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

select 函数监视的文件描述符分3类，分别是writefds. readfds. 和exceptfds。调用后select函数会阻塞，直到有描述副就绪（有数据 可读. 可写. 或者有except），或者超时（timeout指定等待时间，如果立即返回设为null即可），函数返回。当select函数返回后，可以 通过遍历fdset，来找到就绪的描述符。

select目前几乎在所有的平台上支持，其良好跨平台支持也是它的一个优点。select的一 个缺点在于单个进程能够监视的文件描述符的数量存在最大限制，在Linux上一般为1024，可以通过修改宏定义甚至重新编译内核的方式提升这一限制，但 是这样也会造成效率的降低。


- poll

```
int poll (struct pollfd *fds, unsigned int nfds, int timeout);
```


不同与select使用三个位图来表示三个fdset的方式，poll使用一个 pollfd的指针实现。

```
struct pollfd {
    int fd; /* file descriptor */
    short events; /* requested events to watch */
    short revents; /* returned events witnessed */
};
```

pollfd结构包含了要监视的event和发生的event，不再使用select“参数-值”传递的方式。同时，pollfd并没有最大数量限制（但是数量过大后性能也是会下降）。 和select函数一样，poll返回后，需要轮询pollfd来获取就绪的描述符。


- epoll

epoll是在2.6内核中提出的，是之前的select和poll的增强版本。相对于select和poll来说，epoll更加灵活，没有描述符限制。epoll使用一个文件描述符管理多个描述符，将用户关系的文件描述符的事件存放到内核的一个事件表中，这样在用户空间和内核空间的copy只需一次。

```
int epoll_create(int size)；//创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)；
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```

epoll总结
在 select/poll中，进程只有在调用一定的方法后，内核才对所有监视的文件描述符进行扫描，而epoll事先通过epoll_ctl()来注册一 个文件描述符，一旦基于某个文件描述符就绪时，内核会采用类似callback的回调机制，迅速激活这个文件描述符，当进程调用epoll_wait() 时便得到通知。(此处去掉了遍历文件描述符，而是通过监听回调的的机制。这正是epoll的魅力所在。)

epoll的优点主要是一下几个方面：

1. 监视的描述符数量不受限制，它所支持的FD上限是最大可以打开文件的数目，这个数字一般远大于2048,举个例子,在1GB内存的机器上大约是10万左 右，具体数目可以cat /proc/sys/fs/file-max察看,一般来说这个数目和系统内存关系很大。select的最大缺点就是进程打开的fd是有数量限制的。这对 于连接数量比较大的服务器来说根本不能满足。虽然也可以选择多进程的解决方案( Apache就是这样实现的)，不过虽然linux上面创建进程的代价比较小，但仍旧是不可忽视的，加上进程间数据同步远比不上线程间同步的高效，所以也不是一种完美的方案。

IO的效率不会随着监视fd的数量的增长而下降。epoll不同于select和poll轮询的方式，而是通过每个fd定义的回调函数来实现的。只有就绪的fd才会执行回调函数。


## gdb调试

1. run：简记为 r ，其作用是运行程序，当遇到断点后，程序会在断点处停止运行，等待用户输入下一步的命令。
1. continue （简写c ）：继续执行，到下一个断点处（或运行结束）
1. next：（简写 n），单步跟踪程序，当遇到函数调用时，也不进入此函数体；此命令同 step 的主要区别是，step 遇到用户自定义的函数，将步进到函数中去运行，而 next 则直接调用函数，不会进入到函数体内。
1. step （简写s）：单步调试如果有函数调用，则进入函数；与命令n不同，n是不进入调用的函数的
1. until：当你厌倦了在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体。
1. until+行号： 运行至某行，不仅仅用来跳出循环
1. finish： 运行程序，直到当前函数完成返回，并打印函数返回时的堆栈地址和返回值及参数值等信息。
1. call 函数(参数)：调用程序中可见的函数，并传递“参数”，如：call gdb_test(55)
1. quit：简记为 q ，退出gdb

设置断点

1. break n （简写b n）:在第n行处设置断点（可以带上代码路径和代码名称： b OAGUPDATE.cpp:578）
1. b fn1 if a＞b：条件断点设置
1. break func（break缩写为b）：在函数func()的入口处设置断点，如：break cb_button
1. delete 断点号n：删除第n个断点
1. disable 断点号n：暂停第n个断点
1. enable 断点号n：开启第n个断点
1. clear 行号n：清除第n行的断点
1. info b （info breakpoints） ：显示当前程序的断点设置情况
1. delete breakpoints：清除所有断点：

查看源代码

1. list ：简记为 l ，其作用就是列出程序的源代码，默认每次显示10行。
1. list 行号：将显示当前文件以“行号”为中心的前后10行代码，如：list 12
1. list 函数名：将显示“函数名”所在函数的源代码，如：list main
1. list ：不带参数，将接着上一次 list 命令的，输出下边的内容。


# Linux 进程


## 进程组成

![](http://ww3.sinaimg.cn/mw690/78f9859egw1ezwjd0xpapj20ji0ds41o.jpg)

1. 进程控制块:
	1. 进程标识符
	1. 状态
	1. 队列指针
	1. 控制信息: 参数 信号量 消息
	1. 现场保护区

1. 程序 :不可以修改
1. 数据: 一个进程使用,进程可修改地方.


进程间通信方式

## [【Linux编程】进程间通信（IPC）](http://songlee24.github.io/2015/04/21/linux-IPC/)


### 1管道

管道，通常指无名管道，是 UNIX 系统IPC最古老的形式。

1. 特点：

它是半双工的（即数据只能在一个方向上流动），具有固定的读端和写端。

它只能用于具有亲缘关系的进程之间的通信（也是父子进程或者兄弟进程之间）。

它可以看成是一种特殊的文件，对于它的读写也可以使用普通的read. write 等函数。但是它不是普通的文件，并不属于其他任何文件系统，并且只存在于内存中。


原型：

```c
#include <unistd.h>
int pipe(int fd[2]);    // 返回值：若成功返回0，失败返回-1
```

当一个管道建立时，它会创建两个文件描述符：fd[0]为读而打开，fd[1]为写而打开。如下图：

![](http://img.blog.csdn.net/20150419222058628?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGlzb25nbGlzb25nbGlzb25n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

例子

单个进程中的管道几乎没有任何用处。所以，通常调用 pipe 的进程接着调用 fork，这样就创建了父进程与子进程之间的 IPC 通道。如下图所示：

![](http://img.blog.csdn.net/20150419223853807?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGlzb25nbGlzb25nbGlzb25n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

若要数据流从父进程流向子进程，则关闭父进程的读端（fd[0]）与子进程的写端（fd[1]）；反之，则可以使数据流从子进程流向父进程。


```c
#include<stdio.h>
#include<unistd.h>

int main()
{
	int fd[2];  // 两个文件描述符
	pid_t pid;
	char buff[20];

	if(pipe(fd) < 0)  // 创建管道
		printf("Create Pipe Error!\n");

	if((pid = fork()) < 0)  // 创建子进程
		printf("Fork Error!\n");
	else if(pid > 0)  // 父进程
	{
		close(fd[0]); // 关闭读端
		write(fd[1], "hello world\n", 12);
	}
	else
	{
		close(fd[1]); // 关闭写端
		read(fd[0], buff, 20);
		printf("%s", buff);
	}

	return 0;
}
```

### 2命名管道FIFO

FIFO，也称为命名管道，它是一种文件类型。

FIFO可以在无关的进程之间交换数据，与无名管道不同。

FIFO有路径名与之相关联，它以一种特殊设备文件形式存在于文件系统中。

原型

```c
#include <sys/stat.h>
// 返回值：成功返回0，出错返回-1
int mkfifo(const char *pathname, mode_t mode);

```

FIFO的通信方式类似于在进程中使用文件来传输数据，只不过FIFO类型文件同时具有管道的特性。在数据读出时，FIFO管道中同时清除数据，并且“先进先出”。下面的例子演示了使用 FIFO 进行 IPC 的过程：

![](http://img.blog.csdn.net/20150420131002360?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGlzb25nbGlzb25nbGlzb25n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)


- write_fifo.c

```c
#include<stdio.h>
#include<stdlib.h>   // exit
#include<fcntl.h>    // O_WRONLY
#include<sys/stat.h>
#include<time.h>     // time

int main()
{
	int fd;
	int n, i;
	char buf[1024];
	time_t tp;

	printf("I am %d process.\n", getpid()); // 说明进程ID
	
	if((fd = open("fifo1", O_WRONLY)) < 0) // 以写打开一个FIFO 
	{
		perror("Open FIFO Failed");
		exit(1);
	}

	for(i=0; i<10; ++i)
	{
		time(&tp);  // 取系统当前时间
		n=sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
		printf("Send message: %s", buf); // 打印
		if(write(fd, buf, n+1) < 0)  // 写入到FIFO中
		{
			perror("Write FIFO Failed");
			close(fd);
			exit(1);
		}
		sleep(1);  // 休眠1秒
	}

	close(fd);  // 关闭FIFO文件
	return 0;
}
```

- read_fifo.c

```c
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
	int fd;
	int len;
	char buf[1024];

	if(mkfifo("fifo1", 0666) < 0 && errno!=EEXIST) // 创建FIFO管道
		perror("Create FIFO Failed");

	if((fd = open("fifo1", O_RDONLY)) < 0)  // 以读打开FIFO
	{
		perror("Open FIFO Failed");
		exit(1);
	}
	
	while((len = read(fd, buf, 1024)) > 0) // 读取FIFO管道
		printf("Read message: %s", buf);

	close(fd);  // 关闭FIFO文件
	return 0;
}
```


### 3消息队列

消息队列，是消息的链接表，存放在内核中。一个消息队列由一个标识符（即队列ID）来标识。

1. 特点

消息队列是面向记录的，其中的消息具有特定的格式以及特定的优先级。

消息队列独立于发送与接收进程。进程终止时，消息队列及其内容并不会被删除。

消息队列可以实现消息的随机查询,消息不一定要以先进先出的次序读取,也可以按消息的类型读取。


原型

```c
#include <sys/msg.h>
// 创建或打开消息队列：成功返回队列ID，失败返回-1
int msgget(key_t key, int flag);
// 添加消息：成功返回0，失败返回-1
int msgsnd(int msqid, const void *ptr, size_t size, int flag);
// 读取消息：成功返回消息数据的长度，失败返回-1
int msgrcv(int msqid, void *ptr, size_t size, long type,int flag);
// 控制消息队列：成功返回0，失败返回-1
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

在以下两种情况下，msgget将创建一个新的消息队列：

如果没有与键值key相对应的消息队列，并且flag中包含了IPC_CREAT标志位。
key参数为IPC_PRIVATE。
函数msgrcv在读取消息队列时，type参数有下面几种情况：

type == 0，返回队列中的第一个消息；
type > 0，返回队列中消息类型为 type 的第一个消息；
type < 0，返回队列中消息类型值小于或等于 type 绝对值的消息，如果有多个，则取类型值最小的消息。
可以看出，type值非 0 时用于以非先进先出次序读消息。也可以把 type 看做优先级的权值。（其他的参数解释，请自行Google之）


下面写了一个简单的使用消息队列进行IPC的例子，服务端程序一直在等待特定类型的消息，当收到该类型的消息以后，发送另一种特定类型的消息作为反馈，客户端读取该反馈并打印出来。


- msg_server.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// 用于创建一个唯一的key
#define MSG_FILE "/etc/passwd"

// 消息结构
struct msg_form {
	long mtype;
	char mtext[256];
};

int main()
{
	int msqid;
	key_t key;
	struct msg_form msg;
	
	// 获取key值
	if((key = ftok(MSG_FILE,'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 打印key值
	printf("Message Queue - Server key is: %d.\n", key);

	// 创建消息队列
	if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
	{
		perror("msgget error");
		exit(1);
	}

	// 打印消息队列ID及进程ID
	printf("My msqid is: %d.\n", msqid);
	printf("My pid is: %d.\n", getpid());

	// 循环读取消息
	for(;;) 
	{
		msgrcv(msqid, &msg, 256, 888, 0);// 返回类型为888的第一个消息
		printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
		printf("Server: receive msg.mtype is: %d.\n", msg.mtype);

		msg.mtype = 999; // 客户端接收的消息类型
		sprintf(msg.mtext, "hello, I'm server %d", getpid());
		msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
	}
	return 0;
}
```

- msg_client.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// 用于创建一个唯一的key
#define MSG_FILE "/etc/passwd"

// 消息结构
struct msg_form {
	long mtype;
	char mtext[256];
};

int main()
{
	int msqid;
	key_t key;
	struct msg_form msg;

	// 获取key值
	if ((key = ftok(MSG_FILE, 'z')) < 0) 
	{
		perror("ftok error");
		exit(1);
	}

	// 打印key值
	printf("Message Queue - Client key is: %d.\n", key);

	// 打开消息队列
	if ((msqid = msgget(key, IPC_CREAT|0777)) == -1) 
	{
		perror("msgget error");
		exit(1);
	}

	// 打印消息队列ID及进程ID
    printf("My msqid is: %d.\n", msqid);
	printf("My pid is: %d.\n", getpid());

	// 添加消息，类型为888
	msg.mtype = 888;
	sprintf(msg.mtext, "hello, I'm client %d", getpid());
	msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

	// 读取类型为777的消息
	msgrcv(msqid, &msg, 256, 999, 0);
	printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
	printf("Client: receive msg.mtype is: %d.\n", msg.mtype);
	return 0;
}
```

### 4信号量

信号量（semaphore）与已经介绍过的 IPC 结构不同，它是一个计数器。信号量用于实现进程间的互斥与同步，而不是用于存储进程间通信数据。


1. 特点

信号量用于进程间同步，若要在进程间传递数据需要结合共享内存。

信号量基于操作系统的 PV 操作，程序对信号量的操作都是原子操作。

每次对信号量的 PV 操作不仅限于对信号量值加 1 或减 1，而且可以加减任意正整数。

支持信号量组。

原型

最简单的信号量是只能取 0 和 1 的变量，这也是信号量最常见的一种形式，叫做二值信号量（Binary Semaphore）。而可以取多个正整数的信号量被称为通用信号量。

Linux 下的信号量函数都是在通用的信号量数组上进行操作，而不是在一个单一的二值信号量上进行操作。


```c
#include <sys/sem.h>
// 创建或获取一个信号量组：若成功返回信号量集ID，失败返回-1
int semget(key_t key, int num_sems, int sem_flags);
// 对信号量组进行操作，改变信号量的值：成功返回0，失败返回-1
int semop(int semid, struct sembuf semoparray[], size_t numops);  
// 控制信号量的相关信息
int semctl(int semid, int sem_num, int cmd, ...);
```


在semop函数中，sembuf结构的定义如下：
其中 sem_op 是一次操作中的信号量的改变量：

若sem_op > 0，表示进程释放相应的资源数，将 sem_op 的值加到信号量的值上。如果有进程正在休眠等待此信号量，则换行它们。

若sem_op < 0，请求 sem_op 的绝对值的资源。

若sem_op == 0，进程阻塞直到信号量的相应值为0：

在semctl函数中的命令有多种，这里就说两个常用的：

SETVAL：用于初始化信号量为一个已知的值。所需要的值作为联合semun的val成员来传递。在信号量第一次使用之前需要设置信号量。

IPC_RMID：删除一个信号量集合。如果不删除信号量，它将继续在系统中存在，即使程序已经退出，它可能在你下次运行此程序时引发问题，而且信号量是一种有限的资源。


```c
struct sembuf 
{
    short sem_num; // 信号量组中对应的序号，0～sem_nums-1
    short sem_op;  // 信号量值在一次操作中的改变量
    short sem_flg; // IPC_NOWAIT, SEM_UNDO
}
```

例子

例子如果不加信号量，则父进程会先执行完毕。这里加了信号量让父进程等待子进程执行完以后再执行。

```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>

// 联合体，用于semctl初始化
union semun
{
	int              val; /*for SETVAL*/
	struct semid_ds *buf;
	unsigned short  *array;
};

// 初始化信号量
int init_sem(int sem_id, int value)
{
	union semun tmp;
	tmp.val = value;
	if(semctl(sem_id, 0, SETVAL, tmp) == -1)
	{
		perror("Init Semaphore Error");
		return -1;
	}
	return 0;
}

// P操作:
//	若信号量值为1，获取资源并将信号量值-1 
//	若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
	struct sembuf sbuf;
	sbuf.sem_num = 0; /*序号*/
	sbuf.sem_op = -1; /*P操作*/
	sbuf.sem_flg = SEM_UNDO;

	if(semop(sem_id, &sbuf, 1) == -1)
	{
		perror("P operation Error");
		return -1;
	}
	return 0;
}

// V操作：
//	释放资源并将信号量值+1
//	如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
	struct sembuf sbuf;
	sbuf.sem_num = 0; /*序号*/
	sbuf.sem_op = 1;  /*V操作*/
	sbuf.sem_flg = SEM_UNDO;

	if(semop(sem_id, &sbuf, 1) == -1)
	{
		perror("V operation Error");
		return -1;
	}
	return 0;
}

// 删除信号量集
int del_sem(int sem_id)
{
	union semun tmp;
	if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
	{
		perror("Delete Semaphore Error");
		return -1;
	}
	return 0;
}


int main()
{
	int sem_id;  // 信号量集ID
	key_t key;  
	pid_t pid;

	// 获取key值
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 创建信号量集，其中只有一个信号量
	if((sem_id = semget(key, 1, IPC_CREAT|0666)) == -1)
	{
		perror("semget error");
		exit(1);
	}

	// 初始化：初值设为0资源被占用
	init_sem(sem_id, 0);

	if((pid = fork()) == -1)
		perror("Fork Error");
	else if(pid == 0) /*子进程*/ 
	{
		sleep(2);
		printf("Process child: pid=%d\n", getpid());
		sem_v(sem_id);  /*释放资源*/
	}
	else  /*父进程*/
	{
		sem_p(sem_id);   /*等待资源*/
		printf("Process father: pid=%d\n", getpid());
		sem_v(sem_id);   /*释放资源*/
		del_sem(sem_id); /*删除信号量集*/
	}
	return 0;
}
```


## 5共享内存

共享内存（Shared Memory），指两个或多个进程共享一个给定的存储区。

特点

共享内存是最快的一种 IPC，因为进程是直接对内存进行存取。

因为多个进程可以同时操作，所以需要进行同步。

信号量+共享内存通常结合在一起使用，信号量用来同步对共享内存的访问。

原型

```c
#include <sys/shm.h>
// 创建或获取一个共享内存：成功返回共享内存ID，失败返回-1
int shmget(key_t key, size_t size, int flag);
// 连接共享内存到当前进程的地址空间：成功返回指向共享内存的指针，失败返回-1
void *shmat(int shm_id, const void *addr, int flag);
// 断开与共享内存的连接：成功返回0，失败返回-1
int shmdt(void *addr); 
// 控制共享内存的相关信息：成功返回0，失败返回-1
int shmctl(int shm_id, int cmd, struct shmid_ds *buf);
```

当用shmget函数创建一段共享内存时，必须指定其 size；而如果引用一个已存在的共享内存，则将 size 指定为0 

当一段共享内存被创建以后，它并不能被任何进程访问。必须使用shmat函数连接该共享内存到当前进程的地址空间，连接成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问。

shmdt函数是用来断开shmat建立的连接的。注意，这并不是从系统中删除该共享内存，只是当前进程不能再访问该共享内存而已。

shmctl函数可以对共享内存执行多种操作，根据参数 cmd 执行相应的操作。常用的是IPC_RMID（从系统中删除该共享内存）

下面这个例子，使用了【共享内存+信号量+消息队列】的组合来实现服务器进程与客户进程间的通信。

共享内存用来传递数据；
信号量用来同步；
消息队列用来 在客户端修改了共享内存后 通知服务器读取。

Server.c

```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 消息队列结构
struct msg_form {
    long mtype;
    char mtext;
};

// 联合体，用于semctl初始化
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};

// 初始化信号量
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

// P操作:
//  若信号量值为1，获取资源并将信号量值-1 
//  若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*序号*/
    sbuf.sem_op = -1; /*P操作*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V操作：
//  释放资源并将信号量值+1
//  如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*序号*/
    sbuf.sem_op = 1;  /*V操作*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("V operation Error");
        return -1;
    }
    return 0;
}

// 删除信号量集
int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
        perror("Delete Semaphore Error");
        return -1;
    }
    return 0;
}

// 创建一个信号量集
int creat_sem(key_t key)
{
	int sem_id;
	if((sem_id = semget(key, 1, IPC_CREAT|0666)) == -1)
	{
		perror("semget error");
		exit(-1);
	}
	init_sem(sem_id, 1);  /*初值设为1资源未占用*/
	return sem_id;
}


int main()
{
	key_t key;
	int shmid, semid, msqid;
	char *shm;
	char data[] = "this is server";
	struct shmid_ds buf1;  /*用于删除共享内存*/
	struct msqid_ds buf2;  /*用于删除消息队列*/
	struct msg_form msg;  /*消息队列用于通知对方更新了共享内存*/

	// 获取key值
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 创建共享内存
	if((shmid = shmget(key, 1024, IPC_CREAT|0666)) == -1)
	{
		perror("Create Shared Memory Error");
		exit(1);
	}

	// 连接共享内存
	shm = (char*)shmat(shmid, 0, 0);
	if((int)shm == -1)
	{
		perror("Attach Shared Memory Error");
		exit(1);
	}


	// 创建消息队列
	if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
	{
		perror("msgget error");
		exit(1);
	}

	// 创建信号量
	semid = creat_sem(key);
	
	// 读数据
	while(1)
	{
		msgrcv(msqid, &msg, 1, 888, 0); /*读取类型为888的消息*/
		if(msg.mtext == 'q')  /*quit - 跳出循环*/ 
			break;
		if(msg.mtext == 'r')  /*read - 读共享内存*/
		{
			sem_p(semid);
			printf("%s\n",shm);
			sem_v(semid);
		}
	}

	// 断开连接
	shmdt(shm);

    /*删除共享内存. 消息队列. 信号量*/
	shmctl(shmid, IPC_RMID, &buf1);
	msgctl(msqid, IPC_RMID, &buf2);
	del_sem(semid);
	return 0;
}
```

Client.c

```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 消息队列结构
struct msg_form {
    long mtype;
    char mtext;
};

// 联合体，用于semctl初始化
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};

// P操作:
//  若信号量值为1，获取资源并将信号量值-1 
//  若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*序号*/
    sbuf.sem_op = -1; /*P操作*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V操作：
//  释放资源并将信号量值+1
//  如果有进程正在挂起等待，则唤醒它们
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*序号*/
    sbuf.sem_op = 1;  /*V操作*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("V operation Error");
        return -1;
    }
    return 0;
}


int main()
{
	key_t key;
	int shmid, semid, msqid;
	char *shm;
	struct msg_form msg;
	int flag = 1; /*while循环条件*/

	// 获取key值
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 获取共享内存
	if((shmid = shmget(key, 1024, 0)) == -1)
	{
		perror("shmget error");
		exit(1);
	}

	// 连接共享内存
	shm = (char*)shmat(shmid, 0, 0);
	if((int)shm == -1)
	{
		perror("Attach Shared Memory Error");
		exit(1);
	}

	// 创建消息队列
	if ((msqid = msgget(key, 0)) == -1)
	{
		perror("msgget error");
		exit(1);
	}

	// 获取信号量
	if((semid = semget(key, 0, 0)) == -1)
	{
		perror("semget error");
		exit(1);
	}
	
	// 写数据
	printf("***************************************\n");
	printf("*                 IPC                 *\n");
	printf("*    Input r to send data to server.  *\n");
	printf("*    Input q to quit.                 *\n");
	printf("***************************************\n");
	
	while(flag)
	{
		char c;
		printf("Please input command: ");
		scanf("%c", &c);
		switch(c)
		{
			case 'r':
				printf("Data to send: ");
				sem_p(semid);  /*访问资源*/
				scanf("%s", shm);
				sem_v(semid);  /*释放资源*/
				/*清空标准输入缓冲区*/
				while((c=getchar())!='\n' && c!=EOF);
				msg.mtype = 888;  
				msg.mtext = 'r';  /*发送消息通知服务器读数据*/
				msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
				break;
			case 'q':
				msg.mtype = 888;
				msg.mtext = 'q';
				msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
				flag = 0;
				break;
			default:
				printf("Wrong input!\n");
				/*清空标准输入缓冲区*/
				while((c=getchar())!='\n' && c!=EOF);
		}
	}

	// 断开连接
	shmdt(shm);

	return 0;
}
```



## 协程

[谈谈协程和C语言的协程](http://www.yeolar.com/note/2013/02/17/coroutines/)


协程，又称微线程,Coroutine

协程的概念很早就提出来了，但直到最近几年才在某些语言（如Lua）中得到广泛应用。

子程序，或者称为函数，在所有语言中都是层级调用，比如A调用B，B在执行过程中又调用了C，C执行完毕返回，B执行完毕返回，最后是A执行完毕。

所以子程序调用是通过栈实现的，一个线程就是执行一个子程序。

子程序调用总是一个入口，一次返回，调用顺序是明确的。而协程的调用和子程序不同。

协程看上去也是子程序，但执行过程中，在子程序内部可中断，然后转而执行别的子程序，在适当的时候再返回来接着执行。

注意，在一个子程序中中断，去执行其他子程序，不是函数调用，有点类似CPU的中断。


协程: 没有线程切换的开销.

coroutine 和函数一样, 区别在于 coroutine 有多个入口点, 而一般的函数 函数只能有一个入口点. 一般的函数只能从开始的地方执行, 一旦退出, 就只能从 唯一的入口点再开始了. 但是 coroutine 不同, 当它觉得没有任务需要处理时, 它可以把 CPU 让给其他函数, 然后它在这个让出的点等待, 直到其它函数再把 CPU 给它.


看起来A. B的执行有点像多线程，但协程的特点在于是一个线程执行，那和多线程比，协程有何优势？

1. 最大的优势就是协程极高的执行效率。因为子程序切换不是线程切换，而是由程序自身控制，因此，没有线程切换的开销，和多线程比，线程数量越多，协程的性能优势就越明显。

1. 优势就是不需要多线程的锁机制，因为只有一个线程，也不存在同时写变量冲突，在协程中控制共享资源不加锁，只需要判断状态就好了，所以执行效率比多线程高很多。

因为协程是一个线程执行，那怎么利用多核CPU呢？最简单的方法是多进程+协程，既充分利用多核，又充分发挥协程的高效率，可获得极高的性能。

Python对协程的支持还非常有限，用在generator中的yield可以一定程度上实现协程。虽然支持不完全，但已经可以发挥相当大的威力了。

来看例子：

传统的生产者-消费者模型是一个线程写消息，一个线程取消息，通过锁机制控制队列和等待，但一不小心就可能死锁。


coroutine 的优点
通过上面简单的示例(真实情况可能更复杂一些), 我们已经可以看到使用 coroutine 的优点了:

produce 和 consume 都是在同一个线程里执行的, 不会有 race condition 的问题 发生.
coroutine 是在用户空间实现的, coroutine 的堆栈是由用户自己维护的, 在切换 的时候, 用户交换 caller 和 coroutine 的堆栈, 这比在内核空间开执行的 thread 的切换节省了大量的开销(想象一下, 切换 thread 的时候, 需要做很多上下文的 切换, 各种寄存器 ……).
coroutine 的成本很低, 可以产生大量的 coroutine, 不像线程, 每个线程有自己的 线程堆栈, ID, 上下文等.
可以由用户来控制 coroutine 的执行, 虽然 thread 也可以进行某种程序的控制, 但是 基本上 thread 的调度都是由 OS 来完成的






##　python


# 进程线程区别

1.线程是程序执行的最小单位，而进程是操作系统分配资源的最小单位；

2.一个进程由一个或多个线程组成，线程是一个进程中代码的不同执行路线；

3.进程之间相互独立，但同一进程下的各个线程之间共享程序的内存空间(包括代码段. 数据集. 堆等)及一些进程级的资源(如打开文件和信号)，某进程内的线程在其它进程不可见；

4.调度和切换：线程上下文切换比进程上下文切换要快得多。


# Linux 线程

## 多线程的同步和互斥

进程是程序执行时的一个实例，即它是程序已经执行到何种程度的数据结构的汇集。从内核的观点看，进程的目的就是担当分配系统资源（CPU时间. 内存等）的基本单位。

线程是进程的一个执行流，是CPU调度和分派的基本单位，它是比进程更小的能独立运行的基本单位。一个进程由几个线程组成（拥有很多相对独立的执行流的用户程序共享应用程序的大部分数据结构），线程与同属一个进程的其他的线程共享进程所拥有的全部资源。


据统计，总的说来，一个进程的开销大约是一个线程开销的30倍左右

"进程——资源分配的最小单位，线程——程序执行的最小单位"

进程有独立的地址空间，一个进程崩溃后，在保护模式下不会对其它进程产生影响，而线程只是一个进程中的不同执行路径。线程有自己的**堆栈和局部变量**，但线程没有单独的地址空间，一个线程死掉就等于整个进程死掉，所以多进程的程序要比多线程的程序健壮，但在进程切换时，耗费资源较大，效率要差一些。但对于一些要求同时进行并且又要共享某些变量的并发操作，只能用线程，不能用进程。


线程操作函数

#include <pthread.h>
 
1. int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*func) (void *), void *arg);
1. int pthread_join (pthread_t tid, void ** status);
1. pthread_t pthread_self (void);
1. int pthread_detach (pthread_t tid);
1. void pthread_exit (void *status);

```c
1）有一int型全局变量g_Flag初始值为0；

2）在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1

3）在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2

这3点很简单嘛！！！不就是调用pthread_create创建线程。代码如下：

/*
 * 1）有一int型全局变量g_Flag初始值为0；
 *
 * 2）在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1
 *
 * 3）在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

int g_Flag=0;

void* thread1(void*);
void* thread2(void*);

/*
 * when program is started, a single thread is created, called the initial thread or main thread.
 * Additional threads are created by pthread_create.
 * So we just need to create two thread in main().
 */
int main(int argc, char** argv)
{
	printf("enter main\n");
	pthread_t tid1, tid2;
	int rc1=0, rc2=0;
	rc2 = pthread_create(&tid2, NULL, thread2, NULL);
	if(rc2 != 0)
		printf("%s: %d\n",__func__, strerror(rc2));

	rc1 = pthread_create(&tid1, NULL, thread1, &tid2);
	if(rc1 != 0)
		printf("%s: %d\n",__func__, strerror(rc1));
	printf("leave main\n");
	exit(0);	
}
/*
 * thread1() will be execute by thread1, after pthread_create()
 * it will set g_Flag = 1;
 */
void* thread1(void* arg)
{
	printf("enter thread1\n");
	printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
	g_Flag = 1;
	printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
	printf("leave thread1\n");
	pthread_exit(0);
}

/*
 * thread2() will be execute by thread2, after pthread_create()
 * it will set g_Flag = 2;
 */
void* thread2(void* arg)
{
	printf("enter thread2\n");
	printf("this is thread2, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
	g_Flag = 2;
	printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
	printf("leave thread2\n");
	pthread_exit(0);
}
```

编译 ` gcc -lpthread test.c`


线程之间的互斥
上面的代码似乎很好的解决了问题的前面4点要求，其实不然！！！因为g_Flag是一个全局变量，线程thread1和thread2可以同时对它进行操作，需要对它进行加锁保护，thread1和thread2要互斥访问才行。下面我们就介绍如何加锁保护——互斥锁。

- 互斥锁：

使用互斥锁（互斥）可以使线程按顺序执行。通常，互斥锁通过确保一次只有一个线程执行代码的临界段来同步多个线程。互斥锁还可以保护单线程代码。


互斥锁的相关操作函数如下：

```c
#include <pthread.h> 
int pthread_mutex_lock(pthread_mutex_t * mptr); 
int pthread_mutex_unlock(pthread_mutex_t * mptr); 
//Both return: 0 if OK, positive Exxx value on error
```

在对临界资源进行操作之前需要pthread_mutex_lock先加锁，操作完之后pthread_mutex_unlock再解锁。而且在这之前需要声明一个pthread_mutex_t类型的变量，用作前面两个函数的参数。具体代码见第5节。


## 线程之间的同步

条件变量：

使用条件变量可以以原子方式阻塞线程，直到某个特定条件为真为止。条件变量始终与互斥锁一起使用。对条件的测试是在互斥锁（互斥）的保护下进行的。

如果条件为假，线程通常会基于条件变量阻塞，并以原子方式释放等待条件变化的互斥锁。如果另一个线程更改了条件，该线程可能会向相关的条件变量发出信号，从而使一个或多个等待的线程执行以下操作：

唤醒
再次获取互斥锁
重新评估条件
在以下情况下，条件变量可用于在进程之间同步线程：

线程是在可以写入的内存中分配的
内存由协作进程共享



```c
#include <pthread.h>
int pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr); 
int pthread_cond_signal(pthread_cond_t *cptr); 
//Both return: 0 if OK, positive Exxx value on error
```

为什么条件变量始终与互斥锁一起使用，对条件的测试是在互斥锁（互斥）的保护下进行的呢？因为“某个特性条件”通常是在多个线程之间共享的某个变量。互斥锁允许这个变量可以在不同的线程中设置和检测。

通常，pthread_cond_wait只是唤醒等待某个条件变量的一个线程。如果需要唤醒所有等待某个条件变量的线程，需要调用：

int pthread_cond_broadcast (pthread_cond_t * cptr);
默认情况下面，阻塞的线程会一直等待，知道某个条件变量为真。如果想设置最大的阻塞时间可以调用：

int pthread_cond_timedwait (pthread_cond_t * cptr, pthread_mutex_t *mptr, const struct timespec *abstime);
如果时间到了，条件变量还没有为真，仍然返回，返回值为ETIME。


[Linux多线程编程（不限Linux）](http://www.cnblogs.com/skynet/archive/2010/10/30/1865267.html)



## 线程间同步[ 线程同步. 条件变量. 互斥锁的使用](http://blog.csdn.net/yusiguyuan/article/details/14161225)


### 互斥锁

```c
lock_the_mutex(...);
　　临界区
unlock_the_mutex(...);
下列三个函数给一个互斥锁上锁和解锁：
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mptr);　　//若不能立刻获得锁，将阻塞在此处
int pthread_mutex_trylock(pthread_mutex_t *mptr);　　//若不能立刻获得锁，将返回EBUSY，用户可以根据此返回值做其他操作，非阻塞模式
int pthread_mutex_unlock(pthread_mutex_t *mptr);　　//释放锁
```

### 条件变量

它是发送信号与等待信号。互斥锁用户上锁，条件变量则用于等待。一般来说，在一个进程/线程中调用pthread_cond_wait(..)等待某个条件的成立，此时该进程阻塞在这里，另外一个进程/线程进行某种操作，当某种条件成立时，调用pthread_cond_signal(...)来发送信号，从而使pthread_cond_wait(...)返回。此处要注意的是，这里所谈到的信号，不是系统级别的SIGXXXX信号，只是用信号这个词语更容易理解。条件变量与信号量更接近或者就可以认为是信号量。
下列两个函数用来对条件变量进行控制：

```c
#include <pthread.h>
int pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);
int pthread_cond_signal(pthread_cond_t *cptr);
```

在这里需要注意的是，pthread_cond_wait(&cond,&mutex)是一个原子操作，当它执行时，首先对mutex解锁，这样另外的线程才能得到锁来修改条件，pthread_cond_wait解锁后，再将本身的线程/进程投入睡眠，另外，当该函数返回时，会再对mutex进行加锁，这样才能“执行某种操作”后unlock锁。

### 读写锁

顾名思义，读写锁也是一种锁，他是在互斥锁的基础上进行了改进，当一个进程/线程获得写入锁时，其他的进程/线程仍然可以获得锁，只不过获得的是读取锁，因为一个进程/线程写入，不影响其他进程/线程的读操作。

###  信号量

　　　　　进程A                               进程B

　　　　　　　　　　\　　　　　　　　　　/

　　　　　进程　　　　\ 　　　　　　　　/

　　　　　　　　----------------------------------

　　　　　内核　　　　　\　　　　　　/

　　　　　　　　　　　　　　信号量

信号量是由内核来维护的，他独立出进程。因此可以通过它来进行同步。

主要函数有：sem_open. sem_close. sem_unlink，这里要注意，close只是关闭信号量，但并未从系统中删除，而unlink是删除该信号量。 



互斥锁. 条件变量. 信号量三者的差别：

1.  互斥锁必须总是由给他上锁的线程解锁（因为此时其他线程根本得不到此锁），信号量没有这种限制：一个线程等待某个信号量，而另一个线程可以挂出该信号量
1. 每个信号量有一个与之关联的值，挂出时+1，等待时-1，那么任何线程都可以挂出一个信号，即使没有线程在等待该信号量的值。不过对于条件变量来说，如果pthread_cond_signal之后没有任何线程阻塞在pthread_cond_wait上，那么此条件变量上的信号丢失。
1. 在各种各样的同步技巧中，能够从信号处理程序中安全调用的唯一函数是sem_post









# 操作系统

## Linux

计算机端口范围

计算机的端口范围是从0号端口到65535号端口，可分为3大类：

1. 公认端口（Well Known Ports）：从0到1023，它们紧密绑定于一些服务。通常这些端口的通讯明确表明了某种服务的协议。例如：80端口实际上总是HTTP通讯。
1. 注册端口（Registered Ports）：从1024到49151。它们松散地绑定于一些服务。也就是说有许多服务绑定于这些端口，这些端口同样用于许多其它目的。例如：许多系统处理动态端口从1024左右开始。
1. 动态和/或私有端口（Dynamic and/or Private Ports）：从49152到65535。理论上，不应为服务分配这些端口。实际上，机器通常从1024起分配动态端口。但也有例外：SUN的RPC端口从32768开始。

## 查看每个物理cpu实际利用率

在top基本视图中，按键盘数字“1”，可监控每个逻辑CPU的状况：

![](http://images.cnblogs.com/cnblogs_com/peida/top1.jpg)

敲击键盘“b”（打开/关闭加亮效果），top的视图变化如下：

![](http://images.cnblogs.com/cnblogs_com/peida/top2.png)


## RPC


# 数据库

关系数据库

NOSQL数据库


腾讯云MySQL:

PCI-e SSD的强大IO性能保障数据库的访问能力
单实例最大支持37000QPS，1TB存储空间
计算 网络 存储 数据库 域名服务

TDSQL: 

更高性能

基于PCI-E SSD. 强大IO性能保障数据库的访问能力，存储固件采用NVMe协议，专门针对PCI-E SSD设计，更能发挥出性能优势，高IO型单实例最大可支持6TB容量. 480GB内存和22万以上QPS(每秒访问次数)，性能优势让您以较少的数据库实例支撑更高的业务并发。

所有 TDSQL 实例内核都非原版MariaDB内核，而是经过腾讯顶尖数据库研发基于实际需求修改。而且默认参数都是经过多年的生产实践优化而得，并由专业DBA 持续对其进行优化，确保 TDSQL 一直基于最佳实践在运行。

# 网络


[IO模型：同步. 异步. 阻塞. 非阻塞](http://songlee24.github.io/2016/07/19/explanation-of-5-IO-models/)

在Linux的网络编程中，同步IO(synchronous IO). 异步IO(asynchronous IO). 阻塞IO(blocking IO). 非阻塞IO(non-blocking IO)究竟是什么？它们之间又有什么联系和区别？ 本文是我对这个问题的答案整理的笔记，参考《UNIX网络编程.卷1》
select 

通常一个 socket 上的读操作包含两个阶段：

1. 等待数据准备好；
1. 将数据从内核拷贝到进程中。

上述几种IO模型就是在这两个阶段上各有不同的情况。


1. 阻塞式IO（blocking IO）
1. 非阻塞式IO（non-blocking IO）
1. IO复用（IO multiplexing）
1. 信号驱动式IO（signal driven IO）
1. 异步IO（asynchronous IO）



### 1阻塞式IO

![](http://img.blog.csdn.net/20160718144849959)


当进程调用recvfrom时，该函数直到①数据报到达且被复制到应用进程缓冲区；②或者发生错误(比如被信号中断)才返回。

所以，阻塞式IO的特点就是在I/O执行的两个阶段都被阻塞了——阻塞等待数据，阻塞拷贝数据。



### 2非阻塞式IO

![](http://img.blog.csdn.net/20160718150945686)


当对一个非阻塞 socket 执行读操作时，如果内核中的数据还没有准备好，那么它并不会阻塞用户进程，而是立刻返回一个EWOULDBLOCK错误；如果内核中有数据准备好了，它会立即将数据拷贝到用户内存，并成功返回。

由于非阻塞I/O在没有数据时会立即返回，故用户进程通常需要循环调用recvfrom，不断地主动询问内核数据是否ready。

所以，非阻塞式IO的特点是在I/O执行的第一个阶段不会阻塞线程，但在第二阶段会阻塞。

###  3IO复用

![](http://img.blog.csdn.net/20160718154137996)

IO复用(IO multiplexing)，也称事件驱动IO(event-driven IO)，就是在单个线程里同时监控多个套接字，通过 select 或 poll 轮询所负责的所有socket，当某个socket有数据到达了，就通知用户进程。

可以看出，进程阻塞在select调用上，等待有套接字变为可读；当有套接字可读以后，调用recvfrom把数据报从内核复制到用户进程缓冲区，此时进程阻塞在IO执行的第二个阶段。

如上图整个用户进程其实是一直被阻塞的，但IO复用的优势在于可以等待多个描述符就绪。

所以，IO复用的特点是进行了两次系统调用，进程先是阻塞在 select/poll 上，再是阻塞在读操作的第二个阶段上。


### 4信号驱动式IO

![](http://img.blog.csdn.net/20160718161259057)

首先需要开启 socket 的信号驱动式IO功能，然后通过sigaction系统调用注册SIGIO信号处理函数 —— 该系统调用会立即返回。当数据准备好时，内核会为该进程产生一个SIGIO信号，这时就可以在信号处理函数中调用 recvfrom 读取数据了。

所以，信号驱动式IO的特点就是在等待数据ready期间进程不被阻塞，当收到信号通知时再阻塞并拷贝数据。

### 5异步IO

异步IO(asynchronous IO)其实用得很少，在Linux 2.5 版本的内核中首次出现，在 2.6 版本的内核中才成为标准特性。

![](http://img.blog.csdn.net/20160718164415555)

用户进程在发起aio_read操作后，该系统调用立即返回 —— 然后内核会自己等待数据ready，并自动将数据拷贝到用户内存。整个过程完成以后，内核会给用户进程发送一个信号，通知IO操作已完成。

异步IO与信号驱动式IO的主要区别是：信号驱动式IO是由内核通知我们何时启动一个IO操作，而异步IO是由内核通知我们IO操作何时完成。

所以，异步IO的特点是IO执行的两个阶段都由内核去完成，用户进程无需干预，也不会被阻塞。



### 五种IO模型的比较

可以看出，前4种模型的主要区别在于第一阶段，因为它们的第二阶段是一样的：都是阻塞于recvfrom调用，将数据从内核拷贝到用户进程缓冲区。

![](http://img.blog.csdn.net/20160718170600861)


### 处理高并发

1. IO多路复用
1. 协程


### 大端小端问题

![](http://img.ph.126.net/_hT6e4vbPTy2vzHuUrGDsA==/3370381371134432302.jpg)

1. 小端法(Little-Endian)就是低位字节排放在内存的低地址端(即该值的起始地址),高位字节排放在内存的高地址端;
2. 大端法(Big-Endian)就是高位字节排放在内存的低地址端(即该值的起始地址),低位字节排放在内存的高地址端;

**网络 大 大 大**

网络传输一般采用 Big Endian，也被称之为网络字节序，或网络序。当两台采用不同字节序的主机通信时，在发送数据之前都必须经过字节序的转换成为网络字节序后再进行传输。

整数在内存中存储的顺序，现在 Little Endian 比较普遍。


JAVA编写的程序则唯一采用 Big Endian 方式来存储数据


## NAT

（Network Address Translation，网络地址转换）

1. 宽带分享：这是 NAT 主机的最大功能。
2. 安全防护：NAT 之内的 PC 联机到 Internet 上面时，他所显示的 IP 是 NAT 主机的公共 IP，所以 Client 端的 PC 当然就具有一定程度的安全了，外界在进行 portscan（端口扫描） 的时候，就侦测不到源Client 端的 PC 。

- NAT也让主机之间的通信变得复杂，导致通信效率的降低。

NAT实现方式
NAT的实现方式有三种，即静态转换Static Nat. 动态转换Dynamic Nat和端口多路复用OverLoad。

静态转换是指将内部网络的私有IP地址转换为公有IP地址，IP地址对是一对一的，是一成不变的，某个私有IP地址只转换为某个公有IP地址。借助于静态转换，可以实现外部网络对内部网络中某些特定设备（如服务器）的访问。

动态转换是指将内部网络的私有IP地址转换为公用IP地址时，IP地址是不确定的，是随机的，所有被授权访问上Internet的私有IP地址可随机转换为任何指定的合法IP地址。也就是说，只要指定哪些内部地址可以进行转换，以及用哪些合法地址作为外部地址时，就可以进行动态转换。动态转换可以使用多个合法外部地址集。当ISP提供的合法IP地址略少于网络内部的计算机数量时。可以采用动态转换的方式。

端口多路复用（Port address Translation,PAT)
是指改变外出数据包的源端口并进行端口转换，即端口地址转换（PAT，Port Address Translation).采用端口多路复用方式。内部网络的所有主机均可共享一个合法外部IP地址实现对Internet的访问，从而可以最大限度地节约IP地址资源。同时，又可隐藏网络内部的所有主机，有效避免来自internet的攻击。因此，目前网络中应用最多的就是端口多路复用方式。

ALG（Application Level Gateway），即应用程序级网关技术：传统的NAT技术只对IP层和传输层头部进行转换处理，但是一些应用层协议，在协议数据报文中包含了地址信息。为了使得这些应用也能透明地完成NAT转换，NAT使用一种称作ALG的技术，它能对这些应用程序在通信时所包含的地址信息也进行相应的NAT转换。例如：对于FTP协议的PORT/PASV命令. DNS协议的 "A" 和 "PTR" queries命令和部分ICMP消息类型等都需要相应的ALG来支持。

# 存储

一致性哈希


Redis 介绍

Redis 是一款开源的，基于 BSD 许可的，高级键值 (key-value) 缓存 (cache) 和存储 (store) 系统。由于 Redis 的键包括 string，hash，list，set，sorted set，bitmap 和 hyperloglog，所以常常被称为数据结构服务器。你可以在这些类型上面运行原子操作，例如，追加字符串，增加哈希中的值，加入一个元素到列表，计算集合的交集. 并集和差集，或者是从有序集合中获取最高排名的元素。

超高性能

腾讯redis 性能高达10W+ QPS，超高的性能可以满足您绝大部分场景需求，非常适用于游戏，移动，广告，电商等开发场景


文档数据库MongoDB

文档数据库MongoDB（Cloud MongoDB Service）是腾讯云基于全球广受欢迎的MongoDB打造的高性能NoSQL数据库，100%完全兼容MongoDB协议，提供稳定丰富的监控管理，弹性可扩展. 自动容灾，适用于文档型数据库场景，使您无需自建灾备体系及控制管理系统。


## 算法

### [面试题之strcpy/strlen/strcat/strcmp的实现](http://songlee24.github.io/2015/03/15/string-operating-function/)


```c
#include <assert.h>
void assert( int expression );
```

assert的作用是现计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行。请看下面的程序清单badptr.c：


字符串拷贝strcpy

阿里的电面要我用C/C++实现一个字符串拷贝的函数，虽然以前写过 strcpy 的函数实现，但时间过去很久了，再加上有点紧张，突然就措手不及了。最后写是写出来了，但没考虑异常的情况，面试官好像很不满意。(T_T)，写篇文章记录一下，以免日后重蹈覆辙。

函数strcpy的原型是char* strcpy(char* des , const char* src)，des 和 src 所指内存区域不可以重叠且 des 必须有足够的空间来容纳 src 的字符串。


```c
#include <assert.h>
#include <stdio.h>

char* strcpy(char* des, const char* src)
{
	assert((des!=NULL) && (src!=NULL)); 
	char *address = des;  
	while((*des++ = *src++) != '\0');  
	return address;
}
```

要知道 strcpy 会拷贝’\0’，还有要注意：

源指针所指的字符串内容是不能修改的，因此应该声明为 const 类型。

要判断源指针和目的指针为空的情况，思维要严谨，这里使用assert（见文末）。

要用一个临时变量保存目的串的首地址，最后返回这个首地址。

函数返回 char* 的目的是为了支持链式表达式，即strcpy可以作为其他函数的实参。

字符串长度strlen

```c
#include <assert.h>
#include <stdio.h>

int strlen(const char* str)
{
	assert(str != NULL);
	int len = 0;
	while((*str++) != '\0')
		++len;
	return len;
}
```

函数strcat的原型是char* strcat(char* des, char* src)，des 和 src 所指内存区域不可以重叠且 des 必须有足够的空间来容纳 src 的字符串。

```c
#include <assert.h>
#include <stdio.h>

char* strcat(char* des, const char* src)   // const表明为输入参数 
{  
	assert((des!=NULL) && (src!=NULL));
	char* address = des;
	while(*des != '\0')  // 移动到字符串末尾
		++des;
	while(*des++ = *src++)
		;
	return address;
}
```



### C/C++内存对齐

下面是网易的一道笔试题：struct { uint32_t m1; char m2; } varray[2];以下哪些判断一定成立？（多选）

```
sizeof(varray[0]) == 5
sizeof(varray[0]) == 8
(void*)&(varray[0].m1) < (void*)&(varray[0].m2)
(char*)&varray[0] == (char*)&(varray[0].m1)
(char*)&varray[0] + sizeof(varray[0]) == (char*)&varray[1]
(char*)&(varray[0].m2) + 1 == (char*)&varray[1]
(char*)&(varray[0].m2) + 4 == (char*)&varray[1]
这个题目考查的就是内存对齐的知识点，看完这篇文章你就知道这道题应该选什么了。
```

举一个简单的例子，uint32_t所占内存空间为 4 bytes，char为 1 byte。如果把它们放在一个结构体中，则所占的内存空间应该是 4 + 1 = 5 bytes 。而事实上，在VS2012和gcc环境下，sizeof 操作的结果都是 8 bytes：

```c
struct
{
    uint32_t m1;    // #include<stdint.h>
    char m2;
}varray;

int main()
{
    printf("%d\n",sizeof(varray.m1));  // 输出4
    printf("%d\n",sizeof(varray.m2));  // 输出1
    printf("%d\n",sizeof(varray));     // 输出8
    return 0;
}
```

![](http://img.blog.csdn.net/20140921230124812?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGlzb25nbGlzb25nbGlzb25n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

1）概念：

有效对齐值：是 #pragma pack指定值 和 结构体中最长数据类型长度 中较小的那个。有效对齐值也叫对齐单位。

注意：VS. VC 默认是#pragma pack(8)，而 gcc 默认是#pragma pack(4)，并且gcc只支持1，2，4对齐。

2）规则：

结构体变量的首地址是有效对齐值（对齐单位）的整数倍。

结构体第一个成员的偏移量（offset）为0，以后每个成员相对于结构体首地址的 offset 都是该成员大小与有效对齐值中较小那个的整数倍，如有需要编译器会在成员之间加上填充字节。

结构体的总大小为 有效对齐值 的整数倍，如有需要编译器会在最末一个成员之后加上填充字节。

结构体内类型相同的连续元素将在连续的空间内，和数组一样。

下面给出几个例子帮助理解（测试环境为VS2012）：


```c
struct
{
    int i;    // 4个字节
    char c1;  // 1个字节
    char c2;  // 1个字节
}x1;

struct
{
    char c1;  // 1个字节
    int i;    // 4个字节
    char c2;  // 1个字节
}x2;

struct
{
    char c1;  // 1个字节
    char c2;  // 1个字节
    int i;    // 4个字节
}x3;

int main()
{
    printf("%d\n",sizeof(x1));  // 输出8
    printf("%d\n",sizeof(x2));  // 输出12
    printf("%d\n",sizeof(x3));  // 输出8
    return 0;
}
```

![](http://img.blog.csdn.net/20140922013948031?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGlzb25nbGlzb25nbGlzb25n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

