#include "common.h"
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int result = 0;
        int n = arr.size();
        /*
        unordered_map<int, vector<int>> cache; // xor value -> index of first element to get xor value
        int x = 0;
        cache[x] = {-1};
        for (int i = 0; i < n; ++i) {
            x ^= arr[i];
            if (cache.count(x)) {
                for (auto pre : cache[x]) {
                    result += i - pre - 1;
                }
                cache[x].push_back(i);
            } else {
                cache[x] = {i};
            }
        }
        */
        unordered_map<int, pair<int, int>> cache; // xor value -> (sum of prefix, count of previous index)
        cache[0] = {-1, 1};
        int x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= arr[i];
            if (cache.count(x)) {
                // pick any of previous index then arr[pre + 1, ... i] has xor value = 0
                // divide into two non-empty parts, then they have same xor value
                result += (i - 1) * cache[x].second - cache[x].first;
                cache[x].first += i;
                cache[x].second++;
            } else {
                cache[x] = {i, 1};
            }
        }
        return result;
    }
};

int main() {

    vector<int> arr = {2,3,1,6,7}; // 4
    //arr.assign(5, 1); // 10
    arr = {7,11,12,9,5,2,7,17,22}; // 8

    Solution s;

    cout << s.countTriplets(arr) << endl;

	return 0;
}
