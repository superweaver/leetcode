#include "common.h"

class Solution {
  public:
    vector<int> kthSmallestPrimeFraction(vector<int> &A, int K) {
        // find the kth smallest in sorted triangle
        // A[0]/A[n-1] , A[1]/A[n-1],.....			, A[n-2]/A[n-1], A[n-1]/A[n-1]
        // A[0]/A[n-2], A[1]/A[n-2],.., A[n-3]/A[n-2]...A[n-2]/A[n-2], A[n-1]/A[n-2]
        // ....
        // A[0]/A[2], A[1]/A[2]
        // A[0]/A[1], A[1]/A[1]
        // A[0]/A[0], A[1]/A[0], ...........................................A[n-1]/A[0]
        // B[i][j] = A[j]/A[n-1-i]
        // print(A);
        //	cout << endl;
        //	print2(A);
        int n = A.size();
        double low = 0;
        double high = 1.0;
        while (true) {
            // note: this is a double
            double mid = low + (high - low) / 2;
            int p, q;
            int k = count_less_equal(A, n, mid, p, q);
            if (k == K) {
                return getvalue(A, n, p, q);
            }
            if (k < K) {
                low = mid; // :(
            } else {
                high = mid; // :(
            }
        }

        return {};
    }

  private:
    inline vector<int> getvalue(vector<int> &A, int n, int i, int j) {
        return {A[j], (A[n - 1 - i])};
    }
    inline double getvalue_d(vector<int> &A, int n, int i, int j) {
        return -A[j] / double(A[n - 1 - i]);
    }
    inline double getvalue_pd(vector<int> &A, int n, int i, int j) {
        return A[j] / (double)A[n - 1 - i];
    }

    int count_less_equal(vector<int> &A, int n, double value, int &p, int &q) {
        // use p and q to track the closest fration to value
        // top right;
        int count = 0;
        int i = 0;
        int j = n - 2;
        double diff = value;
        while (i < n && j >= 0) {
            auto v = getvalue_pd(A, n, i, j);
            if (v <= value) {
                if (value - v < diff) {
                    p = i;
                    q = j;
                    diff = value - v;
                }
                count += j + 1;
                i++;
            } else {
                j--;
            }
        }
        return count;
    }
};

int main() {

    Solution s;

    return 0;
}
