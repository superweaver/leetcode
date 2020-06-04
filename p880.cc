#include "common.h"

class Solution {
public:
    string decodeAtIndex(string S, int K) {
        //leet2code3
        //vector<int> index_digit;
        vector<pair<int, long long>> len; // index and corresponding length
        int n = S.size();
        int i = 0;
        for(; i < n;) {
            if(S[i] >= '0' && S[i] <= '9') {
                len.push_back({ i, (S[i] - '0') * len.back().second });
                i++;
            } else {
                int j = i;
                while (j < n) {
                    if (S[j] >= 'a' && S[j] <= 'z') {
                        j++;
                    } else {
                        break;
                    }
                }
                int l = j - i;
                if (len.empty()) {
                    len.push_back({ j - 1, l });
                } else {
                    len.push_back({ j - 1, len.back().second + l });
                }
                i = j;
            }
            if (len.back().second >= K) {
                break;
            }
        }
        return getchar(S, K, len, len.size() -1);
    }

private:
    string getchar(const string& S, int k, vector<pair<int, long long> >& len, int index)
    {
        int m = len.size();
        int i = index;
        for(; i >= 0; --i) {
            char x = S[len[i].first];
            if (x >= '0' && x <= '9') {
                continue;
            } else {
                break;
            }
        }
        k = (k - 1) % ((i >= 0 ? len[i].second : 1));
        // x is char 'a' to 'z'
        // k + 1 is 1-indexed count
        int lastindex = (i >= 1 ? len[i - 1].first : -1);
        int lastcount = (i >= 1 ? len[i - 1].second : 0);
        if ((k + 1) > lastcount) {
            string r;
            r.push_back(S[lastindex + k + 1 - lastcount]);
            return r;
        }  else {
            return getchar(S, k + 1, len, i - 1);
        }
    }
};

int main() {

	Solution s;

	return 0;
}
