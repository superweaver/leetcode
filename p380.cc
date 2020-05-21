#include "common.h"
//http://www.cnblogs.com/grandyang/p/5740864.html

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (v2i.find(val) != v2i.end()) {
            return false;
        }
        nums.push_back(val);
        v2i[val] = nums.size() - 1;
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (v2i.find(val) == v2i.end()) {
            return false;
        }
        // this is very smart !!
        int index = v2i[val];
        nums[index] = nums.back();
        v2i[nums[index]] = index;
        nums.pop_back();
        v2i.erase(val);
        return true;

    }

    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand()%nums.size()];
    }
    private:
    unordered_map<int, int> v2i; // value to index in nums;
    vector<int> nums;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() {

	Solution s;

	return 0;
}
