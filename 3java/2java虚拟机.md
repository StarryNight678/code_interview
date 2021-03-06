# Java 虚拟机


##  内存管理与垃圾回收

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm1-1.png)

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-1.jpg)


- 程序计数器

程序计数器是一块较小的内存空间，它的作用可以看作是当前线程所执行的字节码的行号指示器。在虚拟机的概念模型中，字节码解释器工作时就是通过改变这个计数器的值来选取下一条需要执行的字节码指令，分支. 循环. 跳转. 异常等基础功能都需要依赖这个计器来完成。

JVM的多线程是通过线程轮流切换并分配处理器执行时间的方式来实现的，因为为了线程切换后能恢复到正确的执行位置每条线程都需要一个独立的程序计数器，因此应该为“线程私有”的内存。

- Java虚拟机栈

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-2.jpg)

- 本地方法栈

- Java堆

- 方法区

方法区也是各个线程共享的内存区域，用于存放已被虚拟机加载的**类信息. 常量. 静态变量**. 即时编译器编译后的代码等数据。

在JVM规范中，没有强制要求方法区必须实现垃圾回收。很多人习惯将方法区称为“永久代”，是因为HotSpot虚拟机以永久代来实现方法区，从而JVM的垃圾收集器可以像管理堆区一样管理这部分区域，从而不需要专门为这部分设计垃圾回收机制。不过自从JDK7之后，Hotspot虚拟机便将运行时常量池从永久代移除了。


- 运行时常量池

该区域是方法区的一部分。在Class文件中除了类的字段. 方法. 接口等描述信息外，还有一项信息是常量池，用来存储编译期间生成的字面量和符号引用。

运行时常量池是每一个类或接口的常量池的运行时表示形式，在类和接口被加载到JVM后，对应的运行时常量池就被创建出来。当然并非Class文件常量池中的内容才能进入运行时常量池，在运行期间也可将新的常量放入运行时常量池中，比如String的intern方法。



## 对象访问

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-3.png)


# 垃圾收集


我们在上文中介绍了Java内存运行时区域的各个部分，

- 其中程序计数器. 虚拟机栈. 本地方法栈三个区域随线程而生而灭；

栈中的栈帧随着方法的进入和退出而有条不紊的执行着出栈和入栈操作。每一个栈帧分配多少内存基本上在类结构确定下来时就已知的，这几个区域的内存分配和回收都具有确定性，这这几个区域不需要过多考虑回收的问题。

- Java堆和方法区就不一样了，这部分内存的分配和回收是动态的，垃圾收集器所关注的是这部分内存。





## 引用计数法

**早期策略**


优点：引用计数收集器可以很快的执行，交织在程序运行中。对程序需要不被长时间打断的实时环境比较有利。

缺点：无法检测出循环引用。如父对象有一个对子对象的引用，子对象反过来引用父对象。这样，他们的引用计数永远不可能为0.


## 标记-清除算法(Mark-Sweep)

- 根搜索算法

根搜索算法是从离散数学中的图论引入的，程序把所有的引用关系看作一张图，从一个节点GC ROOT开始，寻找对应的引用节点，找到这个节点以后，继续寻找这个节点的引用节点，当所有的引用节点寻找完毕之后，剩余的节点则被认为是没有被引用到的节点，即无用的节点。


java中可作为GC Root的对象有：

1. 虚拟机栈中引用的对象（本地变量表）
1. 方法区中静态属性引用的对象
1. 方法区中常量引用的对象
1. 本地方法栈中引用的对象（Native对象）

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-6.jpg)

如上图。标记-清除算法采用从根集合进行扫描，对存活的对象对象标记，标记完毕后，再扫描整个空间中未被标记的对象，进行回收，如上图所示。标记-清除算法不需要进行对象的移动，并且仅对不存活的对象进行处理，在存活对象比较多的情况下极为高效，但由于标记-清除算法直接回收不存活的对象，因此会造成内存碎片。
该算法是最基础的收集算法，后续的收集算法都是基于这种思想并对其缺点进行改进得到的。它的主要缺点有两个：

效率问题，标记和清除过程的效率都不高

空间问题，标记清除之后会产生大量不连续的内存碎片，空间碎片太多可能会导致，当程序以后的运行过程中需要分配较大对象时无法找到足够的连续内存而不得不提前触发另一次垃圾收集动作。

## 复制算法

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-7.jpg)

该算法的提出是为了克服句柄的开销和解决堆碎片的垃圾回收。它开始时把堆分成 一个对象 面和多个空闲面， 程序从对象面为对象分配空间，当对象满了，基于copying算法的垃圾 收集就从根集中扫描活动对象，并将每个 活动对象复制到空闲面(使得活动对象所占的内存之间没有空闲洞)，这样空闲面变成了对象面，原来的对象面变成了空闲面，程序会在新的对象面中分配内存。
现在的商业虚拟机都采用这种收集算法来回收新生代。更加详细的信息将会在后边介绍。

## 标记-整理算法

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-8.jpg)

标记-整理算法采用标记-清除算法一样的方式进行对象的标记，但在清除时不同，在回收不存活的对象占用的空间后，会将所有的存活对象往左端空闲空间移动，并更新对应的指针。标记-整理算法是在标记-清除算法的基础上，又进行了对象的移动，因此成本更高，但是却解决了内存碎片的问题。

## 分代收集算法

分代的垃圾回收策略，是基于这样一个事实：不同的对象的生命周期是不一样的。

一般为新生代. 老年代和永久代，

这样就可以根据各个年代的特点采用最适当的收集算法。

在新生代中，每次垃圾收集时都会有大批对象死去，那就选用复制算法。

而老年代因为对象存活率高，而没有额外空间对它进行分配担保，必须采用“标记-清除”或者“标记-清理”算法。


- 新生代

所有新生成的对象首先都是放在新生轻代的。新生代的目标就是尽可能快速的收集掉那些生命周期短的对象。
新生代内存按照8:1:1的比例

分为一个eden区和两个survivor(survivor0,survivor1)区。一个Eden区，两个 Survivor区(一般而言)。

大部分对象在Eden区中生成。回收时先将eden区存活对象复制到一个survivor0区，然后清空eden区，当这个survivor0区也存放满了时，则将eden区和survivor0区存活对象复制到另一个survivor1区，然后清空eden和这个survivor0区，此时survivor0区是空的，然后将survivor0区和survivor1区交换，即保持survivor1区为空， 如此往复。
当survivor1区不足以存放 eden和survivor0的存活对象时，就将存活对象直接存放到老年代。（这里指的是老年代对其进行分配担保）
新生代发生的GC也叫做Minor GC，MinorGC发生频率比较高(不一定等Eden区满了才触发)

- 老年代

在年轻代中经历了N次垃圾回收后仍然存活的对象，就会被放到年老代中。因此，可以认为年老代中存放的都是一些生命周期较长的对象。
内存比新生代也大很多(大概比例是1:2)，当老年代内存满时触发Major GC即Full GC，Full GC发生频率比较低，老年代对象存活时间比较长，存活率标记高。

- 持久代

用于存放静态文件，如Java类. 方法等。持久代对垃圾回收没有显著影响，但是有些应用可能动态生成或者调用一些class，例如Hibernate 等，在这种时候需要设置一个比较大的持久代空间来存放这些运行过程中新增的



## 垃圾收集器

![](http://7xk5ao.com1.z0.glb.clouddn.com/jvm2-9.jpg)

新生代收集器使用的收集器：Serial. PraNew. Parallel Scavenge

老年代收集器使用的收集器：Serial Old. Parallel Old. CMS


1. Serial收集器（复制算法)：新生代单线程收集器，标记和清理都是单线程，优点是简单高效。
1. Serial Old收集器(标记-整理算法)：老年代单线程收集器，Serial收集器的老年代版本。
1. ParNew收集器(停止-复制算法)：新生代收集器，可以认为是Serial收集器的多线程版本,在多核CPU环境下有着比Serial更好的表现。
1. Parallel Scavenge收集器(停止-复制算法)：并行收集器，追求高吞吐量，高效利用CPU。吞吐量一般为99%， 吞吐量= 用户线程时间/(用户线程时间+GC线程时间)。适合后台应用等对交互相应要求不高的场景。
1. Parallel Old收集器(停止-复制算法)：Parallel Scavenge收集器的老年代版本，并行收集器，吞吐量优先
1. CMS(Concurrent Mark Sweep)收集器（标记-清理算法）：高并发. 低停顿，追求最短GC回收停顿时间，cpu占用比较高，响应时间快，停顿时间短，多核cpu 追求高响应时间的选择


## 内存分配策略

给对象分配内存以及回收分配给对象的内存。

Java所提倡的自动内存管理最终可以归结为自动化的解决了两个问题：给对象分配内存以及回收分配给对象的内存。
下面来讨论一下给对象分配内存的策略。
下面是几条最普遍的内存分配规则：

对象优先在Eden分配：大多数情况下，对象在新生代Eden区中分配。当Eden区没有足够的空间进行分配的时候，虚拟机将发起一次Minor GC。
大对象直接进入老年代：所谓大对象指的是需要大量连续内存空间的Java对象，最典型的的大对象就是那种很长的字符串及数组。
长期存活的对象将进入老年代：虚拟机给每个对象定义了一个对象年龄计数器。如果对象在Eden每熬过一次Minor GC，年龄增加1，当年龄增加到一定成都，就会晋升到老年代中

## Java有了GC同样会出现内存泄露问题

1. 静态集合类像HashMap. Vector等的使用最容易出现内存泄露，这些静态变量的生命周期和应用程序一致，所有的对象Object也不能被释放，因为他们也将一直被Vector等应用着。


2. 各种连接，数据库连接，网络连接，IO连接等没有显示调用close关闭，不被GC回收导致内存泄露。
3. 监听器的使用，在释放对象的同时没有相应删除监听器的时候也可能导致内存泄露。


# JVM类加载机制

1. 类加载的时机
1. 类加载的过程
1. 类加载器


虚拟机把描述类的数据从Class文件加载到内存，并对数据进行校验、转换解析和初始化，最终形成可以被虚拟机直接使用的Java类型，这就是虚拟机的类加载机制。


类从被加载到虚拟机内存中开始，到卸载出内存为止，整个生命周期包括了：加载、验证、准备、解析、初始化、使用和卸载七个阶段。其中验证、准备和解析三个部分通称为连接。


遇到new、getstatic、putstatic或invokestatic这4条字节码指令时，如果类没有进行过初始化，则需要先触发其初始化。
使用java.lang.reflect包的方法对类进行反射调用的时候，如果类没有进行过初始化，则需要先触发其初始化。
当初始化一个类的时候，如果发现其父类还没有进行过初始化，则需要先触发其父类的初始化。
当虚拟机启动时，用户需要指定一个要执行的主类（包含main()方法的那个类），虚拟机会先初始化这个类。


## 加载

1. 通过一个类的全限定名来获取定义此类的二进制字节流。
1. 将这个字节流所代表的静态存储结构转化为方法区的运行时数据结构。
1. 在Java堆中生成一个代表这个类的java.lang.Class对象，作为方法区这些数据的访问入口。


线程私有的如下：

1. 程序计数器当前线程所执行的字节码的行号指示器
1. Java虚拟机栈Java方法执行的内存模型，每个方法被执行时都会创建一个栈帧，存储局部变量表、操作栈、动态链接、方法出口等信息。
1. 每个线程都有自己独立的栈空间
1. 线程栈只存基本类型和对象地址
1. 方法中局部变量在线程空间中
1. 本地方法栈Native方法服务。在HotSpot虚拟机中和Java虚拟机栈合二为一。

线程共享的如下：

1. Java堆存放对象实例，几乎所有的对象实例以及其属性都在这里分配内存。
1. 方法区存储已经被虚拟机加载的类信息、常量、静态变量、JIT编译后的代码等数据。
1. 运行时常量池方法区的一部分。用于存放编译期生成的各种字面量和符号引用。
1. 直接内存NIO、Native函数直接分配的堆外内存。DirectBuffer引用也会使用此部分内存。


## 对象访问

通过句柄访问

![](http://www.rowkey.me/images/blog_images/javamm/access_object_handler.png)


直接指针

![](http://www.rowkey.me/images/blog_images/javamm/access_direct.png)


- 内存溢出

在JVM申请内存的过程中，会遇到无法申请到足够内存，从而导致内存溢出的情况。一般有以下几种情况：

- 虚拟机栈和本地方法栈溢出
StackOverflowError: 线程请求的栈深度大于虚拟机所允许的最大深度(循环递归)
OutOfMemoryError: 虚拟机在扩展栈是无法申请到足够的内存空间，一般可以通过不停地创建线程引起此种情况

- Java堆溢出: 当创建大量对象并且对象生命周期都很长的情况下，会引发OutOfMemoryError

运行时常量区溢出：OutOfMemoryError:PermGen space，这里一个典型的例子就是String的intern方法，当大量字符串使用intern时，会触发此内存溢出
方法区溢出：方法区存放Class等元数据信息，如果产生大量的类(使用cglib)，那么就会引发此内存溢出，OutOfMemoryError:PermGen space，在使用Hibernate等框架时会容易引起此种情况。
















