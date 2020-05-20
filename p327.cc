#include "common.h"

class Solution {
public:
    int countRangeSum(vector<int> nums, int lower, int upper) {
        // count the number of range sum in [lower, upper]
        int n = nums.size();
        vector<long long > sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + (long long)nums[i];
        }
        // then sum of nums[i..j] = sum[j+1] - sum[i];
        return mergeSort(sum, 0, n + 1, lower, upper);
    }

private:
    int mergeSort(vector<long long>& sum, int start, int end, int lower, int upper)
    {
        // count the number of pairs in merging that sum[j] - sum[i] is in range [lower, upper]
        // end is exclusive
        if (start + 1 >= end) {
            return 0;
        }
        int mid = start + (end - start) / 2;
        int count = mergeSort(sum, start, mid, lower, upper) + mergeSort(sum, mid, end, lower, upper);
        int k = mid;
        int j = mid;
        int right = mid; // the index for right half array used for
        int ic = 0; // index of cache
        vector<long long> cache(end - start, 0);
        // note, left half and right half are sorted at this moment!
        for (int i = start; i < mid; ++i) {
            while(k < end && sum[k] - sum[i] <= upper ) {
                k++;
            }
            while (j < end && sum[j] - sum[i]  < lower) {
                j++;
            }
            count += k - j;
            // merge
           while(right < end && sum[right] < sum[i]) {
               cache[ic] = sum[right];
               ic++;
               right++;
           }
           cache[ic++] = sum[i];
        }
        while(right < end) {
            cache[ic++] = sum[right++];
        }
        // copy back
        for (int i = start; i < end; ++i) {
            sum[i] = cache[i - start];
        }
        return count;
    }
};



int main() {

	Solution s;

	return 0;
}
