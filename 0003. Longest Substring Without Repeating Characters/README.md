# 3. Longest Substring Without Repeating Characters

* Brute force
...
* Sliding Window is better
基本思想是使用滑动窗口表示当前无重复子串，若下一个字符在当前子串中存在则收缩窗口，否则扩大窗口。
在我开始的实现中我是每次在字串中搜索下一个字符，这样无疑加大时间复杂度起码到了O(nlogn)级别，而在标准实现中使用了一个 hash set 存放 ``字符`` 与 ``字符对应的索引`` 的映射，在窗口滑动过程中更新，这样使得判断下一个字符是否存在及获取其对应索引的时间复杂度降到 O(1)，整体是 O(n) 的时间复杂度