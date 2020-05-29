#include "common.h"

class MyHashSet {
private:
    vector<list<int>> data;
    int num_bucket;
    int getHash(int key) {
        return (key % num_bucket);
    }
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        list<int> initLst;
        num_bucket = 1009;
        data.assign(num_bucket, initLst);
    }

    void add(int key) {
        int hash = getHash(key);
        for (auto it = data[hash].begin();
            it != data[hash].end();
            it++) {
            if (*it == key)
                return;
        }
        data[hash].push_back(key);
    }

    void remove(int key) {
        int hash = getHash(key);
        for (auto it = data[hash].begin();
            it != data[hash].end();
            it++) {
            if (*it == key) {
                data[hash].erase(it);
                return;
            }
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int hash = getHash(key);
        for (auto it = data[hash].begin();
            it != data[hash].end();
            it++) {
            if (*it == key)
                return true;
        }
        return false;
    }
};


int main() {

	Solution s;

	return 0;
}
