#include "common.h"
class Solution {
public:
    int maxLength(vector<string>& arr) {
		int n = arr.size();
		vector<bool> valid(n, true);
		vector<pair<int, int>> keys(n, {0, 0});
		for (int i = 0; i < n; ++i) {
			auto& s = arr[i];
			int key = 0;
			for (auto c : s) {
				int probe = 1 << (c-'a');
				if ( key  & probe){
					valid[i] = false;
					break;
				} else {
					key |= probe;
				}
			}
			if (valid[i]) {
                keys[i] = {key, count(key)};
            }
		}
		int result = 0;			
		helper(keys, valid, result, 0, 0, 0);
		/*
        int upper = (1 << n) - 1;
		vector<int> map(upper+1, 0);
		for (int i = 0; i < n; ++i) {
			map[1 << i] = i;
		}
		for (int i = 1; i < upper; ++i) {
			int j = i;
			int key  = 0;
			int len = 0;
			while(j) {
                int lowerbit = j & (-j);
				j &= (j-1);
				auto next =keys[ map[lowerbit]];
				if ((key & next.first) == (key + next.first) ) {
					len += next.second;
					result = max(len, result);
				} else {
					break;
				}
            }
		}
		*/
        return result;
    }
private:
	int count(int key) {
		int ones = 0;
		while(key) {
			key &= (key - 1);
			ones++;
		}
		return ones;
	}
	void helper(vector<pair<int, int>>& keys, vector<bool>& valid, int& result, size_t start, int current, int curLen) {
        if (result == 26) {
            return;
        }
        if (start >= keys.size()) {
            return ;
        }
        if (!valid[start]) {
			helper(keys, valid, result, start + 1, current, curLen);
			return;
		}
		int key = keys[start].first ;
		int len = keys[start].second;
		if ((current | key) == current + key) {
			helper(keys, valid, result, start+ 1, current, curLen);
			result = max(result, curLen+ len);
			helper(keys, valid, result, start, current | key, curLen+ len);
		} else {
			helper(keys,valid, result, start+1, current, curLen);
		}
	}
};

int main() {

    vector<string> arr = { "un", "iq", "ue" }; //4
    arr = { "cha", "r", "act", "ers" };        // 6;
	arr = {"abcdefghijklmnopqrstuvwxyz"}; // 26
	arr = {"yy","bkhwmpbiisbldzknpm"};
    Solution s;
	cout << s.maxLength(arr) << endl;
	return 0;
}
