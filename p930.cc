#include "common.h"
class Solution {
  public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        int prefix_sum = -1;
        // can use vector
        unordered_map<int, int>  sum2count; // prefix_sum  : how many indices in the past
        sum2count[0] = 1;                   // sum = 0, index = -1
        int result = 0;
        int sum = 0;
        for (auto c : A) {
            sum += c;
            int expect = sum - S;
            if (expect >= 0 && sum2count.count(expect)) {
                result += sum2count[expect];
            }
            sum2count[sum]++;
        }
        return result;
    }
};
class Solution2 {
  public:
    int numSubarraysWithSum(vector<int> &A, int S) {
        int n = A.size();
        int left = 0;
        int right = 1;
        int sum = A[0];
        int result = 0;
        if (S == 0) {
            for (int i = 0; i < n;) {
                if (A[i] == 0) {
                    int j = i;
                    while (j < n && A[j] == 0) {
                        j++;
                    }
                    int len = j - i;
                    result += (len + 1) * len / 2;
                    i = j;
                } else {
                    i++;
                }
            }
            return result;
        }

        while (true) {
            while (right < n && sum < S) {
                sum += A[right++];
            }
            if (sum == S) {
                int sub = 1;
                while (left < right && A[left] == 0) {
                    left++;
                    sub++;
                }
                // A[left] == 1 now
                result += sub;
                while (right < n && A[right] == 0) {
                    right++;
                    result += sub;
                } // A[right] == 1
                sum -= A[left++];
            } else {
                break;
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
