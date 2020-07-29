#include "common.h"
class Solution {
public:
    int minJumps(vector<int>& arr) {
        // 1 <= arr.length <= 5 * 10^4
        //-10^8 <= arr[i] <= 10^8
       int n = arr.size();
       unordered_map<int, vector<int>> v2i;
       vector<bool> visited(n, false);
       for (int i = 0; i < n; ++i) {
           v2i[arr[i]].push_back(i);
       }
       int steps = 0;
       queue<int> q;
       q.push(0);
       visited[0] = true;
       while(!q.empty()) {
           int size = q.size();
           while(size--) {
               auto c = q.front();
               q.pop();
               if (c == n - 1) {
                   return steps;
               }
               // left
               if (c - 1 >= 0 && !visited[c - 1]) {
                   visited[c-1] = true;
                   q.push(c-1);
               }
               // right
               if (c + 1 < n && !visited[c + 1]) {
                   visited[c + 1] = true;
                   q.push(c + 1);
               }
               // same value
               for (auto i : v2i[arr[c]]) {
                   if (visited[i]) {
                       continue;
                   }
                   visited[i] = true;
                   q.push(i);
               }
               // drop this v2i[arr[c]]
               // all of them has been handled
               v2i.erase(arr[c]);
           }
           steps++;
       }
       return -1;
    }
};

int main() {
    vector<int> arr = {100,-23,-23,404,100,23,23,23,3,404}; //3
    arr = {11,22,7,7,7,7,7,7,7,22,13}; // 3
    arr = {6, 1, 9};

	Solution s;
    cout << s.minJumps(arr) << endl;

	return 0;
}
