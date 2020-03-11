#include "common.h"
class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
		// counter += 1 if and only if sum of first k terms == (1 + k) * k / 2
		int n = light.size();
		int prefix_sum = 0;
		int counter = 0;
        for (int i = 0; i < n;) {
            prefix_sum += light[i];
			prefix_sum -= ++i;
			if(!prefix_sum) {
				++counter;
			}
        }
        return counter;
    }
};

int main() {

    vector<int> light = { 2, 1, 4, 3, 6, 5 }; // 3
	light = {3,2,4,1,5};
	Solution s;
	cout << s.numTimesAllBlue(light) << endl;
    return 0;
}
