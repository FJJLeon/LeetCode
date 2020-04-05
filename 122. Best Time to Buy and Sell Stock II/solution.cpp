#include<vector>
#include<queue>
#include<limits.h>

using namespace std;

/**
 * Peak & Valley
 * Because we can buy and sell for any times, buy at valley and sell at peak afterwards
 * 
 * Runtime: 8 ms, faster than 49.26%, O(N)
 * Memory Usage: 8 MB, less than 100.00%, O(N), store peak and valley index
*/
class Solution11 {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len < 2)
            return 0;
        // first elem is useful when valley, while last when peak
        // add INTMAX before first, while 0 after last for convenience
        prices.insert(prices.begin(), INT_MAX);
        prices.push_back(0);
        // store peak & valley index
        queue<int> peak, valley;
        // stock trend, true for up, false for down
        bool trend = prices[1] > prices[0];
        // index 0 and len+1 is added, solve [1, len]   
        for (int i = 1; i <= len; ++i) {
            // current tread
            bool rise = prices[i+1] > prices[i];
            if (trend && !rise)  // tread /\ = peak
                peak.push(i);
            if (!trend && rise)  // tread \/ = valley
                valley.push(i);
            trend = rise;
        }
        
        int profit = 0;
        while (!peak.empty() && !valley.empty()) {
            int buy = valley.front();
            
            int sell = peak.front();
            peak.pop();
            // sell time follows buy time
            if (sell > buy) {
                profit += prices[sell] - prices[buy];
                valley.pop();   
            }
        }
        
        return profit;
    }
};

/**
 * Peak & Valley
 * NO Need store peak & valley index
 * peak and valley always appear alternately
 * 
 * Runtime: 4 ms, faster than 97.60%, O(N)
 * Memory Usage: 7.4 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len < 2)
            return 0;
        
        int peak = prices[0], valley = prices[0];
        int profit = 0;
        int i = 0;
        while (i < len - 1) {
            while (i < len - 1 && prices[i] >= prices[i+1])
                ++i;
            // downward tread is broken
            valley = i;
            while (i < len - 1 && prices[i] <= prices[i + 1])
                ++i;
            // upward tread is broken
            peak = i;
            
            profit += prices[peak] - prices[valley];
        }
        
        return profit;
    }
};

/**
 * simple math
 * 脑瓜子想一想，说确实是说必须谷买峰卖，
 * 但是这样的表现形式上就是只要发现股票是上升趋势，收益一定可以获取, 把上升段的收益全加起来就可以
 * 
 * Runtime: 4 ms, faster than 97.60%， O(N)
 * Memory Usage: 7.3 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1])
                profit += prices[i] - prices[i - 1];
        }
        
        return profit;
    }
};