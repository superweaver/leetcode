#include "common.h"
class Solution {
public:
    int hIndex(vector<int>& citations) {
        // citations is sorted
        // A scientist has index h 
        // if h of his/her N papers have at least h citations each,
        // and the other N − h papers have no more than h citations each.
        if (citations.empty() || citations.back() == 0) {
            return 0;
        }
        int n = citations.size();    // number of total papers
        // find largest h which satisfies condition
        // 
        int low = 1;
        int high = n + 1; // exclusive
        while (low < high) {
            int mid = low + (high - low) / 2;
            // check if mid satisify contions
            int index = n - mid; // index in citations
            bool satisfy = (citations[index] >= mid);
            if (!satisfy) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        // find smallest one which doesn't satisfy conditon
        // return low - 1
        return low - 1;

    }
};

int main() {
    vector<int> citations = {0, 1, 3, 5, 6};

    Solution s;
    cout << s.hIndex(citations) << endl;

	return 0;
}
