#include "common.h"
class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        if (nums.empty()) {
            return "";
        }
        string path;
        return helper(nums, 0, nums.size());
    }
private:
    string helper(vector<int>& nums, int start, int end)
    {
        int len = end - start;
        if (len == 0) return "";
        if (len == 1) return to_string(nums[start]);
        if (len == 2) {
            return to_string(nums[start]) + "/" + to_string(nums[start + 1]);
        } else {
            ostringstream oss;
            oss << nums[start] << "/(";
            for (int i = start + 1; i < end; ++i) {
                oss << nums[i];
                if (i < end - 1) {
                    oss << "/";
                }
            }
            oss << ")";
            return oss.str();
        }
    }
};

class Solution2 {
public:
    string optimalDivision(vector<int>& nums) {
        if (nums.empty()) {
            return "";
        }
        string path;
        return helper(nums, 0, nums.size(), true);
    }
private:
    string helper(vector<int>& nums, int start, int end, bool Max)
    {
        int len = end - start;
        if (len == 0) return "";
        if (len == 1) return to_string(nums[start]);
        if (len == 2) {
            return to_string(nums[start]) + "/" + to_string(nums[start + 1]);
        }
        string right = helper(nums, start + 1, end, !Max);
        if (Max) {
            int slash = (end - start - 1) - 1;
            bool hasParenthesis = right.find('(') != string::npos;
            if (hasParenthesis) {
                // move the "(" to head
                auto pos = right.find('(');

                right = to_string(nums[start]) + "/(" + right.substr(0, pos) +
                        right.substr(pos + 1);
            } else {
                if (slash >= 1) {
                    right = to_string(nums[start]) + "/(" + right + ")";
                }
                else {
                    right = to_string(nums[start]) + "/" + right;
                }
            }
        }
        else {
            right = to_string(nums[start]) + "/" + right;
        }
        return right;
    }
};


int main() {

	Solution s;

	return 0;
}
