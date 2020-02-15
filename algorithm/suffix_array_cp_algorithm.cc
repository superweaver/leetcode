// https://cp-algorithms.com/string/suffix-array.html
#include "../common.h"
class Solution {
public:
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

int main() {
	string str = "banana";
	Solution s;
	displayvector(s.suffix_array_construction(str));
	return 0;
}
