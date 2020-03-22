# 820. Short Encoding of Words

Given a list of words, we may encode it by writing a reference string `S` and a list of indexes `A`.

For example, if the list of words is `["time", "me", "bell"]`, we can write it as `S = "time#bell#"` and `indexes = [0, 2, 5]`.

Then for each index, we will recover the word by reading from the reference string from that index until we reach a `"#"` character.

What is the length of the shortest reference string S possible that encodes the given words?

Example:
```
Input: words = ["time", "me", "bell"]
Output: 10
Explanation: S = "time#bell#" and indexes = [0, 2, 5].

Input: words = ["me", "times"]
Output: 9
Explanation: S = "times#me#" and indexes = [0, 6].
    note each masked word must be suffix of reference word, a.k.a ended at "#"
    and word appears later also can be reference of before
```

Note:
1. 1 <= words.length <= 2000.
2. 1 <= words[i].length <= 7.
3. Each word has only lowercase letters.



