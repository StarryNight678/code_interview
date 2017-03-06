# Java工程师面试题整理

[Java工程师面试题整理校招篇](https://zhuanlan.zhihu.com/p/21513402)

那么今天的内容是社招面试中会碰到的一系列面试题目，希望可以帮助在正准备社招或者学习Java的朋友（以下资料整理来自网络，主要来自[骆昊的技术专栏](http://blog.csdn.net/jackfrued/)。

放在第一个的是一本书（Java面试宝典2016版，对于Java初级来说是一本好书） ：[pdf版下载](http://download.csdn.net/download/huangyueranbbc/9392426)

Java面试题全集（以下列出题目，整理以及看答案请转至：

# [Java面试题全集（上）](http://blog.csdn.net/jackfrued/article/details/44921941)



1. 面向对象的特征有哪些方面？
2. 访问修饰符public,private,protected,以及不写（默认）时的区别？
3. String 是最基本的数据类型吗？
4. float f=3.4;是否正确？
5. short s1 = 1; s1 = s1 + 1;有错吗?short s1 = 1; s1 += 1;有错吗？
6. Java有没有goto？
7. int和Integer有什么区别？
8. &amp;和&amp;&amp;的区别？
9. 解释内存中的栈(stack). 堆(heap)和静态区(static area)的用法。
10. Math.round(11.5) 等于多少？Math.round(-11.5)等于多少？
11. switch 是否能作用在byte 上，是否能作用在long 上，是否能作用在String上？
12. 用最有效率的方法计算2乘以8？
13. 数组有没有length()方法？String有没有length()方法？
14. 在Java中，如何跳出当前的多重嵌套循环？
15. 构造器（constructor）是否可被重写（override）？
16. 两个对象值相同(x.equals(y) == true)，但却可有不同的hash code，这句话对不对？
17. 是否可以继承String类？
18. 当一个对象被当作参数传递到一个方法后，此方法可改变这个对象的属性，并可返回变化后的结果，那么这里到底是值传递还是引用传递？
19. String和StringBuilder. StringBuffer的区别？
20. 重载（Overload）和重写（Override）的区别。重载的方法能否根据返回类型进行区分？
21. 描述一下JVM加载class文件的原理机制？
22. char 型变量中能不能存贮一个中文汉字，为什么？
23. 抽象类（abstract class）和接口（interface）有什么异同？
24. 静态嵌套类(Static Nested Class)和内部类（Inner Class）的不同？
25. Java 中会存在内存泄漏吗，请简单描述。
26. 抽象的（abstract）方法是否可同时是静态的（static）,是否可同时是本地方法（native），是否可同时被synchronized修饰？
27. 阐述静态变量和实例变量的区别。
28. 是否可以从一个静态（static）方法内部发出对非静态（non-static）方法的调用？
29. 如何实现对象克隆？
31. String s = new String("xyz");创建了几个字符串对象？
32. 接口是否可继承（extends）接口？抽象类是否可实现（implements）接口？抽象类是否可继承具体类（concrete class）？
33. 一个".java"源文件中是否可以包含多个类（不是内部类）？有什么限制？
34. Anonymous Inner Class(匿名内部类)是否可以继承其它类？是否可以实现接口？
35. 内部类可以引用它的包含类（外部类）的成员吗？有没有什么限制？
36. Java 中的final关键字有哪些用法？
38. 数据类型之间的转换：
39. 如何实现字符串的反转及替换？
40. 怎样将GB2312编码的字符串转换为ISO-8859-1编码的字符串？
41. 日期和时间：
42. 打印昨天的当前时刻。
43. 比较一下Java和JavaSciprt。
44. 什么时候用断言（assert）？
45. Error和Exception有什么区别？
46. try{}里有一个return语句，那么紧跟在这个try后的finally{}里的代码会不会被执行，什么时候被执行，在return前还是后?
47. Java语言如何进行异常处理，关键字：throws. throw. try. catch. finally分别如何使用？
48. 运行时异常与受检异常有何异同？
49. 列出一些你常见的运行时异常？
50. 阐述final. finally. finalize的区别。
51. 类ExampleA继承Exception，类ExampleB继承ExampleA。
请问执行此段代码的输出是什么？
52. List. Set. Map是否继承自Collection接口？
53. 阐述ArrayList. Vector. LinkedList的存储性能和特性。
54. Collection和Collections的区别？
55. List. Map. Set三个接口存取元素时，各有什么特点？
56. TreeMap和TreeSet在排序时如何比较元素？Collections工具类中的sort()方法如何比较元素？
57. Thread类的sleep()方法和对象的wait()方法都可以让线程暂停执行，它们有什么区别?
58. 线程的sleep()方法和yield()方法有什么区别？
59. 当一个线程进入一个对象的synchronized方法A之后，其它线程是否可进入此对象的synchronized方法B？
60. 请说出与线程同步以及线程调度相关的方法。
61. 编写多线程程序有几种实现方式？
62. synchronized关键字的用法？
63. 举例说明同步和异步。
64. 启动一个线程是调用run()还是start()方法？
65. 什么是线程池（thread pool）？
66. 线程的基本状态以及状态之间的关系？
67. 简述synchronized 和java.util.concurrent.locks.Lock的异同？
68. Java中如何实现序列化，有什么意义？
69. Java中有几种类型的流？
70. 写一个方法，输入一个文件名和一个字符串，统计这个字符串在这个文件中出现的次数。
71. 如何用Java代码列出一个目录下所有的文件？
72. 用Java的套接字编程实现一个多线程的回显（echo）服务器。
73. XML文档定义有几种形式？它们之间有何本质区别？解析XML文档有哪几种方式？
74. 你在项目中哪些地方用到了XML？
75. 阐述JDBC操作数据库的步骤。
76. Statement和PreparedStatement有什么区别？哪个性能更好？
77. 使用JDBC操作数据库时，如何提升读取数据的性能？如何提升更新数据的性能？
78. 在进行数据库编程时，连接池有什么作用？
79. 什么是DAO模式？
80. 事务的ACID是指什么？
81. JDBC中如何进行事务处理？
82. JDBC能否处理Blob和Clob？
83. 简述正则表达式及其用途。
84. Java中是如何支持正则表达式操作的？
85. 获得一个类的类对象有哪些方式？
86. 如何通过反射创建对象？
87. 如何通过反射获取和设置对象私有字段的值？
88. 如何通过反射调用对象的方法？
89. 简述一下面向对象的"六原则一法则"。
90. 简述一下你了解的设计模式。
91. 用Java写一个单例类。
92. 什么是UML？
93. UML中有哪些常用的图？
94. 用Java写一个冒泡排序。
95. 用Java写一个折半查找。

Java面试题全集（以下列出题目，看答案请转至：

# [Java面试题全集（中）](http://blog.csdn.net/jackfrued/article/details/44931137)

96. 阐述Servlet和CGI的区别?
97. Servlet接口中有哪些方法？
98. 转发（forward）和重定向（redirect）的区别？
99. JSP有哪些内置对象？作用分别是什么？
100. get和post请求的区别？
101. 常用的Web服务器有哪些？
102. JSP和Servlet是什么关系？
103. 讲解JSP中的四种作用域。
104. 如何实现JSP或Servlet的单线程模式？
105. 实现会话跟踪的技术有哪些？
106. 过滤器有哪些作用和用法？
107. 监听器有哪些作用和用法？
108. web.xml文件中可以配置哪些内容？
109. 你的项目中使用过哪些JSTL标签？
110. 使用标签库有什么好处？如何自定义JSP标签？
111. 说一下表达式语言（EL）的隐式对象及其作用。
112. 表达式语言（EL）支持哪些运算符？
113. Java Web开发的Model 1和Model 2分别指的是什么？
114. Servlet 3中的异步处理指的是什么？
115. 如何在基于Java的Web项目中实现文件上传和下载？
116. 服务器收到用户提交的表单数据，到底是调用Servlet的doGet()还是doPost()方法？
117. JSP中的静态包含和动态包含有什么区别？
118. Servlet中如何获取用户提交的查询参数或表单数据？
119. Servlet中如何获取用户配置的初始化参数以及服务器上下文参数？
120. 如何设置请求的编码以及响应内容的类型？
121. 解释一下网络应用的模式及其特点。
122. 什么是Web Service（Web服务）？
123. 概念解释：SOAP. WSDL. UDDI。
124. Java规范中和Web Service相关的规范有哪些？
125. 介绍一下你了解的Java领域的Web Service框架。

Java面试题全集（以下列出题目，整理以及看答案请转至：

#  [Java面试题全集（下）](http://blog.csdn.net/jackfrued/article/details/44931161)

126. 什么是ORM？
127. 持久层设计要考虑的问题有哪些？你用过的持久层框架有哪些？
128. Hibernate中SessionFactory是线程安全的吗？Session是线程安全的吗（两个线程能够共享同一个Session吗）？
129. Hibernate中Session的load和get方法的区别是什么？
130. Session的save(). update(). merge(). lock(). saveOrUpdate()和persist()方法分别是做什么的？有什么区别？
131. 阐述Session加载实体对象的过程。
132. Query接口的list方法和iterate方法有什么区别？
133. Hibernate如何实现分页查询？
134. 锁机制有什么用？简述Hibernate的悲观锁和乐观锁机制。
135. 阐述实体对象的三种状态以及转换关系。
136. 如何理解Hibernate的延迟加载机制？在实际应用中，延迟加载与Session关闭的矛盾是如何处理的？
137. 举一个多对多关联的例子，并说明如何实现多对多关联映射。
138. 谈一下你对继承映射的理解。
139. 简述Hibernate常见优化策略。
140. 谈一谈Hibernate的一级缓存. 二级缓存和查询缓存。
141. Hibernate中DetachedCriteria类是做什么的？
142. @OneToMany注解的mappedBy属性有什么作用？
143. MyBatis中使用<code>#</code>和<code>$</code>书写占位符有什么区别？
144. 解释一下MyBatis中命名空间（namespace）的作用。
145. MyBatis中的动态SQL是什么意思？
146. 什么是IoC和DI？DI是如何实现的？
147. Spring中Bean的作用域有哪些？
148. 解释一下什么叫AOP（面向切面编程）？
149. 你是如何理解"横切关注"这个概念的？
150. 你如何理解AOP中的连接点（Joinpoint）. 切点（Pointcut）. 增强（Advice）. 引介（Introduction）. 织入（Weaving）. 切面（Aspect）这些概念？
151. Spring中自动装配的方式有哪些？
152. Spring中如何使用注解来配置Bean？有哪些相关的注解？
153. Spring支持的事务管理类型有哪些？你在项目中使用哪种方式？
154. 如何在Web项目中配置Spring的IoC容器？
155. 如何在Web项目中配置Spring MVC？
156. Spring MVC的工作原理是怎样的？
157. 如何在Spring IoC容器中配置数据源？
158. 如何配置配置事务增强？
159. 选择使用Spring框架的原因（Spring框架为企业级开发带来的好处有哪些）？
160. Spring IoC容器配置Bean的方式？
161. 阐述Spring框架中Bean的生命周期？
162. 依赖注入时如何注入集合属性？
163. Spring中的自动装配有哪些限制？
164. 在Web项目中如何获得Spring的IoC容器？
165. 大型网站在架构上应当考虑哪些问题？
166. 你用过的网站前端优化的技术有哪些？
167. 你使用过的应用服务器优化技术有哪些？
168. 什么是XSS攻击？什么是SQL注入攻击？什么是CSRF攻击？
169. 什么是领域模型(domain model)？贫血模型(anaemic domain model)和充血模型(rich domain model)有什么区别？
170. 谈一谈测试驱动开发（TDD）的好处以及你的理解。


# 整理

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

```java
String s="a"+"b"+"c"+"d";
System.out.println(s== "abcd");
```

# StringBuffer
