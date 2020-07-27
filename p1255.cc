#include "common.h"
class Solution {
    // https://leetcode.com/problems/maximum-score-words-formed-by-letters/discuss/425129/java-backtrack-similar-to-78.-Subsets-1ms-beats-100
public:
    /*
     *
    1 <= words.length <= 14
    1 <= words[i].length <= 15
    1 <= letters.length <= 100
    letters[i].length == 1
    score.length == 26
    0 <= score[i] <= 10
    words[i], letters[i] contains only lower case English letters.

     */
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        // 2^n
        vector<int> count(128, 0); // resources
        for (auto c : letters) {
            count[c]++;
        }
        return backtrack(words, count, score, 0); 
    }
private:
  int backtrack(vector<string> &words, vector<int> &count, vector<int> &score, int index) {
      int n = words.size();
      if (index >= n) {
          return 0;
      }
      int result = 0;
      for (int i = index; i < n; ++i) {
          int res = 0;
          bool isValid = true;
          for (auto c : words[i]) {
              // score size == 26
              res += score[c - 'a'];
              if (--count[c] < 0) {
                  // you can't use this word
                  isValid = false;
              }
          }
          // note: words[index]... words[i-1] are skiped
          if (isValid) {
              res += backtrack(words, count, score, i + 1);
              result = max(result, res);
          }
          for (auto c : words[i]) {
              ++count[c];
          }
      }
      return result;
  }
};

int main() {

	Solution s;

	return 0;
}
