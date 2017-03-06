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

```

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

### 集合框架

![](http://img.blog.csdn.net/20130430102251761)




### string，stringBuilder,StringBuffer
### 二叉树遍历
### Arrays.sort实现原理和Collection实现原理
### Object常用方法和equal和hashCode
### 什么是多态（我举得例子：beanFactory）
### session的实现机制
