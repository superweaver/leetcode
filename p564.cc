#include "common.h"
//https://www.cnblogs.com/grandyang/p/6915355.html
class Solution {
  public:
    string nearestPalindromic(string n) {
        // n.size() <= 18
        // stol(n) > 0
        // assume n.size() == 3, then the answer won't be lower than 99 (len = 2)
        // the answer won't be larger than 1001 (len = 4);
        int len = n.size();
        typedef long T;
        T num = stol(n);
        T lower = (T)pow(10, len - 1) - 1;
        T upper = (T)pow(10, len) + 1;
        set<T> candidates;
        candidates.insert(lower);
        candidates.insert(upper);
        // n itself may be palindrome, need to remove it from solution domain
        // assume n is left + right
        // candidates are pre + reverse(pre), where pre = left + i; i = -1, 0, 1
        string left = n.substr(0, (n.size() + 1) / 2);
        T numleft = stol(left);
        for (int i = -1; i <= 1; ++i) {
            T pre = i + numleft;
            string strpre = to_string(pre);
            string right = strpre;
            reverse(right.begin(), right.end());
            // right may have one more chacter in the beginning
            int offset = 0;
            if (n.size() % 2) {
                // n is odd, then need pop head
                offset = 1;
            }
            string c = strpre + right.substr(offset);
            candidates.insert(stol(c));
        }
        candidates.erase(num);
        T r = num;
        T diff = numeric_limits<T>::max();
        for (auto c : candidates) {
            T d = abs(c - num);
            if (d < diff) {
                diff = d;
                r = c;
            }
        }
        return to_string(r);
    }
};

int main() {

	Solution s;

	return 0;
}
