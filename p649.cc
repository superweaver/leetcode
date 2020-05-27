#include "common.h"
//https://www.cnblogs.com/grandyang/p/7439222.html
/*
可以用两个队列queue，把各自阵营的位置存入不同的队列里面，然后进行循环，每次从两个队列各取一个位置出来，看其大小关系，小的那个说明在前面，就可以把后面的那个Ban掉，所以我们要把小的那个位置要加回队列里面，但是不能直接加原位置，因为下一轮才能再轮到他来Ban，所以我们要加上一个n，再排入队列。这样当某个队列为空时，推出循环，我们返回不为空的那个阵营
+n, 保证加入之后排在所有当前轮的index之后
if i < j, then i will diable j's right
if (i < k), both i and k can survive in next round
(i+n) < (k+n) in next round, i+n will be ahead of (k+n)
// nice
*/
class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();
        queue<int> q1, q2;
        for (int i = 0; i < n; ++i) {
            (senate[i] == 'R') ? q1.push(i) : q2.push(i);
        }
        while (!q1.empty() && !q2.empty()) {
            int i = q1.front(); q1.pop();
            int j = q2.front(); q2.pop();
            (i < j) ? q1.push(i + n) : q2.push(j + n);
        }
        return (q1.size() > q2.size()) ? "Radiant" : "Dire";
    }
};

int main() {

	Solution s;

	return 0;
}
