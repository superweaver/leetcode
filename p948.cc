#include "common.h"
class Solution {
  public:
    int bagOfTokensScore(vector<int> &tokens, int P) {
        int n = tokens.size();
        sort(tokens.begin(), tokens.end());
        int point = 0;
        int power = P;
        int result = 0;
        for (int left = 0, right = n - 1; left <= right;) {
            while (left <= right && power >= tokens[left]) {
                point++;
                result = max(result, point);
                power -= tokens[left++];
            }
            if (point > 0 && left < right) {
                power += tokens[right--];
                point--;
            } else {
                break;
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
