# clojure语言学习


[几分钟内学习 Clojure ](https://www.oschina.net/translate/learn-clojure-in-minutes)


##  输出Hello, World

```
(println "Hello, World")
```

```

;(println (= 1 1)) ; => true
;(println (= 2 1)) ; => false

(println  '(1 2 3)  );(1 2 3)
(println (range 4))

(println (map inc [1 2 3]) )
(println (reduce + [1 2 3 4]) )
(println  (map inc [1 2 3]) )
(def x 1)
(println  x )
(def hellofun (fn [] "Hello world"))
(str "Hello" " " "World") ; => "Hello World"

(println  (hellofun) )

(defn hello [name]
  (str "Hello " name))
 ; => "Hello Steve"

(println  (hello "Steve") )
(class {:a 1 :b 2 :c 3})
(println  (class :a)  )
(def keymap (hash-map :a 1 :b 2 :c 3))
 ; => {:a 1, :c 3, :b 2} (不保证顺序)
(println  keymap )
(println  (keymap :a)  )

(do
  (print "Hello")
  "World") ; => "World" (prints "Hello")
```

##  [Clojure入门教程](https://wizardforcel.gitbooks.io/clojure-fpftj/content/48.html)



ojure的方法调用是这样的:

```
(function-name arg1 arg2 arg3)
```

## 输出

```java
// Java
public void hello(String name) {
    System.out.println("Hello, " + name);
}
```


```java
; Clojure
(defn hello [name]
  (println "Hello," name))
```


对Clojure代码的处理分为三个阶段：读入期，编译期以及运行期。在读入期，读入期会读取clojure源代码并且把代码转变成数据结构，基本上来说就是一个包含列表的列表的列表。。。。在编译期，这些数据结构被转化成java的bytecode。在运行期这些java bytecode被执行。函数只有在运行期才会执行。而宏在编译期就被展开成实际对应的代码了。


```java
// This is Java code.
public class PigLatin {

  public static String pigLatin(String word) {
  char firstLetter = word.charAt(0);
  if ("aeiou".indexOf(firstLetter) != -1) return word + "ay";
  return word.substring(1) + firstLetter + "ay";
  }

  public static void main(String args[]) {
  System.out.println(pigLatin("red"));
  System.out.println(pigLatin("orange"));
  }
}
```


```java
; This is Clojure code.
; When a set is used as a function, it returns a boolean
; that indicates whether the argument is in the set.
(def vowel? (set "aeiou"))

(defn pig-latin [word] ; defines a function
  ; word is expected to be a string
  ; which can be treated like a sequence of characters.
  (let [first-letter (first word)] ; assigns a local binding
    (if (vowel? first-letter)
      (str word "ay") ; then part of if
      (str (subs word 1) first-letter "ay")))) ; else part of if

(println (pig-latin "red"))
(println (pig-latin "orange"))
```

## REPL

REPL 是read-eval-print loop的缩写


## 变量

def, let和binding的用法

```java
(def ^:dynamic v 1) ; v is a global binding

(defn f1 []
  (println "f1: v =" v)) ; global binding

(defn f2 []
  (println "f2: before let v =" v) ; global binding
  (let [v 2] ; creates local binding v that shadows global one
    (println "f2: in let, v =" v) ; local binding
    (f1))
  (println "f2: after let v =" v)) ; global binding

(defn f3 []
  (println "f3: before binding v =" v) ; global binding
  (binding [v 3] ; same global binding with new, temporary value
    (println "f3: in binding, v =" v) ; global binding
    (f1))
  (println "f3: after binding v =" v)) ; global binding

(defn f4 []
 (def v 4)) ; changes the value of the global binding

(f2)
(f3)
(f4)
(println "after calling f4, v =" v)
```



结果

```java
f2: before let v = 1
f2: in let, v = 2
f1: v = 1 (let DID NOT change value of global binding)
f2: after let v = 1
f3: before binding v = 1
f3: in binding, v = 3
f1: v = 3 (binding DID change value of global binding)
f3: after binding v = 1 (value of global binding reverted back)
after calling f4, v = 4

```

## 集合

Clojure提供这些集合类型: list, vector, set, map

Clojure集合特性:

1. 可修改:不可修改,一旦一个集合产生之后，你不能从集合里面删除一个元素，也往集合里面添加一个元素
1. 异源:异源的意味着一个集合里面可以装进任何东西（而不必须要这些东西的类型一样）
1. 持久:一个集合新的版本产生之后，旧的版本还是在的


1. 个数count
1. 添加conj 
1. reverse 翻转`(reverse [2 4 7]) ; -> (7 4 2)`

```java
count 返回集合里面的元素个数，比如：
(count [19 "yellow" true]) ; -> 3
```



```java
有很多函数从一个集合里面获取一个元素，比如：
(def stooges ["Moe" "Larry" "Curly" "Shemp"])
(first stooges) ; -> "Moe"
(second stooges) ; -> "Larry"
(last stooges) ; -> "Shemp"
(nth stooges 2) ; indexes start at 0 -> "Curly"
```

## 列表

```java
(def stooges (list "Moe" "Larry" "Curly"))
(def stooges (quote ("Moe" "Larry" "Curly")))
(def stooges '("Moe" "Larry" "Curly"))
```

conj和cons函数的作用都是通过一个已有的集合来创建一个新的包含更多元素的集合—新加的元素在最前面。remove函数创建一个只包含所指定的谓词函数测试结果为false的元素的集合:

```java
(def more-stooges (conj stooges "Shemp")) -> ("Shemp" "Moe" "Larry" "Curly")
(def less-stooges (remove #(= % "Curly") more-stooges)) ; -> ("Shemp" "Moe" "Larry")
```

into 函数把两个list里面的元素合并成一个新的大list

```java
(def kids-of-mike '("Greg" "Peter" "Bobby"))
(def kids-of-carol '("Marcia" "Jan" "Cindy"))
(def brady-bunch (into kids-of-mike kids-of-carol))
(println brady-bunch) ; -> (Cindy Jan Marcia Greg Peter Bobby)
```
peek和pop可以用来把list当作一个堆栈来操作.她们操作的都是list的第一个元素。

## 向量

下面是两种创建vector的方法：

```java
(def stooges (vector "Moe" "Larry" "Curly"))
(def stooges ["Moe" "Larry" "Curly"])
```
get获取vector里面指定索引的元素.我们后面会看到get也可以从map里面获取指定key的value。索引是从0开始的。get函数和函数nth类似.它们都接收一个可选的默认值参数—如果给定的索引超出边界，那么会返回这个默认值。如果没有指定默认值而索引又超出边界了，get函数会返回nil而nth会抛出一个异常.看例子:

```java
(get stooges 1 "unknown") ; -> "Larry"
(get stooges 3 "unknown") ; -> "unknown"
```
assoc替换

```java
(def stooges ["Moe" "Larry" "Curly"])
(assoc stooges 2 "Shemp") ; -> ["Moe" "Larry" "Shemp"]
```
peek和pop

## 集合

Sets是一个包含不重复元素的集合
并且我们不要求集合里面的元素保持它们添加时候的顺序，那么sets是比较适合的。Clojure支持两种不同的set：排序的和不排序的。



```java
(def stooges (hash-set "Moe" "Larry" "Curly")) ; not sorted
(def stooges #{"Moe" "Larry" "Curly"}) ; same as previous
(def stooges (sorted-set "Moe" "Larry" "Curly"))
```

contains?函数可以操作sets和maps.当操作set的时候,它返回给定的set是否包含某个元素。这比在list和vector上面使用的some函数就简单多了.看例子:

```java
(contains? stooges "Moe") ; -> true
(contains? stooges "Mark") ; -> false
```

Sets 可以被当作它里面的元素的函数来使用. 当以这种方式来用的时候，返回值要么是这个元素，要么是nil. 这个比起contains？函数来说更简洁. 比如:

```java
(stooges "Moe") ; -> "Moe"
(stooges "Mark") ; -> nil
(println (if (stooges person) "stooge" "regular person"))
```

在介绍list的时候提到的函数conj和into对于set也同样适用.只是元素的顺序只有对sorted-set才有定义.
disj 函数通过去掉给定的set里面的一些元素来创建一个新的set. 看例子:

```java
(def more-stooges (conj stooges "Shemp")) ; -> #{"Moe" "Larry" "Curly" "Shemp"}
(def less-stooges (disj more-stooges "Curly")) ; -> #{"Moe" "Larry" "Shemp"}
```

## 映射

Maps 保存从key到value的a对应关系— key和value都可以是任意对象。key-value 组合被以一种可以按照key的顺序高效获取的方式保存着。

下面是创建map的一些方法， 其中逗号是为了提高可读性的，它是可选的，解析的时候会被当作空格忽略掉的。

```java
(def popsicle-map
  (hash-map :red :cherry, :green :apple, :purple :grape))
(def popsicle-map
  {:red :cherry, :green :apple, :purple :grape}) ; same as previous
(def popsicle-map
  (sorted-map :red :cherry, :green :apple, :purple :grape))
```

Map可以作为它的key的函数，同时如果key是keyword的话，那么key也可以作为map的函数。下面是三种获取:green所对应的值的方法：

```java
(get popsicle-map :green)
(popsicle-map :green)
(:green popsicle-map)
```
contains?方法可以操作sets和maps.当被用在map上的时候，它返回map是否包含给定的key. keys函数返回map里面的所有的key的集合. vals函数返回map里面所有值的集合.看例子:

```java
(contains? popsicle-map :green) ; -> true
(keys popsicle-map) ; -> (:red :green :purple)
(vals popsicle-map) ; -> (:cherry :apple :grape)
```
assoc函数可以操作maps 和vectors. 当被用在map上的时候，它会创建一个新的map， 同时添加任意对新的name-value pair, 如果某个给定的key已经存在了，那么它的值会被更新。看例子:

```java
(assoc popsicle-map :green :lime :blue :blueberry)
; -> {:blue :blueberry, :green :lime, :purple :grape, :red :cherry}
```

dissoc 创建一个新的map， 同时忽略掉给定的那么些key， 看例子:

```java
(dissoc popsicle-map :green :blue) ; -> {:purple :grape, :red :cherry}
```

我们也可以把map看成一个简单的集合，集合里面的每个元素是一个pair: name-value: clojure.lang.MapEntry对象.这样就可以和doseq跟destructuring一起使用了,它们的作用都是更简单地来遍历map ，我们会在后面详细地介绍这些函数.下面的这个例子会遍历popsicle-map里面的所有元素，把key bind到color，把value bind到flavor。 name函数返回一个keyword的字符串名字。

```java
(doseq [[color flavor] popsicle-map]
  (println (str "The flavor of " (name color)
    " popsicles is " (name flavor) ".")))
```

输出

```java
The flavor of green popsicles is apple.
The flavor of purple popsicles is grape.
The flavor of red popsicles is cherry.
```

select-keys函数接收一个map对象，以及一个key的集合的参数，它返回这个集合里面key在那个集合里面的一个子map。看例子:

```java
(select-keys popsicle-map [:red :green :blue]) ; -> {:green :apple, :red :cherry}
```

嵌套map

```java
(def person {
  :name "Mark Volkmann"
  :address {
    :street "644 Glen Summit"
    :city "St. Charles"
    :state "Missouri"
    :zip 63304}
  :employer {
    :name "Object Computing, Inc."
    :address {
      :street "12140 Woodcrest Executive Drive, Suite 250"
      :city "Creve Coeur"
      :state "Missouri"
      :zip 63141}}})
```

get-in函数、宏-&gt;以及函数reduce都可以用来获得内嵌的key.下面展示了三种获取这个人的employer的address的city的值的方法：

```java
(get-in person [:employer :address :city])
(-> person :employer :address :city) ; explained below
(reduce get person [:employer :address :city]) ; explained below
```


## StructMap

StructMap和普通的map类似，它的作用其实是用来模拟java里面的javabean，所以它比普通的map的优点就是，它把一些常用的字段抽象到一个map里面去，这样你就不用一遍一遍的重复了。并且和java类似，他会帮你生成合适的equals和hashCode方法。并且它还提供方式让你可以创建比普通map里面的hash查找要快的字段访问方法(javabean里面的getXXX方法)。


create-struct函数和defstruct宏都可以用来定义StructMap, defstruct内部调用的也是create-struct。map的key通常都是用keyword来指定的。看例子:

```java
(def vehicle-struct (create-struct :make :model :year :color)) ; long way
(defstruct vehicle-struct :make :model :year :color) ; short way
```

struct实例化StructMap的一个对象，相当于java里面的new关键字. 你提供给struct的参数的顺序必须和你定义的时候提供的keyword的顺序一致，后面的参数可以忽略， 如果忽略，那么对应key的值就是nil。看例子:

```java
(def vehicle (struct vehicle-struct "Toyota" "Prius" 2009))
```
## 函数定义

defn宏用来定义一个函数。它的参数包括一个函数名字，一个可选的注释字符串，参数列表，然后一个方法体。而函数的返回值则是方法体里面最后一个表达式的值。所有的函数都会返回一个值， 只是有的返回的值是nil。看例子



函数定义可以包含多个参数列表以及对应的方法体。每个参数列表必须包含不同个数的参数。这通常用来给一些参数指定默认值。看例子：


```java
(defn parting
  "returns a String parting in a given language"
  ([] (parting "World"))
  ([name] (parting name "en"))
  ([name language]
    ; condp is similar to a case statement in other languages.
    ; It is described in more detail later.
    ; It is used here to take different actions based on whether the
    ; parameter "language" is set to "en", "es" or something else.
    (condp = language
      "en" (str "Goodbye, " name)
      "es" (str "Adios, " name)
      (throw (IllegalArgumentException.
        (str "unsupported language " language))))))

(println (parting)) ; -> Goodbye, World
(println (parting "Mark")) ; -> Goodbye, Mark
(println (parting "Mark" "es")) ; -> Adios, Mark
(println (parting "Mark", "xy"))
; -> java.lang.IllegalArgumentException: unsupported language xy
```

匿名函数是没有名字的。他们通常被当作参数传递给其他有名函数(相对于匿名函数)。匿名函数对于那些只在一个地方使用的函数比较有用。下面是定义匿名函数的两种方法：

```java
(def years [1940 1944 1961 1985 1987])
(filter (fn [year] (even? year)) years) ; long way w/ named arguments -> (1940 1944)
(filter #(even? %) years) ; short way where % refers to the argument
```

有两种方法可以调用java里面的静态方法：

```java
(. Math pow 2 4) ; -> 16.0
(Math/pow 2 4)
```


```java

```






## 特点

函数式编程具有五个鲜明的特点。



1. 函数是"第一等公民"

函数，可以赋值给其他变量，也可以作为参数.

2. 只用"表达式"，不用"语句"

3. 没有"副作用"

所谓"副作用"（side effect），指的是函数内部与外部互动（最典型的情况，就是修改全局变量的值），产生运算以外的其他结果。

函数式编程强调没有"副作用"，意味着函数要保持独立，所有功能就是返回一个新的值，没有其他行为，尤其是不得修改外部变量的值。

4. 不修改状态

上一点已经提到，函数式编程只是返回新的值，不修改系统变量。因此，不修改变量，也是它的一个重要特点。

在其他类型的语言中，变量往往用来保存"状态"（state）。不修改变量，意味着状态不能保存在变量中。函数式编程使用参数保存状态，最好的例子就是递归。下面的代码是一个将字符串逆序排列的函数，它演示了不同的参数如何决定了运算所处的"状态"。

5. 引用透明

更方便的代码管理

易于"并发编程"

代码的热升级: 函数式编程没有副作用，只要保证接口不变，内部实现是外部无关的。所以，可以在运行状态下直接升级代码，不需要重启，也不需要停机。Erlang语言早就证明了这一点，它是瑞典爱立信公司为了管理电话系统而开发的，电话系统的升级当然是不能停机的。

# Clojure编程  图书  


## 1进入Clojure仙境

clojure特性

1. 运行与JVM上
1. Lisp
1. 函数式编程语言
1. 提供了并行 并发编程新式解决方案
1. 动态编程语言


## 2函数式编程

## 3集合类和数据结构

## 4多线程和并发

## 5宏

## 5数据类型和协议

## 7多重方法

## 8clojure项目组织和构建

## 9java和JVM互操作

## 10面向REPL编程

