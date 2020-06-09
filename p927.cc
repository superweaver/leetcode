#include "common.h"
class Solution {
public:
    vector<int> threeEqualParts(vector<int>& A)
    {
        int n = A.size();
        int i = 0;
        int j = n - 1;
        int ones = 0;
        int left_start = -1;
        for (int k = 0; k < n; ++k) {
            ones += A[k];
            if(A[k] && left_start == -1) {
                left_start = k;
            }
        }
        if (ones == 0) {
            // all zeros
            return { 0, n - 1 };
        }
        if (ones %3 != 0) {
            return {-1, -1};
        }
        ones /= 3;
        i = left_start;
        int right_ones = 0;
        int len = 0;
        while (right_ones < ones && j - (left_start + len + 1) >= len + 1) {
            right_ones += A[j--];
            len++;
        }
        if (right_ones == ones) {
            auto r = check_left_right(A, left_start, left_start + len - 1, n - len, n - 1);
            if(!r) {
                return {-1, -1};
            } else {
                auto rb = check_left_mid(A, left_start, left_start + len - 1, left_start + len,
                                          n - len - 1);
                if(rb > left_start) {
                    return {left_start+len-1, rb};
                }
                else {
                    return {-1, -1};
                }
            }
        }
        else {
            return {-1, -1};
        }
    }
private:
    bool check_left_right(vector<int>& A, int left_start, int left_end, int right_start,
                          int right_end)
    {
        // len = left_end - left_start + 1 == right_end - right_start + 1
        for(int i = left_start, j = right_start; i <= left_end; ++i, ++j) {
            if (A[i] != A[j]) {
                return false;
            }
        }
        return true;
    }
    int check_left_mid(vector<int>& A, int left_start, int left_end, int mid_start, int mid_end) {
        int left_len = left_end - left_start + 1;
        int mid_len = mid_end - mid_start + 1;
        if( mid_len < left_len) {
            return 0;
        }
        while (mid_start < mid_end && A[mid_start] == 0) {
            mid_start++;
        }
        mid_len = mid_end - mid_start + 1;
        if(mid_len < left_len) {
            return 0;
        }
        int i = left_start, j = mid_start;
        for (; i <= left_end; ++i, ++j) {
            if (A[i] != A[j]) {
                return false;
            }
        }
        int r = j;
        for(; j <= mid_end; ++j) {
            if(A[j]){
                return 0;
            }
        }
        return r;
    }
};




int main() {

	Solution s;

	return 0;
}
