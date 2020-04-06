#include "common.h"

class Solution {
public:
    int numSteps(string s)
    {
        int steps = 0;
        int n = s.size();
        int i = n - 1;
        int carry = 0;
        while (i > 0) {
            int sum = s[i] - '0' + carry;
            if (sum & 1) {
                // odd, add 1, and shift, 2 steps
				++sum;
                steps += 2;
            } else {
                // even, shift is enough
                steps++;
            }
			carry = sum >> 1;
            //carry = sum ? 1 : 0;
            --i;
        }
		// note: i == 0 is not handled above and s[0] == 1
		// if carry is not zero, carry will add with this 1 and make s[0] == 0
		// and insert an extra 1 in front, so need 1 extra step to shift s[0];
        return steps + carry;
    }

    int numSteps_my(string s)
    {
        deque<int> q;
        for (auto c : s) {
            q.push_back(c - '0');
        }

        int steps = 0;
        while (q.size() > 1) {
            steps++;
            if (!q.back()) {
                q.pop_back();
            } else {
                // add one
                int carry = 1;
                int sum = 0;
                for (int i = q.size() - 1; i >= 0; --i) {
                    if (!carry) {
                        break;
                    }
                    sum = q[i] + carry;
                    q[i] = sum % 2;
                    carry = sum / 2;
                }
                while (carry) {
                    q.push_front(carry % 2);
                    carry /= 2;
                }
            }
        }
        return steps;
    }
};

int main()
{
    string s = "1101";  // 6
                        //	s = "10";
                        //	s = "1";

	s = "11";
    Solution so;
//    Solution2 so2;
    cout << so.numSteps(s) << endl;
 //   cout << so2.numSteps(s) << endl;

    return 0;
}
