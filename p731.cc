#include "common.h"

class MyCalendarTwo {
    //https://www.cnblogs.com/grandyang/p/7968035.html
    // s2 is used to store the existing joint sets
    // s1 is for whole intervals.
public:
    MyCalendarTwo() {}

    bool book(int start, int end) {

        for (auto &a : s2) {
            // if new interval as overlap with exist joints interval, return false

            if (start >= a.second || end <= a.first) continue;
            return false;
        }
        for (auto &a : s1) {
            // otherwise, search in full sets. get new joint sets and insert into s2
            if (start >= a.second || end <= a.first) continue;
            s2.insert({max(start, a.first), min(end, a.second)});
        }
        s1.insert({start, end});
        return true;
    }

private:
    set<pair<int, int>> s1, s2;
};

//https://www.cnblogs.com/grandyang/p/7968035.html
class MyCalendarTwo2 {
public:
    MyCalendarTwo2() {}

    bool book(int start, int end) {
        ++freq[start];
        --freq[end];
        int cnt = 0;
        for (auto f : freq) {
            cnt += f.second;
            if (cnt == 3) {
                --freq[start];
                ++freq[end];
                return false;
            }
        }
        return true;
    }

private:
    map<int, int> freq;
};

class MyCalendarTwo_my {
public:
	MyCalendarTwo_my() {

	}
    bool book(int start, int end) {
        auto itstart = startevents.lower_bound(start);
        int earlierstarts = distance(startevents.begin(), itstart);
        auto itend = endevents.lower_bound(start);
        int earlierends = distance(endevents.begin(), itend);
        int count = earlierstarts - earlierends;
        startevents.insert(start);
        endevents.insert(end);
        itstart = startevents.lower_bound(start);
        itend = endevents.lower_bound(start);
        bool r = true;
        while ((itend != endevents.end() && *itend < end) ||
               (itstart != startevents.end() && *itstart < end)) {
            if (*itend <= *itstart) {
                count--;
                ++itend;
            } else {
                count++;
                ++itstart;
            }
            if (count > maxevents) {
                r = false;
                break;
            }
            if (itstart == startevents.end()) { // key
                break;
            }
        }
        if (!r) {
            startevents.erase(startevents.find(start));
            endevents.erase(endevents.find(end));
            return false;
        }
        return true;
    }

  private:
    int maxevents = 2;
    multiset<int> startevents;
    multiset<int> endevents;
    /*
    vector < pair<int, int>> events;
    struct MyInterval {
        int start;
        int end;
        MyInterval(int s, int e) :start(s), end(e) {}
        bool operator< (const MyInterval& b) const {
            return end <= b.start;
        }
    };
    multiset<MyInterval> mset;
    */
};

int main() { return 0; }
