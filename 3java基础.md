# Java知识点

## finally 语句

try语句执行了 `System.exit(0);` finally语句不会执行.


其实，关于 try，catch，finally 的执行流程远非这么简单，有兴趣的读者可以参考 Java 语言规范第三版（《The Java™ Language Specification, Third Edition》）中对于 Execution of try-catch-finally 的描述，非常复杂的一个流程。限于篇幅的原因，本文不做摘录，请感兴趣的读者自行阅读。


finally 语句块在 try 语句块中的 return 语句之前执行。



其实 finally 语句块是在 try 或者 catch 中的 return 语句之前执行的。更加一般的说法是，finally 语句块应该是在控制转移语句之前执行，控制转移语句除了 return 外，还有 break 和 continue。另外，throw 语句也属于控制转移语句。虽然 return、throw、break 和 continue 都是控制转移语句，但是它们之间是有区别的。

其中 return 和 throw 把程序控制权转交给它们的调用者（invoker），而 break 和 continue 的控制权是在当前方法内转移。请大家先记住它们的区别，在后续的分析中我们还会谈到。


```java
public class Test {
    public static void main(String[] args) {
        System.out.println("return value of getValue(): " + getValue());
    }

    public static int getValue() {
        int i = 1;
        try {
            return i;
        } finally {
            i++;
        }
    }
}
```
