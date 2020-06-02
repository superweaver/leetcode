#include "common.h"
class Solution {
public:
	int kthGrammar(int N, int K) {
		if (N == 1) {
			return 0;
		}
		//return !((K & 1) ^ kthGrammar(N - 1, (K + 1) / 2));
        return (K & 1) == kthGrammar(N - 1, (K + 1) / 2);
        // (K+1)/2 is the parent in N-1 row
        //
        // 0->0,1
        // 1->1,0
        //
        // if  auto parent value = kthGrammar(N - 1, (K + 1) / 2) == 0
        // then if K&1,(left child), v = pv;
        // else v = !pv;
        //
        // similarly for pv = 1
    }
};

int main() {

	Solution s;

	return 0;
}
