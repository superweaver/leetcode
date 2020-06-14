#include "common.h"
class Solution {
  public:
    int largestValsFromLabels(vector<int> &values, vector<int> &labels, int num_wanted,
                              int use_limit) {
        unordered_map<int, multiset<int>> cache;
        int n = values.size();
        //priority_queue<int, vector<int>, greater<int>> q;
        multiset<pair<int, int>> picks; // value, label// not set
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int label = labels[i];
            int value = values[i];
            auto &s = cache[label];
            if ((int)s.size() < use_limit) {
                s.insert(value);
                if ((int)picks.size() < num_wanted) {
                    picks.insert({value, label});
                    sum += value;
                } else {
                    if (value > picks.begin()->first) {
                        sum += value - picks.begin()->first;
                        picks.erase(picks.begin());
                        picks.insert({value, label});
                    }
                }
            } else {
                if (value > *s.begin()) {
                    s.insert(value);
                    auto pre = *s.begin();
                    s.erase(s.begin());
                    auto it = picks.find({pre, label});
                    if (it != picks.end()) {
                        sum -= it->first;
                        picks.erase(it);
                        picks.insert({value, label});
                        sum += value;
                    } else {
                        // has impact
                        if ((int)picks.size() < num_wanted) {
                            picks.insert({value, label});
                            sum += value;
                        } else {
                            if (value > picks.begin()->first) {
                                sum += value - picks.begin()->first;
                                picks.erase(picks.begin());
                                picks.insert({value, label});
                            }
                        }
                    }
                } //else { // no impact for sum	}
            }
        }
        return sum;
    }
};

int main() {

    Solution s;

    return 0;
}
