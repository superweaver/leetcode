#include "common.h"
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int prefix_sum = 0;
        int result = 0;
        vector<int> count(K, 0);
        count[0]++;     // !!!! at the begining, the sum is 0; prefix_sum[-1] = 0;
        for(auto i : A) {
            prefix_sum += i;
            // https://stackoverflow.com/questions/12276675/modulus-with-negative-numbers-in-c/21470301
            int r = prefix_sum  % K;
            if (r < 0) {
                r += K;
            }
            prefix_sum += count[r]++; // delta  = (p + 1) * p / 2 - p * (p - 1) = p;
        }
        /*
        for(auto& p : count) {
            if (p >= 2) {
               result += (p - 1) * p / 2; 
            }
        }
        */
        return result;
    }

    int subarraysDivByK_2(vector<int>& A, int K) {
        int prefix_sum = 0;
        vector<int> count(K, 0);
        count[0]++;     // !!!! at the begining, the sum is 0;
        for(auto i : A) {
            prefix_sum += i;
            // https://stackoverflow.com/questions/12276675/modulus-with-negative-numbers-in-c/21470301
            count[((prefix_sum % K) + K)%K]++;
        }
        int result = 0;
        for(auto& p : count) {
            if (p >= 2) {
               result += (p - 1) * p / 2; 
            }
        }
        return result;
    }

    int subarraysDivByK_3(vector<int>& A, int K) {
        unordered_map<int, int> count;
        int prefix_sum = 0;
        count[0]++;     // at the begining, the sum is 0;
        for(auto i : A) {
            prefix_sum += i;
            // https://stackoverflow.com/questions/12276675/modulus-with-negative-numbers-in-c/21470301
            count[((prefix_sum % K) + K)%K]++;
        }
        int result = 0;
        for(auto& p : count) {
            if (p.second >= 2) {
               result += (p.second - 1) * p.second / 2; 
            }
        }
        return result;
    }
};

int main() {
    vector<int> A = {4,5,0,-2,-3,1};
    for(auto&i:A) {
        i = -i;
    }
    int K = 5;
    Solution s;
    cout << s.subarraysDivByK(A, K) << endl;
    return 0;
}
