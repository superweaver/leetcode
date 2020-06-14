#include "common.h"
class Solution {
public:
    vector<double> sampleStats(vector<int>& count)
    {
        // minimum, maximum, mean, median, and mode
        vector<double> result(5, -1);
        int mode = 0;
        double sum = 0;
        int f = INT_MIN;
        int totalcount = 0;
        int i = 0, j = 255;
        while(i < 256) {
            if(count[i]) {
                break;
            } else {
                ++i;
            }
        }
        // sum (count) >= 1
        result[0] = i;
        int count_i = count[i];
        while(j > i) {
            if(count[j]) {
                break;
            } else {
                --j;
            }
        }
        if (i == j) {
            return { i, i, i, i, i };
        }
        result[1] = j;
        int count_j = count[j];

        while(i < j) {
           // median
            if( count_i < count_j) {
                count_j -= count_i;
                i++;
                count_i = count[i];
            } else if (count_i == count_j) {
                i++;
                --j;
                count_i = count[i];
                count_j = count[j];
            } else {
                count_i -= count_j;
                --j;
                count_j = count[j];
            }
        }
        result[3] = (i + j) / 2.0;  // can handle all cases
        for(int i = 0; i < 256; ++i) {
            sum += i * count[i];
            totalcount += count[i];
            if (f < count[i]) {
                f = count[i];
                mode = i;
            }
        }
        result[2] = sum / totalcount;
        result[4] = mode;
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
