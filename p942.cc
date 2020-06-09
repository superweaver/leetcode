#include "common.h"
class Solution {
public:
    vector<int> diStringMatch(string S) {
        int left = 0;
        int right = S.size();
        vector<int> result;
        for(char c : S){
            if(c == 'I'){
                result.push_back(left++);
            } else{
                result.push_back(right--);
            }
        }
        //left == rigth at this moment
        result.push_back(left);
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
