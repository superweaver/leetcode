#include "common.h"
class Solution {
public:
  int numOfWays(int n) {
    int a121 = 6, a123 = 6, b121, b123, mod = 1e9 + 7;

    // 121form to 121 form : next can be 2 1/3 2, 3 1 3 to form another 121
    // form 123form to 121 form : next can be 2 1 2, 3 1 3
    // so next121 = current121 * 3 +  current123*2
    // similiarlly
    // 121form to 123 form : next can be 2 1 3 , 3 1 2
    // 123form to 123form : next can be 2 3 1, 3 1 2
    // so reuslt = [3, 2; 2, 2]^(n-1) * [6; 6]
    // diagnalize it if n is too big
    for (int i = 2; i <= n; i++) {
      b121 = (a121 * 3 + a123 * 2);
      b123 = (a121 * 2 + a123 * 2);
      a121 = b121 % mod;
      a123 = b123 % mod;
    }
    return (a121 + a123) % mod;
  }
};

class Solution_mysolution {
public:
  int numOfWays(int n) {
    vector<string> states = {"RYR", "YRY", "GRY", "RYG", "YRG", "GRG",
                             "RGR", "YGR", "GYR", "RGY", "YGY", "GYG"};
    constexpr size_t N = 12;
    constexpr size_t Mod = 1000000007;
    vector<vector<int>> graph(N);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = i + 1; j < N; ++j) {
        if (check(states[i], states[j])) {
          graph[i].push_back(j);
          graph[j].push_back(i);
        }
      }
    }
    // base case N == 1
    vector<int> count(N, 1);
    // others
    for (size_t i = 1; i < n; ++i) {
      vector<int> next(N, 0);
      for (size_t s1 = 0; s1 < N; ++s1) { // s1->s2
        for (auto s2 : graph[s1]) {
          next[s2] += count[s1];
          next[s2] %= Mod;
        }
      }
      count.swap(next);
    }
    int result = 0;
    for (auto c : count) {
      result += c;
      result %= Mod;
    }
    return result;
  }

private:
  bool check(const string& s1, const string& s2) {
    for (size_t i = 0; i < s1.size(); ++i) {
      if (s1[i] == s2[i]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  int n = 1; // 12
  n = 2;     // 54
  n = 3;     // 246
  n = 7;     // 106494
  n = 5000;  // 30228214
  Solution s;
  cout << s.numOfWays(n) << endl;
  return 0;
}
