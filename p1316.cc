#include "common.h"
// note, counting
// same string has same prefix_sum
// xor of two same string is 0
// gethash
// note, counting
// same string has same prefix_sum
// xor of two same string is 0
// gethash
// a trick here
class Solution {
  public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        vector<long> hash(n + 1, 1);
        vector<long> power(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            char c = text[i];
            hash[i + 1] = (hash[i] * 33 + c) % MOD;
            power[i + 1] = (power[i] * 33) % MOD;
        }
        unordered_set<long> echostrings; // hash value
        for (int i = 0; i < n; ++i) {
            // from larger len to smaller len
            for (int len = (n - i) / 2; len > 0; len--) {
                auto left = gethash(i, i + len, hash, power);
                auto right = gethash(i + len, i + len*2, hash, power);
                if (left == right) {
                    if (echostrings.count(left)) {
                        //continue;
                        break;
                        // why break works
                        // because echostrings has already has text[i..i + len)
                        // we don't need to consider it any more
                        // why break?
                        // for example
                        // ABCDABCD
                        // len = 4 has been handled
                        // and hash(ABCD) is in echostrings !!!
                        // then the next few steps has been handled for (ABC, DAB), (AB, CD), (A, B)
                        // previously
                    }
                    echostrings.insert(left);
                }
            }
        }
        return echostrings.size();
    }

  private:
    inline long gethash(int begin, int end, vector<long> &hash, vector<long> &power) {
        //[begin, end)
        int len = end - begin;
        // hash[begin] * power[len] + x = hash[end]
        auto h = hash[end] - (hash[begin] * power[len]) % MOD;
        h %= MOD;
        if (h < 0) {
            h += MOD;
        }
        return h;
    }

    const int MOD = 1e9 + 7;
};

class Solution {
  public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        vector<long> hash(n + 1, 1);
        vector<long> power(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            char c = text[i];
            hash[i + 1] = (hash[i] * 33 + c) % MOD;
            power[i + 1] = (power[i] * 33) % MOD;
        }
        unordered_set<long> echostrings; // hash value
        for (int i = 0; i < n; ++i) {
            for (int len = 2; i + len <= n; len += 2) {
                auto left = gethash(i, i + (len >> 1), hash, power);
                if (echostrings.count(left)) {
                    continue;
                }
                auto right = gethash(i + (len >> 1), i + len, hash, power);
                if (left == right) {
                    echostrings.insert(left);
                }
            }
        }
        return echostrings.size();
    }

  private:
    long gethash(int begin, int end, vector<long> &hash, vector<long> &power) {
        //[begin, end)
        int len = end - begin;
        // hash[begin] * power[len] + x = hash[end]
        auto h = hash[end] - (hash[begin] * power[len]) % MOD;
        h %= MOD;
        if (h < 0) {
            h += MOD;
        }
        return h;
    }

    const int MOD = 1e9 + 7;
};

class Solution3 {
  public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        vector<long> hash(n + 1, 1);
        vector<long> power(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            char c = text[i];
            hash[i + 1] = (hash[i] * 33 + c) % MOD;
            power[i + 1] = (power[i] * 33) % MOD;
        }

        vector<vector<int>> cache(256);  // xor -> index
        unordered_set<long> echostrings; // hash value
        cache[0] = {-1};
        char x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= text[i]; // 1)
            for (auto pre : cache[x]) {
                int len = (i - pre);
                if (len >= 2 && len % 2 == 0) { // 2)
                    len >>= 1;
                    auto left = gethash(pre + 1, pre + 1 + len, hash, power);
                    if (echostrings.count(left)) {
                        continue;
                    }
                    auto right = gethash(pre + len + 1, i + 1, hash, power);
                    if (left == right) { // 4)
                        echostrings.insert(left);
                    }
                }
            }
            cache[x].push_back(i);
        }
        return echostrings.size();
    }

  private:
    long gethash(int begin, int end, vector<long> &hash, vector<long> &power) {
        //[begin, end)
        int len = end - begin;
        // hash[begin] * power[len] + x = hash[end]
        auto h = hash[end] - (hash[begin] * power[len]) % MOD;
        h %= MOD;
        if (h < 0) {
            h += MOD;
        }
        return h;
    }

    const int MOD = 1e9 + 7;
};

class Solution2 {
  public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        vector<long> hash(n + 1, 1);
        vector<long> power(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            char c = text[i];
            hash[i + 1] = (hash[i] * 33 + c) % MOD;
            power[i + 1] = (power[i] * 33) % MOD;
        }

        unordered_map<int, vector<int>> cache; // xor -> index
        // unordered_set<string> echostrings;
        unordered_set<long> echostrings; // hash value
        vector<int> prefix_sum(n + 1, 0);
        cache[0] = {-1};
        char x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= text[i]; // 1)
            prefix_sum[i + 1] = prefix_sum[i] + text[i];
            if (cache.count(x)) {
                for (auto pre : cache[x]) {
                    int len = (i - pre);
                    if (len >= 2 && len % 2 == 0) { // 2)
                        len >>= 1;

                        // check sum from [pre + 1, pre + 1 + len) is same as [pre + 1 + len, i+1)
                        if (prefix_sum[pre + 1 + len] - prefix_sum[pre + 1] ==
                            prefix_sum[i + 1] - prefix_sum[pre + 1 + len]) { // 3)
                            // check if substring left is same as right
                            // can be done with hash
                            /*
                            auto left = text.substr(pre + 1, len);
                            if (left == text.substr(pre + 1 + len, len)) {
                                echostrings.insert(move(left));
                            }
                            */
                            auto left = gethash(pre + 1, pre + 1 + len, hash, power);
                            auto right = gethash(pre + len + 1, i + 1, hash, power);
                            if (left == right) { // 4)
                                echostrings.insert(left);
                            }
                        }
                    }
                }
            }
            cache[x].push_back(i);
        }
        return echostrings.size();
    }

  private:
    long gethash(int begin, int end, vector<long> &hash, vector<long> &power) {
        //[begin, end)
        int len = end - begin;
        // hash[begin] * power[len] + x = hash[end]
        auto h = hash[end] - (hash[begin] * power[len]) % MOD;
        h %= MOD;
        if (h < 0) {
            h += MOD;
        }
        return h;
    }

    const int MOD = 1e9 + 7;
};

int main() {

    string str = "abcabcabc"; // 3
    str = "leetcodeleetcode"; // 2
    Solution s;
    cout << s.distinctEchoSubstrings(str) << endl;

    return 0;
}
