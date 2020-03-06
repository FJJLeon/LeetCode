# 后缀表达式转换为中缀表达式

后缀表达式：A B C D − ∗ + E F / −
中缀表达式：A + B ∗ (C − D) − E / F

后缀表达式 -> 表达式树 -> 中缀表达式

表达式树
```    
            -
        /       \
       +         /
     /   \      /  \
    A     *    E    F
         /  \
        B    -
            / \
           C   D
```

必要时添加括号：
* 对于当前节点，如果其左节点是操作符，且运算优先级小于当前节点操作符，则给左子树的中缀表达式加括号；
* 对于当前节点，如果其右节点是操作符，且运算优先级不大于当前节点操作符，则给右子树的中缀表达式加括号。

## Reference
[后缀表达式转中缀表达式](https://blog.csdn.net/polyhedronx/article/details/77343853)
[前缀、中缀、后缀表达式转换详解](https://blog.csdn.net/walkerkalr/article/details/22798365)
[中缀表达式与后缀表达式](https://www.cnblogs.com/zhengxunjie/p/10372329.html)
