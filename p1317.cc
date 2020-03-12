#include "common.h"
class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
		int k = n / 2;
		int m = n - k; // k <= m
		vector<int> vk;
        while (k) {
            vk.push_back(k % 10);
            k /= 10;
        }
        vector<int> vm;
		while(m) {
			vm.push_back(m % 10);
			m /= 10;
		}
		size_t i = 0;
		while(i < vm.size() && i < vk.size()) {
			if (vm[i] != 0 && vk[i] != 0) {
				i++;
			} else {
                if (max(vk[i], vm[i]) > 1) {
                    if (vk[i]) {
                        vk[i]--;
                        vm[i]++;
                    } else {
                        vm[i]--;
                        vk[i]++;
                    }
                } else {
                    // borrow from higher 
					if (vm.size()>= vk.size()) {
                        for (size_t j = i + 1; j < vm.size(); ++j) {
							if (vm[j] != 0){
								vm[j]--;
								if (j == vm.size() - 1 && vm[j] == 0) {
									vm.pop_back();
								}
								for (j--; j > i; --j) {
									vm[j] = 9;
								}
								break;
							}
						}
                    } else {
                        for (size_t j = i + 1; j < vk.size(); ++j) {
                            if (vk[j] != 0) {
                                vk[j]--;
                                if (j == vk.size() - 1 && vk[j] == 0) {
                                    vk.pop_back();
                                }
                                for (j--; j > i; --j) {
                                    vk[j] = 9;
                                }
								break;
                            }
                        }
                    }
                    vk[i] += 5;
                    vm[i] += 5;
                }
                i++;
            }
        }
		size_t minLen = min(vk.size(), vm.size());
        k = vk.size() > minLen ? vk.back() : 0;
        for (int j = minLen - 1; j >= 0; --j) {
            k = 10 * k + vk[j];
        }
        m = vm.size() > minLen ? vm.back() : 0;
        for (int j = minLen - 1; j >= 0; --j) {
            m = 10 * m + vm[j];
        }
		return {k, m};
    }
};

bool check(int x) {
    if (!x) {
        return false;
	}
    while (x) {
        int d = x%10;
		if (d == 0) {
			return false;
		}
		x /= 10;
    }
    return true;
}
int main() {

	int n = 1010;
	n = 69;
	Solution s;
	int solved = 0;
	for (int n = 2; n <= 10000; ++n) {
        auto r = s.getNoZeroIntegers(n);
		if(!check(r[0]) || !check(r[1])) {
			cout << "Error:" << n << endl;
        } else {
            cout << r[0] << " " << r[1] << " " << (n == r[0] + r[1]) << endl;
			solved ++;
        }
    }
	cout << solved << endl;
	return 0;
}
