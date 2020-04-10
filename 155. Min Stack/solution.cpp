#include<stack>

using namespace std;

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

/**
 * use extra stack record appeared minimum value
 *  note: a not-min elem that appear later will never become minimum elem
 * 
 * Runtime: 68 ms
 * Memory Usage: 14.4 MB
*/
class MinStack {
private:
    stack<int> data;

    stack<int> min;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        data.push(x);
        // the pushed elem is less than current min, update
        if (min.empty() || min.top() >= x)
            min.push(x);
    }
    
    void pop() {
        if (data.empty() || min.empty())
            return;
        // current min elem is popped, update
        if (data.top() == min.top())
            min.pop();
        data.pop();
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return min.top();
    }
};

/**
 * use self-defined node
 * including this value, min value if this node as stack top, the node below this one
 * 
 * Runtime: 92 ms
 * Memory Usage: 14.8 MB
*/
class MinStack {
    /** initialize your data structure here. */
private:
    struct Node {
        int val;
        // min value if this node as stack top
        int min;
        // the node below this one
        Node *below;
        // empty constructor
        Node(int x): val(x), min(x), below(NULL) {}
        // normal constructor
        Node(int x, int min, Node* below): val(x), min(min), below(below) {}
    };

    Node *head;
public:
    
    MinStack() {
        head = NULL;
    }
    
    void push(int x) {
        if (head == NULL)
            head = new Node(x);
        else
            head = new Node(x, min(x, head->min), head);
    }
    
    void pop() {
        head = head->below;
    }
    
    int top() {
        return head->val;
    }
    
    int getMin() {
        return head->min;
    }

};
