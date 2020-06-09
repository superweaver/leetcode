#include "common.h"
// https://leetcode.com/problems/beautiful-array/discuss/186679/C++JavaPython-Odd-+-Even-Pattern-O%28N%29
// https://zhanghuimeng.github.io/post/leetcode-932-beautiful-array/
class Solution {
public:
    // property of beautiful array
    // if A is beautiful, then after the following operations, A is still beautiful
    // 1) x + A, add x to any element of A
    // 2) x * A, x != 0, multiply x to every any element of A
    // 3) delete an element in A
    vector<int> beautifulArray1(int N)
    {
        // recursive
        if (N == 1) {
            return { 1 };
        }
        // put odd to left, even to right
        int size_left = (N + 1) / 2; // 1, 3, 5 ...
        int size_right = N / 2; // 2, 4, 6, ...
        auto l = beautifulArray(size_left);
        auto r = beautifulArray(size_right);
        vector<int> result;
        for(auto i : l) {
            result.push_back(2 * i - 1);
        }
        for(auto i : r) {
            result.push_back(2 * i);
        }
        // why does this work?
        // l is beautiful, so 2 * l - 1 is beautiful
        // r is beautiful, so 2 * r is beautiful;
        // pick one element from new l ( 2 * l - 1) , it is odd
        // pick another element from new r ( 2 * r), it is even
        // the mean of this two elements is not an integer, so you won't find a k so that A[k] * 2 = sum of these two elements
        // so the formed array is beautiful
        return result;
    }

    vector<int> beautifulArray(int N) {
        // O(N)
        vector<int> res = { 1 };
        while (res.size() < N) {
            vector<int> tmp;
            for (int i : res) {
                if (i * 2 - 1 <= N) {
                    tmp.push_back(i * 2 - 1);
                }
            }
            for (int i : res) {
                if (i * 2 <= N) {
                    tmp.push_back(i * 2);
                }
            }
            res.swap(tmp);
        }
        return res;
    }
};



int main() {

	Solution s;

	return 0;
}
