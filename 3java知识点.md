# Java知识点

## finally 语句

[关于 Java 中 finally 语句块的深度辨析](https://www.ibm.com/developerworks/cn/java/j-lo-finally/)

try语句执行了 `System.exit(0);` finally语句不会执行.

其实，关于 try，catch，finally 的执行流程远非这么简单，有兴趣的读者可以参考 Java 语言规范第三版（《The Java™ Language Specification, Third Edition》）中对于 Execution of try-catch-finally 的描述，非常复杂的一个流程。限于篇幅的原因，本文不做摘录，请感兴趣的读者自行阅读。


finally 语句块在 try 语句块中的 return 语句之前执行。

其实 finally 语句块是在 try 或者 catch 中的 return 语句之前执行的。更加一般的说法是，finally 语句块应该是在控制转移语句之前执行，控制转移语句除了 return 外，还有 break 和 continue。另外，throw 语句也属于控制转移语句。虽然 return、throw、break 和 continue 都是控制转移语句，但是它们之间是有区别的。

其中 return 和 throw 把程序控制权转交给它们的调用者（invoker），而 break 和 continue 的控制权是在当前方法内转移。请大家先记住它们的区别，在后续的分析中我们还会谈到。

```java
 public class Test { 
 public static void main(String[] args) { 
        System.out.println("return value of getValue(): " + getValue()); 
     } 

 public static int getValue() { 
        try { 
                 return 0; 
        } finally { 
                 return 1; 
            } 
     } 
 }
```

**返回1;**

```java
public class Test {
    public static void main(String[] args) {
        System.out.println("return value of getValue(): " + getValue());
    }

    public static int getValue() {
        int i = 1;
        try {
            return i;
        } finally {
            i++;
        }
    }
}
```

**返回1;**

关于 Java 虚拟机是如何编译 finally 语句块的问题，有兴趣的读者可以参考《 The JavaTM Virtual Machine Specification, Second Edition 》中 7.13 节 Compiling finally。那里详细介绍了 Java 虚拟机是如何编译 finally 语句块。实际上，Java 虚拟机会把 finally 语句块作为 subroutine（对于这个 subroutine 不知该如何翻译为好，干脆就不翻译了，免得产生歧义和误解。）直接插入到 try 语句块或者 catch 语句块的控制转移语句之前。但是，还有另外一个不可忽视的因素，那就是在执行 subroutine（也就是 finally 语句块）之前，try 或者 catch 语句块会保留其返回值到本地变量表（Local Variable Table）中。待 subroutine 执行完毕之后，再恢复保留的返回值到操作数栈中，然后通过 return 或者 throw 语句将其返回给该方法的调用者（invoker）。请注意，前文中我们曾经提到过 return、throw 和 break、continue 的区别，对于这条规则（保留返回值），只适用于 return 和 throw 语句，不适用于 break 和 continue 语句，因为它们根本就没有返回值。



```java
public class Test {
    public static void main(String[] args) {
        System.out.println(test());
    }

    public static String test() {
        try {
            System.out.println("try block");
            return test1();
        } finally {
            System.out.println("finally block");
        }
    }

    public static String test1() {
        System.out.println("return statement");
        return "after return";
    }
}
```


返回值

```
try block
return statement
finally block
after return
```

## jdb

java调试工具


## 

 一、Java基础

   1. String类为什么是final的

	最佳答案：
	主要是为了“效率” 和 “安全性” 的缘故。若 String允许被继承, 由于它的高度被使用率, 可能会降低程序的性能，所以String被定义成final。

	String类不可变性的好处

	只有当字符串是不可变的，字符串池才有可能实现。字符串池的实现可以在运行时节约很多heap空间，因为不同的字符串变量都指向池中的同一个字符串。但如果字符串是可变的，那么String interning将不能实现(译者注：String interning是指对不同的字符串仅仅只保存一个，即不会保存多个相同的字符串。)，因为这样的话，如果变量改变了它的值，那么其它指向这个值的变量的值也会一起改变。

	如果字符串是可变的，那么会引起很严重的安全问题。譬如，数据库的用户名、密码都是以字符串的形式传入来获得数据库的连接，或者在socket编程中，主机名和端口都是以字符串的形式传入。因为字符串是不可变的，所以它的值是不可改变的，否则黑客们可以钻到空子，改变字符串指向的对象的值，造成安全漏洞。
	因为字符串是不可变的，所以是多线程安全的，同一个字符串实例可以被多个线程共享。这样便不用因为线程安全问题而使用同步。字符串自己便是线程安全的。

	类加载器要用到字符串，不可变性提供了安全性，以便正确的类被加载。譬如你想加载java.sql.Connection类，而这个值被改成了myhacked.Connection，那么会对你的数据库造成不可知的破坏。
	因为字符串是不可变的，所以在它创建的时候hashcode就被缓存了，不需要重新计算。这就使得字符串很适合作为Map




   2. HashMap的源码，实现原理，底层结构。

   HashMap是基于哈希表的Map接口的非同步实现。此实现提供所有可选的映射操作，并允许使用null值和null键。此类不保证映射的顺序，特别是它不保证该顺序恒久不变。

	![](http://dl.iteye.com/upload/picture/pic/63364/042032ea-6f15-3428-bfb4-b3b1460769a7.jpg)


    从上图中可以看出，HashMap底层就是一个数组结构，数组中的每一项又是一个链表。当新建一个HashMap的时候，就会初始化一个数组。

    先根据key的hashCode重新计算hash值,如果数组该位置上已经存放有其他元素了，那么在这个位置上的元素将以链表的形式存放，新加入的放在链头，最先加入的放在链尾。如果数组该位置上没有元素，就直接将该元素放到此数组中的该位置上。

    HashMap的resize（rehash）：
   当HashMap中的元素越来越多的时候，hash冲突的几率也就越来越高，因为数组的长度是固定的。所以为了提高查询的效率，就要对HashMap的数组进行扩容，数组扩容这个操作也会出现在ArrayList中，这是一个常用的操作，而在HashMap数组扩容之后，最消耗性能的点就出现了：原数组中的数据必须重新计算其在新数组中的位置，并放进去，这就是resize。
   那么HashMap什么时候进行扩容呢？当HashMap中的元素个数超过数组大小*loadFactor时，就会进行数组扩容，loadFactor的默认值为0.75，这是一个折中的取值。也就是说，默认情况下，数组大小为16，那么当HashMap中元素个数超过16*0.75=12的时候，就把数组的大小扩展为 2*16=32，即扩大一倍，然后重新计算每个元素在数组中的位置，而这是一个非常消耗性能的操作，所以如果我们已经预知HashMap中元素的个数，那么预设元素的个数能够有效的提高HashMap的性能。





   3. 说说你知道的几个Java集合类：list、set、queue、map实现类。

- List:

   ArrayList, LinkedList,AttributeList, CopyOnWriteArrayList,  Stack, Vector

- queue:

ArrayDeque,LinkedList, ArrayBlockingQueue, ConcurrentLinkedQueue, DelayQueue, LinkedBlockingDeque, LinkedBlockingQueue, , LinkedTransferQueue, PriorityBlockingQueue, PriorityQueue, SynchronousQueue

ConcurrentLinkedDeque

-set

 EnumSet, HashSet,LinkedHashSet,TreeSet,ConcurrentSkipListSet, CopyOnWriteArraySet,

- map

ConcurrentHashMap, ConcurrentSkipListMap, EnumMap, HashMap, IdentityHashMap, TreeMap, WeakHashMap

ConcurrentHashMap
ConcurrentLinkedDeque
ConcurrentLinkedQueue
ConcurrentSkipListMap
ConcurrentSkipListSet



   4. 描述一下ArrayList和LinkedList各自实现和区别

   5. Java中的队列都有哪些，有什么区别。

   6. 反射中，Class.forName和classloader的区别。

Class.forName(className)方法，其实调用的方法是Class.forName(className,true,classloader);注意看第2个boolean参数，它表示的意思，在loadClass后必须初始化。比较下我们前面准备jvm加载类的知识，我们可以清晰的看到在执行过此方法后，目标对象的 static块代码已经被执行，static参数也已经被初始化。

 再看ClassLoader.loadClass(className)方法，其实他调用的方法是ClassLoader.loadClass(className,false);还是注意看第2个 boolean参数，该参数表示目标对象被装载后不进行链接，这就意味这不会去执行该类静态块中间的内容。因此2者的区别就显而易见了。


 class.forName()前者除了将类的.class文件加载到jvm中之外，还会对类进行解释，执行类中的static块。

而classLoader只干一件事情，就是将.class文件加载到jvm中，不会执行static中的内容,只有在newInstance才会去执行static块。

Class.forName(name, initialize, loader)带参函数也可控制是否加载static块。并且只有调用了newInstance()方法采用调用构造函数，创建类的对象
看下Class.forName()源码


   7. Java7、Java8的新特性


java7 新特性

switch中可以使用字串了


java8 新特性

Lambda 表达式:。它允许我们将一个函数当作方法的参数（传递函数），

函数式接口

语言的设计者们思考了很多如何让现有的功能和lambda表达式友好兼容。于是就有了函数接口这个概念。函数接口是一种只有一个方法的接口，像这样地，函数接口可以隐式地转换成lambda表达式。


   8. Java数组和链表两种结构的操作效率，在哪些情况下(从开头开始，从结尾开始，从中间开始)，哪些操作(插入，查找，删除)的效率高。

   9. Java内存泄露的问题调查定位：jmap，jstack的使用等等。

[Java内存泄露监控工具：JVM监控工具介绍](http://developer.51cto.com/art/201203/321431.htm)


jstack -- 如果java程序崩溃生成core文件，jstack工具可以用来获得core文件的java stack和native stack的信息，从而可以轻松地知道java程序是如何崩溃和在程序何处发生问题。另外，jstack工具还可以附属到正在运行的java程序中，看到 当时运行的java程序的java stack和native stack的信息, 如果现在运行的java程序呈现hung的状态，jstack是非常有用的。目前只有在Solaris和Linux的JDK版本里面才有。

jconsole – jconsole是基于Java Management Extensions (JMX)的实时图形化监测工具，这个工具利用了内建到JVM里面的JMX指令来提供实时的性能和资源的监控，包括了Java 程序的内存使用，Heap size, 线程的状态，类的分配状态和空间使用等等。

jinfo – jinfo可以从core文件里面知道崩溃的Java应用程序的配置信息，目前只有在Solaris和Linux的JDK版本里面才有。

jmap – jmap 可以从core文件或进程中获得内存的具体匹配情况，包括Heap size, Perm size等等，目前只有在Solaris和Linux的JDK版本里面才有。

jdb – jdb 用来对core文件和正在运行的Java进程进行实时地调试，里面包含了丰富的命令帮助您进行调试，它的功能和Sun studio里面所带的dbx非常相似，但 jdb是专门用来针对Java应用程序的。

jstat – jstat利用了JVM内建的指令对Java应用程序的资源和性能进行实时的命令行的监控，包括了对Heap size和垃圾回收状况的监控等等。

jps – jps是用来查看JVM里面所有进程的具体状态, 包括进程ID，进程启动的路径等等

   10. string、stringbuilder、stringbuffer区别

   11. hashtable和hashmap的区别


   13 .异常的结构，运行时异常和非运行时异常，各举个例子。

运行时异常和非运行时异常
（1）运行时异常都是RuntimeException类及其子类异常，如NullPointerException、IndexOutOfBoundsException等，这些异常是不检查异常，程序中可以选择捕获处理，也可以不处理。这些异常一般是由程序逻辑错误引起的，程序应该从逻辑角度尽可能避免这类异常的发生。

（2）非运行时异常是RuntimeException以外的异常，类型上都属于Exception类及其子类。从程序语法角度讲是必须进行处理的异常，如果不处理，程序就不能编译通过。如IOException、SQLException等以及用户自定义的Exception异常，一般情况下不自定义检查异常。


   14. String 类的常用方法

   16. Java 的引用类型有哪几种

强、软、弱和虚引用

软: 可有可无的引用.

弱: 比软生命周期更短


   17. 抽象类和接口的区别

   18. java的基础类型和字节大小


   19. Hashtable,HashMap,ConcurrentHashMap底层实现原理与线程安全问题。

效率低下的HashTable容器
     HashTable容器使用synchronized来保证线程安全，但在线程竞争激烈的情况下HashTable的效率非常低下。因为当一个线程访问HashTable的同步方法时，其他线程访问HashTable的同步方法时，可能会进入阻塞或轮询状态。如线程1使用put进行添加元素，线程2不但不能使用put方法添加元素，并且也不能使用get方法来获取元素，所以竞争越激烈效率越低。


ConcurrentHashMap的锁分段技术

     HashTable容器在竞争激烈的并发环境下表现出效率低下的原因，是因为所有访问HashTable的线程都必须竞争同一把锁，那假如容器里有多把锁，每一把锁用于锁容器其中一部分数据，那么当多线程访问容器里不同数据段的数据时，线程间就不会存在锁竞争，从而可以有效的提高并发访问效率，这就是ConcurrentHashMap所使用的锁分段技术，首先将数据分成一段一段的存储，然后给每一段数据配一把锁，当一个线程占用锁访问其中一个段数据的时候，其他段的数据也能被其他线程访问。

![](http://ifeve.com/wp-content/uploads/2012/12/ConcurrentHashMap%E7%B1%BB%E5%9B%BE.jpg)

ConcurrentHashMap是由Segment数组结构和HashEntry数组结构组成。Segment是一种可重入锁ReentrantLock，在ConcurrentHashMap里扮演锁的角色，HashEntry则用于存储键值对数据。一个ConcurrentHashMap里包含一个Segment数组，Segment的结构和HashMap类似，是一种数组和链表结构， 一个Segment里包含一个HashEntry数组，每个HashEntry是一个链表结构的元素， 每个Segment守护者一个HashEntry数组里的元素,当对HashEntry数组的数据进行修改时，必须首先获得它对应的Segment锁。

![](http://ifeve.com/wp-content/uploads/2012/12/ConcurrentHashMap%E7%BB%93%E6%9E%84%E5%9B%BE.jpg)


[探索 ConcurrentHashMap 高并发性的实现机制](https://www.ibm.com/developerworks/cn/java/java-lo-concurrenthashmap/)

内存模型:

内存可见性
由于现代可共享内存的多处理器架构可能导致一个线程无法马上（甚至永远）看到另一个线程操作产生的结果。所以 Java 内存模型规定了 JVM 的一种最小保证：什么时候写入一个变量对其他线程可见。
在现代可共享内存的多处理器体系结构中每个处理器都有自己的缓存，并周期性的与主内存协调一致。假设线程 A 写入一个变量值 V，随后另一个线程 B 读取变量 V 的值，在下列情况下，线程 B 读取的值可能不是线程 A 写入的最新值：
执行线程 A 的处理器把变量 V 缓存到寄存器中。
执行线程 A 的处理器把变量 V 缓存到自己的缓存中，但还没有同步刷新到主内存中去。
执行线程 B 的处理器的缓存中有变量 V 的旧值。



下面介绍几个与理解 ConcurrentHashMap 有关的 happens-before 关系法则：
程序次序法则：如果在程序中，所有动作 A 出现在动作 B 
之前，则线程中的每动作 A 都 happens-before 于该线程中的每一个动作 B。
监视器锁法则：对一个监视器的解锁 happens-before 于每个后续对同一监视器的加锁。
Volatile 变量法则：对 Volatile 域的写入操作 happens-before 于每个后续对同一 Volatile 的读操作。
传递性：如果 A happens-before 于 B，且 B happens-before C，则 A happens-before C。




   20. 如果不让你用Java Jdk提供的工具，你自己实现一个Map，你怎么做。说了好久，说了HashMap源代码，如果我做，就会借鉴HashMap的原理，说了一通HashMap实现。

   21. Hash冲突怎么办？哪些解决散列冲突的方法？

   22. HashMap冲突很厉害，最差性能，你会怎么解决?从O（n）提升到log（n）。


HashMap会动态的使用一个专门的treemap实现来替换掉它。这样做的结果会更好，是O(logn)，而不是糟糕的O(n)。它是如何工作的？前面产生冲突的那些KEY对应的记录只是简单的追加到一个链表后面，这些记录只能通过遍历来进行查找。但是超过这个阈值后HashMap开始将列表升级成一个二叉树，使用哈希值作为树的分支变量，

[Java 8：HashMap的性能提升](http://www.importnew.com/14417.html)

   23. rehash

   24. hashCode() 与 equals() 生成算法、方法怎么重写。

   二、Java IO

   1. 讲讲IO里面的常见类，字节流、字符流、接口、实现类、方法阻塞。

   2. 讲讲NIO

   3. String 编码UTF-8 和GBK的区别？

   4. 什么时候使用字节流、什么时候使用字符流？

 处理对象不同：字节流能处理所有类型的数据（如图片、avi等），而字符流只能处理字符类型的数据。 结论：只要是处理纯文本数据，就优先考虑使用字符流

   5. 递归读取文件夹下的文件，代码怎么实现？

   三、Java Web

   1. session和cookie的区别和联系，session的生命周期，多个服务部署时session管理。

   2. servlet的一些相关问题

   3. webservice相关问题

   4. jdbc连接，forname方式的步骤，怎么声明使用一个事务。

   5. 无框架下配置web.xml的主要配置内容

   6. jsp和servlet的区别

   四、JVM

   1. Java的内存模型以及GC算法

   2. jvm性能调优都做了什么

GC的时间足够的小
GC的次数足够的少
发生Full GC的周期足够的长

     其中New和Tenured属于堆内存，堆内存会从JVM启动参数（-Xmx:3G）指定的内存中分配，Perm不属于堆内存，有虚拟机直接分配，但可以通过-XX:PermSize -XX:MaxPermSize 等参数调整其大小。

 JAVA_OPTS="$JAVA_OPTS -server -Xms3G -Xmx3G -Xss256k -XX:PermSize=128m -XX:MaxPermSize=128m -XX:+UseParallelOldGC -XX:+HeapDumpOnOutOfMemoryError -XX:HeapDumpPath=/usr/aaa/dump -XX:+PrintGCDetails -XX:+PrintGCTimeStamps -Xloggc:/usr/aaa/dump/heap_trace.txt -XX:NewSize=1G -XX:MaxNewSize=1G"

  （5）线程堆栈的设置：每个线程默认会开启1M的堆栈，用于存放栈帧、调用参数、局部变量等，对大多数应用而言这个默认值太了，一般256K就足用。理论上，在内存不变的情况下，减少每个线程的堆栈，可以产生更多的线程，但这实际上还受限于操作系统。


   3. 介绍JVM中7个区域，然后把每个区域可能造成内存的溢出的情况说明。

   4. 介绍GC 和GC Root不正常引用

   5. 自己从classload 加载方式，加载机制说开去，从程序运行时数据区，讲到内存分配，讲到String常量池，讲到JVM垃圾回收机制，算法，hotspot。

   6. jvm 如何分配直接内存， new 对象如何不分配在堆而是栈上，常量池解析。

   7. 数组多大放在JVM老年代

虚拟机提供了一个PretenureSizeThreshold参数，令大于这个设置值的对象直接在老年代分配。这样做的目的是避免在Eden区以及两个survivor区之间发生大量的内存复制。因为新生代收集使用的复制算法，复制算法是针对标记—清除算法的缺点，在其基础上进行改进而得到的，它将可用内存按容量分为大小相等的两块，每次只使用其中的一块，当这一块的内存用完了，就将还存活着的对象复制到另外一块内存上面，然后再把已使用过的内存空间一次清理掉。

复制算法有如下优点：

1.每次只对一块内存进行回收，运行高效。

2.内存回收时不用考虑内存碎片的出现。



   8. 老年代中数组的访问方式

   9. GC 算法，永久代对象如何 GC ， GC 有环怎么处理。

   10. 谁会被 GC ，什么时候 GC。

   11. 如果想不被 GC 怎么办

   12. 如果想在 GC 中生存 1 次怎么办

   分配直接内存

   直接内存并不是虚拟机内存的一部分，也不是Java虚拟机规范中定义的内存区域。jdk1.4中新加入的NIO，引入了通道与缓冲区的IO方式，它可以调用Native方法直接分配堆外内存，这个堆外内存就是本机内存，不会影响到堆内存的大小。


   五、开源框架

   1. hibernate和ibatis的区别

   2. 讲讲mybatis的连接池

   3. spring框架中需要引用哪些jar包，以及这些jar包的用途

   4. springMVC的原理

   5. springMVC注解的意思

   6. spring中beanFactory和ApplicationContext的联系和区别

   7. spring注入的几种方式

   8. spring如何实现事物管理的

   9. springIOC

   10. spring AOP的原理

   11. hibernate中的1级和2级缓存的使用方式以及区别原理（Lazy-Load的理解）

   12. Hibernate的原理体系架构，五大核心接口，Hibernate对象的三种状态转换，事务管理。

   六、多线程

   1. Java创建线程之后，直接调用start()方法和run()的区别

   2. 常用的线程池模式以及不同线程池的使用场景

   3. newFixedThreadPool此种线程池如果线程数达到最大值后会怎么办，底层原理。

   4. 多线程之间通信的同步问题，synchronized锁的是对象，衍伸出和synchronized相关很多的具体问题，例如同一个类不同方法都有synchronized锁，一个对象是否可以同时访问。或者一个类的static构造方法加上synchronized之后的锁的影响。

   5. 了解可重入锁的含义，以及ReentrantLock 和synchronized的区别

ReentrantLock 类实现了 Lock ，它拥有与 synchronized 相同的并发性和内存语义，但是添加了类似锁投票、定时锁等候和可中断锁等候的一些特性。此外，它还提供了在激烈争用情况下更佳的性能。（换句话说，当许多线程都想访问共享资源时，JVM 可以花更少的时候来调度线程，把更多时间用在执行线程上。）

eentrant 锁意味着什么呢？简单来说，它有一个与锁相关的获取计数器，如果拥有锁的某个线程再次得到锁，那么获取计数器就加1，然后锁需要被释放两次才能获得真正释放。这模仿了 synchronized 的语义；如果线程进入由线程已经拥有的监控器保护的 synchronized 块，就允许线程继续进行，当线程退出第二个（或者后续） synchronized 块的时候，不释放锁，只有线程退出它进入的监控器保护的第一个 synchronized 块时，才释放锁。
在查看清单 1 中的代码示例时，可以看到 Lock 和 synchronized 有一点明显的区别 —— lock 必须在 finally 块中释放。否则，如果受保护的代码将抛出异常，锁就有可能永远得不到释放！这一点区别看起来可能没什么，但是实际上，它极为重要。忘记在 finally 块中释放锁，可能会在程序中留下一个定时炸弹，当有一天炸弹爆炸时，您要花费很大力气才有找到源头在哪。而使用同步，JVM 将确保锁会获得自动释放。


   6. 同步的数据结构，例如concurrentHashMap的源码理解以及内部实现原理，为什么他是同步的且效率高。

   7. atomicinteger和Volatile等线程安全操作的关键字的理解和使用

   8. 线程间通信，wait和notify

   9. 定时线程的使用

   10. 场景：在一个主线程中，要求有大量(很多很多)子线程执行完之后，主线程才执行完成。多种方式，考虑效率。

   11. 进程和线程的区别

   12. 什么叫线程安全？

   13. 线程的几种状态

   14. 并发、同步的接口或方法

   15. HashMap 是否线程安全，为何不安全。 ConcurrentHashMap，线程安全，为何安全。底层实现是怎么样的。

   16. J.U.C下的常见类的使用。 ThreadPool的深入考察； BlockingQueue的使用。（take，poll的区别，put，offer的区别）；原子类的实现。

   17. 简单介绍下多线程的情况，从建立一个线程开始。然后怎么控制同步过程，多线程常用的方法和结构

   18. volatile的理解

   19. 实现多线程有几种方式，多线程同步怎么做，说说几个线程里常用的方法。

   七、网络通信

   1. http是无状态通信，http的请求方式有哪些，可以自己定义新的请求方式么。

   2. socket通信，以及长连接，分包，连接异常断开的处理。

   3. socket通信模型的使用，AIO和NIO。

   4. socket框架netty的使用，以及NIO的实现原理，为什么是异步非阻塞。

   5. 同步和异步，阻塞和非阻塞。

   6. OSI七层模型，包括TCP,IP的一些基本知识

   7. http中，get post的区别

   8. 说说http,tcp,udp之间关系和区别。

   9. 说说浏览器访问www.taobao.com，经历了怎样的过程。

   10. HTTP协议、  HTTPS协议，SSL协议及完整交互过程；

   11. tcp的拥塞，快回传，ip的报文丢弃

   12. https处理的一个过程，对称加密和非对称加密

   13. head各个特点和区别

   14. 说说浏览器访问www.taobao.com，经历了怎样的过程。

   八、数据库MySql

   1. MySql的存储引擎的不同

   2. 单个索引、联合索引、主键索引

   3. Mysql怎么分表，以及分表后如果想按条件分页查询怎么办

   4. 分表之后想让一个id多个表是自增的，效率实现

   5. MySql的主从实时备份同步的配置，以及原理(从库读主库的binlog)，读写分离。

   6. 写SQL语句和SQL优化

   7. 索引的数据结构，B+树

   8. 事务的四个特性，以及各自的特点（原子、隔离）等等，项目怎么解决这些问题。

   9. 数据库的锁：行锁，表锁；乐观锁，悲观锁

   悲观锁：假定会发生并发冲突，屏蔽一切可能违反数据完整性的操作。[1]      悲观锁假定其他用户企图访问或者改变你正在访问、更改的对象的概率是很高的，因此在悲观锁的环境中，在你开始改变此对象之前就将该对象锁住，并且直到你提交了所作的更改之后才释放锁。悲观的缺陷是不论是页锁还是行锁，加锁的时间可能会很长，这样可能会长时间的限制其他用户的访问，也就是说悲观锁的并发访问性不好。

乐观锁：假设不会发生并发冲突，只在提交操作时检查是否违反数据完整性。[1] 乐观锁不能解决脏读的问题。    乐观锁则认为其他用户企图改变你正在更改的对象的概率是很小的，因此乐观锁直到你准备提交所作的更改时才将对象锁住，当你读取以及改变该对象时并不加锁。可见乐观锁加锁的时间要比悲观锁短，乐观锁可以用较大的锁粒度获得较好的并发访问性能。但是如果第二个用户恰好在第一个用户提交更改之前读取了该对象，那么当他完成了自己的更改进行提交时，数据库就会发现该对象已经变化了，这样，第二个用户不得不重新读取该对象并作出更改。这说明在乐观锁环境中，会增加并发用户读取对象的次数。

   10. 数据库事务的几种粒度

   11. 关系型和非关系型数据库区别

   九、设计模式

   1. 单例模式：饱汉、饿汉。以及饿汉中的延迟加载，双重检查。

   2. 工厂模式、装饰者模式、观察者模式。

   3. 工厂方法模式的优点（低耦合、高内聚，开放封闭原则）

   十、算法

   1. 使用随机算法产生一个数，要求把1-1000W之间这些数全部生成。

   2. 两个有序数组的合并排序

   3. 一个数组的倒序

   4. 计算一个正整数的正平方根

   5. 说白了就是常见的那些查找、排序算法以及各自的时间复杂度。

   6. 二叉树的遍历算法

   7. DFS,BFS算法

   9. 比较重要的数据结构，如链表，队列，栈的基本理解及大致实现。

   10. 排序算法与时空复杂度（快排为什么不稳定，为什么你的项目还在用）

   11. 逆波兰计算器

   12. Hoffman 编码

   13. 查找树与红黑树

   十一、并发与性能调优

   1. 有个每秒钟5k个请求，查询手机号所属地的笔试题，如何设计算法?请求再多，比如5w，如何设计整个系统?

   2. 高并发情况下，我们系统是如何支撑大量的请求的

   3. 集群如何同步会话状态

   4. 负载均衡的原理

   5 .如果有一个特别大的访问量，到数据库上，怎么做优化（DB设计，DBIO，SQL优化，Java优化）

   6. 如果出现大面积并发，在不增加服务器的基础上，如何解决服务器响应不及时问题“。

   7. 假如你的项目出现性能瓶颈了，你觉得可能会是哪些方面，怎么解决问题。

   8. 如何查找 造成 性能瓶颈出现的位置，是哪个位置照成性能瓶颈。

   9. 你的项目中使用过缓存机制吗？有没用用户非本地缓存

   十二、其他

   1.常用的linux下的命令