# C++ STL

# std sort函数的时间复杂度

[知无涯之std::sort源码剖析](http://feihu.me/blog/2014/sgi-std-sort/)

堆排序经常是作为快速排序最有力的竞争者出现，它们的复杂度都是O(N logN)。这里有一个维基百科上的动态图片，直观的反应出堆排序的过程：

![](http://feihu.me/img/posts/stl-heapsort.gif)



# 堆排序缺点何在？

堆排序比快排   make poor use of cache memory？

## 插入排序的优点

它在数据大致有序的情况表现非常好，可以达到O(N)，


## 横空出世

到了正式介绍新算法的时刻。由于快速排序有着前面所描述的问题，因此Musser在1996年发表了一遍论文，提出了Introspective Sorting(内省式排序)，这里可以找到PDF版本。它是一种混合式的排序算法，集成了前面提到的三种算法各自的优点：

1. 在数据量很大时采用正常的快速排序，此时效率为O(logN)。
1. 一旦分段后的数据量小于某个阈值，就改用插入排序，因为此时这个分段是基本有序的，这时效率可达O(N)。
1. 在递归过程中，如果递归层次过深，分割行为有恶化倾向时，它能够自动侦测出来，使用堆排序来处理，在此情况下，使其效率维持在堆排序的O(N logN)，但这又比一开始使用堆排序好。

由此可知，它乃综合各家之长的算法。也正因为如此，C++的标准库就用其作为std::sort的标准实现。


## std::sort适合哪些容器

这么高效的算法，是不是所有的容器都可以使用呢？我们常规数组是否也能使用？我们知道在STL中的容器可以大致分为：

- 序列式容器：vector, list, deque
- 关联式容器：set, map, multiset, multimap
- 配置器容器：queue, stack, priority_queue
- 无序关联式容器：unordered_set, unordered_map, unordered_multiset, unordered_multimap。这些是在C++ 11中引入的


剩下的三种序列式容器中，vector和deque拥有随机访问迭代器，因此它们可以使用std::sort排序。

而list只有双向迭代器，所以它无法使用std::sort，但好在它提供了自己的sort成员函数。

另外，我们最常使用的数组其实和vector一样，它的指针本质上就是一种迭代器，而且是随机访问迭代器，因此也可以使用std::sort。

# 组件

STL的设计非常巧妙，组件间互取短长，形成了一个世界，这是这个世界里的组件：

1. containers（容器）：所谓容器，是指存放数据的地方，将数据以一定的方法组织存放。根据不同的组织方式，可以把容器分为顺序容器，如vector. deque. list，关联容器，如set. map。Container是一种class template。
2. algorithm（算法）：各种常用不常用的算法如sort. copy. search等等。algorithm是一种function template。
3. iterator（迭代器）：迭代器是算法和容器之前的胶合剂，算法作用于容器之上，但算法以迭代器作为形参。从实现上看，迭代器是一种将operator*，operator++，operator--，operator->等指针相关操作予以重载的class template。所以容器都带有自己的迭代器，因为只有容器设计者才知道如何遍历自己的元素。
4. functors（仿函数）：行为类似函数，可作为算法的某种策略。从实现的角度来看，仿函数是一种重载了operator()的class或class template，它常常是算法的一个输入，类似于一种策略。
5. adapters（适配器）：用来形容容器. 迭代器或仿函数接口的东西，有时候上面那些组件的行为可能跟我们想要的约束不大一样，于是给它们包装一下，使它们遵守一定的行为。
6. allocator（配置器）：负责空间配置与管理。从实现的角度来看，配置器是一种实现了动态空间配置. 管理. 空间释放的class template。


# 空间配置器

为解决内存破碎问题.定义了两层配置器.

小于128bit认为小. 采用内存池的方式.


总结起来整个过程大概是这样的，假设我们向系统要x大小的内存，

1. x大于128byte，用第一级配置器直接向系统malloc，至于不成功的处理，过程仿照new，通过set_new_handler来处理，直到成功返回相应大小的内存或者是抛出异常或者是干脆结束运行；
1. x小于128byte，用第二级配置器向内存池相应的free_list要内存，如果该freelist上面没有空闲块了，
	1. 从内存池里面要内存，差不多要的是<=20个相应freelist大小的块，如果要不到：
	1. 从系统的heap里面要内存给到内存池，换算的标准是bytes_to_get=2*total_bytes+ROUND_UP(heap_size>>4)，这时使用的是系统的malloc，如果要不到：
	1. 从比较大的freelist那里要内存到内存池，如果还是要不到：
	1. 从系统的heap里面要内存给到内存池，换算标准跟2.2一样，但是这时候使用的是第一级配置器的allocate，主要是看看能不能通过out_of_memory机制得到一点内存。所以，freelist总是从内存池里要内存的，而内存池可能从freelist也可能从系统heap那里要内存。

sgi stl的alloc的主要开销就在于管理这些小内存，管理这些小内存的主要开销就在于，每次freelist上的内存块用完了，需要重新要空间，然后建立起这个list来。freelist上的内存，会一直保留着直到程序退出才还给系统。但这不会产生内存泄漏，一来是管理的都是小内存，二来是，占用的内存只会是整个程序运行过程中小内存占用量最大的那一刻所占用的内存。


# 迭代器

中心思想: 将数据容器和算法分开

  Iterator模式有三个重要的作用：

1. 它支持以不同的方式遍历一个聚合.复杂的聚合可用多种方式进行遍历，如二叉树的遍历，可以采用前序. 中序或后序遍历。迭代器模式使得改变遍历算法变得很容易: 仅需用一个不同的迭代器的实例代替原先的实例即可，你也可以自己定义迭代器的子类以支持新的遍历，或者可以在遍历中增加一些逻辑，如有条件的遍历等。
2. 迭代器简化了聚合的接口. 有了迭代器的遍历接口，聚合本身就不再需要类似的遍历接口了，这样就简化了聚合的接口。
3. 在同一个聚合上可以有多个遍历 每个迭代器保持它自己的遍历状态，因此你可以同时进行多个遍历。
4. 此外，Iterator模式可以为遍历不同的聚合结构（需拥有相同的基类）提供一个统一的接口，即支持多态迭代。

简单说来，迭代器模式也是Delegate原则的一个应用，它将对集合进行遍历的功能封装成独立的Iterator，不但简化了集合的接口，也使得修改. 增 加遍历方式变得简单。从这一点讲，该模式与Bridge模式. Strategy模式有一定的相似性，但Iterator模式所讨论的问题与集合密切相关， 造成在Iterator在实现上具有一定的特殊性，具体将在示例部分进行讨论。


## 迭代器相应类别

通过template参数推导.


# 序列式容器


容器是用于存储数据的STL类，STL提供了两种类型的容器类：
   
1.  顺序容器

顾名思义，顺序容器按顺序存储数据，如数组和列表。顺序容器具有插入速度快但查找操作慢的性质。
    
STL顺序容器包括：

1. std::vector : 操作与动态数组一样，在最后插入数据
1. std::deque :与上面的类型，但也允许在开头插入新元素
1. std:list:操作和链表一样。

适配器:
stack

queue


```c
#include <vector> 
vector <int> vecIntArray;  
vecIntArray.push_back(1988);  
vecIntArray.push_back(2);  
vecIntArray.push_back(20);  
vecIntArray.push_back(2013);  
vecIntArray.push_back(11);  
vecIntArray.push_back(2);  
cout << "动态数组的内容是：" << endl;  
vector <int>::iterator iArrayWalker = vecIntArray.begin();  
while ( iArrayWalker != vecIntArray.end() ){  
        cout << *iArrayWalker << endl;  
        ++ iArrayWalker;  
}  
```

vector当容量超过当前的容量. 容量增加两倍.


list作为stack的底层容器.

<!-- 以list作为queue的底层容器 -->

2. 关联容器
联容器按照指定的顺序存储数据，减低插入数据的速度，但是查找数据更方便。

STL提供的关联容器包括

1. std::set ： 按顺序排列的唯一值列表。 
1. std::map:   存储键-值对，并更具唯一的键将键-值对排序
1. std::multimap:     与set类型，但是允许存储多个值相同的项，即值不需要是唯一的
1. std::multimap:    与map类似，但不要求键是唯一的。 
  



```c

```

```c

```

```c

```

```c

```

```c

```

# 关联式容器
