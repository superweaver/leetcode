#include "common.h"
class Solution {
public:
	int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
		int n = books.size();
		vector<int> dp(n + 1, INT_MAX); // min Height = put first i books;
		dp[0] = 0;
		for (int i = 0; i < n; i++) {
			int row_sum = 0;
			int maxheight = 0;
			int j = i;
            while (j >= 0) {
                row_sum += books[j][0];
				if (row_sum > shelf_width) {
					break;
				}
                maxheight = max(maxheight, books[j][1]);
                dp[i+1] = min(dp[i+1], dp[j] + maxheight);
				--j;
            }
        }
		return dp[n];
    }

    int minHeightShelves_complicate(vector<vector<int>>& books, int shelf_width) {
		int n = books.size();
        // dp[i][j] is the min height of books by put first i books with last books ending at j
        // j = 1, 2, ....shelf_with
		// dp[i][j] = min(dp[j][...] + min(heights[j+1...i], width of last row <= shelf_width)
		vector<vector<int>> dp(n + 1, vector<int>(shelf_width + 1, INT_MAX));
		vector<int> dpi(n + 1, INT_MAX);
		dp[0] = vector<int>(shelf_width + 1, 0);
		dpi[0] = 0;
		for (int i = 0; i < n; ++i) {
			int rowsum = 0;
			int maxheight_lastrow = 0;
			int j = i;
			while(j >= 0 && rowsum + books[j][0] <= shelf_width) {
				rowsum += books[j][0];
				maxheight_lastrow = max(maxheight_lastrow, books[j][1]);
				for (int k = shelf_width; k - rowsum  +1 >= 0; --k) {
                    dp[i + 1][k] = min(dp[i + 1][k], dpi[j] + maxheight_lastrow);
                    dpi[i + 1] = min(dpi[i + 1], dp[i + 1][k]);
                }
				--j;
			}
		}
		return dpi[n];
    }
};

int main() {
    vector<vector<int>> books = { { 1, 1 }, { 2, 3 }, { 2, 3 }, { 1, 1 },
                                  { 1, 1 }, { 1, 1 }, { 1, 2 } };
    int shelf_width = 4;
    Solution s;
	cout << s.minHeightShelves(books, shelf_width) << endl;
	return 0;
}
