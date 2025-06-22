#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) {
        key = k;
        value = v;
        prev = next = nullptr;
    }
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    // Remove node from DLL
    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Add node to front
    void insert(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(0, 0); // Dummy head
        tail = new Node(0, 0); // Dummy tail
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            insert(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            delete node;
        }
        if (cache.size() == capacity) {
            Node* lru = tail->prev;
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }

        Node* node = new Node(key, value);
        insert(node);
        cache[key] = node;
    }

    void display() {
        Node* temp = head->next;
        while (temp != tail) {
            cout << temp->key << ":" << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LRUCache lru(3);
    lru.put(1, 10);
    lru.put(2, 20);
    lru.put(3, 30);
    lru.display();  // 3:30 2:20 1:10

    lru.get(2);     // Access 2
    lru.display();  // 2:20 3:30 1:10

    lru.put(4, 40); // Insert new -> removes LRU key 1
    lru.display();  // 4:40 2:20 3:30

    return 0;
}
