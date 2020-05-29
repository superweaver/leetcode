#include "common.h"
// left to right
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> res(T.size());
        stack<int> days; // monotonic stack decreasing order
        for (int i = 0; i < T.size(); i++) {
            // for each temperature, find all days before it (no assigned) with lower temperature
            // stack may not be empty after reaching end
            while(!days.empty() && T[i] > T[days.top()]) {
                int idx = days.top();
                days.pop();
                res[idx] = i-idx;
            }
            days.push(i);
        }
        return res;
    }
};
// right to left
class Solution_my {
public:
   vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        int i = n-1;
        stack<int> st; // store index in T
       //单调栈
       //increasing stack
        vector<int> res(n,0);
        for(; i>=0; i--){
            // for each i, try to find warmer temperature after it
            while(!st.empty() && T[st.top()] <= T[i]){
                st.pop();
            }
            if(!st.empty()){
                res[i] = (st.top() - i);
            }
            st.push(i);
        }
        return res;
    }
};

int main() {

	Solution s;

	return 0;
}
