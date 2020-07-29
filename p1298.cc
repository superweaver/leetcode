#include "common.h"
class Solution {
public:
  int maxCandies(vector<int> &status, vector<int> &candies, vector<vector<int>> &keys,
                 vector<vector<int>> &containedBoxes, vector<int> &initialBoxes) {
      int n = status.size();
      queue<int> q; // open boxes
      vector<bool> visited(n, false);

      vector<bool> currentboxes(n, false); // closed
      vector<bool> currentkeys(n, false);

      for (auto i : initialBoxes) {
          if (status[i]) {
              q.push(i);
              visited[i] = true;
          } else {
              currentboxes[i] = true;
          }
      }

      int result = 0;
      while(!q.empty()) {
          int size = q.size();
          while(size--) {
              auto c = q.front();
              q.pop();
              // check the candies in this box
              result += candies[c];
              // add keys to currentkeys if there is no corresponding closed box
              // otherwise, open the box, and erase it from closed box
              for (auto k : keys[c]) {
                  if (currentboxes[k]) {
                        if(visited[k]) {
                            continue;
                        }
                        currentboxes[k] = false;
                        q.push(k);
                        visited[k] = true;
                  } else {
                      currentkeys[k] = true;
                  }
              }

              for (auto &b : containedBoxes[c]) {
                  if (visited[b]) {
                      continue;
                  }
                  if (status[b] || currentkeys[b]) {
                      // add to queue
                      if (currentkeys[b]) {
                          currentkeys[b] = false;
                      }
                      q.push(b);
                      visited[b] = true;
                  } else {
                      currentboxes[b] = true;
                  }
              }
          }
      }
      return result;
  }
};

int main() {
    vector<int> status = {1,0,1,0};
    vector<int> candies = {7,5,4,100};
    vector<vector<int>> keys = {{},{},{1},{}};
    vector<vector<int>> containedBoxes = {{1,2},{3},{},{}};
    vector<int> initialBoxes = {0};

	Solution s;
    cout << s.maxCandies(status, candies, keys, containedBoxes, initialBoxes) << endl;

	return 0;
}
