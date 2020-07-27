#include "common.h"
class Solution_ref {
  public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size(), md = 0;
        // md = max depth
        vector<int> res(n, 0);
        // cnt is the size of stack
        // max depth is the max size of stack during operations
        for (int i = 0, cnt = 0; i < n; ++i) {
            if (seq[i] == '(') {
                res[i] = ++cnt; // ++cnt
            } else {
                res[i] = cnt--; // cnt--
            }
            md = max(md, cnt);
        }

        // nice
        for (int &k : res) {
            k = int(k <= md / 2);
        }
        return res;
    }
};

class Solution {
  public:
    vector<int> maxDepthAfterSplit(string seq) {
        if (seq.empty()) {
            return {};
        }
        int n = seq.size();
        int max_dep = 0;
        vector<int> result(n, 0);
        vector<int> couple(n, 0);
        vector<int> depth(n, 0);

        stack<int> s;
        for (int i = 0; i < n; ++i) {
            if (seq[i] == '(') {
                s.push(i);
            } else {
                int pre = s.top();
                s.pop();
                couple[pre] = i;
                couple[i] = pre;
            }
        }
        helper(depth, 0, n - 1, couple, max_dep);
        int half_depth = (max_dep + 1) / 2;
        for (int i = 0; i < n;) {
            if (seq[i] == '(') {
                if (depth[i] > half_depth) {
                    int next = couple[i];
                    for (int j = i; j <= next;) {
                        if (seq[j] == '(' && depth[j] <= half_depth) { // tricky
                            // must move thos nodes with depth < half_depth so prevent them attaching to node with depth
                            // > half_depth and form new depth
                            // in other words, after operation
                            // only nodes with depth > hale_depth are left as 0
                            for (int k = j; k <= couple[j]; ++k) {
                                result[k] = 1;
                            }
                            j = couple[j] + 1;
                        } else {
                            ++j;
                        }
                    }
                    // verify
                    /*
						string temp;
						for (int k = i ;k <= next; ++k) {
							if (result[k] == 0) {
								temp.push_back(seq[k]);
							}
						}
						cout << temp << endl;
						cout << getDepth(temp) << endl;
						*/
                    //==
                    i = next + 1;
                } else {
                    ++i;
                }
            } else {
                ++i;
            }
        }
        /*
			string A;
			string B;
			for (size_t i = 0; i < result.size();++i) {
				if (result[i]) {
					A.push_back(seq[i]);
				} else {
					B.push_back(seq[i]);
				}
			}
			cout << "A depth = " << getDepth(A) << endl;
			cout << "B depth = " << getDepth(B) << endl;
			*/
        return result;
    }
    int getDepth(const string seq) {
        int n = seq.size();
        vector<int> couple(n, 0);
        vector<int> depth(n, 0);
        //bool valid = true;
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            if (seq[i] == '(') {
                s.push(i);
            } else {
                if (s.empty()) {
                    cout << "Error" << endl;
                    return INT_MAX;
                }
                int pre = s.top();
                s.pop();
                couple[pre] = i;
                couple[i] = pre;
            }
        }
        int max_dep = 0;
        helper(depth, 0, n - 1, couple, max_dep);
        return max_dep;
    }

  private:
    int helper(vector<int> &depth, int start, int end, vector<int> &couple, int &max_dep) {
        if (start > end) {
            return 0;
        }
        if (couple[start] == end) {
            depth[start] = depth[end] = 1 + helper(depth, start + 1, end - 1, couple, max_dep);
            max_dep = max(max_dep, depth[start]);
            return depth[start];
        } else {
            int next = couple[start];
            int l = helper(depth, start, next, couple, max_dep);
            int r = helper(depth, next + 1, end, couple, max_dep);
            return max(l, r);
        }
    }
};

int main() {
	string seq = "(()())";
	//seq = "()(())()";
	//seq = "(())()()(())(())()(()()())()()((())()(((((((((())(((()))((()))))()))(())))))))";
	//vector<int> expected = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1};
	Solution_ref s;
	//string temp = "((((())(((()))((()))))()))";
	//cout << s.getDepth(temp) << endl;
	displayvector(s.maxDepthAfterSplit(seq));
	/*
	string A;
	string B;
	for (size_t i = 0; i < expected.size();++i) {
		if (expected[i]) {
			A.push_back(seq[i]);
		} else {
			B.push_back(seq[i]);
		}
	}

	cout << "A depth = " << s.getDepth(A) << endl;
	cout << "B depth = " << s.getDepth(B) << endl;

*/
	return 0;
}
