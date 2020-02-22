#include "common.h"
class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
		// first is the fold, second is value after module
        pair<long long, long long> ans(0, 0);
		pair<long long, long long> t(0, 0);
		// actual sum ending at index  = t.first* mode + t.second;
		// note: t.second >= 0;
		const long long Mod = 1000000007;
		int n = arr.size();
		int index = 0;
		long long round = 0;
		bool getround = true;
		int oldk = k;
        while (k) {
			if (t.second + Mod * t.first <= 0) {
                if (arr[index] >= 0) {
                    t = { 0, arr[index]};
                } else {
                    t = { -1, Mod + arr[index]};
                }
            } else {
				t.second += arr[index];	
				if (t.second >= Mod) {
					t.first ++;
					t.second -= Mod;
				} 
				else if (t.second < 0) {
					t.second += Mod;
					t.first--;
				}
			}
			if (ans < t) {
				ans = t;
			}
			if (getround) {
                round += arr[index];
            }
			index++;			
			if (index == n) {
				getround = false;
                k = min(k, 2);
                index = 0;
				k--;
			}
        }
		if (round >= 0) {
			int middles = max(oldk - 2, 0);
			round %= Mod;
			round *= middles;
            round %= Mod;
			return (ans.second + round) % Mod;
        } else {
            return (int)ans.second;
        }
    }
};

int main() {

    vector<int> arr = { 1, 2 }; 
	int k = 3; // 9
    arr = { 1, -2, 1 }, k = 5;  // 2
    arr = { -1, -2 }, k = 7;
    Solution s;
	cout << s.kConcatenationMaxSum(arr, k) << endl; 
	return 0;
}
