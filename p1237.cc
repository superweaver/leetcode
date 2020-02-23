#include "common.h"
class CustomFunction {
public:
  // Returns positive integer f(x, y) for any given positive integer x and y.
  int f(int x, int y) {
//	  return x + y;
	  //return x * y;
	return x*x + y;
  }
};
class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
		// ordered 2d array
        // 1 <= x, y <= 1000
		int x = 1;
		int y = 1;
		vector<vector<int>> result;
		unordered_set<int> cache;
		int v_m = customfunction.f(1, 1);
		int v_M = customfunction.f(1000, 1000);
		if (z < v_m || z > v_M) {
			return result;
		}
		// find row
		const int low = 1;
		const int high = 1000;
		const int fixed = 1000;
		y = customLowerBound(customfunction, low, high, true, fixed, z);
		for (; y <= 1000; ++y) {
			if (customfunction.f(1, y) > z) {
				break;
			} else {
                x = customLowerBound(customfunction, low, high, false, y, z);
				if (customfunction.f(x, y) == z) {
                    cache.insert(x * 1000 + y);
                }
			}
		}
		// find column
        x = customLowerBound(customfunction, low, high, false, fixed, z);
        for (; x <= 1000; ++x) {
			if (customfunction.f(x, 1) > z) {
				break;
			} else {
                y = customLowerBound(customfunction, low, high, true, x, z);
				if (customfunction.f(x, y) == z) {
                    cache.insert(x * 1000 + y);
                }
			}
		}
		for(auto i : cache) {
            result.push_back({i / 1000, i % 1000});
        }

        return result;
    }
private:
    int customLowerBound(CustomFunction& customfunction, int low, int high, bool findrow, int fixed,
                         int z)
    {
        int count = high - low + 1;
        while (count > 0) {
            int step = count / 2;
            int mid = low + step;
            int v_mid = findrow ? customfunction.f(fixed, mid) : customfunction.f(mid, fixed);
            if (v_mid < z) {
                low = mid + 1;
                count -= (step + 1);
            } else {
                // high = mid;
                count = step;
            }
        }
        return low;
    }
};

int main() {
	CustomFunction cf;
	int z = 5;	
	z = 4;
	z = 9;
	Solution s;
	auto r = s.findSolution(cf, z);
	for (auto&v : r) {
		displayvector(v);
	}
	return 0;
}
