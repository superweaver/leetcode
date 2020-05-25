#include "common.h"

class Solution {
public:
    int maxVowels(string s, int k) {
        vector<int> delta(128);
        for (auto c : "aeiou") {
            delta[c] = 1;
        }
        int n = s.size();
        // k <= n;
        int count = 0;
        for (int i = 0; i < k; ++i) {
            count += delta[s[i]];
        }
        int result = count;
        for (int i = k ; i < n; ++i) {
            count += delta[s[i]];
            count -= delta[s[i - k]];
            result = max(result, count);
        }
        return result;
    }

};

int main() {

	Solution s;

	return 0;
}
