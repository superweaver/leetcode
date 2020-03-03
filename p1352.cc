#include "common.h"
class ProductOfNumbers {
public:
    ProductOfNumbers() {
		cache.push_back({1, 1});

    }

    void add(int num) {
		if (num == cache.back().first) {
			cache.back().second++;
		} else {
			cache.push_back({num, 1});
		}
		
    }
    int getProduct(int k) {
		int p = 1;
		for (int i = cache.size() - 1; i >= 0; --i) {
			if (k >= cache[i].second) {
                p *= pow(cache[i].first, cache[i].second);
                k -= cache[i].second;
                if (!k) {
                    break;
				}
            } else {
                p *= pow(cache[i].first, k);
				break;
            }
            if (!p) {
                return p;
            }
        }
        return p;
    }
private:
	vector<pair<int, int>> cache;
};


int main() {

	Solution s;

	return 0;
}
