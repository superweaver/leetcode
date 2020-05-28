#include "common.h"

class Solution {
public:
	int maximumSwap(int num) {

        vector<int> vform; // vector form of num
        vector<int> firstoccurance(10, -1); // record the first index of each digit
		int predigit = -1;
		int digits = 0;
		bool des = true; // is decreasing from MSB to LSB
		int num_back = num;

		while (num_back) {
			int digit = num_back % 10; // LSB
			vform.push_back(digit);
            if (digit < predigit) {
                des = false;
            }
            if (firstoccurance[digit] == -1) {
				firstoccurance[digit] = digits;// record first occurance;
			}
			predigit = digit;
			digits++;
			num_back /= 10;
		}
        if (des) {
            // eg :9987
            return num;
        }

        for (int i = 9; i >= 0; --i) {
            if (firstoccurance[i] == -1) {
                // no such digit
                continue;
            }
            int index_in_num = firstoccurance[i];
            // check if there is a smaller digits beform this index
            // if found, swap these two digits
			for (int k = digits - 1; k > index_in_num; --k) {
				if (i > vform[k]) {
					int k_in_num = k;
					int vk = pow(10, k_in_num) * vform[k];
					int vi = pow(10, index_in_num) * i;
					int nvk = pow(10, index_in_num)* vform[k];
					int nvi = pow(10, k_in_num) * i;
					num -= (vi + vk);
					num += (nvk + nvi);
					return num;
				}

			}
		}
		return num;
	}
};

int main() {

	Solution s;

	return 0;
}
