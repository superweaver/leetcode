#include "common.h"
class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {

        //   2 <= x <= 100
        //   1 <= target <= 2 * 10^8
        //   bfs          
        queue<long long> q;
        unordered_set<long long> visited; // up to prev_group_value << 32 + current_value
        q.push(x); // 0 + x = x
        visited.insert(x);
        int steps = 0;
        while(!q.empty()) {
            size_t size = q.size();
            while(size--) {
                auto current = q.front();
                q.pop();
                long long currentValue = current & 0xFFFFFFFF;
                if (currentValue == (long long)target) {
                    return steps;
                }
                long long previousValue = current >>= 32;
                for (int i = ADD; i <= OPERATORS; ++i) {
                    long long nextKey = getNextKey(previousValue, currentValue, i, x);
                    if (nextKey) {
                        if(!visited.count(nextKey)) {
                           visited.insert(nextKey);
                           q.push(nextKey);
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
private:
    enum {ADD, MINUS, MULTIPLY, DIVIDE, OPERATORS};
    const int lowerBound = 1; 
    const int upperBound = 200000000;

    long long getNextKey(long long pv, long long cv, int operation, int x) {
        // lastop is for group
        int lastOp = cv > pv ? ADD : MINUS;
        long long cgv = (lastOp == ADD) ? (cv - pv) : (pv - cv);
        if (operation == ADD || operation == MINUS) {
            pv = cv;
            cv = (operation == ADD) ? (cv + x) : (cv - x);
            if (cv < 0 || cv > INT_MAX) {
                return 0;
            }
            return ((pv << 32) + cv);
        }
        // MULTIPLY and DIVIDE;
        if (cgv == 1) {
            return 0;
        } else {
            if (operation == DIVIDE) {
                if (cgv == x) { 
                    cgv = 1; 
                    cv = (lastOp == ADD) ? (pv + cgv) : (pv - cgv);
                    if (cv < 0 || cv > INT_MAX) {
                        return 0;
                    }
                    return ((pv << 32) + cv);
                }
                else {
                    return 0;
                }
            } else { // Multipy
                cv = (lastOp == ADD) ? (pv + cgv * x) : (pv - cgv * x);
                if (cv < 0 || cv > INT_MAX) {
                    return 0;
                }
                return ((pv << 32) + cv);

            }
        }
    }

};
int main() {
    int x = 3, target = 19; // 5
    x = 5, target = 501; // 8
    x = 100, target = 100000000;
    x = 2, target = 125046;
    Solution s;
    cout << s.leastOpsExpressTarget(x, target) << endl;
    return 0;
}
