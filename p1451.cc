#include "common.h"
class Solution {
public:
  string arrangeWords(string text) { vector<pair<int, int>> cache;
      text.push_back(' ');
      text[0] += 'a' - 'A';
      int n = text.size();
      for (int i = 0; i < n; ) {
          for (int j = i; j < n; ++j) {
              if (text[j] == ' ') {
                  cache.push_back({j - i, i});
                  i = j + 1;
                  break;
              } 
          }
      }
      sort(cache.begin(), cache.end());
      string  result;
      for (auto &p : cache) {
          result += text.substr(p.second, p.first);
          result.push_back(' ');
      }
      result.pop_back();
      result[0] += 'A' - 'a';
      return result;
  }
};

int main() {
    string text = "Leetcode is cool";
    text = "Keep calm and code on";
    Solution s;
    cout << s.arrangeWords(text) << endl;

	return 0;
}
