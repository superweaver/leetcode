#include "common.h"

class Solution {
public:
    //https://www.cnblogs.com/grandyang/p/7098764.html
    int leastInterval(vector<char>& tasks, int n) {
        int mx = 0;             // the max frequence
        int mxCnt = 0;          // how many characters have the max frequence

        vector<int> cnt(26, 0);
        for (char task : tasks) {
            ++cnt[task - 'A'];
            if (mx == cnt[task - 'A']) {
                ++mxCnt;
            } else if (mx < cnt[task - 'A']) {
                mx = cnt[task - 'A'];
                mxCnt = 1;
            }
        }

        int partCnt = mx - 1; // don't consider the last one
        int partLen = n - (mxCnt - 1); // the empty slots with in n
        int emptySlots = partCnt * partLen;

        int taskLeft = tasks.size() - mx * mxCnt;
        // nice !!!
        int idles = max(0, emptySlots - taskLeft);

        return tasks.size() + idles;
    }
};

class Solution2 {
public:
	int leastInterval(vector<char>& s, int n) {
		unordered_map<char, int> cache;
		for (auto c : s) {
			cache[c]++;
		}
		priority_queue<int> q;
		vector<int> q_used;
		for (auto p : cache) {
			q.push(p.second);
		}
		int total = s.size();
		int result = 0;
		int assigned = 0;
		while (!q.empty()) {
			for (int i = 0; i < n + 1; ++i) {
				if(!q.empty()) {
					auto c = q.top();
					++result;
					q.pop();
					assigned++;
					--c;
					if (c > 0) {
						q_used.push_back(c);
					}
				}
				else {
					if (assigned < total) {
						// empty() slot
						result++;
					}
					else {
						return result;
						break;
					}
				}

			}
			// join q and q_used;
			while (!q_used.empty()) {
				q.push(q_used.back());
				q_used.pop_back();
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
