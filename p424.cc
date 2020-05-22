#include "common.h"
//(1) find exact maxCound in current substring arrange
//https://leetcode.com/problems/longest-repeating-character-replacement/discuss/91285/Sliding-window-similar-to-finding-longest-substring-with-k-distinct-characters
//(2) https://leetcode.com/problems/longest-repeating-character-replacement/discuss/91271/Java-12-lines-O(n)-sliding-window-solution-with-explanation
//  check the explanation
//  Since we are only interested in the longest valid substring, our sliding windows need not shrink, even if a window may cover an invalid substring. We either grow the window by appending one char on the right, or shift the whole window to the right by one. And we only grow the window when the count of the new char exceeds the historical max count (from a previous window that covers a valid substring).

//That is, we do not need the accurate max count of the current window; we only care if the max count exceeds the historical max count; and that can only happen because of the new char.



class Solution {
public:
  int characterReplacement(string s, int k) {
      // sliding windows
      // In one operation, you can choose any character of the string and change it 
      // to any other uppercase English character.
      // !!! note, at one operation, only one character can be changed.
      //
      // if there is no limitation of k times;
      // to make a string to have same character, we just need
      // to have str.size() - max count of repeated char, times of operations for this question;
      // it is to find max length of a substring 
      // so that substring.size() - max count of repreated char in this substring <= k
      
      int result = 0;
      int left_index = 0;
      int n = s.size();
      
      vector<int> cache(128, 0); // used as counter
      set<pair<int, char>> q;
      int maxCountInRange = 0;
      for (auto c = 'A'; c <= 'Z'; ++c) {
          q.insert({0, c});
      }
      for (int right_index = 0; right_index < n; ++right_index) {
          const auto c = s[right_index];
          q.erase(q.find({cache[c], c}));
          ++cache[s[right_index]];
          q.insert({cache[c], c});
          maxCountInRange = q.rbegin()->first;
          //maxCountInRange = max(cache[s[right_index]], maxCountInRange);
          int subStrLen = right_index - left_index + 1;
          while (subStrLen - maxCountInRange > k) {
              auto c_left = s[left_index];
              q.erase(q.find({cache[c_left], c_left}));
              --cache[c_left]; // this can be same as current character
              q.insert({cache[c_left], c_left});
              maxCountInRange = q.rbegin()->first;
              left_index++;
              subStrLen--;
          }
          result = max(result, subStrLen);
      }
      return result;
  }
};
int main() {

    string str= "ABAB"; 
    int k = 2;
    Solution s;
    cout << s.characterReplacement(str, k) << endl;

    return 0;
}
