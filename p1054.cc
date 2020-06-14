#include "common.h"
class Solution_ref {
  public:
    // 1 <= barcodes.length <= 10000
    // 1 <= barcodes[i] <= 10000

    vector<int> rearrangeBarcodes(vector<int> &barcodes) {
        short mapping[10001] = {}; // short is enough
        short max_cnt = 0;         // max count
        short max_n = 0;           // barcode value corresponding to max_cnt
        short pos = 0;             // position to fill in result vector
        for (auto n : barcodes) {
            max_cnt = max(max_cnt, ++mapping[n]);
            max_n = max_cnt == mapping[n] ? n : max_n;
        }
        // fill 0 2 4...
        // and then 
        // fill 1 3 5...
        // note it is possible that max_cnt can't reach to barcodes.size() - 1
        for (auto i = 0; i < 10001; i++) {
            auto n = (i == 0) ? max_n : i;
            while (mapping[n]-- > 0) {
                barcodes[pos] = n;
                pos = pos + 2 < barcodes.size() ? pos + 2 : 1;
            }
        }
        return barcodes;
    }
};

class Solution {
  public:
    vector<int> rearrangeBarcodes(vector<int> &barcodes) {
        if (barcodes.size() <= 2) {
            return barcodes;
        }

        unordered_map<int, int> count;
        for (auto i : barcodes) {
            count[i]++;
        }

        vector<pair<int, int>> v;
        for (auto &p : count) {
            v.push_back({p.second, p.first});
        }
        sort(v.begin(), v.end(), greater<pair<int, int>>());

        //		v.size() >= 2;
        //for (auto &p : v) {
        //		cout << p.first << " : " << p.second << endl;
        //}
        int pre = v[0].first;
        int last_value = v[0].second;
        for (size_t i = 1; i < v.size(); ++i) {
            if (v[i].first > pre) {
                pre = v[i].first - pre;
                last_value = v[i].second;
            } else if (v[i].first == pre) {
                pre = 0;
                last_value = -1;
            } else {
                pre = pre - v[i].first;
                // last_value = last_value
            }
        }
        if (pre & 1) { // tricky?
            pre--;
        }
        vector<int> result;
        int i = 0;
        int len_i = v[i].first;
        int j = 1;
        int len_j = v[j].first;
        int next = 2;
        while (true) {
            if (len_i > len_j) {
                for (int len = 0; len < len_j; ++len) {
                    result.push_back(v[i].second);
                    if (pre > 0) {
                        result.push_back(last_value);
                        pre--;
                    }
                    result.push_back(v[j].second);
                    if (pre > 0) {
                        result.push_back(last_value);
                        pre--;
                    }
                }
                len_i = len_i - len_j;
                j = next++;
                if (j == v.size()) {
                    break;
                }
                len_j = v[j].first;
            } else if (len_i == len_j) {
                for (int len = 0; len < len_i; len++) {
                    result.push_back(v[i].second);
                    if (pre > 0) {
                        result.push_back(last_value);
                        pre--;
                    }
                    result.push_back(v[j].second);
                    if (pre > 0) {
                        result.push_back(last_value);
                        pre--;
                    }
                }
                i = next++;
                if (i == v.size()) {
                    break;
                }
                len_i = v[i].first;
                j = next++;
                if (j == v.size()) {
                    break;
                }
                len_j = v[j].first;
            } else {
                // len_i < len_j
                for (int len = 0; len < len_i; ++len) {
                    result.push_back(v[i].second);
                    if (pre > 0) {
                        result.push_back(last_value);
                        pre--;
                    }
                    result.push_back(v[j].second);
                    if (pre > 0) {
                        result.push_back(last_value);
                        pre--;
                    }
                }
                len_j = len_j - len_i;
                i = next++;
                if (i == v.size()) {
                    break;
                }
                len_i = v[i].first;
            }
        }
        if (result.size() < barcodes.size()) {
            //result.push_back(result[result.size() - 2]);
            result.push_back(last_value);
        }
        return result;
    }
};

int main() {

    Solution s;

    return 0;
}
