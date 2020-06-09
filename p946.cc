#include "common.h"
class Solution {
  public:
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
        //with distinct values
        stack<int> s;
        int ipop = 0;
        size_t i = 0;
        while (true) {
            while (i < pushed.size() && (s.empty() || s.top() != popped[ipop])) {
                s.push(pushed[i++]);
            }
            if (i < pushed.size()) {
                s.pop();
                ipop++;
            } else {
                break;
            }
        }
        for (; ipop < popped.size();) {
            if (popped[ipop] != s.top()) {
                return false;
            } else {
                s.pop();
                ++ipop;
            }
        }
        return true;
    }
};

int main() {

	Solution s;

	return 0;
}
