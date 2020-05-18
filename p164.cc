#include "common.h"
class Solution {
public:
    // bucket sort
    int maximumGap(vector<int>& nums) {
        // not solved
        //http://cgm.cs.mcgill.ca/~godfried/teaching/dm-reading-assignments/Maximum-Gap-Problem.pdf best
        // http://yucoding.blogspot.com/2014/12/leetcode-question-maximum-gap.html
        // http://blog.csdn.net/u012162613/article/details/41936569 // good
        int N = nums.size();
        if(N < 2) return -0;

        int Min = INT_MAX;
        int Max = INT_MIN;
        for(int i = 0; i < N; ++i){
            Min = min(Min, nums[i]);
            Max = max(Max, nums[i]);
        }

        //prepare N-1 buckets for middle N-2 elements;  // at least one empty bucket

        int Len = (Max - Min) / (N) + 1;    // tricks
        int Buckets = (Max - Min) / Len + 1;
        //maintain the min and max of N + 1 buckest;
        vector<vector<int> > MinMax;
        MinMax.resize(Buckets);
        for(int i = 0; i < N; i++){
            int index = (nums[i] - Min) / Len;
            if(MinMax[index].empty()){
                MinMax[index].push_back(nums[i]);   //min
                MinMax[index].push_back(nums[i]);   //max
            }
            else{
                MinMax[index][0] = min(MinMax[index][0], nums[i]);
                MinMax[index][1] = max(MinMax[index][1], nums[i]);
            }
        }

        // calculate the max gap
        int pre = 0;    // it is sure the first bucket has element;
        int MaxGap = INT_MIN;
        for(int i = 1; i < Buckets; ++i){
            if(MinMax[i].empty()) continue;
            MaxGap = max(MaxGap, MinMax[i][0] - MinMax[pre][1]);
            pre = i;
        }
        return MaxGap;
    }

    //https://leetcode.com/problems/maximum-gap/discuss/50642/Radix-sort-solution-in-Java-with-explanation
    int maximumGap_radix(vector<int>& nums) {
        // this is real sort
        // radix sort is O(Kn) K is the radix
         int n = nums.size();
         if (n < 2) {
             return 0;
         }
         auto maxv = *max_element(nums.begin(), nums.end());

         const int R = 10;
         int exp = 1; // R^0
         vector<int> output(n);
         vector<int> count(R, 0);
         while ((maxv / exp) > 0) {
             // radix sort
             count.assign(R, 0);
             // count the frequency
             for (auto v : nums) {
                 count[(v / exp) % R]++;
             }
             // convert count to index of output
             // count[i] is 1-indexed index in output
             for (int i = 1; i < R; ++i) { // note : it is R not n
                 count[i] += count[i - 1];
             }
             // build output
             // from n -1 to 0
             // --index;
             for (int i = n - 1; i >= 0; --i) {
                 output[--count[(nums[i] / exp) % R]] = nums[i];
             }
             nums.swap(output);
             exp *= R;
       }
       // find max diff
       int result = INT_MIN;
       for (int i = 1; i < n; ++i) {
           result = max(result, nums[i] - nums[i - 1]);
       }
       return result;
    }
};


int main() {
    vector<int> nums = {15252, 16764, 27963, 7817,  26155, 20757, 3478,  22602, 20404, 6739,
                        16790, 10588, 16521, 6644,  20880, 15632, 27078, 25463, 20124, 15728,
                        30042, 16604, 17223, 4388,  23646, 32683, 23688, 12439, 30630, 3895,
                        7926,  22101, 32406, 21540, 31799, 3768,  26679, 21799, 23740};
    nums = {3, 6, 9, 1};

    Solution s;
    cout << s.maximumGap(nums) << endl;
    cout << s.maximumGap_radix(nums) << endl;

    return 0;
}
