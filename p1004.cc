#include "common.h"
class Solution {
public:
    
    int longestOnes_v1(vector<int>& A, int K) {
		int n = A.size();
		vector<int> prefix_sum(n + 1, 0);
		for (int i = 0; i < n; ++i) {
			prefix_sum[i + 1] = prefix_sum[i] + A[i];
		}
		// f(a, b)means how many 0s are there in [a, b)
		// f(a, b) = (b - a) - (prefix_sum(b) - prefix_sum(a));
		int result = min(n, K);		
		int pre = 0;
		for (int i = 0; i < n;) {
			for (int j = max(i + 1, pre); j <= n; ++j) {
				int zeros = j - i - (prefix_sum[j] - prefix_sum[i]);
				if (zeros == K + 1) {
					pre = j;					
					result = max(result, j - 1 - i);
					break;
				}
				if (j == n  && zeros <= K) {
					result = max(result, j - i);
				}
			}
			if (!A[i]) { ++i;
				continue;
			} else {
				while(i < n && A[i]) {
					i++;
				}
			}
		}
		return result;
    }

    int longestOnes(vector<int> &A, int K) {
        int zeros = 0;
        int n = A.size();
        int right = -1;
        int result = min(n, K);
        if (result == n) {
            return result;
        }
        // two pointers
        for (int left = 0; left < n;) {
            for (++right; right < n; ++right) {
                zeros += 1 - A[right];
                if (zeros == K + 1) { // !!!
                    --right;
                    --zeros;
                    result = max(result, right - left + 1);
                    break;
                }
                if (right == n - 1 && zeros <= K) {
                    result = max(result, right + 1 - left);
                }
            }
            while (left < n && A[left]) {
                ++left;
            }
            if (left < n && !A[left]) {
                left++;
                zeros--;
            }
        }
        return result;
    }
};

int main() {

	Solution s;
	vector<int> A = {1,1,1,0,0,0,1,1,1,1,0}; 
	int K = 2; // 6
	A = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, K = 3; // 10

	cout << s.longestOnes(A, K) << endl;
	return 0;
}
