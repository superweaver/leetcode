#include "common.h"
// not solved
//https://zxi.mytechroad.com/blog/list/leetcode-432-all-oone-data-structure/

class AllOne {
public:
	/** Initialize your data structure here. */
	AllOne() {

	}

	/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
	void inc(string key) {
		if (s2it.count(key)) {
			// key is in list
			auto currentIter = s2it[key];
			auto  nextIter = next(s2it[key]);// next is always valid for a valid iterator
			if (nextIter == NodeList.end() || nextIter->count != currentIter->count + 1) {
				// insert before pos of nextIter
				auto insertLoc = NodeList.insert(nextIter, Node(currentIter->count + 1, key));
				s2it[key] = insertLoc;	// update to new iter
			}
			else {
				nextIter->strs.insert(key);
				s2it[key] = nextIter;
			}
			currentIter->strs.erase(key);
			if (currentIter->strs.empty()) {
				NodeList.erase(currentIter);
			}
		}
		else {
			// key is not in list
			if (NodeList.empty() || NodeList.front().count != 1) {
				NodeList.push_front(Node(1, key));
			}
			else {
				NodeList.front().strs.insert(key);
			}
			s2it[key] = NodeList.begin();
		}
	}

	/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
	void dec(string key) {
		if (s2it.count(key)) {
			// key is in list
			auto currentIter = s2it[key];
			if (currentIter->count == 1) {
				s2it.erase(key);
				currentIter->strs.erase(key);
				if (currentIter->strs.empty()) {
					NodeList.erase(currentIter);
				}
				return;
			}
			// count >= 2
			// prev is not always valid
			if (currentIter == NodeList.begin() || prev(currentIter)->count != currentIter->count - 1) {
				auto insertLoc = NodeList.insert(currentIter, Node(currentIter->count - 1, key));
				s2it[key] = insertLoc;	// update to new iter
			}
			else {
				auto  prevIter = prev(currentIter);
				prevIter->strs.insert(key);
				s2it[key] = prevIter;
			}
			currentIter->strs.erase(key);
			if (currentIter->strs.empty()) {
				NodeList.erase(currentIter);
			}
		}
	}

	/** Returns one of the keys with maximal value. */
	string getMaxKey() {
		if (NodeList.empty()) {
			return string();
		}
		return *(NodeList.back().strs.begin());
	}

	/** Returns one of the keys with Minimal value. */
	string getMinKey() {
		if (NodeList.empty()) {
			return string();
		}
		return *(NodeList.front().strs.begin());
	}
private:
	struct Node {
		int count;
		unordered_set<string> strs;
		Node(int c, string s) :count(c) {
			strs.insert(s);
		}
	};
	list<Node> NodeList;		// list.front is smaller
	unordered_map<string, list<Node>::iterator> s2it;
};


/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */

int main() {

	Solution s;

	return 0;
}
