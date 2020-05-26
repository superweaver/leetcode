#include "common.h"

class Solution {
public:
    // this solution is based on string multiplication
    // there is no restriction on the length of a and b
	string complexNumberMultiply(string a, string b) {
		vector<int> ra, rb, ia, ib;
		int sra, srb, sia, sib; // -1 for negative, 1 for positive
		process(a, ra, ia, sra, sia);
		process(b, rb, ib, srb, sib);
		vector<int> rarb;
		int srarb = sra*srb;
		multiply(ra, rb, rarb);

		vector<int> raib;
		int sraib = sra*sib;
		multiply(ra, ib, raib);

		vector<int> iarb;
		int siarb = sia*srb;
		multiply(ia, rb, iarb);

		vector<int> iaib;
		int siaib = sia*sib;
		multiply(ia, ib, iaib);

		vector<int> vrr;
		int srr;
		siaib = -siaib; // ac - bd,  reverst the sign of bd
		add(rarb, iaib, srarb, siaib, vrr, srr);

		vector<int> vri;
		int sri;
		add(raib, iarb, sraib, siarb, vri, sri);

		return tostring(vrr, srr) + "+" + tostring(vri, sri) + "i";
	}
private:
	void process(string& a, vector<int>& ra, vector<int>&ia, int& sra, int&sia) {
		int n = a.size();
		auto iplus = a.find_first_of('+');
		if (iplus == 0) {
			iplus = a.find_first_of('+', iplus);
		}
		string left = a.substr(0, iplus);
		string right = a.substr(iplus + 1);
		right.pop_back();
		extract(left, sra, ra);
		extract(right, sia, ia);
	}
	void extract(string& s, int& sign, vector<int>& digits) {
		digits.clear();
		int i = 0;
		int n = s.size();
		sign = 1;
		if (s[0] == '-') {
			sign = -1;
			i++;
		}
		else if (s[0] == '+') {
			i++;
		}
		for (; i < n; ++i) {
			digits.push_back(s[i] - '0');
		}
		reverse(digits.begin(), digits.end());
	}
	void multiply(const vector<int>& a, const vector<int>& b, vector<int>& result) {
		result = vector<int>(a.size() + b.size(), 0); // enough
		int n = b.size();
		int m = a.size();
		for (int start = 0; start < n; ++start) {
			int carry = 0;
			int d = b[start];
			for (size_t i = 0; i < a.size(); ++i) {
				int product = d * a[i];
				product += carry;
				product += result[i + start]; // important
				result[i + start] = product % 10;
				carry = product / 10;
			}
			int insert = (a.size() - 1 + start) + 1;
			while (carry) {
				carry = result[insert] + carry;
				result[insert++] += carry % 10;
				carry /= 10;
			}
		}
		int last = result.size() - 1;
		while (last >= 0 && result[last] == 0) {
			result.pop_back();
			--last;
		}
        if (result.empty()) {   // avoid 0-> empty vector
			result.push_back(0);
		}
	}
	void add(const vector<int>&a, const vector<int>&b, int sa, int sb, vector<int>&result, int& sr) {
		bool additon = false;
		if (sa * sb < 0) {
			additon = false;
			if (a.size() > b.size()) {
				sr = sa;
				//  a - b
				doSubstraction(a, b, result);
			}
			else if (b.size() > a.size()) {
				//  b - a
				sr = sb;
				doSubstraction(b, a, result);
			}
			else {
				bool a_is_bigger = true;
				for (int i = a.size() - 1; i >= 0; --i) {
					if (a[i] == b[i]) {
						continue;
					}
					if (a[i] > b[i]) {
						a_is_bigger = true;
						break;
					}
					else {
						a_is_bigger = false;
						break;
					}
				}

				if (a_is_bigger) {
					// a - b
					sr = sa;
					doSubstraction(a, b, result);
				}
				else {
					// b - a
					sr = sb;
					doSubstraction(b, a, result);
				}
			}
		}
		else {
			sr = sa;
			additon = true;
			// add
			doAddition(a, b, result);
		}
		// if result == 0, make sign to be 1
		bool iszero = true;
		for (auto r : result) {
			if (r != 0) {
				iszero = false;
			}
		}
		if (iszero) {
			sr = 1;
		}
	}
	void doAddition(const vector<int>& a, const vector<int>& b, vector<int>& result) {
		int m = a.size();
		int n = b.size();
		result.clear();
		int carry = 0;
		int len = max(m, n);
		for (int i = 0; i < len; ++i) {
			int da = (i < m) ? a[i] : 0;
			int db = (i < n) ? b[i] : 0;
			int sum = da + db + carry;
			result.push_back(sum % 10);
			carry = sum / 10;
		}
		while (carry) {
			result.push_back(carry % 10);
			carry /= 10;
		}

	}
	void doSubstraction(const vector<int>& a, const vector<int>& b, vector<int>& result) {
		// a  - b, a is >= b
		int m = a.size();
		int n = b.size();
		result.clear();
		int carry = 0; // may be less than 0
		int len = max(m, n);
		for (int i = 0; i < len; ++i) {
			int da = (i < m) ? a[i] : 0;
			int db = (i < n) ? b[i] : 0;
			if (da + carry >= db) {
				result.push_back(da + carry - db);
				carry = 0;
			}
			else {
				result.push_back(10 + da + carry - db);
				carry = -1;
			}
		}
         int last = result.size() - 1;
		while (last >= 0 && result[last] == 0) {
			result.pop_back();
			--last;
		}
        if (result.empty()) {   // avoid 0-> empty vector
			result.push_back(0);
		}

	}
	string tostring(const vector<int>& v, int sign) {
		int n = v.size();
		string r;
		if (sign < 0) {
			r.push_back('-');
		}
		for (int i = n - 1; i >= 0; --i) {
			r.push_back(v[i] + '0');
		}
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
