
# Java 学习

学习项目

1. spring
1. 垃圾回收机制


- java类中的4 中成员,成员变量 方法 构造器 初始化模块.
- 垃圾回收: 分代复制,标记,增量垃圾回收.

问题说明:
1. 抽象类与接口

```java
public abstract class Demo {  
    abstract void method1();  
      
      
    void method2(){  
        //实现  
    }  
}  
```
- 抽象类提供了继承的概念.

在使用抽象类时需要注意几点

1. 抽象类不能被实例化，实例化的工作应该交由它的子类来完成，它只需要1. 即可。
1. 抽象方法必须由子类来进行重写。
1. 只要包含一个抽象方法的抽象类，该方法必须要定义成抽象类，不他方法。
1. 抽象类中可以包含具体的方法，当然也可以不包含抽象方法。
1. 子类中的抽象方法不能与父类的抽象方法同名。
1. abstract不能与final并列修饰同一个类。
1. abstract 不能与private、static、final或native并列修饰同一个方法。

- 接口

```java
interface Demo {  
    void method1();  
    void method2();  
} 
```
接口是一种比抽象类更加抽象的“类”。

接口是用来建立类与类之间的协议，它所提供的只是一种形式，而没有具体的实现。

**同时实现该接口的实现类必须要实现该接口的所有方法**，通过使用implements关键字，他表示该类在遵循某个或某组特定的接口，同时也表示着“interface只是它的外貌，但是现在需要声明它是如何工作的”。

但是接口不同，一个类可以同时实现多个接口，不管这些接口之间有没有关系，所以接口弥补了抽象类不能多重继承的缺陷

1. Interface的方所有法访问权限自动被声明为public。确切的说只能为public，当然你可以显示的声明为protected、private，但是编译会出错！
1. 接口中可以定义“成员变量”，或者说是不可变的常量，因为接口中的“成员变量”会自动变为为public static final。可以通过类命名直接访问：ImplementClass.name。
1. 接口中不存在实现的方法。
1. 实现接口的非抽象类必须要实现该接口的所有方法。抽象类可以不用实现。
1. 不能使用new操作符实例化一个接口，但可以声明一个接口变量，该变量必须引用（refer to)一个实现该接口的类的对象。可以使用 instanceof 检查一个对象是否实现了某个特定的接口。例如：if(anObject instanceof Comparable){}。
1. 在实现多接口的时候一定要避免方法名的重复。

区别:

抽象类是对类抽象，而接口是对行为的抽象。
抽象类是继承关系,接口相当于通用的规范.



<<疯狂Java讲义第3版 >>
2016-09



- 栈stack

```
public class Test2 {

    private Stack<Integer> stackData;
    private Stack<Integer> stackMin;

    public Test2() {
        this.stackData = new Stack<Integer>();
        this.stackMin = new Stack<Integer>();
    }
}

peek
public E peek()
查看堆栈顶部的对象，但不从堆栈中移除它。

pop

public E pop()
移除堆栈顶部的对象，并作为此函数的值返回该对象。

```



##  java 写文件

```
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

    String fileName = "/home/jason/code/01_test/jz_1/wordCountBolt.txt";
    try {
        BufferedWriter out=new BufferedWriter(new FileWriter(fileName));
        // 打开一个写文件器，构造函数中的第二个参数true表示以追加形式写文件      
        //     FileWriter writer = new FileWriter(fileName, true);
        out.write(str);
        out.close();
    } catch (IOException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
    }
```


## 1 java语言概述和开发环境

- PATH环境设置
添加java javac环境

JAVA_HOME = C:\Program Files\Java\jdk1.8.0_101

Path = %JAVA_HOME%\bin


- ubuntu下更改Java版本

```
update-alternatives --config java
update-alternatives --config javac
```
- CLASSPATH 
作用搜索java类
jdk 1.5以上版本完全不需要设置CLASSPATH
会自动搜索当前路径和lib\dt.jar  lib\tools.jar


-  编译程序

```
javac -d destdir srcdir
```
程序被java执行. 必须包含main方法,方法是public static void 修饰. main方法的形参必须是 `String[] args`.
**public static void 修饰符中,public 和static 修饰符位置可以互换,其余部分固定***

对于有包的问题编译运行



```
package a.c
public class Test{PP
	
}
```

方法1:
javac example.java 
需要将class文件放到 ./a/c 
java a.c.Test

方法2:
javac -d . example.java  
将会自动创建 a/c 目录.

- 程序打包,运行

	- 打包

	```
	jar
    -c  创建新档案
    -t  列出档案目录
    -x  从档案中提取指定的 (或所有) 文件
    -u  更新现有档案
    -v  在标准输出中生成详细输出
    -f  指定档案文件名
    -m  包含指定清单文件中的清单信息
    -n  创建新档案后执行 Pack200 规范化
    -e  为捆绑到可执行 jar 文件的独立应用程序指定应用程序入口点
    -0  仅存储; 不使用任何 ZIP 压缩
    -P  保留文件名中的前导 '/' (绝对路径) 和 ".." (父目录) 组件
    -M  不创建条目的清单文件
    -i  为指定的 jar 文件生成索引信息
    -C  更改为指定的目录并包含其中的文件(可以理解为首先cd到指定目录)

    打包
    jar -cvf HelloWorld.jar HelloWorld.class   #将HelloWorld.class文件打入jar包
    查看文档内容:
    jason@jason-HP:~/code$ jar tf t.jar 
	META-INF/
	META-INF/MANIFEST.MF
	a/
	a/c/
	a/c/Test.class
	jason@jason-HP:~/code$ 
	```

	- 运行

	```
	生成可以运行的jar包需要 指定应用程序入口点，用-e选项
	jason@jason-HP:~/code$ jar cvfe t.jar a.c.Test ./a
	added manifest
	adding: a/(in = 0) (out= 0)(stored 0%)
	adding: a/c/(in = 0) (out= 0)(stored 0%)
	adding: a/c/Test.class(in = 418) (out= 288)(deflated 31%)
	jason@jason-HP:~/code$ java -jar t.jar 
	hello world!
	jason@jason-HP:~/code$ 
	```

源文件的文件名必须与public类的类名相同，一个java源文件最多定义一个public类。

## 2 理解面向对象

成员变量(状态数据)+方法(行为)= 类定义

面向对象的基本特征:

1. 封装：对象细节隐藏起来
1. 继承：继承父类
1. 多态：子类对象可以直接赋给父类变量，**运行时依然是子类行为特征**。

java不支持多继承

类间的三种关系：

1. 关联：  组合  聚合
1. 泛化：（也就是继承）
1. 依赖



## 3 数据类型和运算符

- 注释语句

1. 单行注释 `//`
1. 多行注释 `/*   */`
1. 文档注释 `/**   */`
javadoc 默认处理public 和protected   内容.

javadoc 选项  java源文件|包

- 标识符

一个语句可以跨多行,只要最后已分号结尾就好.字符串和变量名不能跨多行.
开头:字母 下划线 $.**数字不能打头**

**java所有的关键字都是小写.**


- java类型

	- 基本类型8种
	boolean类型和数值类型(整数类型和浮点类型)


	整数类型： byte short char int long 
	浮点类型：float double

	**char 也是一种整数类型，相当于无符号整数类型**

	java 的8种基本类型对应了包装类

	1. boolean Boolean
	1. byte Byte       1字节
	1. short Short     2字节
	1. int Integer     4字节
	1. long Long       8字节
	1. float Float     4字节
	1. double Double   8字节
	1. char Character  2字节

	- 引用类型4种
	类  接口  数组类型  null

	**引用类型相当于一个指针**

	字符串不是基本的数据类型，字符串是一个应用类型。字符串是一个类。 
	java 使用16bit的Unicode字符作为编码方式。
	java默认浮点类型是double
	boolean 不能使用0和非0来替换

	直接给个整数,默认类型int.
    `long  c=99999999999999 `是错误.无法将一个超出int范围的值赋给long类型.
    应该为`long  longNum=99999999999999L;`


原码: 数值转换成二进制.
实际按照补码保存二进制数.
**正数的补码和原码完全相同,负数的补码是反码+1**

 1. 二进制  0B10
 1. 八进制  010
 1. 十进制   10
 1. 十六进制 0X10

java使用unicode 进行编码,使用两个字节.16位.


- 强制类型转换
(type)value

经常出问题的地方,3.2为double类型.
float a=3.2;

- 字符串转成int类型
	String c="45";
	int nc=Integer.parseInt(c);

每个对应的包装类提供相应方法parseXxx(String c).转换成基本类型.

- 类型自动提升
System.out.println("hello"+'a'+7);  //输出 helloa7
System.out.println('a'+7+"hello");  //输出 104hello

- 常量池
java使用常量池来缓存字符串直接量.后面再使用,直接使用常量池中的字符串直接量.
常量池,指在编译期间被确定.并被保存在.class文件中.包括类 方法 接口中的常量和字符串常量.

- 运算符

`++自加运算`

       int a=5;
       int b=a++ + 6;

输出 a=6  b=11   

 	   int a=5;
       int b=++a + 6;

输出 a=6  b=12 


	- 位运算符

	<<   左移.左边补0
	>>   有符号右移,移出的操作数使用符号位补充.
	>>>  无符号右移.
	注意: 

	1. 低于int类型的类型.操作数自动转换为int再移位.
	1. 一个数过多,自动取余.
	1. 并不会改变操作数本身,只是得到新的结果.

	- 3目运算符
	(if操作)  ? if-true: if-false;


## 4 流程控制和数组

- 选择
if,switch

```
if (){

}else if (){
	
}else{
	
}
```

switch语句.
注意:
switch后面的表达式,只能是 byte,short,char,int 四种整数类型. String(java 7)
或者是枚举类型.
```
switch()
{
	case a:
	{

		xx;
		break;
	}
	default:
	{

	}
}
```

- 枚举类型
```
public class Test {
    public enum rainbowColor {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE}
    public static void main(String[] args) {
        rainbowColor c = rainbowColor.BLUE;
        System.out.println(c.toString());
        //遍历操作
        EnumSet<rainbowColor> EnumSetJz = EnumSet.range(rainbowColor.RED, rainbowColor.PURPLE);
        for (rainbowColor t : EnumSetJz) {
            System.out.println(t.toString());
        }
    }
}
```


- 循环
while ,do while ,for 三种
foreach 新的循环.

foreach 循环.循环变量只是临时变量.

- while

初始化语句.
while(循环条件){
语句.
迭代语句.
}


初始化语句.
do{
语句.
迭代语句.
}while(循环条件);

- 数组类型

数组是一种数据类型. int[]

定义数组不能指定数组长度.

- 静态初始化
int[] arr=new int[]{1,2,3};

简单方式:
int[] arr={1,2,3};

- 动态初始化

intp[] arr=new int[6];

分配初值. 默认  false,0,0.0;

- 深入数组

局部变量放到栈内存中.数组放到堆(heap)内存中.
每个方法都建立自己的内存栈,局部变量保存在栈中.程序创建对象,开销大,放到数据区(堆)便于反复使用.堆内存用来存放所有new 创建的对象和 数组的数据.

[堆和栈的解释](https://my.oschina.net/megan/blog/135280)


没有多维数组.
Arrays



## 5 面向对象(上)

1. 继承`extends`
1. 继承和组合
1. 构造器与初始化模块,静态初始化模块
1. 一个类被初始化时将同时初始化该类的所有父类
1. 抽象类
1. 抽象方法




- 注意
static 修饰的成员不能访问没有static修饰的成员.
- private protected public

- 构造器
没有返回值. 返回值也不是void类型.没有return.

修饰符可以是public,protected,private中一个.

- **[单例模式](http://www.tekbroaden.com/singleton-java.html)**


只能创建单个实例.
```
public class Singleton {
    private static Singleton singleton = null;
    private Singleton(){}
    public static Singleton getSingleton() {
        if(singleton == null) singleton = new Singleton();
        return singleton;
    }
}
```
由私有构造器和一个公有静态工厂方法构成，在工厂方法中对singleton进行null判断，如果是null就new一个出来，最后返回singleton对象。这种方法可以实现延时加载，但是有一个致命

优点: 简单
弱点：线程不安全。如果有两条线程同时调用getSingleton()方法，就有很大可能导致重复创建对象。

静态内部类法

那么，有没有一种延时加载，并且能保证线程安全的简单写法呢？我们可以把Singleton实例放到一个静态内部类中，这样就避免了静态实例在Singleton类加载的时候就创建对象，并且由于静态内部类只会被加载一次，所以这种写法也是线程安全的：
```
public class Singleton {
    private static class Holder {
        private static Singleton singleton = new Singleton();
    }
    
    private Singleton(){}
        
    public static Singleton getSingleton(){
        return Holder.singleton;
    }
}
```

枚举写法

当然，还有一种更加优雅的方法来实现单例模式，那就是枚举写法：
使用枚举除了线程安全和防止反射强行调用构造器之外，还提供了自动序列化机制，防止反序列化的时候创建新的对象。因此，Effective Java推荐尽可能地使用枚举来实现单例。

```
public enum Singleton {
    INSTANCE;
    private String name;
    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }
}
```

- this引用
1. 构造器中引用正在初始化的对象.
1. 方法中引用调用该方法的对象.
1. 谁调用这个this,就代表谁.

static 修饰的方法中,不能使用this引用.找不到合适的对象.
因为static修饰的方法不能是要this引用.因此静态成员不能访问非静态成员.

返回类型是对象.

```
public class Test {
    public int n;
    public Test grow() {
        n = 1;
        return this;
    }
}
```

- 参数传递
java中参数传递机制.使用值传递.副本传递.

**对于引用类型同样采用值传递**只是传递的是引用变量而已.

- 形参个数可变方法

可变的形参只能位于形参列表的最后.

参数变化例子.


```java
    public void info(String... str) {
        for (String s : str) {
            System.out.println(s);
        }
    }
```

- 方法重载

函数名相同.参数个数或者参数类型不同.

系统会为成员变量初始化.  局部变量必须初始化后才可以使用.


 ## 5.4 隐藏和封装


  访问控制符 private default protected  private

  default 包访问权限.protected 可以 被包内类访问.**也可以被子类访问.**
 java 默认导入 java.lang 下的类


import static 导入.可以连类名都不写.



**final 与 abstract 只能出现一次.**
可以与static 组合起来修饰方法.



静态方法属于类. 不能直接访问非静态成员.

子类可以转换成父类.
父类不可转换成子类.

下面本来就是子类.可以转换.
```
Father father = new Son();
在这里Son 对象实例被向上转型为father了，但是请注意这个Son对象实例在内存中的本质还是Son类型的，只不过它的能力临时被消弱了而已，如果我们想变强怎么办？将其对象类型还原！
Son son = (Son)father;
```

##  继承extends

未指明则继承java.lang.Object

- 方法重写: 子类包含和父类同名方法.成为方法覆盖.
- **如果父类的方法是私有的,子类同名方法不是重写.而是新方法**

原则: 
两同: 参数名,形参列表.
两小: 返回值,抛出异常应该小或相等.
一大: 访问权限比父类大或相等.

- super关键

super调用父类的方法.

```java
   void fun(){
       super.fun();
       System.out.println("this is son.");
   }
```
java创建子类时,不仅为类中定义的实例变量分配内存,也为父类继承的所有实例变量分配内存.子类和父类相同的变量,只是隐藏.都会分配内存.


- 调用父类构造器的时机.

1. 子类使用super显示调用对应实参的构造器.
2. 子类使用this,使用本类中另一个构造器.执行另一个构造器前调用父类构造器.
3. 没有super,也没this调用,使用父类的无参数构造器.

父类构造器总会在子类构造器前执行.




 ##  多态

Java变量有两种类型,编译类型和运行类型.
编译类型和运行类型不同,就是多态.


```
 Base a = new sub();
```
将子类赋值给父类.运行时是子类,编译是父类.

1. 方法,因为子类覆盖了父类方法,呈现多态性.调度子类的方法.
2. 对象的实例变量,没有多态线性.调度的是父类的实例变量.

引用变量只能调动编译时所具有的方法.

- 引用变量间的强制类型转换.
引用类型的转换,只能在具有继承关系的两个类型间进行.


- instanceof
 判断前面是否是后面的类,或者子类.

- 继承和组合

	- 继承最大的坏处,破坏封装
	- 组合,提供更好的封装性

**组合: 将旧类当做新类的成员变量组件进来.**

不希望子类重写的方法,使用final修饰.
希望被子类重写的方法使用protected修饰.
父类构造器,调用被子类重写的方法,最后也将使用子类覆盖的方法.

把类设置为最终类,不能被当成父类.使用final修饰.
使用private修饰所有构造器,保证子类无法使用该类的构造器器.无法继承该类.


何时需要派生新类?

1. 子类需要增加新的属性.
2. 子类需要增加特有的行为方式.

- 组合实现复用


组合:将新类作为新类的成员变量组合进来.实现新类的功能.

组合相比继承没有增加开销.

## 5.9 初始化模块

**java类中的4 中成员,成员变量 方法  构造器 初始化模块.**

**初始化模块,修饰符只能是static**

```
[修饰符]{
//初始化代码
	
}
```
初始化模块在构造器前执行.每次创建对象时都执行.

static 修饰的在类加载后,进行初始化.静态初始化模块.
先执行静态初始化模块,再执行普通初始化模块.

```
Base static  初始化模块
Son static 初始化模块
Base初始化模块
Base creae
Son 初始化模块
son create.
```

静态初始化块和声明静态成员变量所指定的初始化代码.按照先后顺序执行.

##  6 面向对象(下)

P163-P238


- 常量池
保证相同的常量 直接量只有一个.


static 无法修饰构造器.

- 单例类: 只能创建一个对象

- final 方法
不能被重写.

- 抽象方法
有抽象方法的类只能被定义成抽象类,抽象类中可以没有抽象方法.

抽象类无法实例化.
没有完全实现接口的类,只能被定义为抽象类.


static和abstract不能同时修饰某个方法,没有所谓的类抽象方法.
static和abstract 可以同时修饰内部类.
private和abstract 不能同时修饰方法.

作用:
模板,避免子类的随意性.


- 更加特殊的抽象类 接口

接口里所有的方法都是抽象方法.

接口只能继承接口,不能继承类.


java8 允许定义默认的方法.

接口不包含构造器和初始化定义,只能是静态常量.

方法:
抽象方法,类方法,默认方法.

默认方法是default修饰,有实现.默认方法不能使用static修饰.


成员变量自动使用 public static final.  必须定义时指定初始值.

普通方法自动使用 public abstract 修饰.



### 6.1 java增强包装类



### 6.2 处理对象


### 6.3 类成员


### 6.4 final修饰符

final修饰方法,类和变量.说明其不可改变.

final 方法不能被重写.不希望子类重写父类的方法.
final 类,不能有子类.

### 6.5 抽象类
### 6.6 Java8改进的接口

接口支持多继承。
继承是 extends 实现是implement。

- 面向接口编程

通过接口降低耦合
	
	- 简单工厂模式
	- 命令模式
	
	将处理方法和处理行为相互分离。
	


### 6.7 内部类

非静态内部类，不能拥有静态成员。


局部内部类和匿名内部类不是类成员。

内部类可以直接使用外部了的成员.
外部类无法直接访问,内部类的实例变量.

- 非静态内部类,不能定义静态方法变量


- 静态内部类

创建内部类对象前,需要创建外部类对象.


- 匿名内部类






### 6.8 Lambda表达式

代码块作为方法的参数.

**Lamda表达式的目标类型必须是函数式接口** 

函数时接口:只含有有个抽象方法的接口.可以有其他的方法,类方法.

### 6.9 枚举类

**枚举类不能派生子类.**


### 6.10 对象和垃圾回收

状态:
可达  可恢复  不可达状态

只有处于不可达状态时,才会进行垃圾回收.

通过两种方式通知,系统进行垃圾回收.

```
    System.gc();
    Runtime.getRuntime().gc();
```

finalize 并不一定会执行.

```
public class T {
    //从可恢复到不可达状态调用 finalize 
    public  void finalize(){
        System.out.println("gc ing");
    }
    public static void main(String[] args) {
        System.out.println("----------");
        for (int i=0;i<4;i++){
            new T();
        }
       System.gc();
      //or Runtime.getRuntime().gc();
    }
}
```


强 软 弱  虚引用.  get()方法.

无法通过虚引用获取引用的对象.


### 6.11 修饰符的适用范围

P232


### 6.12 Jar文件


## 7 java基础类库
P239-P280


正则表达式

^ 开头
$ 行尾
? 出现0次或一次.

日期的格式化器.  忽略.

## 8 java集合
P281-P332

### 8.1  集合概述

1. set 无序,不可重复的集合
1. list 有序 重复集合
1. queue 
1. map 映射关系数组

**集合内只能保存对象.**

迭代器发现迭代过程中,集合被修改了.立即失败.

foreach循环时,集合不能被改变.

### 8.2  cllection和iterator接口


### 8.3  set集合

- set

	- 通过调用hashCode()判断对象是否相等.判断位置,equeue判断是否相等.

	  HastSet:

	- LinkedHashSet 顺序和插入的顺序一致.


- TreeSet

元素处于排序状态.

升序列: 自然排序.

一个类添加到TreeSet必须实现了Comparable接口.(第一个元素添加时不需要实现,取出时依然有问题)

只能添加一种类型的对象.
结果一致.
重写equeue方法时需要和comparable




重写 equals() 或hashCode().应使equals()相同,hashCode()也相同.

通过hashSet找到位置. 通过equeue判断是否删除.

- EnumSet

性能分析:

TreeSet 需要通过红黑树来实现排序.

HashSet  TreeSet  EnumSet 都是线程不安全的.


### 8.4  list集合

list判断对象相等使用,euquals()方法.

- 排序

```
class Test {
    public static void main(String[] args) {
        List ll = new ArrayList();
        ll.add(1);
        ll.add(2);
        ll.add(8);
        ll.add(6);
        ll.add(3);
        System.out.println(ll);
        ll.sort((o2, o3) -> Integer.parseInt(o3.toString()) - Integer.parseInt(String.valueOf(o2.toString())));
        System.out.println(ll);
    }
}

```

ListIterator 迭代器.


ArrayList 和 Vector 实现类. Vector比较古老,少用.
ArrayList 线程不安全,vector线程安全.vector的性能比ArrayList低.
保证线程安全也不推荐是vector.有Collections工具类.

Stack 继承Vector 古老,性能差.  推荐是ArrayDeque


- 固定长度List
Arrays.ArrayList 固定长度.无法增删元素.



### 8.5  Queue集合

- PriorityQueue实现类

元素,按照大小重新排序.

- Deque双端队列.

可以当成stack使用.

addFirst
addLast

- LinkedList 实现类

实现deque 当成双端队列使用. 可以当场栈使用.


### 8.6  java 8 增强的map集合

java 首先实现Map,包装一个value都为null的map的集合实现了set.

- HashTable  和 HashMap 区别.

- SortedMap接口实现 TreeMap类.

红黑树,排序.
自然排序,定制排序.

- WeakHashMap

对象的弱引用.便于垃圾回收.


### 8.7  hashSet和hashMap性能选项


### 8.8  操作集合的工具类: Collections

Collections

返回多线程安全版本

返回不可变集合


### 8.9  繁琐的接口: enumeration



## 9 范型
P334-P355


### 9.1 范型入门

List<String>  sl=new ArrayList<String>

### 9.2 深入范型

静态方法或者静态变量的声明和初始化中,不允许使用类型形参.


### 9.3 类型通配符

类型通配符<?>

限制通配符  <? extends baseClass >



### 9.4 范型方法


范型方法和类型通配符的差别.


### 9.5 擦除和转换

### 9.6 范型与数组


反射功能


## 10 异常处理
P356-P380

-----------------------

java 使用AWT和Swing完成图形用户界面的开发.
AWT(Abstract Window Toolkit=AWT)抽象視窗工具組

## 11 AWT编程


## 12 Swing编程

比AWT更加优秀的图形界面开发工具.100%java实现.


## 13 MySQL数据库与JDBC
## 14 Annotation(注释)
## 15 输入/输出
## 16 多线程

[Java 中的进程与线程](https://www.ibm.com/developerworks/cn/java/j-lo-processthread/)
进程和线程的创建和分析.Process 和 Thread 相关的一些类.

进程创建
Java.lang.Runtime.exec 方法和 Java.lang.ProcessBuilder.start 方法都可以创建一个本地的进程，然后返回代表这个进程的 Java.lang.Process 引用。

创建线程
启动线程
控制线程
多线程同步
线程池来提高多线程性能

并发和并行区别:

1. 并发: 多指令同时执行.
1. 并行: 多指令轮换执行.

进程资源调度和分配的基本单位.

线程使得一个进程可以同时并发处理多个任务.

线程可以用拥有自己的堆栈,程序计数器和局部变量.**不拥有系统资源.**

线程间通信方式:

1. 全局变量
1. 消息
1. 使用事件

进程间通信方式：文件和记录锁定，管道，有名管道，FIFO，信号量，信号，消息队列，共享内存，套接字


线程的生命周期

新建（new Thread）：当创建Thread类的一个实例（对象）时，此线程进入新建状态（未被启动）。例如：Thread t1=new Thread();
就绪（runnable）：线程已经被启动，正在等待被分配给CPU时间片，也就是说此时线程正在就绪队列中排队等候得到CPU资源。例如：t1.start();
运行（running）：线程获得CPU资源正在执行任务（run()方法），此时除非此线程自动放弃CPU资源或者有优先级更高的线程进入，线程将一直运行到结束。
死亡（dead）：当线程执行完毕或被其它线程杀死，线程就进入死亡状态，这时线程不可能再进入就绪状态等待执行。
自然终止：正常运行run()方法后终止
异常终止：调用stop()方法让一个线程终止运行
堵塞（blocked）：由于某种原因导致正在运行的线程让出CPU并暂停自己的执行，即进入堵塞状态。
正在睡眠：用sleep(long t) 方法可使线程进入睡眠方式。一个睡眠着的线程在指定的时间过去可进入就绪状态。
正在等待：调用wait()方法。（调用motify()方法回到就绪状态）
被另一个线程所阻塞：调用suspend()方法。（调用resume()方法恢复）

在多线程中，什么是上下文切换(context-switching)？
上下文切换是存储和恢复CPU状态的过程，它使得线程执行能够从中断点恢复执行。上下文切换是多任务操作系统和多线程环境的基本特征。


- volatile关键字在Java中有什么作用？

当我们使用volatile关键字去修饰变量的时候，所以线程都会直接读取该变量并且不缓存它。这就确保了线程读取到的变量是同内存中是一致的。


[秒杀多线程](http://blog.csdn.net/column/details/killthreadseries.html)

[进程的通信方式及特点](http://blog.csdn.net/chenhuajie123/article/details/9315477)

1. 线程创建和启动

    - 继承thread类
    重写run方法,创建线程实例,调度start方法

    - 实现Runnable接口

    - callbale方法
    call()可以有返回值,可以抛出异常.

1. 控制线程
    join线程
    一个线程等待另一个线程完成的方法.

1. 守护线程
1. 暂停一段时间,进入阻塞. sleep()
1. 线程让步,yield  停下不阻塞,转就绪.重新调度.
1. 线程同步
    
    - 同步代码块

    同步监视器.
    `syncronized()
    {

    }`
    同一时刻,只有一个线程获得对同步监视器的锁定.

    - 同步方法

    syncronized来修饰某个方法.

1. 同步锁
1. 线程通信
1. 线程组
    通过ThreadGroup表示线程组.对一批线程分类管理.允许对线程组直接控制.

1. 线程池

    启动时创建大量空闲线程.执行结束后会再次转为空闲状态.

## 17 网络编程
## 18 类加载机制与反射

java类,加载连接和初始化知识.

类加载:

1. 加载: class读入内存,建立对象.允许预先加载.
1. 连接:二进制合并到JRE中
1. 初始化:类变量初始化

Java 反射API的第一个主要作用是获取程序在运行时刻的内部结构。

只要有了java.lang.Class类 的对象，就可以通过其中的方法来获取到该类中的构造方法、域和方法。对应的方法分别是getConstructor、getField和getMethod。

反射API的另外一个作用是在运行时刻对一个Java对象进行操作。

```java
MyClass myClass = new MyClass(0); //一般做法
myClass.increase(2);
System.out.println("Normal -> " + myClass.count);
try {
    Constructor constructor = MyClass.class.getConstructor(int.class); //获取构造方法
    MyClass myClassReflect = constructor.newInstance(10); //创建对象
    Method method = MyClass.class.getMethod("increase", int.class);  //获取方法
    method.invoke(myClassReflect, 5); //调用方法
    Field field = MyClass.class.getField("count"); //获取域
    System.out.println("Reflect -> " + field.getInt(myClassReflect)); //获取域的值
} catch (Exception e) { 
    e.printStackTrace();
} 
```

- 动态代理



## 19 垃圾回收机制(GC)
主要做两件事:
1. 发现无用的对象
1. 回收被无用对象占用的内存空间

建议进行垃圾回收.`System.gc();`



**字符串是常量,创建后不能改变**
两种创建
```
        String str = "abc";
        char data[] = {'a', 'b', 'c'};
        String s2 = new String(data);
        System.out.println(str);
        System.out.println(s2);
```

java split使用

```
 String[]	split(String regex) 
          根据给定正则表达式的匹配拆分此字符串。
 String[]	split(String regex, int limit) 
          根据匹配给定的正则表达式来拆分此字符串。
根据空格划分字符串
       String str1 = "a b csad fjasj";
        String str3[] = str1.split(" ");
         for (int i=0;i<str3.length;i++) {
            System.out.println(str3[i]);
        }

```


## 23 其他
1	基本说明

依赖：






2.1	类型转换
8个包装类提供parseXXX将字符串转变成相应基本类型.
parseInt(String s)

不可变类


>> 右移   空出来的用符号位补充
>>> 无符号右移	空出来的用0补充


3	流程控制与数组
int[] 也是一种数据类型

int[]=new int[5];
默认初始化
boolean  初始化为false

foreache循环,不需要数组长度和数组索引
		int[] arr = { 1, 2, 3 };
		for (int c : arr)
			System.out.println(c);
不能改变数组的值不能赋值.


数组被存储在堆中

栈内存:局部变量
堆内存:对象创建,创建难度较高,




# java
2016-09
1	基本说明
源文件的文件名必须与public类的类名相同，一个java源文件最多定义一个public类。

封装：对象细节隐藏起来
继承：继承父类
多态：子类对象可以直接赋给父类变量，运行时依然是子类行为特征。
java不支持多继承

类间的三种关系：
关联：  组合  聚合
泛化：
依赖：

java所有的关键字都是小写的
2	java类型
1)	基本类型
boolean类型
数值类型:整数类型和浮点类型
整数类型： byte short int long char
浮点类型：float double
char 也是一种整数类型，相当于无符号整数类型
2)	引用类型
类 接口  数组 nul
字符串不是基本的数据类型，字符串是一个应用类型。字符串是一个类。 
java 使用16bit的Unicode字符作为编码方式。
java默认浮点类型是double
boolean 不能使用0和非0来替换


java 的8种基本类型对应了包装类
1)	boolean Boolean
2)	byte Byte
3)	short Short
4)	int Integer
5)	long Long
6)	float Float
7)	double Double
8)	char Character

2.1	类型转换
8个包装类提供parseXXX将字符串转变成相应基本类型.
parseInt(String s)

不可变类


>> 右移   空出来的用符号位补充
>>> 无符号右移	空出来的用0补充


3	流程控制与数组
int[] 也是一种数据类型

int[]=new int[5];
默认初始化
boolean  初始化为false

foreache循环,不需要数组长度和数组索引
		int[] arr = { 1, 2, 3 };
		for (int c : arr)
			System.out.println(c);
不能改变数组的值不能赋值.


数组被存储在堆中

栈内存:局部变量
堆内存:对象创建,创建难度较高,





final和finally 区别?
native


动态链接库。



##   其他

1. 反射

通俗地说,反射机制就是可以把一个类,类的成员(函数,属性),当成一个对象来操作,希望读者能理解,也就是说,类,类的成员,我们在运行的时候还可以动态地去操作他们.

1. Java内存模型

1. Java线程进程

- [进程间通信](http://polim.iteye.com/blog/1278435)

进程间通信的主要方法有： 
（1）管道（Pipe）：管道可用于具有亲缘关系进程间的通信，允许一个进程和另一个与它有共同祖先的进程之间进行通信。 
（2）命名管道（named pipe）：命名管道克服了管道没有名字的限制，因此，除具有管道所具有的功能外，它还允许无亲缘关系进程间的通信。命名管道在文件系统中有对应的文件名。命名管道通过命令mkfifo或系统调用mkfifo来创建。 
（3）信号（Signal）：信号是比较复杂的通信方式，用于通知接受进程有某种事件发生，除了用于进程间通信外，进程还可以发送信号给进程本身；linux除了支持Unix早期信号语义函数sigal外，还支持语义符合Posix.1标准的信号函数sigaction（实际上，该函数是基于BSD的，BSD为了实现可靠信号机制，又能够统一对外接口，用sigaction函数重新实现了signal函数）。Linux中可以使用kill -12 进程号，像当前进程发送信号，但前提是发送信号的进程要注册该信号。 
example: 
OperateSignal operateSignalHandler = new OperateSignal(); 
Signal sig = new Signal("USR2"); 
Signal.handle(sig, operateSignalHandler); 
（4）消息（Message）队列：消息队列是消息的链接表，包括Posix消息队列system V消息队列。有足够权限的进程可以向队列中添加消息，被赋予读权限的进程则可以读走队列中的消息。消息队列克服了信号承载信息量少，管道只能承载无格式字节流以及缓冲区大小受限等缺限。 
（5）共享内存：使得多个进程可以访问同一块内存空间，是最快的可用IPC形式。是针对其他通信机制运行效率较低而设计的。往往与其它通信机制，如信号量结合使用，来达到进程间的同步及互斥。 
（6）内存映射（mapped memory）：内存映射允许任何多个进程间通信，每一个使用该机制的进程通过把一个共享的文件映射到自己的进程地址空间来实现它。 
Java 中有类 MappedByteBuffer实现内存映射 
（7）信号量（semaphore）：主要作为进程间以及同一进程不同线程之间的同步手段。 
（8）套接口（Socket）：更为一般的进程间通信机制，可用于不同机器之间的进程间通信。起初是由Unix系统的BSD分支开发出来的，但现在一般可以移植到其它类Unix系统上：Linux和System V的变种都支持套接字。 


Java没有共享内存机制，同时Java的管道也只能用于Java线程间的通讯。

看来Java只能通过Socket实现进程间通讯了。Socket本身确实具有很好的通用性，而且可以跨主机通讯。但是Scoket本身也有一些弱点，如效率相对其他方式较低，开发成本较高等。最重要的是，这篇文章我们要介绍的是Java如何使用PIPE实现进程间通讯。所以只好委屈一下Socket

3.1管道的本质
首先，我们需要说明一个基本概念：什么是管道？ 
管道是Linux中很重要的一种通信方式,是把一个程序的输出直接连接到另一个程序的输入,常说的管道多是指无名管道,无名管道只能用于具有亲缘关系的进程之间，这是它与有名管道的最大区别。有名管道叫named pipe或者FIFO(先进先出)，可以用函数mkfifo()创建。



##  重要点

[JAVA多线程和并发基础面试问答](http://ifeve.com/java-multi-threading-concurrency-interview-questions-with-answers/)