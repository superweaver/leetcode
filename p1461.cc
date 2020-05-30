#include "common.h"
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int count = 1 << k; 
        int leastsize = k + count - 1; 
        int n = s.size();
        if (n < leastsize) {
            return false;
        }
        // random pick ?
        int upper = min(count, 100);
       for (int i = 0; i < upper; ++i) {
           int r = rand() % count;
           string str;
           while (s.size() < k) {
               s.push_back(r & 1);
               r >>= 1;
           }
           if (s.find(str) == string::npos) {
               return false;
           }
       }
       // what to do ?
       // return true?
       //
       vector<bool> cache(count, true);
       int num = 0;
       int mask = count - 1;
       for (int i = 0; i < k; ++i) {
           num = ((num << 1) + s[i] - '0') & mask;
       }
       cache[num] = false;
       count--;
       for (int i = k; i < n; ++i) {
           num = ((num << 1) + s[i] - '0') & mask;
           if (cache[num]) {
               cache[num] = false;
               if (!(--count)) {
                   return true;
               }
           }
       }
       return false;
    }
};

int main() {

	Solution s;

	return 0;
}
