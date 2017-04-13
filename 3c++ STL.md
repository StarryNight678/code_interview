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
