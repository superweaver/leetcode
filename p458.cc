#include "common.h"

class Solution {
    // good explanation
    // https://blog.csdn.net/JackZhang_123/article/details/78775716
    // assume minutesToDie = 15, minutesToTest = 60
    // there are fives states for each pig
    // 1) die at minute 15
    // 2) die at minute 30
    // 3) die at minute 45
    // 4) die at minute 60
    // 5) alive after minute 60
    // assume there is only one pigs, how many buckets this pig can test?
    // It is five.
    // then how about two pigs? It is 5^2;
    // how to test ?
    // the index of these 25 pigs [0..24] can be represented as AB in base 5 system
    // index = A*5^1 + B *5^0
    // test:
    // at min 0, first pig drink all buckets whose (AB) reprentation has A == 0
    // at min 0, second pig drink all buckets whose (AB) reprentation has B == 0
    // at min 15, first pig drink all buckets whose (AB) reprentation has A == 1
    // at min 15, first pig drink all buckets whose (AB) reprentation has B == 1
    // ...
    // so similarly, N pigs can cover base^N buckets
    // the answer is int(ceil(log(buckets)/log(base))), where base=minutesToTest/minutesToDie + 1;

public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {

		if (buckets <= 1) return 0;
		int base = minutesToTest / minutesToDie + 1; // important
		int dimensions = 1;
		while (buckets > base) {
			buckets /= base;
			dimensions++;
		}
		return dimensions;
	}

};

int main() {

	Solution s;

	return 0;
}
