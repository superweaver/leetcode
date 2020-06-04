#include "common.h"

class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        int n = shifts.size();
        int shift = 0;
        for (int i = n - 1; i >= 0; --i) {
            shift = (shift + shifts[i]) % 26;
            S[i] = 'a' + (S[i] - 'a' + shift) % 26;
        }
        return S;
    }
    string shiftingLetters2(string S, vector<int>& shifts) {
        int n = shifts.size();
        vector<int> all_shifts(n, 0);
        for(int j = n - 1; j >= 0; --j) {
            all_shifts[j] = shifts[j] % 26;
            if (j + 1 < n) {
                all_shifts[j] += all_shifts[j + 1];
            }
            all_shifts[j] %= 26;
        }
        for(int i = 0; i < n; ++i) {
            S[i] = 'a' + (S[i] - 'a' + all_shifts[i]) % 26;
        }
        return S;
    }
};


int main() {

	Solution s;

	return 0;
}
