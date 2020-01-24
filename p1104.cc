#include "common.h"
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        // length of layer = (1 << i);
        int layer = 0;
        int count = 0;
        while (count < label) {
           int len = (1 << layer);
            count += len;
            layer++;
        }
        // count >= label
        layer--;
        vector<int> result;
        while(layer) {
            result.push_back(label);
            int start = (1 << layer);
            // end = (start << 1) -1;
            // label - start = end - x;
            // x = start + end - label;
            // its child is x >> 1;
            label = (3 * start - 1 - label) >> 1;
            layer--;
        }
        result.push_back(1);
        reverse(result.begin(), result.end());
        return result;
    }
};
int main() {
    int label = 14;
    label = 26;
    label = 1023;
    Solution s;
    displayvector(s.pathInZigZagTree(label));
    return 0;
}
