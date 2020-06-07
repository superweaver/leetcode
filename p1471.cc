#include "common.h"
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int m = ( arr[(n - 1) / 2]);
        int i = 0;
        int j = n - 1;
        vector<int> r;
        int size = 0;
        while (i <= j  &&  size < k) {
            if (abs(arr[i]-m) > abs(arr[j]-m)) {
                r.push_back(arr[i++]);
            } else {
                r.push_back(arr[j--]);
            }
            size++;
        }
        return r;
    }
};

int main() {
    vector<int> arr = {1,2,3,4,5};
    int k = 2;
    arr = {1,1,3,5,5}, k = 2;

    arr = {-7,22,17,3}, k = 2;




	Solution s;
    displayvector(s.getStrongest(arr, k));

	return 0;
}
