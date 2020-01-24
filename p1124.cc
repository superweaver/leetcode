#include "common.h"
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int prefixsum = 0;
        vector<int> Index;
        Index.push_back(-1); // Index[i] = j, the first prefixsum of -i appears at index j in hours;
        // !!! note : i = 0, -1, -2, ....
        int n = hours.size();
        int result = 0;
        for(int i = 0; i < n; ++i) {
           prefixsum += (hours[i] > 8) ? 1 : -1;
           if (prefixsum > 0) {
               result = max(result, i + 1);
           } else if (prefixsum == -Index.size()) {
               Index.push_back(i);
           } else {
               // prefixsum <= 0
               // find index for first (prefixsum - 1)
               int expect = -(prefixsum - 1);
               if( expect + 1 <= (int)Index.size()) {
                   int pre_index = Index[expect];
                   result = max(result, i - pre_index);
               }
           }
        }
        return result;
    }
};
int main() {
    vector<int> hours = {9,9,6,0,6,6,9};
    //hours ={6, 6, 9};
    hours ={6, 9, 6};
    Solution s;
    cout << s.longestWPI(hours) << endl;
    return 0;
}
