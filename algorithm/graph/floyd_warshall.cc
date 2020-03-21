#include "../../../common.h"
class Solution {
public:
    Solution()
    {
        initialize();
    }
    void floyd_warshall()
    {
        int n = d_size;
        auto result = d_adjmat;        // D_(0)
		vector<vector<int>> predessor(n, vector<int>(n, INT_MAX));
		// base case
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j || d_adjmat[i][j] == INT_MAX) {
					predessor[i][j] = -1; // use -1 as NIL
				} else {
					predessor[i][j] = i;
				}
			}
		}
		// transitive closure
		vector<vector<int>> T(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
				if (i == j || d_adjmat[i][j] != INT_MAX) {
					T[i][j] = 1;
				}
            }
        }

        for (int k = 0; k < n; ++k) {  // D_(k)
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
					T[i][j] |= (T[i][k] & T[k][j]);	
                    if (result[i][k] != INT_MAX && result[k][j] != INT_MAX) {
                        int candidate =
                            result[i][k] + result[k][j];  // use new extra vertex k as candidate
						if (result[i][j] <= candidate) {
							// result[i][j] = result[i][j];
							// no need to update result[i][j] or predessor[i][j]
							//
						} else {
							result[i][j] = candidate;
							predessor[i][j] = predessor[k][j]; //!!!!
						}
                    }
                }
            }
        }
        for (auto& v : result) {
            displayvector(v);
        }
		cout << endl;
		for (auto& v:predessor) {
			displayvector(v);
		}
        cout << endl;
        for (auto& v:T) {
			displayvector(v);
		}
    }

private:
    int d_size;
    vector<vector<int>> d_adjmat;
    void initialize()
    {
        d_size = 5;
        d_adjmat = vector<vector<int>>(d_size, vector<int>(d_size, INT_MAX));
		for (int i = 0; i < d_size; ++i) {
			d_adjmat[i][i] = 0;
		}
        d_adjmat[0][1] = 3;
        d_adjmat[0][2] = 8;
        d_adjmat[0][4] = -4;

        d_adjmat[1][3] = 1;
        d_adjmat[1][4] = 7;

        d_adjmat[2][1] = 4;

        d_adjmat[3][0] = 2;
        d_adjmat[3][2] = -5;

        d_adjmat[4][3] = 6;
    }
};
int main()
{
    Solution s;
    s.floyd_warshall();
    return 0;
}
