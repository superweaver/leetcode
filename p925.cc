#include "common.h"
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int len_n = name.size();
        int len_t = typed.size();
        int in = 0;
        int it = 0;
        while(true){
            if(in == len_n){
                return it == len_t;
            }
            if(it==len_t){
                return in == len_n;
            }
            char cn = name[in];
            int nin = in;
            while(nin < len_n && name[nin] == cn){
                nin++;
            }
            char ct = typed[it];
            if (cn != ct) {
                return false;
            }
            int nit = it;
            while (nit < len_t && typed[nit] == ct) {
                nit++;
            }
            if (nit - it < nin - in) {
                return false;
            }
            in = nin;
            it = nit;
        }
        return true;

    }
};

int main() {

	Solution s;

	return 0;
}
