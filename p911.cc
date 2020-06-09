#include "common.h"
class TopVotedCandidate {
  public:
    TopVotedCandidate(vector<int> &persons, vector<int> &times) {
        priority_queue<int> q;         // key = votes for person  << 16 + index
        unordered_map<int, int> count; // person : votes for this person
        time = times;
        int n = persons.size();
        for (int i = 0; i < n; ++i) {
            count[persons[i]]++;
            int key = (count[persons[i]] << 16) + i;
            q.push(key);
            auto top = q.top();
            // In the case of a tie, the most recent vote (among tied candidates) wins.
            result.push_back(persons[top & 0xFFFF]);
        }
    }
    int q(int t) {
        // t >= time [0]
        // find the largest one <= t
        // // lower_bound() using greater<int>
        int low = time.size() - 1;
        int high = -1;
        int count = low - high;
        while (count > 0) {
            int mid = low;
            int step = count / 2;
            mid -= step;
            if (time[mid] > t) { // !!!
                low = --mid;
                count -= step + 1;
            } else {
                count = step;
            }
        }
        return result[low];
    }

  private:
    vector<int> result;
    vector<int> time;
};

int main() {

	Solution s;

	return 0;
}
