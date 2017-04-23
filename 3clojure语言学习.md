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

##

##
