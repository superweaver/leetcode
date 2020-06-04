#include "common.h"

class Solution {
    // https://www.cnblogs.com/grandyang/p/11343552.html
    // https://medium.com/@jolyon129/854-k-similar-strings-7b68772217d0
  public:
    int kSimilarity(string A, string B) {
        int n = A.size();
        int result = 0;
        // take B as target
        // find i , A[i] != B[i]
        // after that find j, so that i < j && A[j] != B[j] && A[j] == B[i]
        queue<string> q;
        q.push(A);
        unordered_set<string> visited;
        visited.insert(A);
        // BFS
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                string current = q.front();
                q.pop();
                if (current == B)
                    return result;
                // find i where current[i]!=B[i]
                int i = 0;
                for (; i < n; ++i) {
                    if (current[i] != B[i]) {
                        break;
                    }
                }
                // find the second to swap
                for (int j = i + 1; j < n; ++j) {
                    if (current[j] != B[j] && current[j] == B[i]) {
                        swap(current[i], current[j]);
                        if (!visited.count(current)) {
                            visited.insert(current);
                            q.push(current);
                        }
                        swap(current[i], current[j]);
                    }
                }
            }
            result++;
        }
        return -1;
    }
};

int main() {

    Solution s;

    return 0;
}
