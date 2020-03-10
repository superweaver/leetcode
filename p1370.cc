#include "common.h"
class Solution {
public:
    string sortString(string s) {
		vector<int> count(128, 0);
		int maxsize = 0;
		for(auto c : s) {
			count[c]++;
			maxsize = max(maxsize, count[c]);
		}
		vector<string> cache(maxsize, "");
		for (char c = 'a'; c <= 'z'; ++c) {
            for (int i = 0; i < count[c]; ++i) {
                cache[i].push_back(c);
            }
        }
		string result;
		bool flag = true;
		for (auto&str : cache) {
			if (!flag) {
				reverse(str.begin(), str.end());
			}
			result += str;
			flag = !flag;
		}
		return result;
    }
    string sortString2(string s)
    {
        map<char, int> cache;
        for (auto c : s) {
            cache[c]++;
        }
        string result;
        bool small2big = true;
        while (!cache.empty()) {
            if (cache.size() == 1) {
                result += string(cache.begin()->second, cache.begin()->first);
                break;
            } else {
                string tmp;
                for (auto it = cache.begin(); it != cache.end();) {
                    tmp.push_back(it->first);
                    it->second--;
                    if (it->second == 0) {
                        it = cache.erase(it);
                    } else {
                        ++it;
                    }
                }
                if (!small2big) {
                    reverse(tmp.begin(), tmp.end());
                }
                result += tmp;
                small2big = !small2big;
            }
        }
        return result;
    }
};

int main()
{

    string str = "aaaabbbbcccc";
	str = "rat";
	str = "leetcode";
//	str = "ggggg";
//	str = "spo";
    Solution s;
    cout << s.sortString(str) << endl;

    return 0;
}
