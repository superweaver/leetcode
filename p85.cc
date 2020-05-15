#include "common.h"

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        size_t Rows = matrix.size();
        if (Rows == 0) return 0;
        size_t Cols = matrix[0].size();
        if (Cols == 0) return 0;
        vector<int> h(Cols, 0);
        size_t i = 0;
        for (size_t j = 0; j < Cols; ++j) {
            h[j] = (matrix[i][j] == '1');
        }
        int maxArea = maxRectangleInHistogram(h);

        for (i = 1; i < Rows; ++i) {
            for(size_t j = 0; j < Cols; ++j) {
                if(matrix[i][j] == '0') {
                    h[j] = 0;
                }
                else {
                    h[j]++;
                }
            }
            maxArea = max(maxArea, maxRectangleInHistogram(h));
        }
        return maxArea;
    }
    int maxRectangleInHistogram(vector<int>& heights){
    int N = heights.size();
		if (N == 0) {
			return 0;
		}
		stack<int> s;	// to store index
		// add 0 to the end of heights;
		heights.push_back(0);
		N += 1;
		//vector<int> area(N, 0);	// for explaination only
		int maxArea = INT_MIN;
		for (int i = 0; i < N; ) {
			if (s.empty() || heights[i] > heights[s.top()]) {
				s.push(i);
				i++;
			}
			else {
				// right index is i
				int rightindex = i;
				/*
				// equivalent
				do {
					int h = heights[s.top()];
					int index = s.top();
					s.pop();
					int leftindex;
					if (s.empty()) {
						leftindex = -1;	// view height[-1] = 0;
					}
					else {
						leftindex = s.top();
					}
					int w = rightindex - leftindex - 1;
					int A = w * h;
					area[index] = A;
					maxArea = max(maxArea, A);
				} while (!s.empty() && heights[s.top()] >= heights[i]);
				*/
				int h = heights[s.top()];
				int index = s.top();
				s.pop();
				int leftindex;
				if (s.empty()) {
					leftindex = -1;	// view height[-1] = 0;
				}
				else {
					leftindex = s.top();
				}
				int w = rightindex - leftindex - 1;
				int A = w * h;
				//area[index] = A;
				maxArea = max(maxArea, A);
			}
		}
		/*
		for (size_t i = 0; i < area.size(); ++i) {
			cout << area[i] << " ";
		}
		cout << endl;
		*/
     heights.pop_back();
		return maxArea;
	}
};

int main() {

	Solution s;

	return 0;
}
