#include "common.h"
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
		constexpr int N = 100001;
		bitset<N> isprime;
		isprime.set();
		isprime.set(0, false);
		isprime.set(1, false);
		for (int i = 2; i < N; ++i) {
			if (isprime[i]) {
				for (int j = i + i; j < N; j+=i) {
                    isprime.set(j, false);
                }
			}
		}
		vector<int> primes;
		for (int i = 2; i < N; ++i) {
			if (isprime[i]) {
				primes.push_back(i);
			}
		}
		int result = 0;
		//sort(nums.begin(), nums.end());
        int pre = nums[0] - 1;
		int sum = 0;
		for (auto x : nums) {
			if (x == pre) {
				result += sum;
				continue;
			}
			else {
                if (isprime[x]) {
                    pre = x;
                    sum = 0;
                    continue;
                }
                int mid = sqrt(x);
                sum = 0;
				//vector<pair<int, int>> temp;
				for (auto p : primes) {
                    if (p > mid) {
                        break;
                    }
                    if (x % p == 0 ) {
                        int other = x / p;
						if (other > p) {
							if (isprime[other] || other == p * p) { // !!!
								sum = 1 + x + p + other;
								//sum = 1 + x + temp[0].first + temp[0].second;
								break;
                                //  temp.push_back({ p, other });
                            }
                        }
                    }
                }
				//if (temp.size() == 1) { }
                pre = x;
                result += sum;
            }
        }
        return result;

    }
};


int main() {
	vector<int>nums {1,2,3,4,5,6,7,8,9,10}; // 45
    nums = { 7286, 18704, 70773, 8224, 91675 };
    Solution s;
	cout << s.sumFourDivisors(nums) << endl;

	return 0;
}
