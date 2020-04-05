#include "common.h"
class Solution {
public:
    int countLargestGroup(int n) {
        auto getsum = [](int i) {
			int sum = 0;
			while(i) {
				sum += i % 10;
				i /= 10;
			}
			return sum;
        };
		counter.assign(37, 0);
        int result = 0;
		int max_freq = -1;
		for (int i = 1; i <= n; ++i)
        {
			int sum = getsum(i);
			counter[sum]++;
			if (max_freq < counter[sum]) {
				result = 1;
				max_freq = counter[sum];
			} else if (max_freq == counter[sum]) {
				result++;
			}
        }
        return result;
    }
private:
    //unordered_map<int, int> counter;  // sum->freq
    // 1 <= n <= 10^4
	// max = 9999
	vector<int> counter;
};

int main() {

	int n = 13; // 4
	n = 2; // 2
	n = 15; // 6
	//n = 24; // 5 
	Solution s;
	cout << s.countLargestGroup(n) << endl;

	return 0;
}
