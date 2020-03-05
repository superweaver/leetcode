#include "common.h"
class Solution {
public:
    int minSetSize(vector<int>& arr) {
		int n = arr.size() >> 1;
        unordered_map<int, int> count;
		for(auto d : arr) {
			count[d]++;
			if (count[d] >= n){
				return 1;
			}
		}
		vector<int> v;
        for (auto& p : count) {
			v.push_back(p.second);
        }
		sort(v.begin(), v.end());
		int index = v.size() - 1;
		int c = 0;
		int r = 0;
		while(c < n) {
			c += v[index--];
			r++;
		}
		return r;
    }
};

int main() {

    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	arr = {1000,1000,3,7};
	arr = {7,7,7,7,7,7};
	arr = {3,3,3,3,5,5,5,2,2,7};
	Solution s;
	cout << s.minSetSize(arr) << endl;

    return 0;
}
