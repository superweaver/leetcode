#include "common.h"
class Solution {
public:
    int maximum69Number (int num) {
        int n = num;
        int index = -1;
        int i = 0;
        while(n){
            if((n % 10) == 6){
                index = i;
            }
            i++;
            n /= 10;
        }
        if (index < 0){
            return num;
        } else {
            return num + 3 * pow(10, index);
        }
    }
};

int main() {
    int num = 9669;
    Solution s;
    cout << s.maximum69Number(num) << endl;
    return 0;
}
