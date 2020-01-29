#include "common.h"
class Solution {
public:
    bool isRationalEqual(string S, string T) {
        auto r1 = helper(S);       
        auto r2 = helper(T);
        if (r1.first * r2.second == r1.second * r2.first) {
            return true;
        } else {
            return false;
        }
    }
private:
    pair<long long, long long> helper(const string& s) {
        auto pd = s.find('.');
        if (pd == string::npos) {
            return {stoi(s), 1};
        }
        long long intPart = stoi(s.substr(0, pd));
        long long p = 0, q = 1;
        auto pp = s.find('(', pd); 
        if (pp == string::npos) {
            string nonrepeat = s.substr(pd+1);
            if (!nonrepeat.empty()) {
                p = stoi(nonrepeat);
                q = (long long)pow(10, nonrepeat.size());
            }
            return {p + q * intPart, q};
        } else {
            if (pp - pd - 1> 0) {
                string nonrepeat = s.substr(pd+1, pp - pd-1);
                p = stoi(nonrepeat);
                q = (long long)pow(10, nonrepeat.size());
            }
            string loop = s.substr(pp+1, s.size() - 2- pp);
            long long a = stoi(loop);
            long long b = (long long)pow(10, loop.size()) - 1;
            b *= q;
            
            long long tp = p * b + a * q;
            long long tq = q*b;
            long long d = lcd(tp, tq);
            tp /= d;
            tq /= d;
            tp += tq * intPart;
            return {tp, tq};
        }
    }
    long long lcd(long long a, long long b) {
        if (a < b) {
            swap(a, b);
        }
        while( b) {
            long long t = (a-b) %b;
            a = b;
            b = t;
        }
        return a;
    }
};
int main() {
    string S = "0.1666(6)";
    string T = "0.166(66)";
    S ="0.(52)";
    T = "0.5(25)";
    S = "0.9(9)";
    T = "1.";
    S=  "8.123(4567)";
    T = "8.123(4566)";

	Solution s;
    cout << s.isRationalEqual(S, T) << endl;
	return 0;
}
