#include "common.h"
// http://zxi.mytechroad.com/blog/string/leetcode-301-remove-invalid-parentheses/
// Author: Huahua
// Runtime: 0 ms
class Solution {
  public:
    vector<string> removeInvalidParentheses(const string &s) {
        int n = s.size();
        int left = 0;
        for (; left < n;) {
            if (s[left] == ')') {
                left++;
            } else {
                break;
            }
        }
        int right = n - 1;
        for (; right > left;) {
            if (s[right] == '(') {
                right--;
            } else {
                break;
            }
        }
        auto sp = s.substr(left, right - left + 1);

        int l = 0; // counter for left parenthesis
        int r = 0; // counter for left parenthesis
        // calculate how many left parenthesis and right parenthesis should be removed
        for (const char ch : sp) {
            l += (ch == '(');
            if (l == 0) {
                r += (ch == ')');
            } else {
                l -= (ch == ')');
            }
        }
        vector<string> ans;
        dfs(sp, 0, l, r, ans);
        return ans;
    }

  private:
    bool isValid(const string &s) {
        int count = 0;
        for (const char ch : s) {
            if (ch == '(') {
                ++count;
            }
            if (ch == ')') {
                --count;
            }
            if (count < 0) {
                return false;
            }
        }
        return count == 0;
    }

    // l/r: number of left/right parentheses to remove.
    void dfs(const string &s, int start, int l, int r, vector<string> &ans) {
        // Nothing to remove.
        if (l == 0 && r == 0) {
            if (isValid(s)) {
                ans.push_back(s);
            }
            return;
        }

        for (int i = start; i < s.length(); ++i) {
            // We only remove the first parenthes if there are consecutive ones to avoid
            // duplications.
            if (i != start && s[i] == s[i - 1]) {
                // nice
                continue;
            }

            if (s[i] == '(' || s[i] == ')') {
                if (r > 0 && s[i] == ')') {
                    string curr = s.substr(0, i) + s.substr(i + 1);
                    dfs(curr, i, l, r - 1, ans);
                } else if (l > 0 && s[i] == '(') {
                    string curr = s.substr(0, i) + s.substr(i + 1);
                    dfs(curr, i, l - 1, r, ans);
                }
            }
        }
    }
};

class Solution_my {
  public:
    vector<string> removeInvalidParentheses(string s) {
        auto r1 = removeInvalidParentheses_helper(s);
        return r1;
    }
    vector<string> removeInvalidParentheses_helper(string s) {
        vector<string> result;
        if (s.empty()) {
            result.push_back("");
            return result;
        }
        // remove heading) and tailing (
        removeHeadingRP(s);
        if (s.empty()) {
            result.push_back("");
            return result;
        }
        removeTailingLP(s);
        if (s.empty()) {
            result.push_back("");
            return result;
        }

        // stroe prefix and affix
        string prefix = getPrefix(s);
        if (prefix.size() == s.size()) {
            result.push_back(prefix);
            return result;
        }
        s = s.substr(prefix.size(), s.size() - prefix.size());

        string affix = getAffix(s);
        if (!affix.empty()) {
            s.resize(s.size() - affix.size());
        }

        if (prefix.empty() && affix.empty()) {
            vector<vector<string>> sections;
            string sp = s;
            while (!sp.empty()) {
                int size = sp.size();
                vector<int> sum(size, 0);
                sum[0] = 0;
                if (s[0] == '(') {
                    sum[0] = -1;
                }
                if (s[0] == ')') {
                    sum[0] = +1;
                }
                int maxSum = sum[0];
                size_t indexmaxSum = 0;
                for (size_t i = 1; i < sp.size(); ++i) {
                    if (sp[i] == '(') {
                        sum[i] = sum[i - 1] - 1;
                    } else if (sp[i] == ')') {
                        sum[i] = sum[i - 1] + 1;
                        if (maxSum <= sum[i]) {
                            maxSum = sum[i];
                            indexmaxSum = i;
                        }
                    } else {
                        sum[i] = sum[i - 1];
                    }
                }
                if (maxSum > 0) {
                    string c = sp.substr(0, indexmaxSum + 1);
                    sp = sp.substr(indexmaxSum + 1, sp.size() - indexmaxSum - 1);
                    reverse(c.begin(), c.end());
                    transform(c);
                    auto temp = removeInvalidParentheses_helper(c);
                    // auto temp = removeRedudantLeftParenthesis(c);
                    for (auto &rs : temp) {
                        reverse(rs.begin(), rs.end());
                        transform(rs);
                    }
                    sections.push_back(temp);

                } else {
                    string c = sp; // left parenthesis is more than right parenthesis;
                    sp.clear();
                    auto temp = removeRedudantLeftParenthesis(c);
                    sections.push_back(temp);
                }
            }
            if (!sections.empty()) {
                string path;
                dfs(result, sections, 0, sections.size(), path);
            }
        } else {
            // prefix or affix is not empty
            result = removeInvalidParentheses_helper(s);
            for (auto &rs : result) {
                rs = prefix + rs + affix;
            }
        }

        if (result.empty()) {
            result.push_back("");
        }
        return result;
    }
    void transform(string &s) {
        for (auto &c : s) {
            if (c == '(') {
                c = ')';
            } else if (c == ')') {
                c = '(';
            }
        }
    }
    void removeHeadingRP(string &s) {
        int n = s.size();
        int hri = 0; // heading right parenthesis
        while (hri < n && s[hri] == ')') {
            ++hri;
        }
        s = s.substr(hri, s.size() - hri);
    }
    void removeTailingLP(string &s) {
        int tli = s.size() - 1; // tailing left parenthesis
        while (tli >= 0 && s[tli] == '(') {
            --tli;
        }
        s.resize(tli + 1);
    }
    string getPrefix(const string &s) {
        string prefix;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == ')') {
                break;
            } else {
                prefix.push_back(s[i]);
            }
        }
        return prefix;
    }
    string getAffix(const string &s) {
        string affix;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == '(' || s[i] == ')') {
                break;
            } else {
                affix.push_back(s[i]);
            }
        }
        if (!affix.empty()) {
            reverse(affix.begin(), affix.end());
        }
        return affix;
    }

    vector<string> removeRedudantLeftParenthesis(string s) {
        // s may have no ( ) , no need to pass in this function
        // s may have less ) than (
        vector<string> result;
        if (s.empty())
            return result;
        // remove back end (
        int n = s.size();
        int i = n - 1;
        for (; i >= 0; --i) {
            if (s[i] == '(') {
                s.pop_back();
            } else {
                break;
            }
        }
        if (s.empty()) { // all (
            return result;
        }
        // abc) or )
        // abc( is also possible for the last section

        string prefix;
        n = s.size();
        for (i = 0; i < n; i++) {
            if (s[i] == ')' || s[i] == '(') {
                break;
            }
        }
        if (i == n) {
            // all chars or abc( [( is removed in previous step]
            result.push_back(s);
            return result;
        } else {
            if (s[i] == ')') {
                // it is sure to have only one ')' in this string s
                prefix = s.substr(0, i);
                if (!prefix.empty()) {
                    result.push_back(prefix);
                }
                return result;
            } else { // s[i] == '(' // prefix can be non-empty: eg: Y(X(
                prefix = s.substr(0, i);
            }
        }
        if (!prefix.empty()) {
            // cout << "Something wrong" << endl;
        }
        // s[i] == '('
        n = s.size();
        vector<int> leftp;
        unordered_map<int, int> lp2g; // lp index to gropuindex
        vector<int> rightp;           // index of right parenthesis;
        int groupindex = 0;
        for (int i = 0; i < n;) {
            if (s[i] == '(') {
                while (i < n && s[i] == '(') {
                    leftp.push_back(i);
                    lp2g[i] = groupindex;
                    ++i;
                }
                groupindex++;
            } else {
                if (s[i] == ')') {
                    rightp.push_back(i);
                }
                ++i;
            }
        }
        if (rightp.empty()) {
            string copy = s;
            size_t index = 0;
            for (size_t i = 0; i < s.size(); ++i) {
                if (copy[i] != '(') {
                    copy[index++] = copy[i];
                }
            }
            copy.resize(index);
            result.push_back(copy);
            return result;
        }
        vector<int> match;
        vector<vector<int>> matches;
        unordered_set<string> exist;
        /*
        cout << lp2g.size() << endl;
        for (auto m = lp2g.begin(); m != lp2g.end(); ++m) {
            cout << m->first << ":" << m->second << " " << endl;
        }
        */
        getMatches(matches, match, leftp, rightp, lp2g, 0, 0, exist);
        // convert to string
        for (size_t i = 0; i < matches.size(); ++i) {
            string copy = s;
            int k = 0;
            size_t index = 0;
            for (size_t j = 0; j < s.size(); ++j) {
                if (copy[j] == '(') {
                    if (index < matches[i].size() && j == matches[i][index]) {
                        index++;
                        copy[k] = copy[j];
                        k++;
                    } else {
                        // skp it (
                    }
                } else {
                    copy[k] = copy[j];
                    k++;
                }
            }
            copy.resize(k);
            result.push_back(copy);
        }
        return result;
    }

  private:
    void dfs(vector<string> &result, vector<vector<string>> &sections, int start, const int end,
             string path) {
        if (start == end) {
            result.push_back(path);
            return;
        }
        if (sections[start].empty() || sections[start][0].empty()) {
            dfs(result, sections, start + 1, end, path);
        } else {
            for (size_t i = 0; i < sections[start].size(); ++i) {
                string &temp = sections[start][i];
                if (!temp.empty()) {
                    dfs(result, sections, start + 1, end, path + temp);
                }
            }
        }
    }

    void getMatches(vector<vector<int>> &matches, vector<int> &match, const vector<int> &leftp,
                    const vector<int> &rightp, const unordered_map<int, int> &lp2g, size_t startlp,
                    size_t startrp, unordered_set<string> &exist) {
        if (startrp > rightp.size()) {
            return;
        }
        if (startrp == rightp.size()) {
            // check match
            assert(match.size() == rightp.size());
            ostringstream oss;
            for (size_t j = 0; j < match.size(); j++) {
                oss << lp2g.at(match[j]);
            }
            string key = oss.str();
            if (exist.find(key) == exist.end()) {
                exist.insert(key);
                matches.push_back(match);
            }
        } else {
            for (int i = startlp; i < leftp.size() && leftp[i] < rightp[startrp]; ++i) {
                match.push_back(leftp[i]);
                getMatches(matches, match, leftp, rightp, lp2g, i + 1, startrp + 1, exist);
                match.pop_back();
            }
        }
    }
};

int main() {

    Solution s;

    return 0;
}
