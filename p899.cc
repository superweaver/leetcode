#include "common.h"
class Solution {
public:
    //https://zhuanlan.zhihu.com/p/63659046
    //https://www.cnblogs.com/grandyang/p/10995474.html
    string orderlyQueue(string S, int K) {
        if (K > 1) {
            // !!!
            sort(S.begin(), S.end());
            return S;
        }
        // for K == 1, rotate S and fid the minimum
        string res = S;
        for (int i = 0; i < S.size(); ++i) {
            res = min(res, S.substr(i) + S.substr(0, i));
        }
        return res;
    }
};

int main() {

	Solution s;

	return 0;
}
