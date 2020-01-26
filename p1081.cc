#include "common.h"
class Solution {
public:
    string smallestSubsequence(string text) {
        int n = text.size(); 
        map<char, vector<int>> cache;
        for(int i = n-1; i >=0; --i) {
            cache[text[i]].push_back(-i);
        }
        set<int> r;
        while(!cache.empty()) {
            auto it  = --cache.end();
            auto &v = it->second;
            if (r.empty()) {
                r.insert(*v.begin());
                cache.erase(it);
            } else {
                auto vit = --r.end(); 
                int head = -*vit;
                int tail = -*r.begin();
                if (-v[0] < head || -v.back() > tail) {
                    cache.erase(it);
                    r.insert(v[0]);
                } else {
                    int index = *upper_bound(v.begin(), v.end(), -tail);
                    cache.erase(it);
                    r.insert(index);
                }
            }
        }
        string result;
        for(auto i : r) {
            result.push_back(text[-i]);
        }
        return result;
    }
};

int main() {
    vector<string> input = {"cdadabcc","abcd", "ecbacba", "leetcode" , "ddeeeccdce" };
    Solution s;
    for(auto &text:input) {
        cout << text << " " << s.smallestSubsequence(text) << endl;
    }
    return 0;
}
