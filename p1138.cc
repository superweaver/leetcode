#include "common.h"
class Solution {
public:
    string alphabetBoardPath(string target) {
       pair<int, int> current (0, 0); 
	   string result;
	   for (size_t i = 0; i < target.size(); ++i) {
		   pair<int, int> next = getCoordinate(target[i]);
		   if (current == next) {
			   result.push_back('!');
			   continue;
		   }
		   if (current.first == 5) {
				result.push_back('U');
				current.first--;
		   }
		   bool toZ = false;
		   if (next.first == 5) {
			   next.first --;
			   toZ = true;
		   }
		   if (current.first < next.first) {
			   result += string(next.first - current.first, 'D');
		   } else if (current.first > next.first) {
			   result += string(current.first - next.first , 'U');
		   }
		   if (current.second < next.second) {
			   result += string(next.second - current.second, 'R');
		   } else if (current.second > next.second) {
			   result += string(current.second - next.second, 'L');
		   }
		   if (toZ) {
			   result.push_back('D');
			   next.first++;
		   }
		   result.push_back('!');
		   current = next;
	   }
	   return result;
    }
private:
	pair<int, int> getCoordinate(char c) {
		// a <= char c <= z
		c = c - 'a' ;
		int r = c / 5;
		int col = c - r * 5;
		return {r, col};
	}
};
int main() {

	string target = "leet";
	target = "code";
	target = "lazyzzy";
	Solution s;
	cout << target << endl;
	cout << s.alphabetBoardPath(target) << endl;
	return 0;
}
