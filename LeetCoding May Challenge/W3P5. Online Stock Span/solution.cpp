#include<vector>
#include<unordered_map>
#include<stack>

using namespace std;

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

/**
 * use vector store stocks
 * use map store index of stock -> [next] value for this stock
 * each time call next with today's stock price, jmp from today's price back with step of current map value of the index (mark today as 1 befor Iteration)
 * until target stock price is larger than today's, return the interval width of target and today
 * 
 * Runtime: 632 ms, O(N) for each call
 * Memory Usage: 97.1 MB, O(2N) = O(N)
*/
class StockSpanner1 {
private:
    vector<int> stocks;
    unordered_map<int, int> nexts;

public:
    StockSpanner1() {
        
    }
    
    int next(int price) {
        int key = stocks.size();
        stocks.push_back(price);

        int it = key, step;
        nexts[key] = 1;
        // jump back until target day price larger than today
        while (it - (step = nexts[it]) >= 0 && stocks[it - step] <= price) {
            it -= step;
        }
        // record width between target and today
        nexts[key] = key - it + step;
        
        return key - it + step;
    }
};


/**
 * from sol 1, we can find the price between two peak price value is useless which can be removed
 * use stack record past stock prices,
 * each time call next with today's stock price, pop out all past prices <= today's price, accumulate [next] of them
 * 
 * Runtime: 496 ms, O(N)
 * Memory Usage: 84.4 MB, O(N)
*/
class StockSpanner2 {
private:
    struct stockscan {
        int price;
        int next;
    };
    stack<stockscan> past;
public:
    StockSpanner2() {
        
    }
    
    int next(int price) {
        stockscan today{price, 1};
        // pop out all past prices <= today's price, accumulate [next] of them
        while (!past.empty() && past.top().price <= price) {
            today.next += past.top().next;
            past.pop();
        }
        // push today's scan result
        past.push(today);
        return today.next;
    }
};
