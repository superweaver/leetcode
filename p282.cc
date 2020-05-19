#include "common.h"
class Solution {
	 //https://www.jianshu.com/p/c62b1c090c3c
	 //https://leetcode.com/problems/expression-add-operators/discuss/71895/java-standard-backtrace-ac-solutoin-short-and-clear
	 //http://fisherlei.blogspot.com/2017/07/leetcode-expression-add-operators.html
	 // dfs + trim
	 // trick to cache the difference gotten from last step
	 // the operand can't have leading zero unless the operand itself is zero
	 public:
		 vector<string> addOperators(string num, int target) {
			 vector<string> result;
			 size_t n = num.size();
			 if (n == 0) return result;
			 long diff_lastcalc = 0;	// difference gotten from last calculation
			 size_t currentindex = 0;
			 long  currentvalue = 0;
			 string path = "";
			 dfs(result, num, (long)target, currentindex, currentvalue, diff_lastcalc, path);
			 return result;
		 }
	 private:
		 void dfs(vector<string>& result, const string& num, const long target, size_t currentindex, long currentvalue, long diff_lastcalc, string path) {
			 if (currentindex == num.size() && currentvalue == target) {
				 result.push_back(path);
				 return;
			 }
			 for (int len = 1; currentindex + len <= num.size(); ++len) {
				 string rightstr = num.substr(currentindex, len);
				 if (len > 1 && rightstr[0] == '0') {
					 // can't have leading 0 except 0 itself;
					 break;// not continue;
				 }
				 long rightoprand = stol(rightstr);
				 if (currentindex == 0) {
					 // we have no last calculation
					 dfs(result, num, target, currentindex + len, rightoprand, rightoprand, path + rightstr);
				 }
				 else {
					 // add
					 long nextvalue = currentvalue + rightoprand;
					 long diff = nextvalue - currentvalue;	// diff > 0;
					 dfs(result, num, target, currentindex + len, nextvalue, diff, path + "+" + rightstr);

					 // minus
					 nextvalue = currentvalue - rightoprand;
					 diff = nextvalue - currentvalue;	// diff < 0
					 dfs(result, num, target, currentindex + len, nextvalue, diff, path + "-" + rightstr);

					 // multiply
					 long prevvalue = currentvalue - diff_lastcalc;	// roll back
					 nextvalue = prevvalue + diff_lastcalc * rightoprand;
					 diff = nextvalue - prevvalue;
					 dfs(result, num, target, currentindex + len, nextvalue, diff, path + "*" + rightstr);
				 }
			 }
		 }
	 };

int main() {

	Solution s;

	return 0;
}
