#include "common.h"
// direct LCS is also OK
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<int> count1(256, 0);
        for (int i = word1.size(); i >= 0; --i) {
            count1[word1[i]]++;
        }
        //for (char c : word1) {
        //    count[c]++;
        //}
        vector<char> count2(256, 0);
        // for (char c : word2) {
        //    count[c]++;
        // }
        for (int i = word2.size(); i >= 0; --i) {
            count2[word2[i]]++;
        }
        unordered_set<char> common;

        for (char i = 'a'; i <= 'z'; ++i) {
            /*
            if (!count1[i] && count2[i]) {
                remove2.insert(i);
            } else if (!count2[i] && count1[i]) {
                remove1.insert(i);
            }
            */
            if (count1[i] && count2[i]) {
                common.insert(i);
            }
        }
        string s1, s2;
        for(auto c : word1) {
            if (common.count(c)) {
                s1.push_back(c);
            }
        }
        for (auto c : word2) {
            if (common.count(c)) {
                s2.push_back(c);
            }
        }
        //int result = word1.size() - s1.size();
        //result += word2.size() - s2.size();
        // find the length of longest common subsequence of s1 and s2
        int lenLCS = getLCS(s1, s2);
        //result += s1.size() + s2.size() - 2 * lenLCS;
        return word1.size() + word2.size() - 2 * lenLCS;
    }
private:
    int getLCS(const string& s1, const string& s2)
    {
        int n1 = s1.size();
        int n2 = s2.size();
        if (!n1 || !n2) {
            return 0;
        }
        // dp[i][j] is the length of LCS of s1[0..i) and s2[0..j)
        // if s1[i-1] == s2[j-1], dp[i][j] = dp[i-1][j-1] + 1
        // otherwise dp[i][j] = max(dp[i-1][j], dp[i][j-1]
        vector<vector<int> > dp(n1 + 1, vector<int>(n2 + 1, 0));
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                if (s1[i] == s2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                } else {
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }
        return dp[n1][n2];
    }
};

int main() {

	Solution s;

	return 0;
}
