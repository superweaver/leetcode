#include "common.h"
class Solution {
public:
    Solution(vector<int> nums) {
        copy.swap(nums);
        back = copy;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        copy = back;
        return copy;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        for (int i = copy.size() - 1; i >= 0; --i){
            int j = rand() % (i + 1);
            swap(copy[i], copy[j]);
        }
        return copy;
    }
    private:
    vector<int> copy;
    vector<int> back;
};


int main() {


	return 0;
}
