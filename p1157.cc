#include "common.h"

class MajorityChecker {
public:
    // keythinking: frequency/count map when we want to quickly query candidates with certain
    // frequency!
    vector<pair<int, int>> freq2num;  // can be replaced with map
    vector<vector<int>> num2idx;
    MajorityChecker(vector<int>& arr)
    {
        int max_num = *max_element(arr.begin(), arr.end());
        num2idx.resize(max_num + 1);
        for (size_t i = 0; i < arr.size(); i++) {
            num2idx[arr[i]].emplace_back(i);
        }
        for (int i = 1; i <= max_num; i++) {
            if (!num2idx[i].empty()) {
                freq2num.push_back({ num2idx[i].size(), i });
            }
        }
        sort(freq2num.rbegin(), freq2num.rend());  // note it sorts reversely
    }

    int query(int left, int right, int threshold)
    {
        for (const auto& p : freq2num) {  // iterate from largest frequency to smallest
            if (p.first < threshold) {
                return -1;
			}
            int v = p.second; // value
            vector<int>& idx = num2idx[p.second];
            if (idx.front() > right || idx.back() < left) {
                continue;
			}
            int count = distance(lower_bound(idx.begin(), idx.end(), left),
                                 upper_bound(idx.begin(), idx.end(), right));
            if (count >= threshold) {
                return v;
			}
        }
        return -1;
    }
};

class MajorityChecker_my {
	// my solution
public:
    MajorityChecker_my(vector<int>& arr) {
        int n = arr.size();
		for (int i = 0; i < n; ++i) {
			int v = arr[i];
			if (!cache.count(v)) {
				First.push_back(i);
			}
			cache[v].push_back(i);
        }
        Array.swap(arr);
    }

    int query(int left, int right, int threshold)
    {
        int len = right - left + 1;
        if (2 * threshold <= len) {
            return -1;
        }
		
		auto it1 = upper_bound(First.begin(), First.end(), right);
        for (auto it = First.begin(); it != it1; ++it) {
            auto& v = Array[*it];
            auto& index = cache[v];
			if (index.back() < left) {
				continue;
			}
            int len = distance(lower_bound(index.begin(), index.end(), left),
                               upper_bound(index.begin(), index.end(), right));
            if (len >= threshold) {
                return v;
            }
        }
        return -1;
    }

private:
    unordered_map<int, vector<int>> cache;
	vector<int> Array;
	vector<int> First;
};


int main() {

	vector<int> arr = {1,1,2,2,1,1};
    MajorityChecker s(arr);
	cout << s.query(0, 5, 4) << endl;
	cout << s.query(0, 3, 3) << endl;
	cout << s.query(2, 3, 2) << endl;

    return 0;
}
