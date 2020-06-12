#include "common.h"
class Solution {
  public:
    bool isValid(string S) {
        string t;
        for (auto c : S) {
            if (c == 'c') {
                if (t.size() >= 2) {
                    if (t.back() == 'b') {
                        t.pop_back();
                        if (t.empty()) {
                            t.push_back('b');
                            t.push_back(c);
                        } else {
                            if (t.back() == 'a') {
                                t.pop_back();
                            } else {
                                t.push_back('b');
                                t.push_back(c);
                            }
                        }
                    } else {
                        t.push_back(c);
                    }
                }
            } else {
                t.push_back(c);
            }
            if (t.size() == 1 && t[0] != 'a') {
                return false;
            }
        }
        return t.empty();
    }
};

int main() {

	Solution s;

	return 0;
}
