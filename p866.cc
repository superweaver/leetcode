#include "common.h"
class Solution {
public:
	int primePalindrome(int N) {
		//https://www.cnblogs.com/grandyang/p/10714003.html
		// all palindrom numbers with even size, except 11, are not prime number
        if (N >= 8 && N <= 11) {
            return 11;
        }
        for (int i = 1; i < 1e5; ++i) {
			string str = to_string(i);
			string rev(str.rbegin(), str.rend());
			str += rev.substr(1);
			int num = stoi(str);
			if (num >= N && isPrime(num)) {
				return num;
			}
		}
		return -1;// not found
	}
private:
	bool isPrime(int num) {
		if (num < 2 || ((num % 2) == 0)) return num == 2;
		int upper = sqrt(num);
		for (int i = 3; i <= upper; ++i) {
			if (num %i == 0) {
				return false;
			}
		}
		return true;
	}
};

int main() {

	Solution s;

	return 0;
}
