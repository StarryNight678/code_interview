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