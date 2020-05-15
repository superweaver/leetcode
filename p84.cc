#include "common.h"
class Solution {
public:
	int largestRectangleArea(vector<int>& heights) {
		//https://www.geeksforgeeks.org/largest-rectangular-area-in-a-histogram-set-1/
		//https://www.geeksforgeeks.org/largest-rectangular-area-in-a-histogram-set-2/
		//https://www.geeksforgeeks.org/largest-rectangle-under-histogram/ !!! good explanation
		// for bar x, calculate the area of rectangle
		// which contains barx and bar x is the smallest bar of the bars forming the rectangle
		// to do this, we need to find the first index of bar smaller than bar x on the left
		// and first index of bar smaller than bar x on the right
		// find the max of such area;
		// trick add 0 to the end of heights;
		/* 1) Create an empty stack.

			2) Start from first bar, and do following for every bar ‘hist[i]’ where ‘i’ varies from 0 to n-1.
			a) If stack is empty or hist[i] is higher than the bar at top of stack, then push ‘i’ to stack.
			b) If this bar is smaller than the top of stack, then keep removing the top of stack while top of the stack is greater. Let the removed bar be hist[tp]. Calculate area of rectangle with hist[tp] as smallest bar. For hist[tp], the ‘left index’ is previous (previous to tp) item in stack and ‘right index’ is ‘i’ (current index).

			3) If the stack is not empty, then one by one remove all bars from stack and do step 2.b for every removed bar.
		*/
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
		return maxArea;
	}
};

int main() {

	Solution s;

	return 0;
}
