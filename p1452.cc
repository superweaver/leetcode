#include "common.h"
class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {

       // company  -> person
       unordered_map<string, vector<int>> graph;
       int n = favoriteCompanies.size();
       for (int i = 0; i < n; ++i) {
           vector<string> &v = favoriteCompanies[i];
           for (auto & c : v) {
               graph[c].push_back(i);
           }
       }
       vector<int> result;
       for (int i = 0; i < n; ++i) {
           //unordered_map<int , int> count;
           vector<int> count(n, 0);
           int maxoccurance = 0;
           for (const auto& com : favoriteCompanies[i]) {
               auto &ps = graph[com]; 
               for (auto p : ps) {
                   if (p != i) {
                       count[p]++;
                       maxoccurance = max(maxoccurance, count[p]);
                   }
               }
           }
           if (maxoccurance != favoriteCompanies[i].size()) {
               result.push_back(i);
           }
       }
       return result;
    }
};

int main() {

	Solution s;
    vector<vector<string>> favoriteCompanies = {{"leetcode"},{"google"},{"facebook"},{"amazon"}};
    // favoriteCompanies =
    // {{"leetcode","google","facebook"},{"leetcode","amazon"},{"facebook","google"}};// 0, 1
    favoriteCompanies = {{"leetcode", "google", "facebook"},
                         {"google", "microsoft"},
                         {"google", "facebook"},
                         {"google"},
                         {"amazon"}}; //

    displayvector(s.peopleIndexes(favoriteCompanies));
    return 0;
}
