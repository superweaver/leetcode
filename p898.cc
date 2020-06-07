#include "common.h"
class Solution {
public:

	int subarrayBitwiseORs(vector<int>& A) {
        unordered_set<int> result(A.begin(), A.end());
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            //result.insert(A[i]);
            auto current = A[i];
            auto pre = 0;
            for (int j = i - 1; j >= 0; --j) {
                pre |= A[j]; // xor of A[j]...A[i-1]
                auto next = pre | A[i]; // xor of A[j...i]
                if (next == pre) {
                    break;
                } else {
                    result.insert(next);
                }
            }
        }
        return result.size();
    }
	//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-898-bitwise-ors-of-subarrays/
	int subarrayBitwiseORs_ref(vector<int>& A) {
        // construct subarray
        // sub[i] = {sub[i-1]+A[i], {}+A[i]}
        // apply OR on it
        unordered_set<int> result;
		unordered_set<int> current;
		unordered_set<int> next;
		for (auto i : A) {
			next.clear();
			for (auto c : current) {
				next.insert(c | i);
			}
			next.insert(i);	// don't forget this
			current.swap(next);
			result.insert(current.begin(), current.end());
		}
		return result.size();
	}
};

int main() {

	Solution s;

	return 0;
}
