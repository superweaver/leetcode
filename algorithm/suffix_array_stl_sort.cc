#include "../common.h"
#include <cstdio>
// http://www.stanford.edu/class/cs97si/suffix-array.pdf
//
#define MAXN 65536
#define MAXLG 17
// 2^17

char A[MAXN];
struct entry {
	// nr[0] is rank 1
	// nr[0] is rank 2
	// p is starting index
	int nr[2], p;
} L[MAXN];
int P[MAXLG][MAXN], N , i, stp, cnt;
int cmp(struct entry& a, struct entry& b) {
	if (a.nr[0] == b.nr[0]) {
		return a.nr[1] < b.nr[1];
	} else {
		return a.nr[0] < b.nr[0];
	}
}
int main() {
	gets(A);
	for (N = strlen(A), i = 0; i < N; ++i) {
		P[0][i] = A[i] - 'a'; // this is rank
	}
	for (stp = 1, cnt = 1; (cnt >> 1) < N; cnt <<= 1) {
		for (i = 0; i < N; ++i) {
			L[i].nr[0] = P[stp-1][i]; // rank 1
			L[i].nr[i] = (i + cnt < N) ? P[stp-1][i + cnt] : -1; // rank 2
			L[i].p = i;
		}
		sort(L, L + N, cmp);
		for (i = 0; i < N; ++i) {
            P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1]
                                 ? P[stp][L[i - 1].p]
                                 : i;
        }
    }
	return 0;
}
