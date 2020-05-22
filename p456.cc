#include "common.h"
class Solution {
public:
   //  https://www.cnblogs.com/grandyang/p/6081984.html
  bool find132pattern(vector<int>& nums) {
        int third = INT_MIN; // good initial value
        stack<int> st;
      // keep all elements on the right side of third and they are bigger than third
                             // this stack will be an monotonous stack
        for (int i = nums.size() - 1; i >= 0; --i) {
            if (nums[i] < third) {
                // at this moment, st is not empty
                return true;
            }
            while (!st.empty() && nums[i] > st.top()) {
                // nums[i] is a better candidate for older "third"
                // so we can update third, because nums[i] is larger
                third = st.top();
                st.pop();
            }
            st.push(nums[i]);
        }
      return false;
    }


};


int main() {

	Solution s;

	return 0;
}
