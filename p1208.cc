#include "common.h"
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost)
    {
        int n = s.size();
        int result = 0;
		int left = 0;
		int sum = 0;
		for (int right = 0; right < n; ++right) {
			sum += std::abs(s[right] - t[right]);;
			while(sum > maxCost) {
				sum -= abs(s[left] - t[left]);
				++left;
			}
			result = max(result, right - left + 1);
		}
        return result;
    }
    // n
    int equalSubstring_O_n(string s, string t, int maxCost) {
        int n = s.size();
        vector<int> prefix_sum(n + 1, 0);
        int result = 0;
		// double pointers
		int left = 0;
		int right = 1;
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + std::abs(s[i] - t[i]);
			// right is i + 1
			right = i + 1;
            while (prefix_sum[right] - prefix_sum[left] > maxCost) {
				left++;
            }
            result = max(result, right - left);
        }
		return result;
    }
    // nlog(n)
    int equalSubstring2(string s, string t, int maxCost) {
		int n = s.size();
		vector<int> prefix_sum(n + 1, 0);
		int result = 0;
		for (int i = 0; i < n; ++i) {
			int c = std::abs(s[i] - t[i]);
            prefix_sum[i + 1] = prefix_sum[i] + c;
            if (prefix_sum[i + 1] <= maxCost) {
                result = max(result, i + 1);
            } else {
                auto it = lower_bound(prefix_sum.begin(), prefix_sum.begin() + (i + 2),
                                      prefix_sum[i + 1] - maxCost);
                result = max(result, (int)distance(it, prefix_sum.begin() + (i + 1)));
            }
        }
		return result;
    }
};

int main() {
	string s = "abcd", t = "bcdf"; 
	int maxCost = 3; // 3
	//s = "abcd", t = "cdef", maxCost = 3; // 1
    //s = "abcd", t = "acde", maxCost = 0;   // 1
    s = "tuhwpmkerswypuexja", t = "sdmxfcgynmhhfvwcfp", maxCost = 173; // 17

    Solution so;
	cout << so.equalSubstring(s, t, maxCost) << endl;
	return 0;
}
