#include "common.h"
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0;
        int right = people.size() - 1;
        int boat = 0;
        while (left <= right) {
            if (people[right] + people[left] > limit) {
                right--;
                boat++;
            } else {
                left++;
                right--;
                boat++;
            }
        }
        return boat;
    }
};


int main() {

	Solution s;

	return 0;
}
