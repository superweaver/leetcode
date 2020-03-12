#include "common.h"
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string> >& people)
    {
        // dp
        // how to represent state of each people?
        // int state; bit i = 1 means people has skill i
        // dp[i][state] = min people in the first i people to achieve state
        // dp[i][j|k] = min { dp[i-1][j|k], // people i is not used
        //                    dp[i-1][j] + 1} // people i is used
        //                  where k is people i's skill
        //  dp[0][0] = 0;
        //  note j|k >= j, j|k >= k
        int n = req_skills.size();
        int target = (1 << n) - 1;
        unordered_map<string, int> cache;
        for (int i = 0; i < n; ++i) {
            cache[req_skills[i]] = i;
        }
        vector<int> dp(1 << n, INT_MAX >> 1);
        vector<pair<int, int> > parents(1 << n);
        dp[0] = 0; // base case
        n = people.size();
        for (int i = 0; i < n; ++i) {
            auto &p = people[i];
            int skill = 0;
            for (auto &s : p) {
                skill |= (1 << cache[s]);
            }
            if (!skill) continue;
            for (int state = target; state >= 0; --state) { // back to front !!!!
                // state used as intermediate state
                if (dp[state] + 1 < dp[state | skill]) {
                    dp[state | skill] = dp[state] + 1;
                    parents[state | skill] = {state, i };
                    // by adding i to team, state-> state | skill
                }
            }
        }
        vector<int> result;
        int current = target;
        while(current) {
            result.push_back(parents[current].second);
            current = parents[current].first;
        }
        return result;
    }
};


class Solution_my {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people)
    {
		// TLE
        unordered_set<string> skills;
        for (auto& v : people) {
            for (auto& s : v) {
                skills.insert(s);
            }
        }
		unordered_map<string, int> cache;
		int i = 0;
        for (auto it = skills.begin(); it != skills.end(); ++it, ++i) {
            cache[*it] = i;
        }
		int req = 0;
		for(auto &s : req_skills) {
			req |= (1 << (cache[s]));
		}
		vector<unsigned int> p;
		for (auto &v : people) {
			int tmp = 0;
			for (auto&s : v) {
                tmp |= (1 << (cache[s]));
            }
            // tmp == 0 means empty set
            p.push_back(tmp);
        }
		// state = (people , skill)
		
		int n = p.size();
		vector<vector<int>> graph(n);
		for (int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				// at least have one difference
				unsigned int tmp = p[i] | p[j];
				if (!((tmp == p[i]) || (tmp == p[j]))){
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
		}
		queue<pair<long long, unsigned int>> q;
		int result = 1;	

		unordered_set<long long> visited;
		for (unsigned int i = 0; i < p.size(); ++i) {
            long long group = ((long long)1) << i;
            q.push({group, (i << 16) | p[i] });
            visited.insert(group);
        }

		while (!q.empty()) {
			size_t size = q.size();
			while(size--) {
				auto current = q.front();
				q.pop();
				int last = current.second >> 16;
				int cover = current.second & 0xFFFF;
				if ((cover & req) == req) {
					vector<int> ans; 
					for (int i = 0; i< n; ++i) {
						if ((((long long)1 << i)) & current.first) {
							ans.push_back(i);
						}
					}
					return ans;
				}
				// check last's connected node
				for (auto other: graph[last]) {
					long long nextgroup = current.first | (((long long)1) << other);
					if (nextgroup == current.first || visited.count(nextgroup)) {
						continue;
					}
					unsigned int nextcover = cover | p[other];
					visited.insert(nextgroup);
					q.push ({nextgroup, ((other << 16) | nextcover)});
				}
			}
			result++;
		}
		return {};
    }
};

int main() {
	//[0, 2]
    vector<string> req_skills = { "java", "nodejs", "reactjs" };
    vector<vector<string>> people = { { "java" }, { "nodejs" }, { "nodejs", "reactjs" } };  

	// [1, 2]	
    req_skills = { "algorithms", "math", "java", "reactjs", "csharp", "aws" };
    people = { { "algorithms", "math", "java" },
               { "algorithms", "math", "reactjs" },
               { "java", "csharp", "aws" },
               { "reactjs", "csharp" },
               { "csharp", "math" },
               { "aws", "java" } };

	// [0, 1, 2, 4]
    req_skills = { "uhppib", "mgdipkgt", "vaostwmycy", "bjwxnfbbubpnd" };
    people = { { "vaostwmycy" }, { "mgdipkgt" }, { "bjwxnfbbubpnd" }, {}, { "uhppib" } };

	// [3, 4, 6]
    req_skills = { "ubstd",          "dpsez",     "baflyxlgfgtqhpvs", "ftfwxwmdyugyov",
                   "nxpttsc",        "trthbxodw", "ijvnticzojqrtanc", "rwrrpymftayspv",
                   "ypcjwuiqinwrytk" };
    people = { {},
               {},
               { "rwrrpymftayspv" },
               { "ubstd", "dpsez", "baflyxlgfgtqhpvs", "nxpttsc" },
               { "ftfwxwmdyugyov", "ijvnticzojqrtanc", "ypcjwuiqinwrytk" },
               { "trthbxodw" },
               { "trthbxodw", "rwrrpymftayspv" },
               { "ubstd" },
               { "ijvnticzojqrtanc" },
               { "baflyxlgfgtqhpvs", "nxpttsc" } };

    Solution s;

    displayvector(s.smallestSufficientTeam(req_skills, people));
    return 0;
}
