#include "common.h"

// https://blog.csdn.net/sysucph/article/details/90214803
// https://www.acwing.com/solution/LeetCode/content/4699/
class Solution {
public:
    string longestDupSubstring(string S)
    {
        int n = S.size();
        if (n == 0) {
            return "";
		}
        auto ret = suffix_array_construction(S);
        auto height = lcp_construction(S, ret);
        int ans = 0, ans_index = 0;
        for (int i = 1; i < n; i++) {
            if (height[i] > ans) {
                ans_index = i;
                ans = height[i];
            }
        }
        if (ans == 0) {
            return "";
        }
        return S.substr(ret[ans_index], ans);
    }

    vector<int> sort_cyclic_shifts(string const& s)
    {
        int n = s.size();
        const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
		// p is permutation of [0..n-1]
		// p[i] = j : the index of suffix[j] in the sorted order is i
		// c[i] corresponds to the equivalent class to which the substring belongs.
		// equiavlent class, for index i, j, and length 2^k, then suffix[i] and suffix[j]
		// belong to equivalent class if s[i...i + 2^k-1] == s[j...j + 2^k-1]
		//
		// iteration 0
		// counting
        for (int i = 0; i < n; i++) {
            cnt[s[i]]++;
		}
		// accumulation
        for (int i = 1; i < alphabet; i++) {
            cnt[i] += cnt[i - 1];
		}
		// 	-- will make the index start from 0
		// 	for i, its char is s[i]
		// 	corresponding to count cnt[s[i]] , note this is accumulation !!!
		// 	that means s[i] is the cnt[s[i]]'th char in sorted single char array
		// 	so cnt[s[i]]-1 is the index of suffix[i] in sorted order
		// 	using --cnt[s[i]] will automatically decrease cnt[s[i]]
		// 	for next same char c == s[i], the next char should be put before current char
        for (int i = 0; i < n; i++) {
            p[--cnt[s[i]]] = i;
		}
		// what is p[0]?
		// p[0] = j means suffix[j] is the first substring in the sorted subsring array
		// we assign class 0 to it
        c[p[0]] = 0;
        int classes = 1; // == c[p[0]] + 1; // next class
		// for length = 1 comparison
		// calculate class for p[i]
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]]) { // only need to compare one character in first step (length == 1)
                classes++; // different class, then increase classes
			}
            c[p[i]] = classes - 1; // if it is same as previous char, then use previous class
        }
		// pn == new p
		// cn = new c
		// to sort the pairs we first sort them by the second element,
		// and then by the first element (with a stable sort, i.e. sorting without breaking the relative order of equal elements).
		// However the second elements were already sorted in the previous iteration.
		// Thus, in order to sort the pairs by the second elements,
		// !!!!
		// we just need to subtract 2^(k-1) from the indices in p[](e.g. if the smallest substring of length 2^(k-1)
		// starts at position i, then the substring of length 2^(k) !!! with the smallest second half starts at (i - 2^(k-1)).
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
			// cyclic substring of length 2^h
			// equivalent to sort on second half first
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h); // h is previous step
                if (pn[i] < 0) { // cyclic
                    pn[i] += n;
                }
            }
            fill(cnt.begin(), cnt.begin() + classes, 0); // classes
			// count based on classes
			// pn[i] now is the second rank
            for (int i = 0; i < n; i++) {
                cnt[c[pn[i]]]++;
			}
            for (int i = 1; i < classes; i++) {
                cnt[i] += cnt[i - 1];
			}
			// n - 1 to 0 !!!
            for (int i = n - 1; i >= 0; i--) {
                p[--cnt[c[pn[i]]]] = pn[i];
			}

            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = { c[p[i]], c[(p[i] + (1 << h)) % n] };
                pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n] };
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }

    vector<int> suffix_array_construction(string s)
    {
        s += "$";
        vector<int> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }
    /*
    int compare(int i, int j, int l, int k) {
        pair<int, int> a = {c[k][i], c[k][(i+l-(1 << k))%n]};
        pair<int, int> b = {c[k][j], c[k][(j+l-(1 << k))%n]};
        return a == b ? 0 : a < b ? -1 : 1;
    }
    */
    /*
    int lcp(int i, int j) {
        int ans = 0;
        for (int k = log_n; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
    */
    vector<int> lcp_construction(string const& s, vector<int> const& p)
    {
        int n = s.size();
        vector<int> rank(n, 0);
        for (int i = 0; i < n; i++)
            rank[p[i]] = i;

        int k = 0;
        vector<int> lcp(n - 1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
        }
        return lcp;
    }
};


struct node {
    int index;
    int rank[2];
};

bool cmp(const node& a, const node& b)
{
    if (a.rank[0] != b.rank[0]) {
        return a.rank[0] < b.rank[0];
	}
    if (a.rank[1] != b.rank[1]) {
        return a.rank[1] < b.rank[1];
	}
    return a.index < b.index;
}

vector<int> quickSortSuffix(vector<int>& r)
{
    int n = r.size();
    vector<node> a(n);
    for (int i = 0; i < n; i++) {
        a[i].index = i;
        a[i].rank[0] = r[i];
        a[i].rank[1] = i < n - 1 ? r[i + 1] : -1;
    }
    sort(a.begin(), a.end(), cmp);
    vector<int> ind(n);
    for (int k = 2; k < n; k *= 2) {
        int rank = 0;
        int pre_rank = a[0].rank[0];
        a[0].rank[0] = 0;
        ind[a[0].index] = 0;
        for (int i = 1; i < n; i++) {
            if (pre_rank == a[i].rank[0] && a[i - 1].rank[1] == a[i].rank[1]) {
                pre_rank = a[i].rank[0];
                a[i].rank[0] = rank;
            } else {
                pre_rank = a[i].rank[0];
                a[i].rank[0] = ++rank;
            }
            ind[a[i].index] = i;
        }
        if (rank == n)
            break;

        for (int i = 0; i < n; i++) {
            int j = a[i].index;
            if (j + k < n) {
                j = ind[j + k];
                a[i].rank[1] = a[j].rank[0];
            } else {
                a[i].rank[1] = -1;
            }
        }
        sort(a.begin(), a.end(), cmp);
    }
    vector<int> sa(n);
    for (int i = 0; i < n; i++)
        sa[i] = a[i].index;
    return sa;
}

vector<int> radixSuffix(vector<int>& r, int m)
{
    // m large elements in array r and large than or equal r.size()
    // m = max(m, r.size())
    int n = r.size();
    vector<int> count(m, 0);  // radix sort count array
    vector<int> wv(r);        // keyword value
    vector<int> sa(n);        // suffix array : sa[i] means the ith rank element's index is sa[i]
    vector<int> rank(n);      // rank array: rank[i] the rank of ith element is rank[i]
    // size 1 suffix radix sort
    for (int i = 0; i < n; i++) {
        rank[i] = wv[i];
        count[wv[i]]++;
    }
    for (int i = 1; i < m; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--)
        sa[--count[wv[i]]] = i;
    vector<int> second_sa(n);  // suffix array by second key word
    vector<int> new_rank(n);   // store new_rank
    auto cmp = [&](int a, int b, int l) {
        if (rank[a] != rank[b])
            return false;
        if (a + l >= n && b + l >= n)
            return true;
        if (a + l >= n || b + l >= n)
            return false;
        return rank[a + l] == rank[b + l];
    };
    for (int p = 0, j = 1; p < n; j *= 2, m = p) {
        // second key word sort
        p = 0;
        for (int i = n - j; i < n; i++)
            second_sa[p++] = i;
        for (int i = 0; i < n; i++)
            if (sa[i] >= j)
                second_sa[p++] = sa[i] - j;
        // first keyword sort
        for (int i = 0; i < m; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            wv[i] = rank[second_sa[i]];
        for (int i = 0; i < n; i++)
            count[wv[i]]++;
        for (int i = 1; i < m; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            sa[--count[wv[i]]] = second_sa[i];
        new_rank[sa[0]] = 0;
        p = 1;
        for (int i = 1; i < n; i++) {
            new_rank[sa[i]] = cmp(sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
        rank.swap(new_rank);
    }
    return sa;
}

vector<int> calcHeight(vector<int>& sa, vector<int>& r)
{
    int n = sa.size();
    vector<int> height(n);
    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        int cur = rank[i];
        if (cur == 0) {
            height[cur] = 0;
            k = 0;
        } else {
            if (k > 0)
                k--;
            int j = sa[cur - 1];
            while (i + k < n && j + k < n && r[i + k] == r[j + k])
                k++;
            height[cur] = k;
        }
    }
    return height;
}

class Solution {
public:
    string longestDupSubstring(string S)
    {
        int n = S.size();
        if (n == 0) {
            return "";
		}
        vector<int> r(n);
        for (int i = 0; i < n; i++) {
            r[i] = S[i] - 'a';
        }
        auto ret = radixSuffix(r, max(n + 1, 27));
        auto height = calcHeight(ret, r);
        int ans = 0, ans_index = 0;
        for (int i = 1; i < n; i++) {
            if (height[i] > ans) {
                ans_index = i;
                ans = height[i];
            }
        }
        if (ans == 0) {
            return "";
		}
        return S.substr(ret[ans_index], ans);
    }
};

class Solution3 {
    // https://www.acwing.com/solution/LeetCode/content/4699/
public:
    const int mod = 999983;

    bool cmp(const string& s, const vector<int>& c, int x, int len)
    {
        for (int st : c) {
            bool flag = true;
            for (int i = st, j = x; i < st + len; i++, j++)
                if (s[i] != s[j]) {
                    flag = false;
                    break;
                }
            if (flag)
                return true;
        }
        return false;
    }

    string check(const string& s, int len, int power)
    {
        vector<vector<int>> vis(mod);
        int n = s.length();

        int hash = 0;
        for (int i = 0; i < len; i++)
            hash = (hash * 27 + s[i] - 'a' + 1) % mod;

        vis[hash].push_back(0);

        for (int i = len; i < n; i++) {
            hash = (hash - power * (s[i - len] - 'a' + 1) % mod + mod) % mod;
            hash = (hash * 27 + s[i] - 'a' + 1) % mod;

            if (!vis[hash].empty() && cmp(s, vis[hash], i - len + 1, len))
                return s.substr(i - len + 1, len);

            vis[hash].push_back(i - len + 1);
        }

        return "";
    }

    string longestDupSubstring(string S)
    {
        int n = S.length();
        int l = 0, r = n - 1;

        vector<int> power(n, 1);
        for (int i = 1; i < n; i++)
            power[i] = power[i - 1] * 27 % mod;

        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(S, mid + 1, power[mid]) == "") {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        if (l == 0)
            return "";
        return check(S, l, power[l - 1]);
    }
};

class Solution2 {
public:
    string longestDupSubstring(string S)
    {
        int n = S.size();
        int l = 1, r = n;
        int ans = 0, ans_st = 0;
        // lambda function, check if S.substr(a, len) == S.substr(b.end)
        auto check = [&](int a, int b, int len) {
            for (int i = 0; i < len; i++) {
                if (S[i + a] != S[i + b])
                    return false;
            }
            return true;
        };

        const int M = 1000000007;
        while (l <= r) {
            int mid = l + ((r - l) >> 1);
            unordered_map<int, vector<int>> mp;
            // calculate hash
            long long h = 1;
            for (int i = 0; i < mid - 1; i++)
                h = (h * 26) % M;

            long long s = 0;
            int j = 0;
            for (j = 0; j < mid - 1; j++) {
                s = (s * 26 + S[j] - 'a') % M;
            }

            bool find = false;
            int find_st = 0;
            for (j = mid - 1; j < n; j++) {
                s = (s * 26 + S[j] - 'a') % M;
                auto& p = mp[s];
                for (size_t k = 0; k < p.size(); k++) {
                    if (check(j - mid + 1, p[k], mid)) {
                        find = true;
                        find_st = j - mid + 1;
                        break;
                    }
                }
                if (find)
                    break;
                p.push_back(j - mid + 1);
                s = ((s - (S[j - mid + 1] - 'a') * h) % M + M) % M;
            }
            if (find) {
                ans = mid;
                ans_st = find_st;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (ans == 0) {
            return "";
        }
        return S.substr(ans_st, ans);
    }
};

int main()
{

    Solution s;
	string str("banana");
	cout << s.longestDupSubstring(str) << endl;

    return 0;
}
