#include "common.h"
class Solution {
public:
    string removeKdigits(string num, int k) {
        string res; // act as stack and keep result
        size_t keep = num.size() - k;
        int deletes = k;
        // we need to remove k digits
        for (size_t i = 0; i < num.size(); ++i) {
            while (!res.empty() && res.back() > num[i] && deletes > 0) {
                res.pop_back();
                deletes--;
            }
            res.push_back(num[i]);
        }
        // res.resize(keep);
        //
        // it is possible that actual deletes is less than k
        // and in that way res.size() is larger than keep
        //
        // for example : 1, 2, 3, 4, 5, k = 2
        // res = {1,2,3,4,5}
        // need to keep at most "keep"
        res.erase(keep, string::npos);

        // trim leading zeros
        size_t s = 0;
        while (s < res.size() && res[s] == '0') {
            s++;
        }
        // there are s zeros
        res = res.substr(s, res.size() - s);

        return res == "" ? "0" : res;
    }
};

int main() {

	Solution s;

	return 0;
}
