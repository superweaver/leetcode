#include "common.h"

class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
      // idea: median m + n if even; median is (arr[(m+n)/2 - 1] + arr[(m+n)/2])/2
      // if odd, arr[(m+n)/2];
      //
      // Then it can be converted to find out kth element which can be done using binarysearch
      //[a1,a2,...,am-1,am,am+1,...,an], [b1,b2,...,bm-1,bm,bm+1,...,bn]
      //
      // if k > m we can drop the smallest part of the above arr of size len so that we search k -
      // len in the rest until k == 0 return it
      if ((nums1.size() + nums2.size()) % 2 == 0) {
          return (findKth(nums1, 0, nums2, 0, (nums1.size() + nums2.size()) / 2) +
                  findKth(nums1, 0, nums2, 0, (nums1.size() + nums2.size()) / 2 + 1)) *
                 0.5;
      } else {
          return findKth(nums1, 0, nums2, 0, (nums1.size() + nums2.size()) / 2 + 1);
      }
  }
        int findKth(vector<int>& nums1, int start1, vector<int>& nums2, int start2, int k) {
            if (start1 >= nums1.size()) return nums2[start2 + k - 1];
            if (start2 >= nums2.size()) return nums1[start1 + k - 1];
            if (k == 1) return min(nums1[start1], nums2[start2]);
            // advance by k/2
            int vmid1 = (start1 + k/2 - 1 < nums1.size()) ? nums1[start1 + k/2 - 1] : INT_MAX;
            int vmid2 = (start2 + k/2 - 1 < nums2.size()) ? nums2[start2 + k/2 - 1] : INT_MAX;
            // 
            if (vmid1 < vmid2) {
                // vmid1 is smaller , then we advance start1 by k / 2
                return findKth(nums1, start1 + k / 2, nums2, start2, k - k / 2);
            } else {
                return findKth(nums1, start1, nums2, start2 + k/2, k - k/2);
            }
        }
};
int main() {

	Solution s;

	return 0;
}
