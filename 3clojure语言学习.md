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

