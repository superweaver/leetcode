#include "common.h"
class Solution {
	public:
		// my solution
		int subarraysWithKDistinct(vector<int>& A, int K) {
			int n = A.size();
			int k = 0; // how many different integer in that range
			int result = 0;
			int left = 0; // left pointer
			int right = 0; // right pointer , not included
			vector<int> lastIndex(n + 1, -1); // lastIndex[v] is the last apperance of v
			for (; right < n;) {
				int v = A[right];
				if (k < K) {
					if (lastIndex[v] < left) { // we and add this v to range to increase k
						// link previous node to current node // in higer 16 bits
						if (lastIndex[v] >= 0) {
							A[lastIndex[v]] = (right << 16) + A[lastIndex[v]];
						}
						k++;
					} 
					lastIndex[v] = right;
					if (k == K ) {
						// try to expand the range where left ... right up to r have K different number
						int r = right + 1;
						while(r < n && lastIndex[A[r]] >= left) {
							// also need to link
							int vv = A[r];
							if (lastIndex[vv]>= 0) {
								A[lastIndex[vv]] = (r << 16) + A[lastIndex[vv]];
							}
							lastIndex[vv] = r;
							r++;
						}
						int len_right = r - right;
						while( k == K) {
							result += len_right;	
							int ov = A[left] &0xFFFF;
							// try to change left
							if (lastIndex[ov] == left) {
								// this is the last that value
								left++;
								k--;
								right = r;
								break;
							} else {
								int next = A[left] >> 16;
								if (next <= right) {
									// there are k different before right
									len_right = r - right;
									left++;	
								} else {
									if (next <= r) {
										left++;
										right = next;
										len_right = r - right;
									} else {
										// handled
									}
								}
							}	
						}

						if (r == n) {
							break;
						} //else { right = r-1; }
					}
					else {
						right++;
					}
				} else {
				}
			}
			for(auto & a : A) {
				a = a & 0xFFFF;
			}
			return result;
		}

		// other's solution for reference
		int subarraysWithKDistinct_ref(vector<int>& A, int K) {
			int n = A.size(), ans = 0;
			vector<int> count(n + 1, 0); // counting is better than recording lastIndex
			int k = 0;
			int left_start = 0;
			int left = 0;
			for(int right = 0; right < n; ++right) {
				if (count[A[right]]++ == 0) {
					// increase k
					k++;
				}
				if (k < K) {
					continue;
				}
				while (k > K) {
					if(--count[A[left++]] == 0) {
						// one to zero
						k--;
					}
					left_start = left; // actually next one
				}
				// k == K
				while(count[A[left]] > 1) {
					count[A[left++]]--;
				}
				ans += left - left_start + 1; // how many sub arrays ending at right have K differents numbers
			}
			return ans;
		}
};


int main() {
	vector<int> A = {1,2,1,2,3}; int K = 2; // 7
	A = {1,2,1,3,4}; K = 3; // 3
	A = {1, 1, 1}; K = 1; // 3
	Solution s;
	cout << s.subarraysWithKDistinct(A, K) << endl;
	cout << s.subarraysWithKDistinct_ref(A, K) << endl;
	return 0;
}
