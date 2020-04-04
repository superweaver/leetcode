#include "common.h"
class Solution {
public:
    int numTeams(vector<int>& rating)
    {
        size_t n = rating.size();
        if (n < 3) {
            return 0;
        }
        multiset<int> left{ rating[0] };
        multiset<int> right(next(rating.begin(), 2), rating.end());
        int total = 0;
        for (size_t i = 1; i < n - 1; ++i) {  // for middle point
            auto& current = rating[i];
            auto eq_left = left.equal_range(current);
            auto less_left = distance(left.begin(), eq_left.first);
            auto greater_left = distance(eq_left.second, left.end());

            if (less_left || greater_left) {
                auto eq_right = right.equal_range(current);
                auto less_right = distance(right.begin(), eq_right.first);
                auto greater_right = distance(eq_right.second, right.end());
                total += less_left * greater_right;
                total += greater_left * less_right;
            }
            left.insert(current);
            right.erase(right.find(rating[i + 1]));
        }
        return total;
    }

    int numTeams_2(vector<int>& rating)
    {
        int n = rating.size();
        vector<int> less(n, 0);
        vector<int> greater(n, 0);
        multiset<int> cache;
        for (size_t i = 0; i < rating.size(); ++i) {
            // count how many previous elements are less than i
            auto p = cache.equal_range(rating[i]);
            less[i] = distance(cache.begin(), p.first);
            // count how many previous elements are larger than i
            greater[i] = distance(p.second, cache.end());
            cache.insert(rating[i]);
        }
        int total = 0;
        for (size_t i = 2; i < rating.size(); ++i) {
            for (size_t j = 1; j < i; ++j) {
                if (rating[i] > rating[j]) {
                    total += less[j];
                } else if (rating[i] < rating[j]) {
                    total += greater[j];
                }
            }
        }
        return total;
    }
};

int main()
{

    vector<int> rating = { 2, 5, 3, 4, 1 };  // 3
    //rating = { 2, 1, 3 };                    // 0
    //rating = { 1, 2, 3, 4 };                 // 4

    Solution s;
    cout << s.numTeams(rating) << endl;

    return 0;
}
