#include "common.h"
class Solution {
public:
    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice,
                                  int maxDistance)
    {
        vector<pair<int, int>> picks;
        for (auto& v : restaurants) {
            if (v[2] >= veganFriendly && v[3] <= maxPrice && v[4] <= maxDistance) {
                picks.push_back({ -v[1], -v[0] });
            }
        }
        sort(picks.begin(), picks.end());
        vector<int> result;
        for (auto& p : picks) {
            result.push_back(-p.second);
        }
        return result;
    }
};

int main()
{

    vector<vector<int>> restaurants = { { 1, 4, 1, 40, 10 },
                                        { 2, 8, 0, 50, 5 },
                                        { 3, 8, 1, 30, 4 },
                                        { 4, 10, 0, 10, 3 },
                                        { 5, 1, 1, 15, 1 } };
    int veganFriendly = 1, maxPrice = 50, maxDistance = 10;
	restaurants = {{1,4,1,40,10},{2,8,0,50,5},{3,8,1,30,4},{4,10,0,10,3},{5,1,1,15,1}}, veganFriendly = 0, maxPrice = 50, maxDistance = 10;

	restaurants = {{1,4,1,40,10},{2,8,0,50,5},{3,8,1,30,4},{4,10,0,10,3},{5,1,1,15,1}}, veganFriendly = 0, maxPrice = 30, maxDistance = 3;

    Solution s;
    displayvector(s.filterRestaurants(restaurants, veganFriendly, maxPrice, maxDistance));
    return 0;
}
