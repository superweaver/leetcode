#include "common.h"

class Solution {
public:
	Solution(int N, vector<int>& blacklist) {
        set<int> blackset(blacklist.begin(), blacklist.end());
        int n = N;
		while (!blackset.empty()) {
			int b = *blackset.begin();
			//	swap b with the tail of array A[n-1]
			int targetindex = n - 1; // index
			// if the target is not in blackset, continue;
            while (blackset.find(targetindex) != blackset.end()) {
                blackset.erase(targetindex);
                targetindex--;
            }
            // find the value at targetindex
			int targetvalue = targetindex;
			if (whitelist.count(targetindex)) {
				targetvalue = whitelist[targetindex]; // may not needed
			}
			whitelist[b] =  targetvalue;
			blackset.erase(b);
			n = targetindex;
		}
		M = N - blacklist.size();
	}

	int pick() {
		//int i = (int)(rand() / (RAND_MAX /double(M))) ;
        int i = rand() % M;
		if (whitelist.count(i)) {
			return whitelist[i];
		}
		else {
			return i;
		}
	}
private:
	unordered_map<int, int> whitelist;	// index and value at that index
	int M;
};

int main() {

	Solution s;

	return 0;
}
