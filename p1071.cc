#include "common.h"
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        if (str1.size() < str2.size()){
            swap(str1, str2);
        }
        while(str2.size()){
            int k = str1.size() / str2.size();
            string temp;
            for(int i = 0; i < k; ++i){
                temp += str2;
            }
            if(str1.substr(0, k*str2.size()) == temp) {
                str1 = str1.substr(temp.size());
                swap(str1, str2);
            }
            else{
                return "";
            }
        }
        return str1;
    }
};

class Solution_ref {
public:
    string gcdOfStrings(string str1, string str2) {
        if(str1+str2 != str2+str1) return "";
        return str1.substr(0, __gcd(str1.size(), str2.size()));
    }
};

int main() {

	Solution s;

	return 0;
}
