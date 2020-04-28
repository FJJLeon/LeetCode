# 55. Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

## Example:
``` markdown
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
```

## Reference
[Jump Game solution](https://leetcode.com/problems/jump-game/solution/)
Introduce from 1.**Backtracking** to 2. **Dynamic Programming Top-down** (use memo) 3. **Dynamic Programming Bottom-up** (eliminate recursion) and 4. **Greedy** (search left-most position)