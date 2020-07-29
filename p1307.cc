#include "common.h"
// https://leetcode.com/problems/verbal-arithmetic-puzzle/discuss/463916/C%2B%2B-12ms-DFS-and-Backtracking-and-Prunning-Strategy
class Solution {
    // chracter to digit mapping, and the inverse
	// (if you want better performance: use array instead of unordered_map)
    unordered_map<char, int> c2i;
    unordered_map<int, char> i2c;
	// limit: length of result
    int limit = 0;
	// digit: index of digit in a word
    // widx: index of a word in word list
    // sum: summation of all word[digit]
    bool helper(vector<string>& words, string& result, int digit, int widx, int sum) {
        if (digit == limit) {
            // !!!
            return sum == 0;
        }
		// if summation at digit position complete, validate it with result[digit].
        //
        // for this digit, summation is done
        //
        if (widx == words.size()) {
            // sum % 10 is the digit value in result from summation
            if (c2i.count(result[digit]) == 0 && i2c.count(sum % 10) == 0) {
                if (sum % 10 == 0 && digit + 1 == limit) { 
                    // Avoid leading zero in result
                    return false;
                }
                // map it to sum%10
                c2i[result[digit]] = sum % 10;
                i2c[sum%10] = result[digit];

                bool tmp = helper(words, result, digit + 1, 0, sum / 10);

                c2i.erase(result[digit]);
                i2c.erase(sum%10);
                return tmp;

            } else if (c2i.count(result[digit]) && c2i[result[digit]] == sum % 10) {
                // word index = 0;
                return helper(words, result, digit + 1, 0, sum / 10);
            } else {
                return false;
            }
        }

		// if word[widx] length less than digit, ignore and go to next word
        if (digit >= words[widx].length()) {
            return helper(words, result, digit, widx+1, sum);
        }
		// if word[widx][digit] already mapped to a value
        if (c2i.count(words[widx][digit])) {
            if (digit+1 == words[widx].length() && words[widx].length() > 1 && c2i[words[widx][digit]] == 0) {
                // leading zero
                return false;
            }
            return helper(words, result, digit, widx+1, sum + c2i[words[widx][digit]]);
        }
		// if word[widx][digit] not mapped to a value yet
        for (int i = 0; i < 10; i++) {
            if (digit + 1 == words[widx].length() && i == 0 && words[widx].length() > 1) {
                // leading zero
                continue;
            }
            if (i2c.count(i)) {
                // it has been mapped
                continue;
            }

            c2i[words[widx][digit]] = i;
            i2c[i] = words[widx][digit];

            bool tmp = helper(words, result, digit, widx+1, sum+i);
            c2i.erase(words[widx][digit]);
            i2c.erase(i);
            if (tmp) {
                return true;
            }
        }
        return false;
    }
public:
    bool isSolvable(vector<string>& words, string result) {
        limit = result.length();
        for (auto &w: words) {
            if (w.length() > limit) {
				return false;
            }
        }
        for (auto&w:words) {
            reverse(w.begin(), w.end());
        }
        reverse(result.begin(), result.end());
        return helper(words, result, 0, 0, 0);
    }
};

class Solution_fast {
  public:
    bool help(vector<string>& words, string& result, int idx, int digit, int sum)
    {
        if (digit == result.size()) {
            return sum == 0;
        }

        if (idx == words.size())
        {
            if (c2i[result[digit] - 'A'] != -1)
            {
                if (sum % 10 == c2i[result[digit] - 'A'])
                    return help(words, result, 0, digit+1, sum / 10);
            }
            else if (i2c[sum % 10] == '\0')
            {
                c2i[result[digit] - 'A'] = sum % 10;
                i2c[sum % 10] = result[digit];
                if (help(words, result, 0, digit+1, sum / 10)) return true;
                c2i[result[digit] - 'A'] = -1;
                i2c[sum % 10] = '\0';
            }
            return false;
        }

        if (digit >= words[idx].size())
            return help(words, result, idx+1, digit, sum);

        if (c2i[words[idx][digit] - 'A'] != -1)
            return help(words, result, idx+1, digit, sum + c2i[words[idx][digit] - 'A']);

        for (int i = 0; i < 10; ++i)
        {
            if (i2c[i] != '\0') continue;
            if (i == 0 && digit == words[idx].size() - 1 && words[idx].size() > 1) continue;
            i2c[i] = words[idx][digit];
            c2i[words[idx][digit] - 'A'] = i;
            if (help(words, result, idx+1, digit, sum + i))
                return true;
            i2c[i] = '\0';
            c2i[words[idx][digit] - 'A'] = -1;
        }
        return false;
    }

    bool isSolvable(vector<string>& words, string result) {
        for (auto &s : words) if (s.size() > result.size()) return false;
        memset(c2i, -1, sizeof c2i);
        memset(i2c, '\0', sizeof i2c);
        for (auto& s: words) reverse(s.begin(), s.end());
        reverse(result.begin(), result.end());
        return help(words, result, 0, 0, 0);
    }
private:
    char i2c[10];
    int c2i[26];
};

int main() {

	Solution s;

	return 0;
}
