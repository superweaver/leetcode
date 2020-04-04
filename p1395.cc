#include "common.h"
class Solution {
public:
    int numTeams(vector<int>& rating) {
		int n = rating.size();	
		vector<int> less(n, 0);
		vector<int> greater(n, 0);
		multiset<int> cache;
		for (size_t i = 0; i < rating.size(); ++i) {
			// count how many previous elements are less than i
			auto p = cache.equal_range(rating[i]);
			less[i] = distance(cache.begin(), p.first);
			// count how many previous elements are larger than i
			greater[i] = distance(p.second, cache.end());
			cache.insert(rating[i]);
		} 
		int total = 0;
		for (size_t i = 2; i < rating.size(); ++i) {
			for (size_t j = 1; j < i; ++j) {
				if (rating[i] > rating[j]) {
					total += less[j];
				} else if (rating[i] < rating[j]) {
					total += greater[j];
				}
			}
		}
		return total;
    }
};

int main() {

    vector<int> rating = { 2, 5, 3, 4, 1 }; // 3
    rating = { 2, 1, 3 };                   // 0
	rating = {1,2,3,4}; // 4

    Solution s;
	cout << s.numTeams(rating) << endl;

	return 0;
}
