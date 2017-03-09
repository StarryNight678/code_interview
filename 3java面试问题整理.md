# 整理


### 集合框架

![](http://img.blog.csdn.net/20130430102251761)

![](http://images.cnitblog.com/i/532548/201404/262238192165666.jpg)

![](http://i.imgur.com/mkBAWS5.png)


[Java Collections Framework（JAVA集合框架）中的常用集合实现简介](http://blog.tingyun.com/web/article/detail/396)

Collections、Arrays类

Collections、Arrays是集合类的一个工具类/帮助类，其中提供了一系列静态方法，用于对集合中
元素进行排序、搜索以及线程安全等各种操作。

### Collection

1. List<E>
1. Queue<E>
1. Set<E>

hashCode() 
equals(Object o) 
size() 
iterator() 
size() - 集合内的对象数量

add(E)/addAll(Collection) - 向集合内添加单个/批量对象

remove(Object)/removeAll(Collection) - 从集合内删除单个/批量对象

contains(Object)/containsAll(Collection) - 判断集合中是否存在某个/某些对象

toArray() - 返回包含集合内所有对象的数组

### stack

```
java.lang.Object
  继承者 java.util.AbstractCollection<E>
      继承者 java.util.AbstractList<E>
          继承者 java.util.Vector<E>
              继承者 java.util.Stack<E>
```


boolean	empty()           测试堆栈是否为空。

E	peek()           查看堆栈顶部的对象，但不从堆栈中移除它。

E	pop()           移除堆栈顶部的对象，并作为此函数的值返回该对象。

E	push(E item)           把项压入堆栈顶部。

int	search(Object o)           返回对象在堆栈中的位置，以 1 为基数。


问题由来

曾经遇到过一条面试题，“Java中的Stack是通过Vector来实现的，这种设计被认为是不良的设计，说说你的看法？”

java API说明

Deque 接口及其实现提供了 LIFO 堆栈操作的更完整和更一致的 set，应该优先使用此 set，而非此类。例如：

   Deque<Integer> stack = new ArrayDeque<Integer>();



1. 继承Vector确实不好，1没来由的多了非stack特性的方法，多了错误选择的可能性；2Vector带来了线程安全性，这个非必需的特性带来了性能丢失。
2. 使用数组实现不一定比链表实现优良。栈的大小在非常非常大的情况下，基于链表的实现才会比数组实现体现出性能优势，一般情况下，数组的实现在速度上反而超过链表的实现。因为数组元素都在cpu缓存内，而链表的元素就需要查询了。


### List

```java
public interface List<E>
extends Collection<E>
```

允许重复的元素。


List在Collection基础上增加的主要方法包括：

get(int) - 返回指定index位置上的对象

add(E)/add(int, E) - 在List末尾/指定index位置上插入一个对象

set(int, E) - 替换置于List指定index位置上的对象

indexOf(Object) - 返回指定对象在List中的index位置

subList(int,int) - 返回指定起始index到终止index的子List对象




- **实现类 **

ArrayList, Vector,LinkedList


- ArrayList

ArrayList基于**数组**来实现集合的功能，其内部维护了一个可变长的对象数组，集合内所有对象存储于这个数组中，并实现该数组长度的动态伸缩

- LinkedList

LinkedList基于**链表**来实现集合的功能，其实现了静态类Node，集合中的每个对象都由一个Node保存，每个Node都拥有到自己的前一个和后一个Node的引用

ArrayList vs LinkedList

ArrayList的寻址效率更高，基于数组实现的ArrayList可直接定位到目标对象，而LinkedList需要从头Node或尾Node开始向后/向前遍历若干次才能定位到目标对象

LinkedList的插入、删除和顺序遍历的效率更高，因为LinkedList的每一个Node都拥有上一个和下一个Node的引用。但需要注意，遍历LinkedList时应用iterator方式，不要用get(int)方式，否则效率会很低

-Vector

Vector和ArrayList很像，都是基于数组实现的集合，它和ArrayList的主要区别在于

Vector是线程安全的，而ArrayList不是

由于Vector中的方法基本都是synchronized的，其性能低于ArrayList

Vector可以定义数组长度增长的因子，ArrayList不能

### Queue

```java
public interface Queue<E>
extends Collection<E>
```
实现类LinkedList

	1. poll()  获取并移除此队列的头
	1. add(E e) 
	1. remove() 
	1. peek()   获取但不移除此队列的头

Queue接口继承Collection接口，实现FIFO（先进先出）的集合。Queue接口的常用方法包括：

add(E)/offer(E)：入队，即向队尾追加元素，二者的区别在于如果队列是有界的，add方法在队列已满的情况下会抛出IllegalStateException，而offer方法只会返回false

remove()/poll()：出队，即从队头移除1个元素，二者的区别在于如果队列是空的，remove方法会抛出NoSuchElementException，而poll只会返回null

element()/peek()：查看队头元素，二者的区别在于如果队列是空的，element方法会抛出NoSuchElementException，而peek只会返回null


- Deque

实现类 ArrayDeque, LinkedBlockingDeque, LinkedList

```java
public interface Deque<E>
extends Queue<E>
```

Deque继承了Queue接口，定义了双端队列，也就是说Deque可以从队头或队尾进行出队/入队操作。它比Queue更加灵活，可以用于实现Queue、Stack等数据结构。Deque在Queue的基础上提供了额外的方法：

addFirst(E)/addLast(E)/offerFirst(E)/offerLast(E)

removeFirst()/removeLast()/pollFirst()/pollLast()

getFirst()/getLast()/peekFirst()/peekLast()


### Set

实现类 HashSet TreeSet

不要将Collection认为是Java集合中的顶级接口，Map和Collection在层次结构
上没有必然的关系


Set的常用实现也包括 HashSet、TreeSet、ConcurrentSkipListSet等，原理和对应的Map实现完全一致，此处不再赘述。 



###  Map


size() - 集合内的对象数量 

put(K,V)/putAll(Map) - 向Map内添加单个/批量对象

get(K) - 返回Key对应的对象

remove(K) - 删除Key对应的对象

keySet() - 返回包含Map中所有key的Set

values() - 返回包含Map中所有value的Collection

entrySet() - 返回包含Map中所有key-value对的EntrySet

containsKey(K)/containsValue(V) - 判断Map中是否存在指定key/value



- HashMap

HashMap处理哈 希冲突的方法是拉链法


- Hashtable

HashMap的前身,Hashtable是线程安全的，其提供的方法几乎都是同步的。

- ConcurrentHashMap

ConcurrentHashMap是HashMap的线程安全版（自JDK1.5引入），提供比Hashtable更高效的并发性能


- HashMap vs Hashtable vs ConcurrentHashMap

三者在数据存储层面的机制基本一致

HashMap不是线程安全的，多线程环境下除了不能保证数据一致性之外，还有可能引发Entry链表成环，导致get方法死循环

Hashtable是线程安全的，能保证绝对的数据一致性，但是由于其粗暴地将所有操作加锁，性能低下

ConcurrentHashMap 也是线程安全的，使用分离锁和volatile等方法极大地提升了读写性能，同时也能保证在绝大部分情况下的数据一致性。但其不能保证绝对的数据一致性， 在一个线程向Map中加入Entry的操作没有完全完成之前，其他线程有可能读不到新加入的Entry。 

- LinkedHashMap

LinkedHashMap与HashMap非常类似，唯一的不同在于前者的Entry在HashMap.Entry的基础上增加了到前一个插入和后一个插入的Entry的引用，以实现能够按Entry的插入顺序进行遍历。 

- TreeMap

TreeMap是基于红黑树实现的Map结构，其Entry类拥有到左/右叶子节点和父节点的引用，同时还记录了自己的颜色：

TreeMap的Entry是有序的，所以提供了一系列方便的功能，比如获取以升序或降序排列的KeySet(EntrySet)、获取在指定key(Entry)之前/之后的key(Entry)等等。适合需要对key进行有序操作的场景。 


### Java垃圾回收机制二 工作原理–How Java Garbage Collection Works?


### string，stringBuilder,StringBuffer

1. String 字符串常量
1. StringBuffer 字符串变量（线程安全）
1. StringBuilder 字符串变量（非线程安全）


对 String 类型进行改变的时候其实都等同于生成了一个新的 String 对象，然后将指针指向新的 String 对象,生成的多说了 GC 就会开始工作. 速度相当慢.

在大部分情况下 StringBuffer > String
StringBuffer 上的主要操作是 append 和 insert 方法


stringBuilder一个可变的字符序列。此类提供一个与 StringBuffer 兼容的 API，但不保证同步。



### 二叉树遍历
### Arrays.sort实现原理和Collection实现原理

[Java Arrays.sort源代码解析　](http://www.cnblogs.com/gw811/archive/2012/10/04/2711746.html)

[深入理解 timsort 算法（1）：自适应归并排序](http://blog.jobbole.com/99681/)

也就是说，优化的归并排序既快速（nlog(n)）又稳定。

对于对象的排序，**稳定性很重要**。比如成绩单，一开始可能是按人员的学号顺序排好了的，现在让我们用成绩排，那么你应该保证，本来张三在李四前面，即使他们成绩相同，张三不能跑到李四的后面去。

而快速排序是不稳定的，而且最坏情况下的时间复杂度是O(n^2)。

另外，对象数组中保存的只是对象的引用，这样多次移位并不会造成额外的开销，但是，对象数组****对比较次数**一般比较敏感，有可能对象的比较比单纯数的比较开销大很多。归并排序在这方面比快速排序做得更好，这也是选择它作为对象排序的一个重要原因之一。

排序优化：实现中快排和归并都采用递归方式，而在递归的底层，也就是待排序的数组长度小于7时，直接使用**冒泡排序**，而不再递归下去。

分析：长度为6的数组冒泡排序总比较次数最多也就1+2+3+4+5+6=21次，最好情况下只有6次比较。而快排或归并涉及到递归调用等的开销，其时间效率在n较小时劣势就凸显了，因此这里采用了冒泡排序，这也是对快速排序极重要的优化。

看源代码，根据这个（java中Sort方法底层实现），应该是基于速排和优化的合并排。


- 源码中的快速排序，主要做了以下几个方面的优化


　　1）当待排序的数组中的元素个数较少时，源码中的阀值为7，采用的是插入排序。尽管插入排序的时间复杂度为0(n^2)，但是当数组元素较少时，插入排序优于快速排序，因为这时快速排序的递归操作影响性能。

　　2）较好的选择了划分元（基准元素）。能够将数组分成大致两个相等的部分，避免出现最坏的情况。例如当数组有序的的情况下，选择第一个元素作为划分元，将使得算法的时间复杂度达到O(n^2).

- 源码中选择划分元的方法

当数组大小为 size=7 时 ，取数组中间元素作为划分元。int n=m>>1;(此方法值得借鉴)

当数组大小 7<size<=40时，取首、中、末三个元素中间大小的元素作为划分元。

当数组大小 size>40 时 ，从待排数组中较均匀的选择9个元素，选出一个伪中数做为划分元。

　　3）根据划分元 v ，形成不变式 v* (<v)* (>v)* v*

　　普通的快速排序算法，经过一次划分后，将划分元排到素组较中间的位置，左边的元素小于划分元，右边的元素大于划分元，而没有将与划分元相等的元素放在其附近，这一点，在Arrays.sort()中得到了较大的优化。

　　举例：15、93、15、41、6、15、22、7、15、20

　　因  7<size<=40,所以在15、6、和20 中选择v = 15 作为划分元。

　　经过一次换分后： 15、15、7、6、41、20、22、93、15、15. 与划分元相等的元素都移到了素组的两边。

　　接下来将与划分元相等的元素移到数组中间来，形成：7、6、15、15、15、15、41、20、22、93.

　　最后递归对两个区间进行排序[7、6]和[41、20、22、93].


- 事实上Collections.sort方法底层就是调用的array.sort方法，而且不论是Collections.sort或者是Arrays.sort方法

不论是Collections.sort方法或者是Arrays.sort方法，底层实现都是TimSort实现的，这是jdk1.7新增的，以前是归并排序。**TimSort算法**就是找到已经排好序数据的子序列，然后对剩余部分排序，然后合并起来 


### TimSort算法


[Timsort算法简介](http://xieyan87.com/2015/08/timsort%E7%AE%97%E6%B3%95%E7%AE%80%E4%BB%8B/)

Timsort是一种结合了归并排序和插入排序的混合算法，由Tim Peters在2002年提出，并且已经成为Python 2.3版本以后内置排序算法，并且Java SE 7, Android平台，GNU Octave也引入了这一排序算法。简单来说，这个算法可以概括为两步：
1. 第一步就是把待排数组划分成一个个run，当然run不能太短，如果长度小于minrun这个阈值，则用插入排序进行扩充；
2. 第二步将run入栈，当栈顶的run的长度满足：runLen[n-2] <= runLen[n-1] + runLen[n]或者 runLen[n-1] <= runLen[n], 则对两个短run归并为一个新run，则到只剩栈顶元素时排序也完成了。


Timsort算法作为一个稳定性的排序算法，最好时间复杂度为O(n)O(n), 平均和最坏复杂度都为O(nlogn)O(nlogn), 空间复杂度为O(n)O(n). Java SE 7中的Timsort内部实现对栈空间的深度是定长数组，在大多数情况下满足使用要求，


### Object常用方法和equal和hashCode

- hashCode()
返回该对象的哈希码值。

这个方法的存在主要是配合一些基于hash表的数据结构的集合，像HashMap。在这些基于hash结构的数据集合中，存放的对象要有自己的hashCode方法，除了String类型。以HashMap为例:

HashMap在存放或者检索数据时，都会先去计算的key的hash值。这些基于hash表的集合，只能要求被存放的对象实现自己的hash方法，保证hash的均匀性。在jdk中，为了保证一个通用的计算hash的方法，jvm采用将对象的内部地址转换成一个整数来实现我们也可以根据自己的逻辑修改hashcode方法


- equals(Object o)

用于测试某个对象是否同另一个对象相等

在Java语言中要比较两个对象是否相等，有时只用"=="是不行的，还有这个equals方法。比如在Java中比较两个字符串相等，那就必须使用equals方法
因为，==计算表达式在判断引用对象时，只是去判断内存地址引用是否一样，而equals方法才会去判断内存的值是否一样或是按照自实行逻辑去判断。

-必要时重写equals

equals方法在很多地方会调用，包括我们直接调用equals方法，还有判断集合对象是否相等时的间接调用。在这种间接调用时，我们一般都会去重写它的equals方法。比如，有个User对象，我们认为User的id相等就是同一个对象

重写equals方法的要求：

1. 自反性：对于任何非空引用x，x.equals(x)应该返回true。
1. 对称性：对于任何引用x和y，如果x.equals(y)返回true，那么y.equals(x)也应该返回true。
1. 传递性：对于任何引用x、y和z，如果x.equals(y)返回true，y.equals(z)返回true，那么x.equals(z)1. 也应该返回true。
1. 一致性：如果x和y引用的对象没有发生变化，那么反复调用x.equals(y)应该返回同样的结果。
1. 非空性：对于任意非空引用x，x.equals(null)应该返回false。


-重写了equals方法要不要重写hashCode方法

当我们重写hashcode方法时，都会有一套模板，我们使用到的编辑器一般都会支持基于模板自动生成。如果留心，你会发现当你使用这个功能时重写equals方法会自动也把hashcode方法重写。


在Java规范中，要求：

如果a.equals(b),那么a和b的hashcode方法一定要相等，但a和b不相等时，hashcode方法可以相等也可以不相等。所以当我们重写了它的equals方法后，最好遵从这份规范，修改它的hashcode方法。


### 什么是多态（我举得例子：beanFactory）
### session的实现机制

因此在web应用开发里就出现了保持http链接状态的技术：一个是cookie技术，另一种是session技术。

- cookie技术是客户端的解决方案

Cookie就是由服务器发给客户端的特殊信息，而这些信息以文本文件的方式存放在客户端，然后客户端每次向服务器发送请求的时候都会带上这些特殊的信息。让我们说得更具体一些：当用户使用浏览器访问一个支持Cookie的网站的时候，用户会提供包括用户名在内的个人信息并且提交至服务器；接着，服务器在向客户端回传相应的超文本的同时也会发回这些个人信息，当然这些信息并不是存放在HTTP响应体（Response Body）中的，而是存放于HTTP响应头（Response Header）；当客户端浏览器接收到来自服务器的响应之后，浏览器会将这些信息存放在一个统一的位置，对于Windows操作系统而言，我们可以从： [系统盘]:\Documents and Settings\[用户名]\Cookies目录中找到存储的Cookie；自此，客户端再向服务器发送请求的时候，都会把相应的Cookie再次发回至服务器。而这次，Cookie信息则存放在HTTP请求头（Request Header）了。有了Cookie这样的技术实现，服务器在接收到来自客户端浏览器的请求之后，就能够通过分析存放于请求头的Cookie得到客户端特有的信息，从而动态生成与该客户端相对应的内容。通常，我们可以从很多网站的登录界面中看到“请记住我”这样的选项，如果你勾选了它之后再登录，那么在下一次访问该网站的时候就不需要进行重复而繁琐的登录动作了，而这个功能就是通过Cookie实现的。

session技术则是服务端的解决方案，**它是通过服务器来保持状态的**

Session指的是服务器端为客户端所开辟的存储空间，在其中保存的信息就是用于保持状态。


Java中是通过调用HttpServletRequest的getSession方法（使用true作为参数）创建的。在创建了Session的同时，服务器会为该Session生成唯一的Session id，而这个Session id在随后的请求中会被用来重新获得已经创建的Session

。由于Session这个词汇包含的语义很多，因此需要在这里明确一下 Session的含义。首先，我们通常都会把Session翻译成会话，因此我们可以把客户端浏览器与服务器之间一系列交互的动作称为一个 Session。从这个语义出发，我们会提到Session持续的时间，会提到在Session过程中进行了什么操作等等；其次，Session指的是服务器端为客户端所开辟的存储空间，在其中保存的信息就是用于保持状态。从这个语义出发，我们则会提到往Session中存放什么内容，如何根据键值从 Session中获取匹配的内容等。要使用Session，第一步当然是创建Session了。那么Session在何时创建呢？当然还是在服务器端程序运行的过程中创建的，不同语言实现的应用程序有不同创建Session的方法，而在Java中是通过调用HttpServletRequest的getSession方法（使用true作为参数）创建的。在创建了Session的同时，服务器会为该Session生成唯一的Session id，而这个Session id在随后的请求中会被用来重新获得已经创建的Session；在Session被创建之后，就可以调用Session相关的方法往Session中增加内容了，而这些内容只会保存在服务器中，发到客户端的只有Session id；当客户端再次发送请求的时候，会将这个Session id带上，服务器接受到请求之后就会依据Session id找到相应的Session，从而再次使用之。正式这样一个过程，用户的状态也就得以保持了。
 
  
### TCP/IP协议过程




## java面试宝典2016版

1. java跳出多层循环

```java
ok:
for(int i=0;i<10;i++) {
	for(int j=0;j<10;j++) {
	System.out.println(“i=” + i + “,j=” + j);
	if(j == 5) break ok;
	}
}
```

或者采用标志数字

```java
for(int i=0;i<arr.length&& !found;i++) {
	for(int j=0;j<arr[i].length;j++){
	System.out.println(“i=” + i + “,j=” + j);
	if(arr[i][j] ==5) {
		found = true;
		break;
		}
	}
}
```

1. switch

switch（expr1）中，expr1只能是一个整数表达式或者枚举常量（更大字体），整数表达式可以是int基本类型或Integer包装类型，由于，byte,short,char都可以隐含转换为int，可以.
long和String类型都不符合switch的语法规定，并且不能被隐式转换成int类型，所以，它们不能作用于swtich语句中。

1. 使用final关键字修饰一个变量时，是指引用变量不能变，引用变量所指向的对象中的内容还是可以改变的。

1. == 和 equals 区别

a==b, 数值是否相等. 对象的话,比较是否是一个对象,内存是否相等.

equals比较对象内容是否相同.


1. 是否可以从一个static方法内部发出对非static方法的调用？


	不可以。因为非static方法是要与对象关联在一起的，必须创建一个对象后，才可以在该对象上进行方法调用，而static方法调用时不需要创建对象，可以直接调用。也就是说，当一个static方法被调用时，可能还没有创建任何实例对象，如果从一个static方法中发出对非static方法的调用，那个非static方法是关联到哪个对象上的呢？这个逻辑无法成立，所以，一个static方法内部发出对非static方法的调用。


1. Integer 和  int 区别

	int的默认值为0，而Integer的默认值为null，即Integer可以区分出未赋值和值为0的区别，int则无法表达出未赋值的情况




1. Math类中提供了三个与取整有关的方法：ceil. floor. round

	这些方法的作用与它们的英文名称的含义相对应，例如，ceil的英文意义是天花板，该方法就表示向上取整，Math.ceil(11.3)的结果为12,Math.ceil(-11.3)的结果是-11；floor的英文意义是地板，该方法就表示向下取整，Math.ceil(11.6)的结果为11,Math.ceil(-11.6)的结果是-12；最难掌握的是round方法，它表示“四舍五入”，算法为Math.floor(x+0.5)，即将原来的数字加上0.5后再向下取整，所以，Math.round(11.5)的结果为12，Math.round(-11.5)的结果为-11。


-  Overload是重载的意思，Override是覆盖的意思，也就是重写。

	重载Overload表示同一个类中可以有多个名称相同的方法，即参数个数或类型不同。

	重写Override:

	表示子类中的方法可以与父类中的某个方法的名称和参数完全相同，通过子类创建的实例对象调用这个方法时，将调用子类中的定义方法，这相当于把父类中定义的那个完全相同的方法给覆盖了，这也是面向对象编程的多态性的一种表现。子类覆盖父类的方法时，只能比父类抛出更少的异常，或者是抛出父类抛出的异常的子异常，因为子类可以解决父类的一些问题，不能比父类有更多的问题。子类方法的访问权限只能比父类的更大，不能更小。如果父类的方法是private类型，那么，子类则不存在覆盖的限制，相当于子类中增加了一个全新的方法。


1. 覆盖的方法的标志必须要和被覆盖的方法的标志完全匹配，才能达到覆盖的效果；
2. 覆盖的方法的返回值必须和被覆盖的方法的返回一致；
3. 覆盖的方法所抛出的异常必须和被覆盖方法的所抛出的异常一致，或者是其子类；
4. 被覆盖的方法不能为private，否则在其子类中只是新定义了一个方法，并没有对其进行覆盖。



- 构造器Constructor是否可被override?

构造器Constructor不能被继承，因此不能重写Override，但可以被重载Overload


- 接口是否可继承接口?抽象类是否可实现(implements)接口?抽象类是否可继承具体类(concrete class)?抽象类中是否可以有静态的main方法？

接口可以继承接口。抽象类可以实现(implements)接口，抽象类可以继承具体类。抽象类中可以有静态的main方法。

只有记住抽象类与普通类的唯一区别：**就是不能创建实例对象和允许有abstract方法。**

- 面向对象的特征有哪些方面 

封装:这就是面向对象的封装性，即将对象封装成一个高度自治和相对封闭的个体，对象状态（属性）由这个对象自己的行为（方法）来读取和改变


抽象:包括行为抽象和状态抽象

继承: 提高了软件的可重用性和可扩展性。

多态：因为在程序运行时才确定具体的类，这样，不用修改源程序代码，就可以让引用变量绑定到各种不同的类实现上，从而导致该引用调用的具体方法随之改变

多态存在的三个必要条件:
继承
重写
父类引用指向子类对象

**靠的是父类或接口定义的引用变量可以指向子类或具体实现类的实例对象**

- Java中实现多态的机制是什么？

- abstract class和interface有什么区别?

	1. 抽象类可以有构造方法，接口中不能有构造方法。
	2. 抽象类中可以有普通成员变量，接口中没有普通成员变量
	3. 抽象类中可以包含非抽象的普通方法，接口中的所有方法必须都是抽象的，不能有非抽象的普通方法。
	4. 抽象类中的抽象方法的访问类型可以是public，protected和（默认类型,虽然
	eclipse下不报错，但应该也不行），但接口中的抽象方法只能是public类型的，并且默认即为public abstract类型。
	5. 抽象类中可以包含静态方法，接口中不能包含静态方法
	6. 抽象类和接口中都可以包含静态成员变量，抽象类中的静态成员变量的访问类型可以任意，但接口中定义的变量只能是public static final类型，并且默认即为public static final类型。
	7. 一个类可以实现多个接口，但只能继承一个抽象类。

接口更多的是在系统架构设计方法发挥作用，主要用于定义模块之间的通信契约。

抽象类在代码实现方面发挥作用，可以实现代码的重用，

- abstract的method是否可同时是static,是否可同时是native，是否可同时是synchronized?

abstract的method不可以是static的，因为抽象的方法是要被子类实现的，而static与子类扯不上关系！

native方法表示该方法要用另外一种依赖平台的编程语言实现的，不存在着被子类实现的问题，所以，它也不能是抽象的，不能与abstract混用

- 什么是内部类？Static Nested Class和Inner Class的不同。

内部类就是在一个类的内部定义的类，内部类中不能定义静态成员（静态成员不是对象的特性，只是为了找一个容身之处，所以需要放到一个类中而已，这么一点小事，你还要把它放到类内部的一个类中，过分了啊！提供内部类，不是为让你干这种事情，无聊，不让你干。我想可能是既然静态成员类似c语言的全局变量，而内部类通常是用于创建内部对象用的，所以，把“全局变量”放在内部类中就是毫无意义的事情，既然是毫无意义的事情，就应该被禁止），内部类可以直接访问外部类中的成员变量，内部类可以定义在外部类的方法外面，也可以定义在外部类的方法体中.

- 内部类可以引用它的包含类的成员吗？有没有什么限制？

完全可以。如果不是静态内部类，那没有什么限制！


- String是最基本的数据类型吗?

基本数据类型包括byte、int、char、long、float、double、boolean和short。
java.lang.String类是final类型的，因此不可以继承这个类、不能修改这个类。为了提高效率节省空间，我们应该用StringBuffer类


使用String来代表字符串的话会引起很大的内存开销。因为 String对象建立之后不能再改变，所以对于每一个不同的字符串，都需要一个String对象来表示


考虑使用StringBuffer类，它允许修改

- 是否可以继承String类?

String类是final类故不可以继承




- String和StringBuffer的区别

JAVA平台提供了两个类：String和StringBuffer，它们可以储存和操作字符串，即包含多个字符的字符数据。这个String类提供了数值不可改变的字符串。而这个StringBuffer类提供的字符串进行修改。当你知道字符数据要改变的时候你就可以使用StringBuffer。典型地，你可以使用StringBuffers来动态构造字符数据。另外，String实现了equals方法，new String(“abc”).equals(newString(“abc”)的结果为true,而StringBuffer没有实现equals方法，所以，new StringBuffer(“abc”).equals(newStringBuffer(“abc”)的结果为false


效率高,只有一个对象
```java
StringBuffer sbf = new StringBuffer();
for(int i=0;i<100;i++)
{
sbf.append(i);
}
```

效率低,创建了101个对象
```java
String str = new String();
for(int i=0;i<100;i++)
{
str = str + i;
}
```

String覆盖了equals方法和hashCode方法，而StringBuffer没有覆盖equals方法和hashCode方法，所以，将StringBuffer对象存储进Java集合类中时会出现问题。


String实现了equals方法，new String(“abc”).equals(newString(“abc”)的结果为true,

而StringBuffer没有实现equals方法，所以，new StringBuffer(“abc”).equals(newStringBuffer(“abc”)的结果为false。

- 数组有没有length()这个方法? String有没有length()这个方法？

数组没有length()这个方法，有length的属性。String有有length()这个方法。


- 创建了多少对象. 

```java
String s1 = "a";
String s2 = s1 + "b";
String s3 = "a" + "b";
System.out.println(s2 == "ab");//false
System.out.println(s3 == "ab");//true
```

在编译阶段`String s3 = "a" + "b"`是直接对常量进行优化的.

下面直接相等
```java
String s="a"+"b"+"c"+"d";
System.out.println(s== "abcd");
```



- try {}里有一个return语句，那么紧跟在这个try后的finally {}里的code会不会被执行，什么时候被执行，在return前还是后?

```java
int x=1;
try{
    System.out.println(x);
}
finally{
    ++x;
}
```

输出结果为`1`.


try中的return语句调用的函数先于finally中调用的函数执行，也就是说return语句先执行，finally语句后执行。Return并不是让函数马上返回，而是return语句执行后，将把返回结果放置进函数栈中，此时函数并不是马上返回，它要执行finally语句后才真正开始返回。

- Java中的异常处理机制的简单原理和应用。

所有异常的根类为java.lang.Throwable

Throwable下面又派生了两个子类：Error和Exception，Error表示应用程序本身无法克服和恢复的一种严重问题，程序只有死的份了:说内存溢出和线程死锁等系统问题
Exception表示程序还能够克服和恢复的问题，其中又分为系统异常和普通异常，系统异常是软件本身缺陷所导致的问题，也就是软件开发人员考虑不周所导致的

普通异常是运行环境的变化或异常所导致的问题，是用户能够克服的问题，例如，网络断线，硬盘空间不够

- 请写出你最常见到的5个runtime exception。

NullPointerException、ArrayIndexOutOfBoundsException、ClassCastException。
EmptyStackException,BufferOverflowException,EventException


- JAVA语言如何进行异常处理，关键字：throws,throw,try,catch,finally分别代表什么意义？在try块中可以抛出异常吗？

throws捕获并向外抛出异常
throw抛出异常
try catch是内部捕获异常并做自定义处理
finally是无论是否有异常都会被处理的语句，除非在finally前存在被执行的System.exit(int i)时除外

- java中有几种方法可以实现一个线程？用什么关键字修饰同步方法? stop()和suspend()方法为何不推荐使

第一种:
继承Thread类，重写父类run()方法.应该用start（）方法来启动线程,start()方法会自动调用run（）方法。
```
public class thread1 extends Thread {
      public void run() {
              for (int i = 0; i < 10000; i++) {
                      System.out.println("我是线程"+this.getId());
              }
      }
      public static void main(String[] args) {
              thread1 th1 = new thread1();
              thread1 th2 = new thread1();
              th1.start();
              th2.start();
      }
   }
```


第二种:

实现runnable接口,ru# 整理

## java面试宝典2016版

1. java跳出多层循环

```java
ok:
for(int i=0;i<10;i++) {
  for(int j=0;j<10;j++) {
  System.out.println(“i=” + i + “,j=” + j);
  if(j == 5) break ok;
  }
}
```

或者采用标志数字

```java
for(int i=0;i<arr.length&& !found;i++) {
  for(int j=0;j<arr[i].length;j++){
  System.out.println(“i=” + i + “,j=” + j);
  if(arr[i][j] ==5) {
    found = true;
    break;
    }
  }
}
```

1. switch

switch（expr1）中，expr1只能是一个整数表达式或者枚举常量（更大字体），整数表达式可以是int基本类型或Integer包装类型，由于，byte,short,char都可以隐含转换为int，可以.
long和String类型都不符合switch的语法规定，并且不能被隐式转换成int类型，所以，它们不能作用于swtich语句中。

1. 使用final关键字修饰一个变量时，是指引用变量不能变，引用变量所指向的对象中的内容还是可以改变的。

1. == 和 equals 区别

a==b, 数值是否相等. 对象的话,比较是否是一个对象,内存是否相等.

equals比较对象内容是否相同.


1. 是否可以从一个static方法内部发出对非static方法的调用？


  不可以。因为非static方法是要与对象关联在一起的，必须创建一个对象后，才可以在该对象上进行方法调用，而static方法调用时不需要创建对象，可以直接调用。也就是说，当一个static方法被调用时，可能还没有创建任何实例对象，如果从一个static方法中发出对非static方法的调用，那个非static方法是关联到哪个对象上的呢？这个逻辑无法成立，所以，一个static方法内部发出对非static方法的调用。


1. Integer 和  int 区别

  int的默认值为0，而Integer的默认值为null，即Integer可以区分出未赋值和值为0的区别，int则无法表达出未赋值的情况




1. Math类中提供了三个与取整有关的方法：ceil. floor. round

  这些方法的作用与它们的英文名称的含义相对应，例如，ceil的英文意义是天花板，该方法就表示向上取整，Math.ceil(11.3)的结果为12,Math.ceil(-11.3)的结果是-11；floor的英文意义是地板，该方法就表示向下取整，Math.ceil(11.6)的结果为11,Math.ceil(-11.6)的结果是-12；最难掌握的是round方法，它表示“四舍五入”，算法为Math.floor(x+0.5)，即将原来的数字加上0.5后再向下取整，所以，Math.round(11.5)的结果为12，Math.round(-11.5)的结果为-11。


-  Overload是重载的意思，Override是覆盖的意思，也就是重写。

  重载Overload表示同一个类中可以有多个名称相同的方法，即参数个数或类型不同。

  重写Override:

  表示子类中的方法可以与父类中的某个方法的名称和参数完全相同，通过子类创建的实例对象调用这个方法时，将调用子类中的定义方法，这相当于把父类中定义的那个完全相同的方法给覆盖了，这也是面向对象编程的多态性的一种表现。子类覆盖父类的方法时，只能比父类抛出更少的异常，或者是抛出父类抛出的异常的子异常，因为子类可以解决父类的一些问题，不能比父类有更多的问题。子类方法的访问权限只能比父类的更大，不能更小。如果父类的方法是private类型，那么，子类则不存在覆盖的限制，相当于子类中增加了一个全新的方法。


1. 覆盖的方法的标志必须要和被覆盖的方法的标志完全匹配，才能达到覆盖的效果；
2. 覆盖的方法的返回值必须和被覆盖的方法的返回一致；
3. 覆盖的方法所抛出的异常必须和被覆盖方法的所抛出的异常一致，或者是其子类；
4. 被覆盖的方法不能为private，否则在其子类中只是新定义了一个方法，并没有对其进行覆盖。



- 构造器Constructor是否可被override?

构造器Constructor不能被继承，因此不能重写Override，但可以被重载Overload


- 接口是否可继承接口?抽象类是否可实现(implements)接口?抽象类是否可继承具体类(concrete class)?抽象类中是否可以有静态的main方法？

接口可以继承接口。抽象类可以实现(implements)接口，抽象类可以继承具体类。抽象类中可以有静态的main方法。

只有记住抽象类与普通类的唯一区别：**就是不能创建实例对象和允许有abstract方法。**

- 面向对象的特征有哪些方面 

封装:这就是面向对象的封装性，即将对象封装成一个高度自治和相对封闭的个体，对象状态（属性）由这个对象自己的行为（方法）来读取和改变


抽象:包括行为抽象和状态抽象

继承: 提高了软件的可重用性和可扩展性。

多态：因为在程序运行时才确定具体的类，这样，不用修改源程序代码，就可以让引用变量绑定到各种不同的类实现上，从而导致该引用调用的具体方法随之改变

多态存在的三个必要条件:
继承
重写
父类引用指向子类对象

**靠的是父类或接口定义的引用变量可以指向子类或具体实现类的实例对象**

- Java中实现多态的机制是什么？

- abstract class和interface有什么区别?

  1. 抽象类可以有构造方法，接口中不能有构造方法。
  2. 抽象类中可以有普通成员变量，接口中没有普通成员变量
  3. 抽象类中可以包含非抽象的普通方法，接口中的所有方法必须都是抽象的，不能有非抽象的普通方法。
  4. 抽象类中的抽象方法的访问类型可以是public，protected和（默认类型,虽然
  eclipse下不报错，但应该也不行），但接口中的抽象方法只能是public类型的，并且默认即为public abstract类型。
  5. 抽象类中可以包含静态方法，接口中不能包含静态方法
  6. 抽象类和接口中都可以包含静态成员变量，抽象类中的静态成员变量的访问类型可以任意，但接口中定义的变量只能是public static final类型，并且默认即为public static final类型。
  7. 一个类可以实现多个接口，但只能继承一个抽象类。

接口更多的是在系统架构设计方法发挥作用，主要用于定义模块之间的通信契约。

抽象类在代码实现方面发挥作用，可以实现代码的重用，

- abstract的method是否可同时是static,是否可同时是native，是否可同时是synchronized?

abstract的method不可以是static的，因为抽象的方法是要被子类实现的，而static与子类扯不上关系！

native方法表示该方法要用另外一种依赖平台的编程语言实现的，不存在着被子类实现的问题，所以，它也不能是抽象的，不能与abstract混用

- 什么是内部类？Static Nested Class和Inner Class的不同。

内部类就是在一个类的内部定义的类，内部类中不能定义静态成员（静态成员不是对象的特性，只是为了找一个容身之处，所以需要放到一个类中而已，这么一点小事，你还要把它放到类内部的一个类中，过分了啊！提供内部类，不是为让你干这种事情，无聊，不让你干。我想可能是既然静态成员类似c语言的全局变量，而内部类通常是用于创建内部对象用的，所以，把“全局变量”放在内部类中就是毫无意义的事情，既然是毫无意义的事情，就应该被禁止），内部类可以直接访问外部类中的成员变量，内部类可以定义在外部类的方法外面，也可以定义在外部类的方法体中.

- 内部类可以引用它的包含类的成员吗？有没有什么限制？

完全可以。如果不是静态内部类，那没有什么限制！


- String是最基本的数据类型吗?

基本数据类型包括byte、int、char、long、float、double、boolean和short。
java.lang.String类是final类型的，因此不可以继承这个类、不能修改这个类。为了提高效率节省空间，我们应该用StringBuffer类


使用String来代表字符串的话会引起很大的内存开销。因为 String对象建立之后不能再改变，所以对于每一个不同的字符串，都需要一个String对象来表示


考虑使用StringBuffer类，它允许修改

- 是否可以继承String类?

String类是final类故不可以继承




- String和StringBuffer的区别

JAVA平台提供了两个类：String和StringBuffer，它们可以储存和操作字符串，即包含多个字符的字符数据。这个String类提供了数值不可改变的字符串。而这个StringBuffer类提供的字符串进行修改。当你知道字符数据要改变的时候你就可以使用StringBuffer。典型地，你可以使用StringBuffers来动态构造字符数据。另外，String实现了equals方法，new String(“abc”).equals(newString(“abc”)的结果为true,而StringBuffer没有实现equals方法，所以，new StringBuffer(“abc”).equals(newStringBuffer(“abc”)的结果为false


效率高,只有一个对象
```java
StringBuffer sbf = new StringBuffer();
for(int i=0;i<100;i++)
{
sbf.append(i);
}
```

效率低,创建了101个对象
```java
String str = new String();
for(int i=0;i<100;i++)
{
str = str + i;
}
```

String覆盖了equals方法和hashCode方法，而StringBuffer没有覆盖equals方法和hashCode方法，所以，将StringBuffer对象存储进Java集合类中时会出现问题。


String实现了equals方法，new String(“abc”).equals(newString(“abc”)的结果为true,

而StringBuffer没有实现equals方法，所以，new StringBuffer(“abc”).equals(newStringBuffer(“abc”)的结果为false。

- 数组有没有length()这个方法? String有没有length()这个方法？

数组没有length()这个方法，有length的属性。String有有length()这个方法。


- 创建了多少对象. 

```java
String s1 = "a";
String s2 = s1 + "b";
String s3 = "a" + "b";
System.out.println(s2 == "ab");//false
System.out.println(s3 == "ab");//true
```

在编译阶段`String s3 = "a" + "b"`是直接对常量进行优化的.

下面直接相等
```java
String s="a"+"b"+"c"+"d";
System.out.println(s== "abcd");
```



- try {}里有一个return语句，那么紧跟在这个try后的finally {}里的code会不会被执行，什么时候被执行，在return前还是后?

```java
int x=1;
try{
    System.out.println(x);
}
finally{
    ++x;
}
```

输出结果为`1`.


try中的return语句调用的函数先于finally中调用的函数执行，也就是说return语句先执行，finally语句后执行。Return并不是让函数马上返回，而是return语句执行后，将把返回结果放置进函数栈中，此时函数并不是马上返回，它要执行finally语句后才真正开始返回。

- Java中的异常处理机制的简单原理和应用。

所有异常的根类为java.lang.Throwable

Throwable下面又派生了两个子类：Error和Exception，Error表示应用程序本身无法克服和恢复的一种严重问题，程序只有死的份了:说内存溢出和线程死锁等系统问题
Exception表示程序还能够克服和恢复的问题，其中又分为系统异常和普通异常，系统异常是软件本身缺陷所导致的问题，也就是软件开发人员考虑不周所导致的

普通异常是运行环境的变化或异常所导致的问题，是用户能够克服的问题，例如，网络断线，硬盘空间不够

- 请写出你最常见到的5个runtime exception。

NullPointerException、ArrayIndexOutOfBoundsException、ClassCastException。
EmptyStackException,BufferOverflowException,EventException


- JAVA语言如何进行异常处理，关键字：throws,throw,try,catch,finally分别代表什么意义？在try块中可以抛出异常吗？

throws捕获并向外抛出异常
throw抛出异常
try catch是内部捕获异常并做自定义处理
finally是无论是否有异常都会被处理的语句，除非在finally前存在被执行的System.exit(int i)时除外

- java中有几种方法可以实现一个线程？用什么关键字修饰同步方法? stop()和suspend()方法为何不推荐使

第一种:
继承Thread类，重写父类run()方法.应该用start（）方法来启动线程,start()方法会自动调用run（）方法。
```
public class thread1 extends Thread {
      public void run() {
              for (int i = 0; i < 10000; i++) {
                      System.out.println("我是线程"+this.getId());
              }
      }
      public static void main(String[] args) {
              thread1 th1 = new thread1();
              thread1 th2 = new thread1();
              th1.start();
              th2.start();
      }
   }
```


第二种:

实现runnable接口,runnable是没有start方法）。上述代码修改为：

```java
public class Test implements Runnable {
    public String ThreadName;
    public Test(String tName){
        ThreadName = tName;
    }
    public void run() {
        for (int i = 0; i < 10000; i++) {
            System.out.println(ThreadName);
        }
    }
    public static void main(String[] args) {
        System.out.println("--begin--");
        Test th1 = new Test("线程A:");
        Test th2 = new Test("线程B:");
        Thread myth1 = new Thread(th1);
        Thread myth2 = new Thread(th2);
        myth1.start();
        myth2.start();
    }
}
```

第三种

使用ExecutorService、Callable、Future实现有返回结果的多线程(JDK5.0以后)
可返回值的任务必须实现Callable接口，类似的，无返回值的任务必须Runnable接口。执行Callable任务后，可以获取一个Future的对象，在该对象上调用get就可以获取到Callable任务返回的Object了，再结合线程池接口ExecutorService就可以实现传说中有返回结果的多线程了。下面提供了一个完整的有返回结果的多线程测试例子，在JDK1.5下验证过没问题可以直接使用。代码如下：

### 集合框架
### string，stringBuilder,StringBuffer
### 二叉树遍历
### Arrays.sort实现原理和Collection实现原理
### Object常用方法和equal和hashCode
### 什么是多态（我举得例子：beanFactory）
### session的实现机制
nnable是没有start方法）。上述代码修改为：

```java
public class Test implements Runnable {
    public String ThreadName;
    public Test(String tName){
        ThreadName = tName;
    }
    public void run() {
        for (int i = 0; i < 10000; i++) {
            System.out.println(ThreadName);
        }
    }
    public static void main(String[] args) {
        System.out.println("--begin--");
        Test th1 = new Test("线程A:");
        Test th2 = new Test("线程B:");
        Thread myth1 = new Thread(th1);
        Thread myth2 = new Thread(th2);
        myth1.start();
        myth2.start();
    }
}# 整理

## java面试宝典2016版

1. java跳出多层循环

```java
ok:
for(int i=0;i<10;i++) {
  for(int j=0;j<10;j++) {
  System.out.println(“i=” + i + “,j=” + j);
  if(j == 5) break ok;
  }
}
```

或者采用标志数字

```java
for(int i=0;i<arr.length&& !found;i++) {
  for(int j=0;j<arr[i].length;j++){
  System.out.println(“i=” + i + “,j=” + j);
  if(arr[i][j] ==5) {
    found = true;
    break;
    }
  }
}
```

1. switch

switch（expr1）中，expr1只能是一个整数表达式或者枚举常量（更大字体），整数表达式可以是int基本类型或Integer包装类型，由于，byte,short,char都可以隐含转换为int，可以.
long和String类型都不符合switch的语法规定，并且不能被隐式转换成int类型，所以，它们不能作用于swtich语句中。

1. 使用final关键字修饰一个变量时，是指引用变量不能变，引用变量所指向的对象中的内容还是可以改变的。

1. == 和 equals 区别

a==b, 数值是否相等. 对象的话,比较是否是一个对象,内存是否相等.

equals比较对象内容是否相同.


1. 是否可以从一个static方法内部发出对非static方法的调用？


  不可以。因为非static方法是要与对象关联在一起的，必须创建一个对象后，才可以在该对象上进行方法调用，而static方法调用时不需要创建对象，可以直接调用。也就是说，当一个static方法被调用时，可能还没有创建任何实例对象，如果从一个static方法中发出对非static方法的调用，那个非static方法是关联到哪个对象上的呢？这个逻辑无法成立，所以，一个static方法内部发出对非static方法的调用。


1. Integer 和  int 区别

  int的默认值为0，而Integer的默认值为null，即Integer可以区分出未赋值和值为0的区别，int则无法表达出未赋值的情况




1. Math类中提供了三个与取整有关的方法：ceil. floor. round

  这些方法的作用与它们的英文名称的含义相对应，例如，ceil的英文意义是天花板，该方法就表示向上取整，Math.ceil(11.3)的结果为12,Math.ceil(-11.3)的结果是-11；floor的英文意义是地板，该方法就表示向下取整，Math.ceil(11.6)的结果为11,Math.ceil(-11.6)的结果是-12；最难掌握的是round方法，它表示“四舍五入”，算法为Math.floor(x+0.5)，即将原来的数字加上0.5后再向下取整，所以，Math.round(11.5)的结果为12，Math.round(-11.5)的结果为-11。


-  Overload是重载的意思，Override是覆盖的意思，也就是重写。

  重载Overload表示同一个类中可以有多个名称相同的方法，即参数个数或类型不同。

  重写Override:

  表示子类中的方法可以与父类中的某个方法的名称和参数完全相同，通过子类创建的实例对象调用这个方法时，将调用子类中的定义方法，这相当于把父类中定义的那个完全相同的方法给覆盖了，这也是面向对象编程的多态性的一种表现。子类覆盖父类的方法时，只能比父类抛出更少的异常，或者是抛出父类抛出的异常的子异常，因为子类可以解决父类的一些问题，不能比父类有更多的问题。子类方法的访问权限只能比父类的更大，不能更小。如果父类的方法是private类型，那么，子类则不存在覆盖的限制，相当于子类中增加了一个全新的方法。


1. 覆盖的方法的标志必须要和被覆盖的方法的标志完全匹配，才能达到覆盖的效果；
2. 覆盖的方法的返回值必须和被覆盖的方法的返回一致；
3. 覆盖的方法所抛出的异常必须和被覆盖方法的所抛出的异常一致，或者是其子类；
4. 被覆盖的方法不能为private，否则在其子类中只是新定义了一个方法，并没有对其进行覆盖。



- 构造器Constructor是否可被override?

构造器Constructor不能被继承，因此不能重写Override，但可以被重载Overload


- 接口是否可继承接口?抽象类是否可实现(implements)接口?抽象类是否可继承具体类(concrete class)?抽象类中是否可以有静态的main方法？

接口可以继承接口。抽象类可以实现(implements)接口，抽象类可以继承具体类。抽象类中可以有静态的main方法。

只有记住抽象类与普通类的唯一区别：**就是不能创建实例对象和允许有abstract方法。**

- 面向对象的特征有哪些方面 

封装:这就是面向对象的封装性，即将对象封装成一个高度自治和相对封闭的个体，对象状态（属性）由这个对象自己的行为（方法）来读取和改变


抽象:包括行为抽象和状态抽象

继承: 提高了软件的可重用性和可扩展性。

多态：因为在程序运行时才确定具体的类，这样，不用修改源程序代码，就可以让引用变量绑定到各种不同的类实现上，从而导致该引用调用的具体方法随之改变

多态存在的三个必要条件:
继承
重写
父类引用指向子类对象

**靠的是父类或接口定义的引用变量可以指向子类或具体实现类的实例对象**

- Java中实现多态的机制是什么？

- abstract class和interface有什么区别?

  1. 抽象类可以有构造方法，接口中不能有构造方法。
  2. 抽象类中可以有普通成员变量，接口中没有普通成员变量
  3. 抽象类中可以包含非抽象的普通方法，接口中的所有方法必须都是抽象的，不能有非抽象的普通方法。
  4. 抽象类中的抽象方法的访问类型可以是public，protected和（默认类型,虽然
  eclipse下不报错，但应该也不行），但接口中的抽象方法只能是public类型的，并且默认即为public abstract类型。
  5. 抽象类中可以包含静态方法，接口中不能包含静态方法
  6. 抽象类和接口中都可以包含静态成员变量，抽象类中的静态成员变量的访问类型可以任意，但接口中定义的变量只能是public static final类型，并且默认即为public static final类型。
  7. 一个类可以实现多个接口，但只能继承一个抽象类。

接口更多的是在系统架构设计方法发挥作用，主要用于定义模块之间的通信契约。

抽象类在代码实现方面发挥作用，可以实现代码的重用，

- abstract的method是否可同时是static,是否可同时是native，是否可同时是synchronized?

abstract的method不可以是static的，因为抽象的方法是要被子类实现的，而static与子类扯不上关系！

native方法表示该方法要用另外一种依赖平台的编程语言实现的，不存在着被子类实现的问题，所以，它也不能是抽象的，不能与abstract混用

- 什么是内部类？Static Nested Class和Inner Class的不同。

内部类就是在一个类的内部定义的类，内部类中不能定义静态成员（静态成员不是对象的特性，只是为了找一个容身之处，所以需要放到一个类中而已，这么一点小事，你还要把它放到类内部的一个类中，过分了啊！提供内部类，不是为让你干这种事情，无聊，不让你干。我想可能是既然静态成员类似c语言的全局变量，而内部类通常是用于创建内部对象用的，所以，把“全局变量”放在内部类中就是毫无意义的事情，既然是毫无意义的事情，就应该被禁止），内部类可以直接访问外部类中的成员变量，内部类可以定义在外部类的方法外面，也可以定义在外部类的方法体中.

- 内部类可以引用它的包含类的成员吗？有没有什么限制？

完全可以。如果不是静态内部类，那没有什么限制！


- String是最基本的数据类型吗?

基本数据类型包括byte、int、char、long、float、double、boolean和short。
java.lang.String类是final类型的，因此不可以继承这个类、不能修改这个类。为了提高效率节省空间，我们应该用StringBuffer类


使用String来代表字符串的话会引起很大的内存开销。因为 String对象建立之后不能再改变，所以对于每一个不同的字符串，都需要一个String对象来表示


考虑使用StringBuffer类，它允许修改

- 是否可以继承String类?

String类是final类故不可以继承




- String和StringBuffer的区别

JAVA平台提供了两个类：String和StringBuffer，它们可以储存和操作字符串，即包含多个字符的字符数据。这个String类提供了数值不可改变的字符串。而这个StringBuffer类提供的字符串进行修改。当你知道字符数据要改变的时候你就可以使用StringBuffer。典型地，你可以使用StringBuffers来动态构造字符数据。另外，String实现了equals方法，new String(“abc”).equals(newString(“abc”)的结果为true,而StringBuffer没有实现equals方法，所以，new StringBuffer(“abc”).equals(newStringBuffer(“abc”)的结果为false


效率高,只有一个对象
```java
StringBuffer sbf = new StringBuffer();
for(int i=0;i<100;i++)
{
sbf.append(i);
}
```

效率低,创建了101个对象
```java
String str = new String();
for(int i=0;i<100;i++)
{
str = str + i;
}
```

String覆盖了equals方法和hashCode方法，而StringBuffer没有覆盖equals方法和hashCode方法，所以，将StringBuffer对象存储进Java集合类中时会出现问题。


String实现了equals方法，new String(“abc”).equals(newString(“abc”)的结果为true,

而StringBuffer没有实现equals方法，所以，new StringBuffer(“abc”).equals(newStringBuffer(“abc”)的结果为false。

- 数组有没有length()这个方法? String有没有length()这个方法？

数组没有length()这个方法，有length的属性。String有有length()这个方法。


- 创建了多少对象. 

```java
String s1 = "a";
String s2 = s1 + "b";
String s3 = "a" + "b";
System.out.println(s2 == "ab");//false
System.out.println(s3 == "ab");//true
```

在编译阶段`String s3 = "a" + "b"`是直接对常量进行优化的.

下面直接相等
```java
String s="a"+"b"+"c"+"d";
System.out.println(s== "abcd");
```



- try {}里有一个return语句，那么紧跟在这个try后的finally {}里的code会不会被执行，什么时候被执行，在return前还是后?

```java
int x=1;
try{
    System.out.println(x);
}
finally{
    ++x;
}
```

输出结果为`1`.


try中的return语句调用的函数先于finally中调用的函数执行，也就是说return语句先执行，finally语句后执行。Return并不是让函数马上返回，而是return语句执行后，将把返回结果放置进函数栈中，此时函数并不是马上返回，它要执行finally语句后才真正开始返回。

- Java中的异常处理机制的简单原理和应用。

所有异常的根类为java.lang.Throwable

Throwable下面又派生了两个子类：Error和Exception，Error表示应用程序本身无法克服和恢复的一种严重问题，程序只有死的份了:说内存溢出和线程死锁等系统问题
Exception表示程序还能够克服和恢复的问题，其中又分为系统异常和普通异常，系统异常是软件本身缺陷所导致的问题，也就是软件开发人员考虑不周所导致的

普通异常是运行环境的变化或异常所导致的问题，是用户能够克服的问题，例如，网络断线，硬盘空间不够

- 请写出你最常见到的5个runtime exception。

NullPointerException、ArrayIndexOutOfBoundsException、ClassCastException。
EmptyStackException,BufferOverflowException,EventException


- JAVA语言如何进行异常处理，关键字：throws,throw,try,catch,finally分别代表什么意义？在try块中可以抛出异常吗？

throws捕获并向外抛出异常
throw抛出异常
try catch是内部捕获异常并做自定义处理
finally是无论是否有异常都会被处理的语句，除非在finally前存在被执行的System.exit(int i)时除外

- java中有几种方法可以实现一个线程？用什么关键字修饰同步方法? stop()和suspend()方法为何不推荐使

第一种:
继承Thread类，重写父类run()方法.应该用start（）方法来启动线程,start()方法会自动调用run（）方法。
```
public class thread1 extends Thread {
      public void run() {
              for (int i = 0; i < 10000; i++) {
                      System.out.println("我是线程"+this.getId());
              }
      }
      public static void main(String[] args) {
              thread1 th1 = new thread1();
              thread1 th2 = new thread1();
              th1.start();
              th2.start();
      }
   }
```


第二种:

实现runnable接口,runnable是没有start方法）。上述代码修改为：

```java
public class Test implements Runnable {
    public String ThreadName;
    public Test(String tName){
        ThreadName = tName;
    }
    public void run() {
        for (int i = 0; i < 10000; i++) {
            System.out.println(ThreadName);
        }
    }
    public static void main(String[] args) {
        System.out.println("--begin--");
        Test th1 = new Test("线程A:");
        Test th2 = new Test("线程B:");
        Thread myth1 = new Thread(th1);
        Thread myth2 = new Thread(th2);
        myth1.start();
        myth2.start();
    }
}
```

第三种

实现 Callable 接口

Java 5 开始提供

1. 可以返回结果（通过 Future），也可以抛出异常
1. 需要实现的是 call() 方法
1. 以上两点也是 Callable 接口 与 Runnable 接口的区别

使用ExecutorService、Callable、Future实现有返回结果的多线程(JDK5.0以后)
可返回值的任务必须实现Callable接口，类似的，无返回值的任务必须Runnable接口。执行Callable任务后，可以获取一个Future的对象，在该对象上调用get就可以获取到Callable任务返回的Object了，再结合线程池接口ExecutorService就可以实现传说中有返回结果的多线程了。

```java
public class MultiThread_Test {
    public static void main(String[] args) throws Exception {
        ExecutorService es = Executors.newSingleThreadExecutor();

        // 自动在一个新的线程上启动 MyCallable，执行 call 方法
        Future<Integer> f = es.submit(new MyCallable());

        // 当前 main 线程阻塞，直至 future 得到值
        System.out.println(f.get());

        es.shutdown();
    }
}

class MyCallable implements Callable<Integer> {
    public Integer call() {
        System.out.println(Thread.currentThread().getName());

        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return 123;
    }
}
```



### 集合框架
### string，stringBuilder,StringBuffer
### 二叉树遍历
### Arrays.sort实现原理和Collection实现原理
### Object常用方法和equal和hashCode
### 什么是多态（我举得例子：beanFactory）
### session的实现机制


第三种

使用ExecutorService、Callable、Future实现有返回结果的多线程(JDK5.0以后)
可返回值的任务必须实现Callable接口，类似的，无返回值的任务必须Runnable接口。执行Callable任务后，可以获取一个Future的对象，在该对象上调用get就可以获取到Callable任务返回的Object了，再结合线程池接口ExecutorService就可以实现传说中有返回结果的多线程了。下面提供了一个完整的有返回结果的多线程测试例子，在JDK1.5下验证过没问题可以直接使用。代码如下：


用synchronized关键字修饰同步方法

反对使用stop()，是因为它不安全。。suspend()方法容易发生死锁.

- sleep()和 wait()有什么区别?

sleep就是正在执行的线程主动让出cpu，cpu去执行其他线程，在sleep指定的时间过后，cpu才会回到这个线程上继续往下执行，如果当前线程进入了同步锁，sleep方法并不会释放锁.

wait():使一个线程处于等待状态，并且释放所持有的对象的lock。

sleep():使一个正在运行的线程处于睡眠状态，是一个静态方法，调用此方法要捕捉

wait必须在synchronized内部调用。


调用线程的start方法后线程进入就绪状态，线程调度系统将就绪状态的线程转为运行状态，遇到synchronized语句时，由运行状态转为阻塞，当synchronized获得锁后，由阻塞转为运行，在这种情况可以调用wait方法转为挂起状态，当线程关联的代码执行完后，线程变为结束状态。


同步的实现方面有两种，分别是synchronized,wait与notify

notify():唤醒一个处于等待状态的线程，注意的是在调用此方法的时候，并不能确切的唤醒某一个等待状态的线程，而是由JVM确定唤醒哪个线程，而且不是按优先级。

Allnotity():唤醒所有处入等待状态的线程，注意并不是给所有唤醒线程一个对象的锁，而是让它们竞争。


- Collection框架中实现比较要实现什么接口

comparable/comparator

- ArrayList和Vector的区别

ArrayList  线程不安全,效率高

Vector 线程安全

总结：即Vector增长原来的一倍，ArrayList增加原来的0.5倍。


- HashMap和Hashtable的区别

HashMap是Hashtable的轻量级实现（非线程安全的实现），他们都完成了Map接口，主要区别在于HashMap允许空（null）键值（key）,由于非线程安全，在只有一个线程访问的情况下，效率要高于Hashtable。

Hashtable  旧  线程安全,同步,

HashMap: 只有HashMap可以让你将空值作为一个表的条目的key或value


- List和 Map区别

- List, Set, Map是否继承自Collection接口?

List，Set是，Map不是


- List、Map、Set三个接口，存取元素时，各有什么特点？

List与Set具有相似性，它们都是单列元素的集合，所以，它们有一个功共同的父接口，叫Collection

Map与List和Set不同，它是双列的集合，其中有put方法，定义如下：put(obj key,objvalue)，每次存储时，要存储一对key/value，不能存储重复的key，

hashset集合比较两个对象是否相等，首先看hashcode方法是否相等，然后看equals方法是否相等

- 说出ArrayList,Vector, LinkedList的存储性能和特性


ArrayList和Vector都是使用数组方式存储数据，此数组元素数大于实际存储的数据以便增加和插入元素，它们都允许直接按序号索引元素，但是插入元素要涉及数组元素移动等内存操作，所以索引数据快而插入数据慢，Vector由于使用了synchronized方法（线程安全），通常性能上较ArrayList差，而LinkedList使用双向链表实现存储，按序号索引数据需要进行前向或后向遍历，但是插入数据时只需要记录本项的前后项即可，所以插入速度较快。
LinkedList也是线程不安全的，LinkedList提供了一些方法，使得LinkedList可以被当作堆栈和队列来使用

- 去掉一个Vector集合中重复的元素

还有一种简单的方式，HashSet set = new HashSet(vector);

- Collection和 Collections的区别。

Collection是集合类的上级接口，继承与他的接口主要有Set和List.

Collections是针对集合类的一个帮助类，他提供一系列静态方法实现对各种集合的搜索、排序、线程安全化等操作。

- Set里的元素是不能重复的，那么用什么方法来区分重复与否呢?是用==还是equals()?它们有何区别?



元素重复与否是使用equals()方法进行判断的。

如果对象要保存在HashSet或HashMap中，它们的equals相等，那么，它们的hashcode值就必须相等。


-  什么是java序列化，如何实现java序列化？或者请解释Serializable接口的作用。


- heap和stack有什么区别。

java的内存分为两类，一类是栈内存，一类是堆内存。栈内存是指程序进入一个方法时，会为这个方法单独分配一块私属存储空间，用于存储这个方法内部的局部变量，当这个方法结束时，分配给这个方法的栈会释放，这个栈中的变量也将随之释放。
堆是与栈作用不同的内存，一般用于存放不放在当前方法栈中的那些数据，例如，使用new创建的对象都放在堆里，所以，它不会随方法的结束而消失。

**方法中的局部变量使用final修饰后，放在堆中，而不是栈中。**

### 垃圾回收

GC采用有向图的方式记录和管理堆(heap)中的所有对象。
对象是
"可达的"，哪些对象是"不可达的"。当GC确定一些对象为"不可达"时，GC就有责任回收这些内存空间。可以。程序员可以手动执行System.gc()，通知GC运行，但是Java语言规范并不保证GC一定会执行。



