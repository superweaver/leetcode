#include "common.h"
class Solution {
    // https://lzl124630x.github.io/2016/12/18/leetcode-466-count-the-repetitions.html
    // https://medium.com/@ChYuan/leetcode-no-467-count-the-repetitions-%E5%BF%83%E5%BE%97-hard-214c77d76cd6
    // https://www.cnblogs.com/grandyang/p/6149293.html
  public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        // there are n1 segments in S1, each is s1
        // nextIndex[k] indicate in kth segments
        // we should look for s2[nextIndex[k]]
        //
        // obviously nextIndex[0] = 0; (s2[0]);
        // note that nextIndex[k]'s range is [0 ... s2.size()-1];
        //
        // then there must be repeation if n1 is >= s2.size() + 1; !!!
        // we can find the interval of repetition;

        vector<int> nextIndex(n1 + 1, 0);        // nextIndex[0] = 0;
        vector<int> rep_s2inS1(n1 + 1, 0);
        // rep_s2inS1[k] = m; then it means there are m repeatition of s2 in the
        // first k segments of S1 (upto the end of first k segments of S1).
        //
        int i = 0; // pointer to s2;
        int cnt = 0;
        for (int k = 1; k <= n1; ++k) { // scan s1 n1 times
            for (size_t j = 0; j < s1.size(); ++j) {
                if (s2[i] == s1[j]) {
                    i++;
                    if (i == s2.size()) { // find one s2
                        i = 0;
                        cnt++;
                    }
                }
            }
            rep_s2inS1[k] = cnt;
            nextIndex[k] = i;

            for (int start = 0; start < k; ++start) {
                if (nextIndex[start] == nextIndex[k]) { // == i
                    // there is repetition
                    // there is a way to save time
                    int interval = k - start;
                    // then from n1 to start, how many times will repetition show up?
                    int repeatedTimes = (n1 - start) / interval;
                    // for each repepition, how many s2 are there?
                    int repeatedCount = repeatedTimes * (rep_s2inS1[k] - rep_s2inS1[start]);
                    // there are remaining counts!
                    int remainingCount = rep_s2inS1[start + (n1 - start) % interval]; // hard here
                    // this is to find rep_s2inS1[n1]
                    rep_s2inS1[n1] = remainingCount + repeatedCount;
                    return rep_s2inS1[n1] / n2;
                }
            }
        }
        // didn't find repetition
        return rep_s2inS1[n1] / n2;
    }
};

int main() {
    string s1 = "acb";
    int n1 = 4;
    string s2 = "ab";
    int n2 = 2;

    Solution s;
    cout << s.getMaxRepetitions(s1, n1, s2, n2) << endl;

    return 0;
}
