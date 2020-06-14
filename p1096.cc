#include "common.h"
class Solution_ref {
    int i = 0;
    vector<string> handleList(string &s) {
        ++i; // {
        vector<string> ans;
        while (s[i] != '}') {
            auto st = dfs(s);
            for (auto &a : st)
                ans.push_back(a);
            if (s[i] == ',')
                ++i;
        }
        ++i; // }
        return ans;
    }
    vector<string> dfs(string &s) {
        vector<string> ans{""};
        while (i < s.size() && s[i] != ',' && s[i] != '}') {
            if (s[i] != '{') {
                for (auto &a : ans)
                    a += s[i];
                ++i;
            } else {
                auto list = handleList(s);
                vector<string> tmp;
                for (auto &a : ans)
                    for (auto &b : list)
                        tmp.push_back(a + b);
                swap(tmp, ans);
            }
        }
        return ans;
    }

  public:
    vector<string> braceExpansionII(string s) {
        auto st = dfs(s);
        vector<string> ans(st.begin(), st.end());
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }
};

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
		int n = expression.size();
        vector<int> match = vector<int>(n, -1);
		unordered_map<int, vector<int>> semicolon; // frame, index
        stack<int> s;
		for (int i = 0; i < n; ++i) {
			if (expression[i] == '{') {
				s.push(i);
			} else if (expression[i] == '}') {
				match[i] = s.top();
				match[s.top()] = i;
				s.pop();
			} else if (expression[i] == ',') {
                int frame = s.size();
				semicolon[frame].push_back(i);
			}
		}
        auto r = helper(expression, 0, n - 1, match, semicolon, 0);
		sort(r.begin(), r.end());
        return r;
    }
private:
    vector<string> helper(string& expression, int start, int end, const vector<int>& match,
                          const unordered_map<int, vector<int>>& semicolon, int frame)
    {
		if (frame > (int)semicolon.size()) {
			return {};
		}
        if (start > end) {
            return {};
        }
        //if (match[start] == end) {
         //   return helper(expression, start + 1, end - 1, match, semicolon, frame + 1);
        //}
        if (semicolon.count(frame)) {
			auto& v = semicolon.at(frame);
			// find all semicolons in current frame , in [start, end]
			auto itstart = upper_bound(v.begin(), v.end(), start);
			auto itend = itstart;	
			for (; itend != v.end(); ++itend) {
				if (*itend > end) {
					break;
				}
			}	
			int delimiters = distance(itstart, itend);
			if (delimiters == 0) {
                return helper2(expression, start, end, match, semicolon, frame );
            } else {
				unordered_set<string> s;
                for (; itstart < itend; ++itstart) {
					if (*itstart > end) {
						break;
					}
                    auto r = helper(expression, start, (*itstart) - 1, match, semicolon, frame);
                    for(auto &str : r) {
						s.insert(str);
					}
                    start = (*itstart) + 1;
                }
                auto r = helper(expression, start, end, match, semicolon, frame);
                for (auto& str : r) {
                    s.insert(str);
                }
				start = end + 1;
                return vector<string>(s.begin(), s.end());
            }
		} else {
			return helper2(expression, start, end, match, semicolon, frame);		
		}
    }
	
    vector<string> helper2(string& expression, int start, int end, const vector<int>& match,
                          const unordered_map<int, vector<int>>& semicolon, int frame)
    {
        // no semicolon in current frame
        if(match[start] == end) {
            return helper(expression, start + 1, end - 1, match, semicolon, frame + 1);
        } else {
			vector<vector<string>> cache;
			string str;
			for (int i = start; i <= end; ) {
				if (expression[i] != '{') {
					str.push_back(expression[i]);	
					++i;
				} else {
					if (!str.empty()) {
						cache.push_back({str});
						str.clear();
					}
					auto r = helper(expression, i + 1, match[i]-1, match, semicolon, frame + 1);
					cache.push_back(r);
					i = match[i] + 1;
				}
			}
			if (!str.empty()) {
                cache.push_back({ str });
                str.clear();
            }
			unordered_set<string> result;		
			string path;
			dfs(result, cache, 0, path);
			return {result.begin(), result.end()};
        }
    }
	void dfs(unordered_set<string>& result, vector<vector<string>>& cache, size_t start, string& path) {
		if (start == cache.size()) {
			result.insert(path);
			return;
		}
        auto& v = cache[start];
		for (auto & s : v) {
			path += s;
			dfs(result, cache, start + 1, path);
			path.resize(path.size() - s.size());
		}
    }
};

int main() {

	string expression = "{a,b}{c,{d,e}}"; // ac be bd ae ad bc 
	expression = "{{a,z},a{b,c},{ab,z}}";  // ab ,ac, a, z
    Solution s;
	displayvector(s.braceExpansionII(expression));
	return 0;
}
