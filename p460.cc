#include "common.h"
// https://www.cnblogs.com/grandyang/p/6258459.html
class LFUCache {
public:
	LFUCache(int capacity) {
		d_capacity = capacity;

	}

	int get(int key) {
		if (d_cache.count(key) == 0) {
			return -1;	// no such key
		}
		// d_cache has such key, and we visit it again
		// need to update its frequency
		int old_frequency = d_cache[key].second;
		list<int>& old_list = d_freq[old_frequency];
		list<int>::iterator& old_iterator = d_iter[key];
		// remove it from  old_list
		old_list.erase(old_iterator); // it is possible old_list become empty
		// visit it again
		int new_frequency = old_frequency + 1;
		d_cache[key].second = new_frequency;
		// push key to new list
		list<int>& new_list = d_freq[new_frequency];
		new_list.push_back(key);
		// update iter[key]
		d_iter[key] = --new_list.end();
		// !!!
		// if we just make the d_freq[old_frequency] empty because of erasing
		// then we just minFreq++;
		if (d_freq[d_minFreq].empty()) {
			d_minFreq++;
		}
		return d_cache[key].first;
	}

	void put(int key, int value) {
		if (d_capacity <= 0) return;
		if (get(key) != -1) { //  important
			// note, if key exists in d_cache,
			// get() function will update its frequency
			d_cache[key].first = value;
			return;
		}
		// going to insert key
		if (d_cache.size() >= d_capacity) {
			// remove the least frequently used term
			int key = d_freq[d_minFreq].front();
			d_cache.erase(key);
			d_iter.erase(key);
			d_freq[d_minFreq].pop_front();	// remove the first node in the list, which is the oldest node
		}
		d_cache[key] = { value, 1 };
		d_minFreq = 1;
		d_freq[d_minFreq].push_back(key); // freq == 1
		d_iter[key] = --d_freq[d_minFreq].end();
	}
private:
	int d_capacity; // capacity of cache
	int d_minFreq;	// minimum frequency of key
	unordered_map<int, pair<int, int> > d_cache;	// key -> <value, frequency>;
	unordered_map<int, list<int> >  d_freq;		// frequency-> list<key>
												// in the list <key>, head is oldest, tail is the newest
	unordered_map<int, list<int>::iterator> d_iter;	 // key -> iterator, *iterator == key
};
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {

	Solution s;

	return 0;
}
