#include "common.h"

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {

    }

    void addNum(int val) {
       auto it = s.lower_bound(Interval(val, val));
        /*
       while (it != s.begin() && prev(it)->end + 1 >= val) {
           --it;
       }
       */
        if (it != s.begin() && (--it)->end + 1 < val){
            ++it;
            // note: --it is done no matter if (--it)->end + 1 vs val
        }
       Interval temp(val, val);
       while(it != s.end() && hasOverlap(temp, *it)) {
           temp.start = min(temp.start, it->start);
           temp.end = max(temp.end, it->end);
           it = s.erase(it); // note "it" is invalid after erase
       }
       s.insert(it, temp);
    }
    vector<Interval> getIntervals() {
        vector<Interval> r;
        for(auto it = s.begin(); it != s.end(); ++it) {
            r.push_back(*it);
        }
        return r;
    }
private:
    struct Cmp{
        bool operator () (const Interval& a, const Interval&b) const {
            return a.start < b.start;
        }
    };
    set<Interval, Cmp> s;
    inline bool hasOverlap(const Interval& a, const Interval& b) const {
        return !((a.start > b.end + 1) || (b.start > a.end + 1));
    }
};


int main() {


	return 0;
}
