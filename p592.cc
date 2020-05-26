#include "common.h"
class Solution {
public:
	typedef long long LL;
	string fractionAddition(string expression) {
		if (expression.empty()) return "0/1";
		string str = preprocess(expression);
		vector<string> numstr = split(str);
		vector<pair<LL, LL> > nums = tonumber(numstr);
		if (nums.size() == 1) return expression;
		return transform(nums);
	}
private:
	string preprocess(const string& s) {
		// add "+" to before - sign
		int n = s.size();
		string str;
		for (auto c : s) {
			if (c == '-') {
				if (!str.empty()) { // avoid leading '+'
					str.push_back('+');
				}
			}
			str.push_back(c);
		}
		str.push_back('+');
		return str;
	}
	vector<string> split(const string& s) {
		vector<string> result;
		int n = s.size();
		auto pos = s.find_first_of('+');
		auto pre = pos;
		pre = 0;
		while (pos != string::npos) {
			result.push_back(s.substr(pre, pos-pre));
			pre = pos + 1;
			pos = s.find_first_of('+', pre);
		}
		return result;
	}
	vector<pair<LL, LL> > tonumber(vector<string>& v) {
		vector<pair<LL, LL> > r;
		for (auto s : v) {
			auto pos = s.find_first_of('/');
			LL numerator = stoi(s.substr(0, pos));
			LL denominator = stoi(s.substr(pos + 1));
			r.push_back({numerator, denominator});
		}
		return r;
	}
	string transform(vector<pair<LL, LL> > nums) {
		int n = nums.size();
		LL common_lcm = nums[0].second;
		for (int i = 1; i < n; ++i) {
			common_lcm = lcm(common_lcm, nums[i].second);
		}
		LL sum = 0;
		for (auto p : nums) {
			sum += (p.first * (common_lcm / p.second));
		}
		auto t = gcd(abs(sum), abs(common_lcm));// key
		sum /= t;
		common_lcm /= t;
		return to_string(sum) + "/" + to_string(common_lcm);
	}
    private:
	LL gcd(LL a, LL b)
	{
		LL temp;
		if (a < b) {
			//交换两个数，使大数放在a上
			temp = a;
			a = b;
			b = temp;
		}
		while (b != 0) {
			//利用辗除法，直到b为0为止
			temp = a % b;
			a = b;
			b = temp;
		}
		return a;
	}

	LL lcm(LL a, LL b)
	{
		LL temp_lcm;
		temp_lcm = a * (b / gcd(a, b));//最小公倍数等于两数之积除以其最大公约数
		return temp_lcm;
	}
};

int main() {

	Solution s;

	return 0;
}
