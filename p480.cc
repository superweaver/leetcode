#include "common.h"
// https://www.google.com/search?client=firefox-b-1-d&q=480.+Sliding+Window+Median
//
class Solution_iterator_trick {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        if (k < 1) return result;
        int n = nums.size();
        if (k > n) return result;

        int offset = 1 - k % 2; // 0 or 1
        multiset<int> ms(nums.begin(), nums.begin() + k);
        // keep the mid iterator
        auto mid = next(ms.begin() , k / 2);
        double median =  ((double)*mid + (double)*(prev(mid, offset))) / 2.0;
        result.push_back(median);

        for (int i = k ; i < n; ++i) {
            ms.insert(nums[i]);
            if (nums[i] < *mid) {
                // nums[i] has been inserted
                --mid; // if the inerted one is less than *mid, go left
            }
            if (nums[i-k] <= *mid) {
                // nums[i-k] has not been erased
                ++mid;
            }
            // remove the first nums[i-k]
            ms.erase(ms.lower_bound(nums[i-k]));

            double median =  ((double)*mid + (double)*(prev(mid, offset))) / 2.0;
            result.push_back(median);
        }
        return result;
    }
};

// https://www.google.com/search?client=firefox-b-1-d&q=480.+Sliding+Window+Median
//
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k)
    {
        // use multiset as heap
        // priority_queue can't find and erase certain element
        vector<double> result;
        if (k < 1) {
            return result;
        }
        int n = nums.size();
        if (k > n) {
            return result;
        }

        multiset<int> small, large;  // keep small.size() >= large
        for (int i = 0; i < k - 1; ++i) {
            insert(small, large, nums[i]);
        }

        for (int i = k - 1; i < n; ++i) {
            // get segment
            insert(small, large, nums[i]);
            // get median
            if (k % 2) {
                result.push_back(*small.rbegin());
            } else {
                result.push_back(((double)*small.rbegin() + *large.begin()) / 2.0);
            }
            remove(small, large, nums[i - k + 1]);
        }
        return result;
    }


private:
     bool insert(multiset<int>& small, multiset<int>& large, int num)
    {
        // assmume small.size() - large.size() == 0 or 1
        if (small.size() > large.size() + 1) {
            return false;
        }
        if (small.size() > large.size()) {
            // small.size() == large.size() + 1
            if (num >= *small.rbegin()) {
                large.insert(num);
            } else {
                small.insert(num);
                large.insert(*small.rbegin());
                small.erase(--small.end());
            }
        } else {
            // small.size() == large.size()
            if (small.empty()) {
                small.insert(num);
            } else {
                if (num > *large.begin()) {
                    // num needs to be in large
                    large.insert(num);
                    small.insert(*large.begin());
                    large.erase(large.begin());
                } else {
                    small.insert(num);
                }
            }
        }
        return true;
    }

    bool remove(multiset<int>& small, multiset<int>& large, int num)
    {
        // assmume small.size() - large.size() == 0 or 1
        if (small.size() > large.size() + 1) {
            return false;
        }
        if (!(small.count(num) || large.count(num))) {
            return false;
        }
        if (small.count(num)) {
            if (small.size() > large.size()) {
                small.erase(small.find(num));
            } else {
                // large is not empty
                small.erase(small.find(num));
                small.insert(*large.begin());
                large.erase(large.begin());
            }
        } else {
            // in large
            if (small.size() > large.size()) {
                //large is not empty
                large.erase(large.find(num));
                large.insert(*small.rbegin());
                small.erase(--small.end());
            } else {
                // small is not empty
                large.erase(large.find(num));
            }
        }
        return true;
    }
};



int main() {

	Solution s;

	return 0;
}
