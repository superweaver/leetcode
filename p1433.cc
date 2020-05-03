#include "common.h"
class Solution {
public:

    bool checkIfCanBreak(string s1, string s2) {
        // use count instead of sort
        vector<int> count(128, 0);
        for (auto c : s1) {
            count[c]++;
        }
        for (auto c : s2) {
            count[c]--;
        }
        //true
        //1) +++
        //      ---
        //2) ---
        //      +++
        //false
        //+  +
        // --
        //
		
		for (char i = 'a'; i <= 'z'; ++i) {
            if (count[i] != 0) {
                bool less = count[i] > 0;
                if (less) {
                    int c = 0;
                    for (; i <= 'z'; ++i) {
                        c+= count[i];
                        if (c < 0) {
                            return false;
                        }
					}
				} else {
                    int c = 0;
					for(; i <= 'z'; ++i)
					{
						c += count[i];
						if(c > 0)
						{
							return false;
						}
					}
				}
            }
        }
        return true;
    }
    bool checkIfCanBreak2(string s1, string s2) {
       sort(s1.begin(), s1.end());
       sort(s2.begin(), s2.end());
       int n = s1.size();
       int i = 0;
       for (; i < n; ++i) {
           if (s1[i] != s2[i]) {
               break;
           }
       }
       if (i == n) {
           return true;
       }
       bool less = s1[i] < s2[i];
       if (less) {
		   for(++i; i < n; ++i)
		   {
			   if (s1[i] > s2[i]) {
                   return false;
               }
		   }
		   return true;
       } else {
           // s1[i] > s2[i]
		   for(++i; i < n; ++i)
		   {
			   if(s1[i] < s2[i])
			   {
				   return false;
			   }
		   }
           return true;
	   }
    }
};

int main() {
	string s1 = "abc", s2 = "xya";
    //s1 = "abe", s2 = "acd"; // false;

	Solution s;
    cout << s.checkIfCanBreak(s1, s2) << endl; 

	return 0;
}
