#include "common.h"
class Solution {
public:
    //0 <= trips[i][1] < trips[i][2] <= 1000
    bool carPooling(vector<vector<int> >& trips, int capacity) {
        vector<int> passengers(1001, 0); // how many passengers are in car at distance i
        for (auto& t : trips) {
            passengers[t[2]] -= t[0]; // drop off
            passengers[t[1]] += t[0]; // pick up
        }
        for(auto i : passengers) {
            capacity -= i;
            if (capacity < 0) { // not enough capacity left
                return false;
            }
        }
        return true;
    }
};

class Solution2 {
public:
    bool carPooling(vector<vector<int> >& trips, int capacity)
    {
        vector<pair<int, int> > endPoints;
        for (auto& v : trips) {
            endPoints.push_back({ v[1], v[0] });   // pick up
            endPoints.push_back({ v[2], -v[0] });  // drop off
        }
        sort(endPoints.begin(), endPoints.end());
        int currentPassengers = 0;
        for (auto& p : endPoints) {
            currentPassengers += p.second;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        return true;
    }
};



int main() {

	Solution s;

	return 0;
}
