#include "common.h"
class Solution {
public:
    vector<string> restoreIpAddresses(string ip)
    {
        int remainglength = ip.size();
        int dotsplaced = 0;
        int remainingdots = 4 - dotsplaced;

        vector<string> result;
        if (remainglength < remainingdots || remainglength > (remainingdots )*3) {
            return result;
        }
        // size_t totaldottoplace = 4
        int previousdotindex = -1;
        for (size_t len = 1; len <= 3; ++len) {
            dsf(result, ip, "", dotsplaced, previousdotindex + len, previousdotindex);
        }
        return result;
    }

    void dsf(vector<string>& result, string ip, string path, int dotsplaced, int probedotindex,
             int previousdotindex)
    {
        // probedotindex is the index you are going to insert a new dot after that element
        // check if previous insertion is valid
        if (probedotindex > ip.size() + 1)
            return;
        string sub = ip.substr(previousdotindex + 1, probedotindex - previousdotindex);
        if (!isValid(sub)) {
            return;
        }
        // sub is valid, need to check it will it possible for remaining length
        int remainglength = ip.size() - probedotindex - 1;
        int remainingdots = 4 - (dotsplaced + 1); // we are checking current dot
        if (remainglength < remainingdots || remainglength > 3 * remainingdots) {
            return;
        }
        // previous insertion is valid
        path += sub + ".";
        dotsplaced++;
        previousdotindex = probedotindex;

        if (probedotindex > ip.size() - 1 || dotsplaced > 4) {
            return;
        }
        if (probedotindex == ip.size() - 1 && dotsplaced > 4) {
            return;
        }
        if (probedotindex == ip.size() - 1 && dotsplaced == 4) {
            path.pop_back();
            result.push_back(path);
            return;
        }
        // try len 1 or 2 or 3
        for (size_t len = 1; len <= 3; ++len) {
            dsf(result, ip, path, dotsplaced, previousdotindex + len, previousdotindex);
        }
    }

    bool isValid(string s)
    {
        if (s.empty())
            return false;
        if (s.size() > 3)
            return false;
        if (s.size() == 2) {
            int sum = 10 * (s[0] - '0') + (s[1] - '0');
            return sum >= 10;
        }
        if (s.size() == 3) {
            int sum = 100 * (s[0] - '0') + 10 * (s[1] - '0') + (s[2] - '0');
            return sum >= 100 && sum <= 255;
        }
        return true;
    }
};


int main() {

	Solution s;

	return 0;
}
