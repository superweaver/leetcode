#include "common.h"
class Solution {
    // https://zxi.mytechroad.com/blog/greedy/leetcode-1383-maximum-performance-of-a-team/
public:
  int maxPerformance(int n, vector<int> &speed, vector<int> &efficiency, int k) {
      const int Mod = 1e9 + 7;
      // !!!
      // sort them according to desceding efficiency
      vector<pair<int, int>> es; // efficiency, speed
      for (int i = 0; i < n; ++i) {
          es.push_back({efficiency[i], speed[i]});
      }
      // nice
      sort(es.rbegin(), es.rend());
      long long sum = 0; // sum of speed
      priority_queue<int, vector<int>, greater<int>> q; // store speed

      long long performance = 0;
      // !!!! at most k engineers
      // not exactly k engineers
      for (int i = 0; i < k; ++i) {
          sum += es[i].second;
          q.push(es[i].second);
          performance = max(performance, sum * es[i].first);
      }
      // this is wrong !!!
      //long long performance = sum * es[k-1].first;
      //// es[k-1] has the lowest efficiency
      for (int i = k; i < n; ++i) {
          // remove the shortest speed
          sum -= q.top();
          q.pop();
          // for the new candidate
          // 1) don't include, performace has no change
          // 2) include it, the minimum efficiency must be es[i].frist;
          //    find the smallest speed, and replace it with es[i].second;
          // add the new candidate
          sum += es[i].second;
          q.push(es[i].second);
          performance = max(performance, sum * es[i].first);
      }
      return performance % Mod;
  }
};
// Author: Huahua
class Solution_huahua {
public:
  int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
    vector<pair<int, int>> es;
    for (int i = 0; i < n; ++i)
      es.push_back({efficiency[i], speed[i]});
    sort(es.rbegin(), es.rend());
    priority_queue<int, vector<int>, greater<int>> q;
    long sum = 0;
    long ans = 0;
    for (int i = 0; i < n; ++i) {
      if (i >= k) {
        sum -= q.top();
        q.pop();
      }
      sum += es[i].second;
      q.push(es[i].second);
      ans = max(ans, sum * es[i].first);
    }
    return ans % static_cast<int>(1e9 + 7);
  }
};

int main() {
    int n = 6;
    vector<int> speed = {2,10,3,1,5,8}; 
    vector<int> efficiency = {5,4,3,9,7,2};
    int k = 2; // 60
    n = 6, speed = {2, 10, 3, 1, 5, 8}, efficiency = {5, 4, 3, 9, 7, 2}, k = 3; // 68
    n = 3,speed = {2,8,2}, efficiency = {2,7,1}, k = 2;


    Solution s;
    cout << s.maxPerformance(n, speed, efficiency, k) << endl;
    {
        Solution_huahua s;
        cout << s.maxPerformance(n, speed, efficiency, k) << endl;
    }


	return 0;
}
