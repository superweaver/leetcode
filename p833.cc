#include "common.h"

class Solution {
public:
    // proposed solution
    // use a vector<int> to store index
    // initially v[i] = i; for S
    // for each replacement, (need to check size issue)
    // if it can be done, then recorde index = -1 - j, j is index in targets
    // else v[i] is unchanged
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        int n = S.size();
        vector<int> index(n, 0);
        iota(index.begin(), index.end(), 0);
        int replaces = indexes.size();
        for (int j = 0; j < replaces; ++j) {
            auto& s = sources[j];
            int len = s.size();
            int i = indexes[j];
            if ((n - i) >= len) {
                if (S.substr(i, len) == s) {
                    index[i] = -1 - j;
                    for (int k = i + 1; k < i + len; ++k) {
                        index[k] = INT_MAX;
                    }
                }
            }
        }
        string result;
        for(auto i : index) {
            if (i < 0) {
                i = (-i - 1);
                result += targets[i];
            } else if (i < INT_MAX) {
                result.push_back(S[i]);
            }
        }
        return result;
    }
    string findReplaceString_my(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        int n = S.size();
        vector<pair<int, int> > pindex; // :(, be careful
        for(int i = 0; i < indexes.size(); ++i) {
            pindex.push_back({indexes[i], i});
        }
        sort(pindex.begin(), pindex.end());
        int i = 0;
        string result;
        for (size_t j = 0; j < pindex.size(); ++j) {
            int index = pindex[j].first;
            if (index >= n) {
                break;
            }
            if (i < index) {
                result += S.substr(i, index - i);
                i = index;
            }
            int strindex = pindex[j].second;
            string& s = sources[strindex];
            if (n - index >= (int)s.size()) {
                if (S.substr(index, s.size()) == s) {
                    result += targets[strindex];
                    i += s.size();
                }
            }
        }
        if (i < n) {
            result += S.substr(i, n - i);
        }
        return result;
    }
};


int main() {
string S = "abcd";
vector<int> indexes = {0,2};
vector<string> sources = {"a", "cd"}, targets = {"eee", "ffff"};

Solution s;
cout << s.findReplaceString(S, indexes, sources, targets) << endl;

return 0;
}
