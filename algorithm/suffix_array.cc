/*
 * https://www.hackerearth.com/practice/data-structures/advanced-data-structures/suffix-arrays/tutorial/
 *
Reference 
https://oi.men.ci/suffix-array-notes/
https://baike.baidu.com/item/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84
https://zhuanlan.zhihu.com/p/39876310
https://riteme.site/blog/2016-6-19/sais.html
https://www.youtube.com/watch?v=m2-N853rS6U


for a string S, get its all suffix 
	s[j] means the suffix of S which starts at index of j in S
first of all, group them together
1)
sa = { s[j] }, j = 0, 1, ..., n-1
2)
sort sa, then we have
		sa[i] = j
It means the i_th suffix in sa is the suffix starting at index j in S
A corresponding array is rank
		rank[j] = i;
It means the s[j] suffix starting at index j is the i_th element in sorted sa
3) height array 
height[i] = 0 if i == 0
else height[i] = length(LCP(s[sa[i]], s[sa[i-1]])); 
not it is not LCP(s[i], s[i-1])
LCP means Longest Common Prefix
but LCP(s[sa[i]], s[sa[i-1]])
in sa, find value sa[i] and s[i-1]
then find LCP of two corresponding suffix

define h[i]
s[i] is the suffix starting at index i
rank[i] is the rank for this suffix
rank[i] - 1 is the rank for its previous rank
then s[sa[rank[i]-1]] is the suffix for rank[i] - 1
h[i] is the length of LCP (s[i], s[sa[rank[i]-1]]) = height[rank[i]]

h[i] >= h[i-1] - 1


define k = height[rank[i-1]] = h[i-1]

for (int i = 1, k = 0; i <= n; i++)
{
    if (rk[i] == 1) k = 0;
    else
    {
        if (k > 0) k--;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && a[i + k] == a[j + k]) k++;
    }
    ht[rk[i]] = k;
}




how to get sa, rank and height array?
1) get each suffix, do sort, O(n^2*log(n))
2) Doubling Algorithm
please refer to 
https://baike.baidu.com/item/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84
https://algs4.cs.princeton.edu/63suffix/SuffixArray.java.html
#include "../common.h"
// r is used for store original string s
// n = s.size() < maxn
// r[n-1] = 0, r[i] > 0, i = [0, n-2]
// sa = suffix array
// array x is used for rank (not real rank value)
// m is 2^k, m >= n

const int maxn = 100000 + 1;
int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
 
int cmp(int *r , int a, int b, int l)
{
    return r[a] == r[b] && r[a+l] == r[b+l];
}
void da (int *r , int *sa , int n, int m)
{
    int i, j, p, *x = wa, *y = wb , *t;
	// sort for k = 1
	// using count sort
	// initiate
    for(i = 0; i < m; i++) {
        ws[i] = 0;
	}
	// count and assign value to x
    for(i = 0; i < n; i++) {
        ws[x[i] = r[i]]++;
	}
	// ?
    for(i = 1; i < m; i++)  {
        ws[i] += ws[i-1];
	}
    for(i = n - 1; i >= 0; i--) {
        sa[--ws[x[i]]] = i;
	}

    for(j = 1, p = 1; p < n ; j <<= 1,m = p)
    {
        for(p = 0, i = n - j; i < n; i++) 
            y[p++]=i;
        for(i = 0; i < n; i++)
            if(sa[i] >= j)
                y[p++] = sa[i] - j;
        for(i = 0; i < n; i++)
            wv[i] = x[y[i]];
        for(i = 0; i < m; i++)
            ws[i] = 0;
        for(i = 0; i < n; i++)
            ws[wv[i]]++;
        for(i = 1; i < m; i++)
            ws[i] += ws[i-1];
        for(i = n-1; i >= 0; i--)
            sa[--ws[wv[i]]] = y[i];
        for(t = x,x = y,y = t,p = 1,x[sa[0]] = 0,i = 1; i < n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
*/
// http://www.cbcb.umd.edu/confcour/Fall2012/lec14b.pdf
// http://www.stanford.edu/class/cs97si/suffix-array.pdf
// in http://www.cbcb.umd.edu/confcour/Fall2012/lec14b.pdf
//
//
#include "../common.h"
using namespace std;
//static const int maxNode = 100000 + 3;
static const int maxNode = 1000 + 3;
int n;
char str[maxNode];
void buildSA(int m, vector<int>& sa, vector<int>& rank) {
	vector<int> cnt(maxNode, 0);
	vector<int> tmpSA(maxNode, 0);
	vector<int> rank1(maxNode, 0);
	vector<int> rank2(maxNode, 0);
    //static int cnt[maxNode], tmpSA[maxNode], rank1[maxNode], rank2[maxNode];

    n = strlen(str) + 1; str[n] = 0; //结尾的 $
	// m == 2^k, m >= n
    //fill(cnt, cnt + m, 0);
	// count sort
    for (int i = 0; i < n; ++i) {
        cnt[(int)str[i]]++;
    }
    // i - 1 is a index in original str
	// accumulation sum
    for (int i = 1; i < m; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < n; ++i){
        rank[i] = cnt[(int)str[i]] - 1;
    }

    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; ++i) {
            rank1[i] = rank[i], rank2[i] = i + l < n ? rank1[i + l] : 0;
		}
		
        //fill(cnt, cnt + n, 0);
        fill(cnt.begin(), cnt.begin() + n, 0);
        for (int i = 0; i < n; ++i){
			cnt[rank2[i]]++;
		}
        for (int i = 1; i < n; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            tmpSA[--cnt[rank2[i]]] = i;
        }
        //fill(cnt, cnt + n, 0);
        fill(cnt.begin(), cnt.begin() + n, 0);
        for (int i = 0; i < n; ++i){
			cnt[rank1[i]]++;
		}
        for (int i = 1; i < n; ++i){
			cnt[i] += cnt[i - 1];
		}
        for (int i = n - 1; i >= 0; --i) {
			sa[--cnt[rank1[tmpSA[i]]]] = tmpSA[i];
		}
        bool unique = true;
        rank[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            rank[sa[i]] = rank[sa[i - 1]];
            if (rank1[sa[i]] == rank1[sa[i - 1]] && rank2[sa[i]] == rank2[sa[i - 1]]) unique = false;
            else rank[sa[i]]++;
        }
        if (unique) break;
    }
}
int main() {
	string s = "banana";
	int m = 1;
	while (m < (int)s.size()) {
		m <<= 1;
	}
	vector<int> sa(maxNode, 0);
	vector<int> rank(maxNode, 0);

    strcpy(str, s.c_str());
	buildSA(m, sa, rank);
	displayvector(sa);
	displayvector(rank);
	return 0;
}
