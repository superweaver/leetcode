#include "common.h"
class MountainArray {
public:
    MountainArray(vector<int>& b)
    {
        a = b;
    }
    int get(int index)
    {
        return a[index];
    }
    int length()
    {
        return a.size();
    }

private:
    vector<int> a;
};
class Solution {
public:
    int findInMountainArray(int target, MountainArray& mountainArr)
    {
        int n = mountainArr.length();
        if (n == 1) {
            return get(0, mountainArr) == target ? 0 : -1;
        }
        int start = get(0, mountainArr);
        int end = get(n - 1, mountainArr);
        if (target < start && target < end) {
            return -1;
        }
        set<int> candidate;
        if (start == target) {
            return 0;
        }
        if (end == target) {
            candidate.insert(n - 1);
        }
        int l = 1;
        int r = n - 2;
        // try to find mid
        int mid = l + (r - l) / 2;
        while (l <= r) {
            mid = l + (r - l) / 2;
            int current = get(mid, mountainArr);
            if (current == target) {
                candidate.insert(mid);
            }
            int pre = get(mid - 1, mountainArr);
            if (pre == target) {
                candidate.insert(mid - 1);
            }
            int next = get(mid + 1, mountainArr);
            if (next == target) {
                candidate.insert(mid + 1);
            }
            if (pre < current && current > next) {
                break;
            } else if (pre < current && current < next) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (candidate.size() == 2) {
            return *candidate.begin();
        }
        int peak = get(mid, mountainArr);
        if (peak < target) {
            return -1;
        }
        if (peak == target) {
            return mid;
        }
        // check left side
        if (start < target) {
            l = 1;
            r = l;
            for (auto it = cache.begin(); it != cache.end(); ++it) {
                if (it->second == target) {
                    return it->first;
                }
                if (it->second > target) {
                    r = it->first;
                    break;
                }
            }
            // check if we can find target in [l, r]
            if (find(target, l, r, candidate, mountainArr, true)) {
                return *candidate.begin();
            }
        }
        if (end < target) {
            bool secondfound = false;
            r = n - 2;
            l = r;
            for (auto it = cache.find(mid); it != cache.end(); ++it) {
                if (it->second == target) {
                    candidate.insert(it->first);
                    secondfound = true;
                    break;
                }
                if (it->second < target) {
                    --it;
                    l = it->first;
                    break;
                }
            }
            if (!secondfound) {
                find(target, l, r, candidate, mountainArr, false);
            }
        }
        // check candidate
        if (candidate.empty()) {
            return -1;
        } else {
            return *candidate.begin();
        }
    }

private:
    map<int, int> cache;  // index to value
    int get(int index, MountainArray& mountainArr)
    {
        if (cache.count(index)) {
            return cache[index];
        } else {
            return cache[index] = mountainArr.get(index);
        }
    }
    bool find(int target, int l, int r, set<int>& candidate, MountainArray& mountainArr,
              bool isleft)
    {
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int current = get(mid, mountainArr);
            if (current == target) {
                candidate.insert(mid);
                return true;
            } else if (current < target) {
                if (isleft) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            } else {
                if (isleft) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        return false;
    }
};

int main() {
    vector<int> a{ 1, 2, 5, 1 };
	int target = 5;
    a = { 1,  3,  5,  7,  9,  11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39,
          41, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9,  7,  5,  3 };
    target = 21;
    MountainArray m(a);
	Solution s;
	cout << s.findInMountainArray( target, m) << endl;
	return 0;
}
