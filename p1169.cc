#include "common.h"
struct Node {
    string name;
    int time;
    int amount;
    string city;
    int i;
    Node(string& s, int index)
    {
        auto c = s.find(',');
        name = s.substr(0, c);
        auto next = s.find(',', c + 1);
        time = atoi(s.substr(c + 1, next - c - 1).c_str());
        c = s.find(',', next + 1);
        amount = atoi(s.substr(next + 1, c - next - 1).c_str());
        city = s.substr(c + 1);
        i = index;
    }
    bool operator<(const Node& b) const
    {  // no need
        if (name != b.name) {
            return name < b.name;
        } else {
            if (time != b.time) {
                return time < b.time;
            } else {
                if (amount != b.amount) {
                    return amount < b.amount;
                } else {
                    if (city != b.city) {
                        return city < b.city;
                    } else {
                        return i < b.i;
                    }
                }
            }
        }
    }
};
class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions)
    {
        //{name},{time},{amount},{city}
        vector<Node> cache;
        int n = transactions.size();
        for (int i = 0; i < n; ++i) {
            cache.push_back(Node(transactions[i], i));
        }
        sort(cache.begin(), cache.end());
        unordered_set<int> result;
        for (int i = 0; i < n; ++i) {
            if (cache[i].amount > 1000) {
                result.insert(cache[i].i);
            }

			/* // forward is not needed
            for (int j = i - 1; j >= 0; --j) {
                if (cache[j].name != cache[i].name) {
                    break;
                } else {
                    if (cache[j].time + 60 < cache[i].time) {
                        break;
                    } else {
                        if (cache[j].city != cache[i].city) {
                            result.insert(cache[i].i);
                            result.insert(cache[j].i);
                        }
                    }
                }
            }
			*/
			// afterward is enough
            for (int j = i + 1; j < n; ++j) {
                if (cache[j].name != cache[i].name) {
                    break;
                } else {
                    if (cache[j].time - 60 > cache[i].time) {
                        break;
                    } else {
                        if (cache[j].city != cache[i].city) {
                            result.insert(cache[i].i);
                            result.insert(cache[j].i);
                        }
                    }
                }
            }
        }

	vector<string> ans;
	for (auto i : result) {
		ans.push_back(transactions[i]);
	}
    return ans;
    }
};

int main()
{

    vector<string> transactions = { "alice,20,800,mtv", "alice,50,100,beijing" };
	transactions = {"alice,20,800,mtv","alice,50,1200,mtv"};
	transactions = {"alice,20,800,mtv","bob,50,1200,mtv"};
	transactions= {"alice,20,800,mtv","alice,20,800,mtv", "alice,50,100,beijing"};
    Solution s;
	displayvector(s.invalidTransactions(transactions));
    return 0;
}
