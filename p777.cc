#include "common.h"

// L can't go to the Left of R
// R can't go the right of L
// so there are equal number of R between any two Ls
// there are equal number of L between any two Rs
// remove X and the leftover should be identical if transformable
// counting is the best choice in such case

class Solution {
public:
  // https://www.cnblogs.com/grandyang/p/9001474.html
  // note: start.size()== end.size()
  bool canTransform(string start, string end) {
      int n = start.size(), cntL = 0, cntR = 0;
      for (int i = 0; i < n; ++i) {
          // ignore 'x'
          if (start[i] == 'R') {
              ++cntR;
          }
          if (end[i] == 'L') {
              ++cntL;
          }
          if (start[i] == 'L') {
              --cntL;
          }
          if (end[i] == 'R') {
              --cntR;
          }
          // at any time, cntL or cntR can't be negative
          // otherwise, one string has less/more L or R than the other
          // at any time, at least one of cntL and cntR is 0
          if (cntL < 0 || cntR < 0 || cntL * cntR != 0) {
              return false;
          }
      }
      // final verification
      return cntL == 0 && cntR == 0;
    }
};
class Solution_my {
public:
	bool canTransform(string start, string end) {
		if (start == end) return true;
		if (start.size() != end.size()) return false;
		return count(start, end);
	}
private:
	bool count(const string& start, const string& end) {
		// L can't go to the Left of R
		// R can't go the right of L
		// so there are equal number of R between any two Ls
		// there are equal number of L between any two Rs
		//start = "LR" + start + "LR";
		//end = "LR" + end + "LR";
		vector<vector<int>> countStart(128);
		vector<vector<int>> countEnd(128);
		int n = start.size();
		for (int i = 0; i < n; ++i) {
			countStart[start[i]].push_back(i);
			countEnd[end[i]].push_back(i);
		}
		string l("XLR");
		for (auto c : l) {
			if (countStart[c].size() != countEnd[c].size()) {
				return false;
			}
		}
		// remove X and the leftover should be identical if transformable
		string startprime;
		for (auto c : start) {
			if (c != 'X') {
				startprime.push_back(c);
			}
		}
		string endprime;
		for (auto c : end) {
			if (c != 'X') {
				endprime.push_back(c);
			}
		}
		if (endprime != startprime) {
			return false;
		}
		vector<int>& StartL = countStart['L'];
		vector<int>& StartR = countStart['R'];
		vector<int>& EndL = countEnd['L'];
		vector<int>& EndR = countEnd['R'];
		bool s2e = true;
		int lenL = StartL.size();
		for (int i = 0; i < lenL; ++i) {
			if (StartL[i] < EndL[i]) {
				s2e = false;
				break;
			}
		}
		int lenR = StartR.size();
		if (s2e) {
			for (int i = 0; i < lenR; ++i) {
				if (StartR[i] > EndR[i]) {
					s2e = false;
					break;
				}
			}
		}


		// e2s
		/*
		bool e2s = true;
		for (int i = 0; i < lenL; ++i) {
			if (EndL[i] < StartL[i]) {
				e2s = false;
				break;
			}
		}
		if (e2s) {
			for (int i = 0; i < lenR; ++i) {
				if (EndR[i] > StartR[i]) {
					e2s = false;
					break;
				}
			}
		}
		*/

		return s2e;
		//return s2e || e2s;
	}
};


int main() {

	Solution s;

	return 0;
}
