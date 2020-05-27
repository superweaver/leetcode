#include "common.h"

class Solution {
  public:
    vector<int> exclusiveTime(int n, vector<string> &logs) {
        if (logs.empty()) {
            return {};
        }
        int pretimestamp = 0;
        int preID = 0;
        bool preStart = true;
        stack<int> cache; // fid, only push starting one

        const string &s = logs[0];
        auto pos = s.find_first_of(":");
        int fid = stoi(s.substr(0, pos));
        cache.push(fid);
        int pre_ts = 0;
        bool pre_start = true;
        vector<int> duration(n, 0);

        for (size_t i = 0; i < logs.size(); ++i) {
            const string &s = logs[i];
            auto pos = s.find_first_of(":");
            int fid = stoi(s.substr(0, pos));
            // fid acts as index in duration
            bool start = true;
            if (s[pos + 1] == 's') {
                start = true;
                pos += 7; // "start:"
            } else {
                start = false;
                pos += 5;
            }
            int ts = stoi(s.substr(pos));

            if (start) {
                if (!pre_start) {
                    pre_ts++;
                }
                int d = ts - pre_ts;
                duration[cache.top()] += d;
                cache.push(fid);
            } else {
                if (!pre_start) {
                    pre_ts++;
                }
                int d = ts + 1 - pre_ts;
                duration[cache.top()] += d;
                cache.pop(); // this must be fid
            }
            pre_ts = ts;
            pre_start = start;
        }
        return duration;
    }
};

int main() {

	Solution s;

	return 0;
}
