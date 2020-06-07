#include "common.h"
class StockSpanner {
public:
    StockSpanner() {
        index = 0;
        // nice trick
        s.push({INT_MAX, -1});
    }
    int next(int price) {
        while (s.top().first <= price) {
            s.pop();
        }
        int r = index - s.top().second;
        s.push({price, index++});
        return r;
    }
private:
    stack<pair<int, int>> s;
    // value and index
    int index;
};

int main() {


	return 0;
}
