#include "common.h"
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
        int m = strs.size();
        if (m == 1) {
            return strs[0];
        }
        size_t minLen = UINT_MAX;
        for (auto &s : strs) {
            minLen = min(minLen, s.size());
        }
        if (minLen == 0) {
            return "";
        }
       
       return getCommonPrefix(strs, 0, minLen); 
    }
    string getCommonPrefix(vector<string>& strs, int start, int end) {
        // [start, end)
        if (start >= end) return string();

        int mid = start + ((end - start) >> 1);
        bool same = true;
        const char charatmid = strs[0][mid];
        for (size_t i = 1; i < strs.size(); ++i) {
            if (strs[i][mid] != charatmid) {
                same = false;
                break;
            }
        }
        if (same) {
            string leftcommonprefix = getCommonPrefix(strs, start, mid);
            if (leftcommonprefix.size() < mid - start) {
                return leftcommonprefix;
            } else {
                return leftcommonprefix + string(1, charatmid) + getCommonPrefix(strs, mid + 1, end);
            }

        } else {
            // common prefix is sure to be in the left of mid
            return getCommonPrefix(strs, start, mid);
        }
    }
};

int main() {

    vector<string> strs = {"flower","flow","flight"};
    //strs = {"dog", "racecar", "car"};
    strs = {"a", "b"};

    Solution s;
    cout << s.longestCommonPrefix(strs) << endl;
	return 0;
}
