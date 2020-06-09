#include "common.h"
class Solution {
public:
    vector<string> wordSubsets(vector<string>& A, vector<string>& B)
    {
        vector<int> count(128, 0);
        for (auto& s : B) {
            vector<int> count_s(128, 0);
            for (char c : s) {
                count_s[c]++;
            }
            for (char c = 'a'; c <= 'z'; ++c) {
                // !!!
                count[c] = max(count[c], count_s[c]);
            }
        }
        vector<string> result;
        for (auto& s : A) {
            vector<int> count_s(128, 0);
            for (char c : s) {
                count_s[c]++;
            }
            bool isValid = true;
            for (char c = 'a'; c <= 'z'; ++c) {
                if (count_s[c] < count[c]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                result.push_back(s);
            }
        }
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
