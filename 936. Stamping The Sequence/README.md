# [936. Stamping The Sequence](https://leetcode.com/problems/stamping-the-sequence/)

## 题目

顾名思义，用一个一维邮戳 stamp 不断盖，后盖字符的会覆盖之前的字符，最后盖出 target。

认为 target 的首字符为索引 0，问可行的盖戳索引序列。

## 实现

每日一题又是逆向思维。如果存在可行的盖戳序列，不管怎么盖，最后都会盖了一次停了，那么势必存在一个完整的邮戳，我们用可以把这个戳刮掉（用 ？ 代替），记录邮戳开始索引，随后 ？ 的位置可以认为是任意字符。接着再考虑上一个完整的邮戳（可以有？），循环直到没有完整邮戳可以刮掉。若最后全是 ？，则索引序列的倒序即为盖戳顺序。

``` c++
TC=O(N*(N-M))
SC=O(N)


class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int win = stamp.size(), n = target.size();
        vector<int> res;
        // 检查当前 target 的 idx 开始位置是否是一个完整的邮戳，可以包含 ？
        auto tryStamp = [&stamp, &target, win, &res] (int idx) {
            bool canStamp = false;
            for (int i = 0; i < win; i++) {
                // 若全是 ？ 则无需盖戳
                if (target[idx + i] == '?')
                    continue;
                // 存在非 ？ 字符与邮戳不匹配
                if (target[idx + i] != stamp[i])
                    return false;
                // 存在非 ？ 字符匹配
                canStamp = true;
            }
            // 全是 ？ 则无需盖戳
            if (canStamp == false)
                return false;
            // 完整邮戳，且存在非 ？字符，刮掉（用 ？ 代替）
            for (int i = idx; i < idx + win; i++)
                target[i] = '?';
            // 记录邮戳起始索引
            res.push_back(idx);
            return true;
        };
        
        bool matched = true;
        // 若上次还可以盖戳
        while (matched) {
            matched = false;
            // 检查所有位置是否是完整的邮戳
            for (int i = 0; i < n - win + 1; i++) {
                // 若是则刮掉，不是则跳过
                matched |= tryStamp(i);
            }
        }
        
        // 所有完整的邮戳刮掉后是否全是 ？，不是则无法形成 target
        int allMatched = true;
        for (char c : target)
            if (c != '?') {
                allMatched = false;
                break;
            }
        // 刮戳序列逆序即为盖戳序列
        reverse(res.begin(), res.end());
        return allMatched ? res : vector<int>();
    }
};
```
