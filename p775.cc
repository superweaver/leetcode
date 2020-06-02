#include "common.h"
class Solution {
  public:
    // from left to right, to make it ideal permutation
    // A[i] == i or A[i] == i + 1 && A[i+1] == i
    bool isIdealPermutation(vector<int> &A) {
        for (int i = 0; i < A.size(); i++) {
            if (A[i] == i) {
                continue;
            }
            if (A[i] == i + 1 && A[i + 1] == i) {
                i++;
            } else {
                return false;
            }
        }
        return true;
    }
};

class Solution_2 {
public:
	bool isIdealPermutation(vector<int>& A) {
		vector<int> sorted;
		int n = A.size();
		int global = 0;
		int local = 0;
		for (int i = 0; i < n; ++i) {
            if (i > 0 && A[i] < A[i - 1]) {
                local++;
            }
            if (sorted.empty() || *sorted.rbegin() < A[i]) {
				sorted.push_back(A[i]);
			}
			else {
                // sorted.back() > A[i]
                //
				if (sorted.size() < 2) {
					sorted.push_back(A[i]);
					swap(sorted[0], sorted[1]);
					global++;
				}
				else {
					int last = sorted.back();
					sorted.pop_back();
					if (A[i] < sorted.back()) {
						// no more than 2 elements larger than A[i]
						return false;
					}
					else {
						sorted.push_back(A[i]);
						sorted.push_back(last);
						global++;
					}
				}
				if (local != global) {
					return false;
				}
			}
		}
		if (local != global) {
			return false;
		}
		return true;
	}
};
class Solution_1 {
public:
	bool isIdealPermutation(vector<int>& A) {
		// for any element i
		// from 0...i-1, the number of elements larger than A[i] <= 1
		set<int> sorted;
		int n = A.size();
		int global = 0;
		int local = 0;
		for (int i = 0; i < n; ++i) {
			if (i > 0 && A[i] < A[i - 1]) {
				local++;
			}
			if (sorted.empty() || *sorted.rbegin() < A[i]) {
				sorted.insert(A[i]);
			}
			else {
				int larger = distance(sorted.upper_bound(A[i]), sorted.end());
		//		if (larger >= 2) {
		//			return false;
		//		}
				global += larger;
				if (local != global) {
					return false;
				}
        		sorted.insert(A[i]);

			}
		}
		if (local != global) {
			return false;
		}

		return true;
	}
};

int main() {

	Solution s;

	return 0;
}
