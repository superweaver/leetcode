#include "common.h"
//https://www.cnblogs.com/grandyang/p/8606024.html
class Solution {
public:
    string makeLargestSpecial(string S) {
       // note: S is guaranteed to be a special string !!!
       // take 1 as left (
       // and 0 as right )
       // then every matached () is a special string
       // call  makeLargestSpecial() itself to make substructure optimal
       // then re-order each substructure !!!
       //  move consists of choosing two consecutive(!!!!!, stupid), non-empty, special substrings of S,
       //  and swapping them. (Two strings are consecutive if the last character of the first
       //  string is exactly one index before the first character of the second string.
       //
       // string S = "1101001100";
       // I can't replace 1010 with 1100, since they are not consecutive :(
       int count = 0;
       int n = S.size();
       vector<string> result;
       int pre = -1;
       for (int i = 0; i < n; ++i) {
           if(S[i] == '1') {
               count++;
           } else{
               count--;
           }
           if (count == 0) {
               // pre + 1 to i is a special string
               // S[pre + 1] is 1 and
               // S[i] is 0
               result.push_back('1' + makeLargestSpecial(S.substr(pre + 2, i - pre - 2)) + '0');
               pre = i;
           }
       }
       // sort(result);
       sort(result.begin(), result.end(), greater<string>());
       string r;
       for(auto&s : result) {
           r += s;
       }
       return r;
    }
};


int main() {

	Solution s;

	return 0;
}
