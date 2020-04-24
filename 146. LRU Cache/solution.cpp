#include<unordered_map>
#include<iostream>

using namespace std;

/**
 * 要做到 get 和 put 都是 O(1) 的时间复杂度
 * 需要使用 HashTable 保存 key 到 cache 队列节点 的映射
 * cache 队列用双链表来维护，做到增加、删除和移动特定节点都不需要移动其他节点
 * 
 * Runtime: 160 ms
 * Memory Usage: 35.6 MB
*/
class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->head = new DNode(0, 0);
        this->tail = new DNode(0, 0);
        this->head->next = tail;
        this->tail->last = head;
    }
    
    int get(int key) {
        auto it = map.find(key);
        // 该 key 存在
        if (it != map.end()) {
            // 储存对应 value 的双链表节点
            DNode* target = it->second;
            // 将节点从原来的位置移走
            target->last->next = target->next;
            target->next->last = target->last;
            // 将节点插入到 head 之后
            target->last = head;
            target->next = head->next;
            head->next->last = target;
            head->next = target;            
            return target->val;
        }
        else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        // 先查看是否以及存在该 key，用 get 可以在存在时移到head之后
        if (this->get(key) != -1) {
            map[key]->val = value;
            return;
        }
        // 新插入则创建新节点
        DNode *cur = new DNode(key, value, head->next, head);
        head->next->last = cur;
        head->next = cur;
        map[key] = cur;
        // 若 cache 已满，则移除链表最后一个节点
        if (map.size() > capacity) {
            DNode *del = tail->last;
            // 将 del 节点移出链表
            del->last->next = tail;
            tail->last = del->last;
            // 将对应的 key 移出哈希表
            map.erase(del->key);
            // 释放空间
            delete del;
        }
    }
private:
    struct DNode {
        int key;
        int val;
        DNode *next;
        DNode *last;
        DNode(int k, int v) : key(k), val(v), next(NULL), last(NULL) {}
        DNode(int k, int v, DNode *n, DNode *l) : key(k), val(v), next(n), last(l) {}
    };
    // 双链表节点储存值
    DNode *head, *tail;
    // 哈希表储存 key 所对应的 value 所在的双链表节点
    unordered_map<int, DNode*> map;
    int capacity;
};



/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    LRUCache cache = LRUCache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // returns 1
    cache.put(3, 3);    // evicts key 2
    cache.get(2);       // returns -1 (not found)
    cache.put(4, 4);    // evicts key 1
    cache.get(1);       // returns -1 (not found)
    cache.get(3);       // returns 3
    cache.get(4);       // returns 4

    return 0;
}
