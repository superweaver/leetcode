#include "common.h"
struct Basket{
    int type; // -1 is not specified;
    int last; // the initial index of type
    Basket():type(-1), last(-1){}
    void clear()
    {
        type = -1;
        last = -1;
    }
};

class Solution {
public:
    int totalFruit(vector<int>& tree) {
        //1 <= tree.length <= 40000
        // Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
        // !!! any one of these two baskets
        // Move to the next tree to the right of the current tree.  If there is no tree to the
        // right, stop
        int result = 0;
        vector<Basket> b(2);
        int n = tree.size();
        tree.push_back(n); // an impossible type
        n++;
        int start = 0;      // begining of current valid two types of fruits
        bool flag = false;  // may not be necessary if we have put a type "n" in the back of tree
        for (int i = 0; i < n;) {
            if(b[0].type < 0 || b[0].type == tree[i]) {
                int j = i;
                for(; j < n;++j) {
                    if(tree[j] != tree[i]) {
                        break;
                    }
                }
                b[0].type = tree[i];
                b[0].last = i;
                i = j;
            } else if (b[1].type < 0 || b[1].type == tree[i]) {
                int j = i;
                for (; j < n; ++j) {
                    if (tree[j] != tree[i]) {
                        break;
                    }
                }
                b[1].type = tree[i];
                b[1].last = i;
                i = j;
            } else {
                flag = true;
                // type different from those in baskets
                // update result
                result = max(result, i - start);
                // clear one basket
                // keep the basket of type == type of tree[i-1]
                if (b[0].type == tree[i - 1]) {
                    start = b[0].last;
                    b[1].clear();
                } else {
                    start = b[1].last;
                    b[0].clear();
                }
            }
        }
        tree.pop_back();
        n--;
        return flag ? result : n;
    }
};



int main() {

	Solution s;

	return 0;
}
