#include "common.h"
class Solution {
public:
    string longestDiverseString(int a, int b, int c)
    {
        vector<pair<int, char>> cache;
        cache.push_back({ a, 'a' });
        cache.push_back({ b, 'b' });
        cache.push_back({ c, 'c' });
        sort(cache.begin(), cache.end(), greater<pair<int, char>>());
        a = cache[0].first;
        b = cache[1].first;
        c = cache[2].first;
        char ca = cache[0].second;
        char cb = cache[1].second;
        char cc = cache[2].second;

        vector<pair<char, int>> str;
        int a_s = 0;
        for (int i = 0; i < c; ++i) {
            // a b c
            str.push_back({ ca, 1 });
            str.push_back({ cb, 1 });
            str.push_back({ cc, 1 });
            ++a_s;
        }
        for (int i = c; i < b; ++i) {
            // ab
            str.push_back({ ca, 1 });
            str.push_back({ cb, 1 });
            ++a_s;
        }
        if (a > b) {
			// a possible 'a'
            str.push_back({ ca, 1 });
            ++a_s;
        }

		// for 'a', change count from 1 to 2
        int left_a_s = a - a_s;
        if (left_a_s) {
            for (auto& p : str) {
                if (p.first == ca) {
                    p.second++;
                    left_a_s--;
                    if (!left_a_s) {
                        break;
                    }
                }
            }
        }

        string result;
        if (!left_a_s) {
            for (auto& p : str) {
                result += string(p.second, p.first);
            }
        } else {
            // need to insert extra aa or a before c
            for (auto& p : str) {
                if (p.first == cc) {
                    int toinsert = min(2, left_a_s);
                    result += string(toinsert, ca);
                    left_a_s -= toinsert;
                }
                result += string(p.second, p.first);
            }
        }
        return result;
    }
};

int main()
{
	int a = 1, b = 1, c = 7;
	a = 2, b = 2, c = 1;
	a = 7, b = 1, c = 0;

    Solution s;
	cout << s.longestDiverseString(a, b, c) << endl;

    return 0;
}

