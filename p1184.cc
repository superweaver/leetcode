#include "common.h"
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        if (start == destination) return 0;
        if (start > destination) swap(start, destination);
        int a = 0;
        int b = 0;
        int n = distance.size();
        for (int i = 0; i < start; ++i){
            a += distance[i];
        }
        for (int i = start; i < destination; ++i){
            b += distance[i];
        }
        for (int i = destination; i < n; ++i){
            a += distance[i];
        }
        return min(a, b);

    }
};

int main() {

	vector<int> distance = {1,2,3,4};
	int start = 0;
	int destination = 1;
	Solution s;
	cout << s.distanceBetweenBusStops(distance, start, destination) << endl;
	return 0;
}
