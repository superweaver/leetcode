#include "common.h"
//https://leetcode.com/problems/rotated-digits/discuss/117975/Java-dp-solution-9ms
//dp[i] = 0, invalid number
//dp[i] = 1, valid and same number
//dp[i] = 2, valid and different number
class Solution {
public:    
    // nice solution
    int rotatedDigits(int N) {
        int ans = 0;
        vector<int> dp(N+1, 0);
        for(int i = 0; i <= N; i++){
            if(i < 10){
                if(i == 1 || i == 8 || i == 0){
                    dp[i] = 1;
                }
                if(i == 2 || i == 5 || i == 6 || i == 9){
                    ans++;
                    dp[i] = 2;
                }
            }
            else {
                int a = dp[i % 10]; // decomposed to be a sub question
                int b = dp[i / 10];
                if (a == 0 || b == 0) {
                    dp[i] = 0;
                }
                else {
                    // a >= 1, b >= 1
                    //
                    // if any of a or b == 2
                    // then dp[i] = 2
                    //  only a == 1 and b == 1
                    //  then dp[i] = 1
                    dp[i] = max(a, b);
                    if(dp[i] == 2){
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
};

class Solution_my {
public:
    int rotatedDigits(int N) {
        return N - count347(N) - count018(N);
    }
    int count018(int N) {
        // how many number x , 0 < x <= N, that is only composed by 0, 1, 8
        if(N <= 0) return 0;
        int n = N;
        int digits = 0;
        while(n) {
            digits++;
            n /= 10;
        }
        vector<int> bases_10(digits, 1);  // 10^x
        for (int i = 1; i < digits; ++i) {
            bases_10[i] = 10 * bases_10[i - 1];
        }
        int j = digits;
        int count018 = 0;
        n = N;
        bool hasbreak = false;
        while(j) {
            int i = j - 1;
            int digit = (n / bases_10[i]) % 10;
            if (digit > 8) {
               count018 += 3 * pow(3, i);
               hasbreak = true;
               break;
            }
            else if (digit == 8){
                count018 += 2 * pow(3, i);
            }
            else if (digit > 1) {
                count018 += 2 * pow(3, i);
                hasbreak = true;
                break;
            } else if (digit == 1) {
                count018 += 1 * pow(3, i);
            }
            else {
                count018 += 0;
            }
            j--;
        }
        if (!hasbreak) count018++;
        return count018 - 1; // remove 0

    }
    int count347(int N) {
        int n = N;
        int digits = 0;
        while(n) {
            digits++;
            n /= 10;
        }

        vector<int> bases_10(digits, 1);  // 10^x
        for (int i = 1; i < digits; ++i) {
            bases_10[i] = 10 * bases_10[i - 1];
        }
        vector<int> bases(digits + 1, 0);
        for (int i = 1; i <= digits; ++i) {
            bases[i] = 3 * bases_10[i -1] + 7 * bases[i - 1];
            //cout << bases[i] << endl;
        }
        n = N;
        int count347 = 0;
        int j = digits;
        int right;
        bool stop = false;
        while(j&&!stop) {
            int i = j - 1;
            int digit = (n / bases_10[i]) % 10;
            right =  n % bases_10[i];
            switch(digit) {
                case 9:
                case 8:
                    count347 += (digit  - 3) * bases[i] + 3 * bases_10[i]; // 3, 4, 7
                    break;
                case 7:
                    count347 += (digit  - 2) * bases[i] + 2 * bases_10[i]; // 3, 4
                    count347 += right + 1; // 7 xxxx ~ 7 0000
                    stop = true;
                    break;
                case 6:
                case 5:
                    count347 += (digit  - 2) * bases[i] + 2 * bases_10[i]; // 3, 4
                    break;
                case 4:
                    count347 += (digit  - 1) * bases[i] + 1 * bases_10[i]; // 3
                    count347 += right + 1; // 4 xxxx ~ 4 0000
                    stop = true;
                    break;
                case 3:
                    count347 += (digit) * bases[i] + 0 * bases_10[i]; // 3
                    count347 += right + 1;
                    stop = true;
                    break;
                case 2:
                case 1:
                case 0:
                    count347 += digit * bases[i] + 0 * bases_10[i];
                    break;
            }
            j--;
        }
        return count347;
    }
    int count018brutal(int N) {
        int c = 0;
        for (int i = 1; i <= N; ++i) {
            int j = i;
            bool is018 = true;
            while(j) {
                int d = j % 10;
                if (d != 0 && d != 1&& d != 8) {
                    is018 = false;
                    break;
                }
                j /= 10;
            }
            c += is018;
            //if (is018) cout << i << " ";
        }
        //cout << endl;
        return c;
    }
};


int main() {

	Solution s;

	return 0;
}
