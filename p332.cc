#include "common.h"
// from solution
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {

        for (const auto& ticket : tickets)
            trips_[ticket[0]].push_back(ticket[1]);

        for (auto& trip : trips_) {
            auto& dests = trip.second;
            std::sort(dests.begin(), dests.end());
        }

        const string kStart = "JFK";

        dfs(kStart);

        return vector<string>(ans_.crbegin(), ans_.crend());
    }
private:
    vector<string> ans_;
    // deque or list
    // allow loops
    unordered_map<string, deque<string>> trips_;

    void dfs(const string& src) {
        auto& dests = trips_[src];
        while (!dests.empty()) {
            const auto dest = dests.front();
            // as long as we remove it , it is sure we can reconstruct the path
            dests.pop_front();
            dfs(dest);
        }
        // note when this src is put into ans !!!
        ans_.push_back(src);
    }
};

int main() {

	Solution s;

	return 0;
}
