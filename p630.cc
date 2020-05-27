#include "common.h"
class Solution {
    // https://www.cnblogs.com/grandyang/p/7126289.html
    // https://zxi.mytechroad.com/blog/greedy/leetcode-630-course-schedule-iii/
    //
    // sort the coures accoding to their ending time
    // initially, current time is 0
    // for any cources c, if currenttime + c.duration <= c.endtime
    // then put it into priority_queue q, where the duration of previous courses were stored.
    //
    // if c.duration < the max of previous duration, swap it with the longest duration and adjust current time
    // return q.size();

  public:
    int scheduleCourse(vector<vector<int>> &courses) {
        sort(courses.begin(), courses.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[1] < b[1]; // sort according to coures' endtime
        });
        priority_queue<int> durations;
        int currenttime = 0;
        for (auto &c : courses) {
            if (currenttime + c[0] <= c[1]) {
                durations.push(c[0]);
                currenttime += c[0];
            } else {
                if (!durations.empty() && c[0] < durations.top()) {
                    // for same duration, the one with ealier end time should be picked
                    // that is why we sort it according to end time
                    currenttime -= durations.top();
                    currenttime += c[0];
                    durations.pop();
                    durations.push(c[0]); // sum of durations is always equal to currenttime
                }
            }
        }
        return durations.size();
    }
};

int main() {

	Solution s;

	return 0;
}
